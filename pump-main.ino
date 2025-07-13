
#include <time.h>
#include <RTClib.h>
#include <EEPROM.h>
#include "button.h"
#include "buzzer.h"
#include "sensor.h"

// =========== Setup ============
#define OUTLETS 14                // A B C D
#define DEFAULT_THROUGHPUT 0.013  // L/second
#define MAX_CONFIG_THROUGHPUT 0.030
#define MIN_CONFIG_THROUGHPUT 0.010
#define MAX_VOLUME 200            // Maximum of liters that can be set in schedule
#define VOLUME_SCALE 0.05         // Multiply by volume
// ==============================

#if OUTLETS > 16
#error "OUTLETS must not be greater than 16"
#endif

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
  uint16_t volume;  // In order to calculate actual volume of water, multiply by VOLUME_SCALE
  uint8_t hour;
  uint8_t minute;
  bool active;
  uint16_t _crc;             // CRC16 checksum
  uint32_t _timestamp_days;  // From 2000-01-01
};

struct Config {
  uint8_t water_check_interval;
  float throughput;
  uint16_t _crc;
};

Config config = { 5, DEFAULT_THROUGHPUT, 0 };  // Default values

#define EEPROM_SIZE 512 
#include "display.h"
#include "core.h"

#define CONFIG_ADDRESS 0x190

#define LEFT_BUTTON_PIN 39
#define RIGHT_BUTTON_PIN 36
#define OK_BUTTON_PIN 34

Button left_button(LEFT_BUTTON_PIN);
Button right_button(RIGHT_BUTTON_PIN);
Button ok_button(OK_BUTTON_PIN);

RTC_DS1307 rtc;
Core core;

ScheduleSet schedule_sets[OUTLETS] = {};

volatile uint32_t check_schedule_timestamp = 0;
volatile bool water_is_done = false;

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

/*
* Returns number of days starting from 2000-01-01 till now.
*/
uint32_t get_days_time(void) {
  return (uint32_t)(rtc.now().secondstime() / 86400);  // 86400 seconds in 24 hours
}


void save_schedule_set(uint8_t outlet, ScheduleSet* data) {
  data->_crc = 0;
  data->_timestamp_days = get_days_time();
  uint16_t crc = crc16((uint8_t*)data, sizeof(ScheduleSet));
  data->_crc = crc;
  uint8_t address = outlet * sizeof(ScheduleSet);
  EEPROM.put(address, *data);
  EEPROM.commit();
}

void save_config() {
  Serial.printf("Save config: WCI: %d\n", config.water_check_interval);
  Sensor.set_check_interval(config.water_check_interval);
  config._crc = 0;
  uint16_t crc = crc16((uint8_t*)&config, sizeof(Config));
  config._crc = crc;
  EEPROM.put(CONFIG_ADDRESS, config);
  EEPROM.commit();
}

void load_config() {
  EEPROM.get(CONFIG_ADDRESS, config);
  uint16_t stored_crc = config._crc;
  config._crc = 0;  // Reset CRC field for calculation
  uint16_t calc_crc = crc16((uint8_t*)&config, sizeof(Config));

  if (stored_crc != calc_crc) {
    Serial.println("Config CRC mismatch. Reinit");
    config.water_check_interval = 5;
    config.throughput = DEFAULT_THROUGHPUT;
    save_config();
    return;
  }
  Serial.printf("Load config: WCI: %d\n", config.water_check_interval);
  config._crc = stored_crc;  // Restore CRC field
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
    save_schedule_set(outlet, &def);
    return def;
  }

  data._crc = stored_crc;  // Restore CRC field
  return data;
}

void save_schedule(uint8_t outlet) {
  ScheduleSet* schedule = &schedule_sets[outlet];
  save_schedule_set(outlet, schedule);
  Serial.printf("Saved Schedule> O: %d; A: %d; D: %d; H: %d, M: %d; V: %d; T: %d\n", outlet,
                schedule->active,
                schedule->days,
                schedule->hour,
                schedule->minute,
                schedule->volume,
                schedule->_timestamp_days);
}

void setup() {
  Serial.begin(9600);
  EEPROM.begin(EEPROM_SIZE);
  Serial.println("Start");

  Display.init();
  left_button.init();
  right_button.init();
  ok_button.init();
  Buzzer.init();
  Sensor.init();
  core.init();

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

  Display.get_current_datetime = get_current_datetime;
  Display.apply_datetime = apply_datetime;

  load_config();
  Sensor.set_check_interval(config.water_check_interval);

  for (uint8_t i = 0; i < OUTLETS; i++) {
    schedule_sets[i] = get_schedule_set(i);
    Serial.printf("Loaded Schedule> O: %d; A: %d; D: %d; H: %d, M: %d; V: %d; T: %d\n", i,
                  schedule_sets[i].active,
                  schedule_sets[i].days,
                  schedule_sets[i].hour,
                  schedule_sets[i].minute,
                  schedule_sets[i].volume,
                  schedule_sets[i]._timestamp_days);
  }

  Display.schedule_sets = schedule_sets;
  Display.save_schedule = save_schedule;
  Display.config = &config;
  Display.save_config = save_config;

  core.config = &config;

  Display.showSplash();
}

void loop() {
  if (millis() - check_schedule_timestamp >= 1000) {
    DateTime now = rtc.now();
    uint32_t days_time = get_days_time();
    for (uint8_t outlet = 0; outlet < OUTLETS; outlet++) {
      ScheduleSet* schedule = &schedule_sets[outlet];
      if (!schedule->active)
        continue;

      uint32_t days_diff = (days_time > schedule->_timestamp_days)
                             ? (days_time - schedule->_timestamp_days)
                             : (schedule->_timestamp_days - days_time);

      // If days_diff == 0 we skip it because at that day the schedule was set
      if (/*days_diff != 0 &&*/ (schedule->days > 0) && (days_diff % schedule->days == 0)) {
        if (schedule->hour == now.hour() && schedule->minute == now.minute()) {
          // The function is being called many times, but under the hood, it handled one time.
          // After 60 sec the same outlet called be called
          core.add(outlet, schedule->volume);
        }
      }
    }

    check_schedule_timestamp = millis();
  }


  ButtonState os = ok_button.get_state();
  if (os == CLICK) {
    if (water_is_done) {
      Display.show_no_water(false);
      core.resume();
      Buzzer.reset();
      water_is_done = false;
    } else {
      Buzzer.beep();
      Display.click();
    }
  }

  if (Display.trigger_run) {
    if (ok_button.hold()) {
      Sensor.start_measuring();
      core.start_pumping(Display.selected_outlet);
      Display.print_throughput();
    } else {
      Sensor.stop_measuring();
      core.stop_pumping();
      Display.stop_measuring_throughput();
    }
  } else {
    if (os == LONG_PRESS) {
      Display.long_click();
      Buzzer.long_beep();
    }
  }

  if (right_button.get_state() == CLICK) {
    Buzzer.beep();
    Display.right();
  }

  if (left_button.get_state() == CLICK) {
    Buzzer.beep();
    Display.left();
  }

  Display.no_water = Sensor.no_water();

  if (core.is_pumping()) {
    Sensor.start_measuring();
    if (Sensor.no_water()) {
      Display.show_no_water(true);
      core.suspend();
      Buzzer.beeping();
      water_is_done = true;
    }
  } else {
    if (!Display.trigger_run)
      Sensor.stop_measuring();
  }

  if (core.is_processing()) {
    Display.disable();
  } else {
    Display.enable();
  }

  Display.tick();
  right_button.tick();
  left_button.tick();
  ok_button.tick();
  Buzzer.tick();
  Sensor.tick();
  core.tick();
}
