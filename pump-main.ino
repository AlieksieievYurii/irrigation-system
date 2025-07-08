
#include <time.h>
#include <RTClib.h>
#include <EEPROM.h>
#include "button.h"
#include "buzzer.h"
#include "sensor.h"

struct DateTimeInfo {
  uint16_t year;
  uint8_t month;
  uint8_t day;
  uint8_t hour;
  uint8_t minute;
  uint8_t second;
};

struct ScheduleSet {
  uint16_t days;
  uint16_t volume;
  uint8_t hour;
  uint8_t minute;
  bool active;
  uint16_t _crc;             // CRC16 checksum
  uint32_t _timestamp_days;  // From 2000-01-01
};

#define OUTLETS 4  // A B C D
#define THROUGHPUT 0.017

#define EEPROM_SIZE 512  // Reserve space (adjust as needed)
#include "display.h"
#include "outlet.h"

#define LEFT_BUTTON_PIN 39
#define RIGHT_BUTTON_PIN 36
#define OK_BUTTON_PIN 34

#define DIRECTION_CW 0   // clockwise direction
#define DIRECTION_CCW 1  // counter-clockwise direction

#define BUZZER 12

#define WATER_S 35

Button left_button(LEFT_BUTTON_PIN);
Button right_button(RIGHT_BUTTON_PIN);
Button ok_button(OK_BUTTON_PIN);

Buzzer buzzer(BUZZER);

Sensor sensor(WATER_S);

Outlets outlets;

ScheduleSet shechule_sets[OUTLETS] = {};

volatile int counter = 0;
volatile int direction = DIRECTION_CW;
volatile unsigned long last_time;  // for debouncing
int prev_counter;
volatile uint8_t pressed = 0;
uint32_t exppp = 0;
RTC_DS1307 rtc;
struct tm timeinfo;

bool b = false;

char daysOfTheWeek[7][12] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };

DateTimeInfo get_current_datetime() {
  DateTime now = rtc.now();
  DateTimeInfo datetime_now = {
    now.year(),
    now.month(),
    now.day(),
    now.hour(),
    now.minute(),
    now.second()
  };
  return datetime_now;
}

uint16_t crc16(const uint8_t* data, size_t len) {
  uint16_t crc = 0xFFFF;
  for (size_t i = 0; i < len; i++) {
    crc ^= data[i];
    for (uint8_t j = 0; j < 8; j++) {
      if (crc & 1) crc = (crc >> 1) ^ 0xA001;
      else crc >>= 1;
    }
  }
  return crc;
}

void apply_datetime(DateTimeInfo datetime) {
  rtc.adjust(DateTime(datetime.year, datetime.month, datetime.day, datetime.hour, datetime.minute, 0));
}

void save_schedule_set(uint8_t outlet, ScheduleSet& data) {
  data._crc = 0;
  data._timestamp_days = (uint32_t)(rtc.now().secondstime() / 86400);
  uint16_t crc = crc16((uint8_t*)&data, sizeof(ScheduleSet));
  data._crc = crc;
  uint8_t address = outlet * sizeof(ScheduleSet);
  EEPROM.put(address, data);
  EEPROM.commit();
}

ScheduleSet get_schedule_set(uint8_t outlet) {
  ScheduleSet data;
  uint8_t address = outlet * sizeof(ScheduleSet);
  EEPROM.get(address, data);

  uint16_t stored_crc = data._crc;
  data._crc = 0;  // Reset CRC field for calculation
  uint16_t calc_crc = crc16((uint8_t*)&data, sizeof(ScheduleSet));

  if (stored_crc != calc_crc) {
    Serial.printf("O: %d CRC mismatch. Reinit", outlet);
    ScheduleSet def = { 7, 100, 12, 0, false, 0 };
    save_schedule_set(outlet, def);
    return def;
  }

  data._crc = stored_crc;  // Restore CRC field
  return data;
}

void save_schedule(uint8_t outlet) {
  //Serial.println(rtc.now().secondstime() / 86400);
  save_schedule_set(outlet, shechule_sets[outlet]);
  Serial.println();
}

void setup() {
  Serial.begin(9600);
  EEPROM.begin(EEPROM_SIZE);
  Serial.println("Start");
  Display.init();
  left_button.init();
  right_button.init();
  ok_button.init();
  buzzer.init();
  outlets.init();
  sensor.init();

  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    while (1) delay(10);
  }

  if (!rtc.isrunning()) {
    Serial.println("RTC is NOT running");
    Display.replace_battery_message = true;
    rtc.adjust(DateTime(2025, 1, 1, 12, 0, 0));
  }

  pinMode(WATER_S, INPUT_PULLDOWN);


  Display.get_current_datetime = get_current_datetime;
  Display.apply_datetime = apply_datetime;

  // ScheduleSet a = { 7, 999, 12, 44, true, 0 };
  // save_schedule_set(0, a);

  for (uint8_t i = 0; i < OUTLETS; i++) {
    shechule_sets[i] = get_schedule_set(i);
    Serial.printf("O: %d; A: %d; D: %d; H: %d, M: %d; V: %d; T: %d\n", i,
                  shechule_sets[i].active,
                  shechule_sets[i].days,
                  shechule_sets[i].hour,
                  shechule_sets[i].minute,
                  shechule_sets[i].volume,
                  shechule_sets[i]._timestamp_days);
  }

  Display.schedule_sets = shechule_sets;
  Display.save_schedule = save_schedule;

  Display.showSplash();
  // ScheduleSet loaded = get_schedule_set(0);
  // Serial.print("Active: ");
  // Serial.println(loaded.active);
  // Serial.print("Days: ");
  // Serial.println(loaded.days);
  // Serial.print("Hour: ");
  // Serial.println(loaded.hour);
  // Serial.print("Minute: ");
  // Serial.println(loaded.minute);
  // Serial.print("Volume: ");
  // Serial.println(loaded.volume);
}


void loop() {
  ButtonState os = ok_button.get_state();
  if (os == CLICK) {
    //Serial.println("OK CLICK");
    buzzer.beep();
    Display.click();
  }

  if (Display.trigger_run) {
    if (ok_button.hold()) {
      buzzer.beep();
      outlets.start(Display.selected_outlet);
      Display.print_thoughtput();
    } else {
      outlets.stop();
      Display.stop_measuring_throughput();
    }
  } else {
    if (os == LONG_PRESS) {
      //Serial.println("OK LONG_PRESS");
      Display.long_click();
      buzzer.long_beep();
    }
  }

  ButtonState rs = right_button.get_state();
  if (rs == CLICK) {
    //Serial.println("RIGHT CLICK");
    buzzer.beep();
    Display.right();
  }
  if (rs == LONG_PRESS) {
    //S//erial.println("RIGHT LONG_PRESS");
  }

  ButtonState ls = left_button.get_state();
  if (ls == CLICK) {
    //Serial.println("LEFT CLICK");
    buzzer.beep();
    Display.left();
  }
  if (ls == LONG_PRESS) {
    Serial.println("LEFT LONG_PRESS");
  }

  Display.no_water = sensor.no_water();

  Display.run();
  right_button.tick();
  left_button.tick();
  ok_button.tick();
  buzzer.tick();
  sensor.tick();
}
