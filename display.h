#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define DISPLAY_ADDRESS 0x3C

#define OLED_RESET -1

#define NO_SCREEN_SELECTED 0x0
#define SCREEN_SCHEDULE 0x1
#define SCREEN_SET_TIME 0x2
#define SCREEN_TRIGGER 0x3

// Schedule Update Status
#define SCHEDULE_IS_SAVED_NO_HINT 0x0
#define SCHEDULE_UNSAVED 0x1
#define SCHEDULE_SAVED 0x2
//--------------------------

// Schedule Cursor ID
#define SCHEDULE_CURSOR_SET_STATE 0x0
#define SCHEDULE_CURSOR_SET_DAYS 0x1
#define SCHEDULE_CURSOR_SET_HOUR 0x2
#define SCHEDULE_CURSOR_SET_MINUTE 0x3
#define SCHEDULE_CURSOR_SET_VOLUME 0x4

const unsigned char icon_lock[] PROGMEM = {
  0x00, 0x07, 0xe0, 0x00, 0x00, 0x0f, 0xf0, 0x00, 0x00, 0x1f, 0xf8, 0x00, 0x00, 0x3f, 0xfc, 0x00,
  0x00, 0x7f, 0xfe, 0x00, 0x00, 0x7c, 0x3e, 0x00, 0x00, 0x78, 0x1e, 0x00, 0x00, 0x78, 0x1e, 0x00,
  0x00, 0x78, 0x1e, 0x00, 0x03, 0xff, 0xff, 0xc0, 0x07, 0xff, 0xff, 0xe0, 0x0f, 0xff, 0xff, 0xf0,
  0x0f, 0xff, 0xff, 0xf0, 0x0f, 0xff, 0xff, 0xf0, 0x0f, 0x00, 0x00, 0xf0, 0x0f, 0x00, 0x00, 0xf0,
  0x0f, 0x00, 0x00, 0xf0, 0x0f, 0x03, 0xc0, 0xf0, 0x0f, 0x07, 0xe0, 0xf0, 0x0f, 0x07, 0xe0, 0xf0,
  0x0f, 0x07, 0xe0, 0xf0, 0x0f, 0x07, 0xe0, 0xf0, 0x0f, 0x03, 0xc0, 0xf0, 0x0f, 0x00, 0x00, 0xf0,
  0x0f, 0x00, 0x00, 0xf0, 0x0f, 0x00, 0x00, 0xf0, 0x0f, 0xff, 0xff, 0xf0, 0x0f, 0xff, 0xff, 0xf0,
  0x0f, 0xff, 0xff, 0xf0, 0x07, 0xff, 0xff, 0xe0, 0x03, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x00
};

const unsigned char icon_schedule[] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x07, 0x00, 0x00, 0xe0, 0x07, 0x00,
  0x0f, 0xff, 0xff, 0xf0, 0x1f, 0xff, 0xff, 0xf8, 0x1f, 0xff, 0xff, 0xf8, 0x1e, 0x00, 0x00, 0x78,
  0x1e, 0x00, 0x00, 0x78, 0x1e, 0x00, 0x00, 0x78, 0x1e, 0x00, 0x00, 0x78, 0x1f, 0xff, 0xff, 0xf8,
  0x1f, 0xff, 0xff, 0xf8, 0x1e, 0x00, 0x00, 0x78, 0x1e, 0x00, 0x00, 0x78, 0x1e, 0x31, 0x8c, 0x78,
  0x1e, 0x7b, 0xde, 0x78, 0x1e, 0x7b, 0xde, 0x78, 0x1e, 0x73, 0xce, 0x78, 0x1e, 0x00, 0x00, 0x78,
  0x1e, 0x00, 0x00, 0x78, 0x1e, 0x73, 0xce, 0x78, 0x1e, 0x7b, 0xde, 0x78, 0x1e, 0x7b, 0xde, 0x78,
  0x1e, 0x31, 0x8c, 0x78, 0x1e, 0x00, 0x00, 0x78, 0x1e, 0x00, 0x00, 0x78, 0x1f, 0xff, 0xff, 0xf8,
  0x1f, 0xff, 0xff, 0xf8, 0x0f, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

const unsigned char icon_time[] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0xc0, 0x07, 0x00, 0x00, 0xe0, 0x0f, 0x80, 0x01, 0xf0,
  0x1f, 0x9f, 0xf1, 0xf8, 0x3f, 0x7f, 0xfe, 0xfc, 0x7e, 0xff, 0xff, 0x7e, 0xfd, 0xff, 0xff, 0xbf,
  0xfb, 0xfe, 0x7f, 0xdf, 0x77, 0xf0, 0x0f, 0xee, 0x0f, 0xc3, 0xc3, 0xf0, 0x0f, 0x83, 0xc1, 0xf0,
  0x1f, 0x83, 0xc1, 0xf8, 0x1f, 0x03, 0xc0, 0xf8, 0x1e, 0x03, 0xc0, 0x78, 0x1e, 0x03, 0xc0, 0x78,
  0x1e, 0x03, 0xc0, 0x78, 0x1e, 0x03, 0xe0, 0x78, 0x1e, 0x03, 0xf0, 0x78, 0x1e, 0x01, 0xf8, 0xf8,
  0x1f, 0x00, 0xfc, 0xf8, 0x1f, 0x00, 0x7c, 0xf8, 0x1f, 0x80, 0x39, 0xf0, 0x0f, 0xc0, 0x03, 0xf0,
  0x0f, 0xe0, 0x07, 0xe0, 0x07, 0xf8, 0x1f, 0xe0, 0x03, 0xff, 0xff, 0xc0, 0x01, 0xff, 0xff, 0x80,
  0x00, 0xff, 0xff, 0x00, 0x00, 0x3f, 0xfc, 0x00, 0x00, 0x07, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00
};

const unsigned char icon_trigger[] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0x00, 0x00, 0x01, 0xff, 0x00, 0x00, 0x03, 0xff, 0x80, 0x00,
  0x03, 0xc7, 0x80, 0x00, 0x07, 0x93, 0xc0, 0x00, 0x07, 0x3b, 0xc0, 0x00, 0x07, 0x39, 0xc0, 0x00,
  0x07, 0xbb, 0xc0, 0x00, 0x03, 0x39, 0x80, 0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00,
  0x00, 0x38, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 0x39, 0xff, 0x80, 0x00, 0x39, 0xff, 0xc0,
  0x00, 0x39, 0xff, 0xe0, 0x0f, 0xb8, 0x01, 0xe0, 0x1f, 0xf8, 0x00, 0xe0, 0x0f, 0xf8, 0x00, 0xe0,
  0x0f, 0xf8, 0x00, 0xe0, 0x07, 0xf8, 0x00, 0xe0, 0x03, 0xd8, 0x00, 0xe0, 0x01, 0xe0, 0x00, 0xe0,
  0x00, 0xf0, 0x00, 0xe0, 0x00, 0xf8, 0x00, 0xe0, 0x00, 0x7c, 0x01, 0xe0, 0x00, 0x3f, 0xff, 0xe0,
  0x00, 0x1f, 0xff, 0xc0, 0x00, 0x0f, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};



class Display {
public:
  typedef DateTimeInfo (*Callback)();
  typedef void (*ApplyDateTimeCallback)(DateTimeInfo);
  typedef void (*SaveSchedule)(uint8_t);
  ScheduleSet* schedule_sets = nullptr;

  Callback get_current_datetime = nullptr;
  ApplyDateTimeCallback apply_datetime = nullptr;
  SaveSchedule save_schedule = nullptr;
  bool replace_battery_message = false;
  bool trigger_run = false;
  uint8_t selected_outlet = 0;

  bool no_water = false;

  void init() {
    _display = Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
    if (!_display.begin(SSD1306_SWITCHCAPVCC, DISPLAY_ADDRESS)) {
      Serial.println(F("SSD1306 allocation failed"));
      while (1) {};
    }
    _display.clearDisplay();
    _last_active_time = millis();
  }

  void showSplash() {
    _display.setTextSize(1.5);
    _display.setTextColor(SSD1306_WHITE);
    _display.setCursor(40, 28);
    _display.println(F("Loading..."));
    _display.display();
    delay(1000);
    invalidate();
  }
  uint32_t _throughput_timestamp = 0;
  uint32_t _time = 0;
  uint32_t l = 0;
  uint32_t buff = 0;
  float _throughput = 0;

  void print_thoughtput(void) {
    if (_throughput_timestamp == 0)
      _throughput_timestamp = millis();
    else {
      _time = millis() - _throughput_timestamp;

      if (_time < 500)  // Ignore until the motor starts working
        return;
      _time = _time + buff - 500;

      if (millis() - l >= 900) {
        _throughput = (_time / 1000) * THROUGHPUT;
        invalidate();
        l = millis();
      }
    }
  }

  void stop_measuring_throughput() {
    _throughput_timestamp = 0;
    buff = _time;
  }

  void reset_measuring_throughput() {
    buff = 0;
    _time = 0;
    _throughput = 0;
    _throughput_timestamp = 0;
    l = 0;
  }

  void left() {
    if (_last_active_time == 0 || _screen_locked) {  // If the display is in speeping mode, just activate
      invalidate();
      return;
    }

    if (_screen == NO_SCREEN_SELECTED) {
      if (_screen_select_cursor > 0)
        _screen_select_cursor--;
    } else if (_screen == SCREEN_SET_TIME) {
      if (_edit_datetime_value) {
        _update_datetime_config(true);
      } else if (_config_time_select > 1) {  // year, month, day, hour, minute
        _config_time_select--;
      }
    } else if (_screen == SCREEN_TRIGGER) {
      reset_measuring_throughput();
      if (selected_outlet > 0)
        selected_outlet--;
    } else if (_screen == SCREEN_SCHEDULE) {
      if (_edit) {
        _update_schedule_value(true);
      } else if (_active_schedule_set_cursor) {
        if (_schedule_set_cursor > 0) {
          _schedule_set_cursor--;
        } else {
          _schedule_set_cursor = 4;
        }
      } else if (_schedule_set > 0) {
        _schedule_change_status = SCHEDULE_IS_SAVED_NO_HINT;
        _schedule_set--;
      }
    }

    invalidate();
  }

  void right() {
    if (_last_active_time == 0 || _screen_locked) {  // If the display is in speeping mode, just activate
      invalidate();
      return;
    }

    if (_screen == NO_SCREEN_SELECTED) {
      if (_screen_select_cursor < 2)
        _screen_select_cursor++;
    } else if (_screen == SCREEN_SET_TIME) {
      if (_edit_datetime_value) {
        _update_datetime_config(false);
      } else if (_config_time_select < 5) {  // year, month, day, hour, minute
        _config_time_select++;
      }
    } else if (_screen == SCREEN_TRIGGER) {
      reset_measuring_throughput();
      if (selected_outlet < OUTLETS - 1)
        selected_outlet++;
    } else if (_screen == SCREEN_SCHEDULE) {
      if (_edit) {
        _update_schedule_value(false);
      } else if (_active_schedule_set_cursor) {
        if (_schedule_set_cursor < 4) {
          _schedule_set_cursor++;
        } else {
          _schedule_set_cursor = 0;
        }
      } else if (_schedule_set < OUTLETS - 1) {
        _schedule_change_status = SCHEDULE_IS_SAVED_NO_HINT;
        _schedule_set++;
      }
    }

    invalidate();
  }

  void click() {
    if (_last_active_time == 0 || _screen_locked) {  // If the display is in speeping mode, just activate
      invalidate();
      return;
    }
    if (_screen == NO_SCREEN_SELECTED) {
      _screen = _screen_select_cursor + 1;  // Curson starts with 0 but screen id starts from 1
    } else if (_screen == SCREEN_SET_TIME) {
      _edit_datetime_value = !_edit_datetime_value;
    } else if (_screen == SCREEN_TRIGGER) {
      _screen = NO_SCREEN_SELECTED;
      selected_outlet = 0;
    } else if (_screen == SCREEN_SCHEDULE) {
      if (!_active_schedule_set_cursor) {
        _active_schedule_set_cursor = true;
        _edit = false;
      } else if (_active_schedule_set_cursor && !_edit) {
        _edit = true;
      } else if (_active_schedule_set_cursor && _edit) {
        _edit = false;
      }
      _active_schedule_set_cursor = true;
    }

    invalidate();
  }

  void long_click() {
    if (_last_active_time == 0 || _sleep_mode) {  // If the display is in speeping mode, just activate
      invalidate();
      return;
    }

    if (_screen_locked) {
      _screen_locked = false;
    } else if (_screen == SCREEN_SET_TIME) {
      apply_datetime(_datetime);
      replace_battery_message = false;
      _config_time_select = 0;
      _screen = NO_SCREEN_SELECTED;
    } else if (_screen == SCREEN_SCHEDULE) {
      if (_active_schedule_set_cursor && _edit) {
        _edit = false;
        _schedule_change_status = SCHEDULE_UNSAVED;
      } else if (_active_schedule_set_cursor) {
        _save_schedule();
        _active_schedule_set_cursor = false;
      } else {
        _screen = NO_SCREEN_SELECTED;
        _schedule_change_status = SCHEDULE_IS_SAVED_NO_HINT;
      }
    }

    invalidate();
  }

  void run(void) {
    if (!_sleep_mode && _last_active_time != 0 && millis() - _last_active_time >= 10000) {
      _display.ssd1306_command(SSD1306_DISPLAYOFF);
      _last_active_time = 0;
      _sleep_mode = true;
      _screen_locked = true;
      return;
    }
    trigger_run = !_screen_locked && _screen == SCREEN_TRIGGER;

    if (_invalidate) {
      if (_sleep_mode) {
        _display.ssd1306_command(SSD1306_DISPLAYON);
        _sleep_mode = false;
      }
      _draw();
      _invalidate = false;
    }
  }

private:
  Adafruit_SSD1306 _display;
  bool _screen_locked = true;
  bool _sleep_mode = false;
  bool _invalidate = false;
  uint32_t _last_active_time = 0;

  uint8_t _screen = NO_SCREEN_SELECTED;
  uint8_t _screen_select_cursor = 0;

  DateTimeInfo _datetime;
  uint8_t _config_time_select = 0;
  bool _edit_datetime_value = false;

  bool _active_schedule_set_cursor = false;
  uint8_t _schedule_set_cursor = 0;
  uint8_t _schedule_set = 0;
  bool _edit = false;
  uint8_t _schedule_change_status = SCHEDULE_IS_SAVED_NO_HINT;

  bool active = true;
  void _draw() {
    _display.clearDisplay();
    if (_screen_locked) {
      _draw_time_in_bar();
      _draw_locked_screen();
    } else if (_screen == NO_SCREEN_SELECTED) {
      _draw_time_in_bar();
      _draw_menu();
    } else if (_screen == SCREEN_SCHEDULE) {
      _draw_screen_schedule();
    } else if (_screen == SCREEN_SET_TIME) {
      _draw_time_config();
    } else if (_screen == SCREEN_TRIGGER) {
      _draw_trigger();
    }
    _display.display();
  }

  void _draw_menu() {
    _display.setTextSize(1);
    _display.setTextColor(SSD1306_WHITE);

    if (_screen_select_cursor == 0) {
      _display.drawBitmap(48, 17, icon_schedule, 32, 32, WHITE);
      _display.setCursor(40, 52);
      _display.println(F("Schedule"));
    } else if (_screen_select_cursor == 1) {
      _display.drawBitmap(48, 17, icon_time, 32, 32, WHITE);
      _display.setCursor(40, 52);
      _display.println(F("Set time"));
    } else if (_screen_select_cursor == 2) {
      _display.drawBitmap(48, 17, icon_trigger, 32, 32, WHITE);
      _display.setCursor(43, 52);
      _display.println(F("Trigger"));
    }

    if (_screen_select_cursor > 0) {
      _display.fillTriangle(2, 32, 12, 22, 12, 42, WHITE);
    }

    if (_screen_select_cursor < 2) {
      _display.fillTriangle(126, 32, 116, 22, 116, 42, WHITE);
    }
  }

  void _draw_screen_schedule(void) {
    ScheduleSet* schedule = &schedule_sets[_schedule_set];
    _display.setTextSize(1);
    _display.setTextColor(SSD1306_WHITE);
    _display.setCursor(0, 0);
    _display.println(F("< Schedule"));

    if (_schedule_change_status == SCHEDULE_UNSAVED) {
      _display.setCursor(66, 0);
      _display.println(F("| UNSAVED"));
    } else if (_schedule_change_status == SCHEDULE_SAVED) {
      _display.setCursor(66, 0);
      _display.println(F("| SAVED"));
    }

    _display.setTextSize(3);
    _display.setCursor(93, 16);
    char character = (char)65 + _schedule_set;
    _display.print(character);

    _display.setTextSize(1);
    _display.setCursor(15, 18);
    _display.println(F("Status:"));

    if (schedule->active) {
      _display.setCursor(69, 18);
      _display.println(F("ON"));
    } else {
      _display.setCursor(63, 18);
      _display.println(F("OFF"));
    }

    _display.setCursor(15, 29);
    _display.println(F("Days:"));
    uint8_t days_length = _get_uint_length(schedule->days);
    _display.setCursor(87 - 6 - (6 * days_length), 29);
    _display.println(schedule->days);

    _display.setCursor(15, 40);
    _display.println(F("Time:    "));
    _display.setCursor(schedule->hour > 9 ? 57 : 63, 40);
    _display.println(schedule->hour);
    _display.setCursor(75, 40);
    _display.println(schedule->minute);
    _display.setCursor(69, 40);
    _display.println(":");

    _display.setCursor(15, 51);
    _display.println(F("Volume:       "));
    _display.setCursor(57, 51);
    float v = schedule->volume * 0.05;
    _display.print(v, 2);

    _display.setCursor(schedule->volume >= 200 ? 89 : 83, 51);
    _display.println("L");

    if (_schedule_set > 0) {
      _display.fillTriangle(0, 32, 10, 22, 10, 42, WHITE);
    }

    if (_schedule_set < OUTLETS - 1) {
      _display.fillTriangle(127, 32, 117, 22, 117, 42, WHITE);
    }

    if (!_active_schedule_set_cursor)
      return;

    uint8_t x, y, w;

    if (_schedule_set_cursor == SCHEDULE_CURSOR_SET_STATE) {
      y = 16;
      if (schedule->active) {
        x = 67;
        w = 15;
      } else {
        x = 61;
        w = 21;
      }
    } else if (_schedule_set_cursor == SCHEDULE_CURSOR_SET_DAYS) {  // Days
      x = 79 - (6 * days_length);
      y = 27;
      w = (6 * days_length) + 3;
    } else if (_schedule_set_cursor == SCHEDULE_CURSOR_SET_HOUR) {  // Hour
      x = schedule->hour > 9 ? 55 : 61;
      y = 38;
      w = schedule->hour > 9 ? 15 : 9;
    } else if (_schedule_set_cursor == SCHEDULE_CURSOR_SET_MINUTE) {  // Minute
      x = 73;
      y = 38;
      w = schedule->minute > 9 ? 15 : 9;
    } else if (_schedule_set_cursor == SCHEDULE_CURSOR_SET_VOLUME) {  // Volume
      x = 55;
      y = 49;
      w = schedule->volume >= 200 ? 33 : 27;
    }

    if (_edit)
      _display.fillRect(x, y, w, 11, SSD1306_INVERSE);
    else
      _display.drawRect(x, y, w, 11, SSD1306_INVERSE);
  }

  void _save_schedule(void) {
    if (_schedule_change_status == SCHEDULE_UNSAVED) {
      save_schedule(selected_outlet);
    }
    _schedule_change_status = SCHEDULE_SAVED;
    _schedule_set_cursor = 0;
  }

  void _update_schedule_value(bool decrease) {
    _schedule_change_status = SCHEDULE_UNSAVED;
    ScheduleSet* schedule = &schedule_sets[_schedule_set];
    if (_schedule_set_cursor == 0) {  // Enable/Disable
      schedule->active = !schedule->active;
    } else if (_schedule_set_cursor == 1) {  // Days
      uint16_t new_days = schedule->days;
      if (decrease) {
        if (new_days > 1) new_days--;
        else new_days = 999;
      } else {
        if (new_days < 999) new_days++;
        else new_days = 1;
      }
      schedule->days = new_days;
    } else if (_schedule_set_cursor == 2) {  // Hour
      uint8_t new_hour = schedule->hour;
      if (decrease) {
        if (new_hour > 0)
          new_hour--;
        else new_hour = 23;
      } else {
        if (new_hour < 23)
          new_hour++;
        else new_hour = 0;
      }
      schedule->hour = new_hour;
    } else if (_schedule_set_cursor == 3) {  // Minute
      uint8_t new_minute = schedule->minute;
      if (decrease) {
        if (new_minute > 0)
          new_minute--;
        else new_minute = 59;
      } else {
        if (new_minute < 59)
          new_minute++;
        else new_minute = 0;
      }
      schedule->minute = new_minute;
    } else if (_schedule_set_cursor == 4) {  // Volume
      uint8_t new_volume = schedule->volume;
      if (decrease) {
        if (new_volume > 0)
          new_volume--;
        else new_volume = 200;
      } else {
        if (new_volume < 200)
          new_volume++;
        else new_volume = 0;
      }
      schedule->volume = new_volume;
    }
  }

  void _update_datetime_config(bool decrease) {
    if (decrease) {
      if (_config_time_select == 1 && _datetime.year > 2025) {  // Select year for Config Time Fragment
        _datetime.year--;
      } else if (_config_time_select == 2 && _datetime.month > 1) {  // Select month for Config Time Fragment
        _datetime.month--;
      } else if (_config_time_select == 3 && _datetime.day > 1) {  // Select day for Config Time Fragment
        _datetime.day--;
      } else if (_config_time_select == 4 && _datetime.hour > 0) {  // Select day for Config Time Fragment
        _datetime.hour--;
      } else if (_config_time_select == 5 && _datetime.minute > 0) {  // Select day for Config Time Fragment
        _datetime.minute--;
      }
    } else {
      if (_config_time_select == 1 && _datetime.year <= 2099) {  // Select year for Config Time Fragment
        _datetime.year++;
      } else if (_config_time_select == 2 && _datetime.month < 12) {  // Select month for Config Time Fragment
        _datetime.month++;
      } else if (_config_time_select == 3 && _datetime.day < get_max_days()) {  // Select month for Config Time Fragment
        _datetime.day++;
      } else if (_config_time_select == 4 && _datetime.hour < 23) {
        _datetime.hour++;
      } else if (_config_time_select == 5 && _datetime.minute < 59) {
        _datetime.minute++;
      }
    }
  }

  void _draw_trigger(void) {
    _display.setTextSize(1);
    _display.setTextColor(SSD1306_WHITE);
    _display.setCursor(0, 0);
    _display.println(F("< Trigger"));

    if (no_water) {
      _display.setCursor(60, 0);
      _display.println(F("| No water"));
    }

    _display.setTextSize(2);
    _display.setCursor(19, 17);
    char character = (char)65 + selected_outlet;
    _display.print(character);

    _display.drawLine(35, 16, 35, 40, WHITE);

    _display.setTextSize(1);
    _display.setCursor(40, 18);
    _display.println(F("Vol: "));
    _display.setCursor(76, 18);
    _display.println(_throughput, 2);

    _display.setCursor(40, 30);
    _display.println(F("Time: "));
    _display.setCursor(76, 30);
    _display.println((int)(_time / 1000));
    _display.setCursor(25, 45);
    _display.println(F("Hold O to run"));
    _display.setCursor(19, 56);
    _display.println(F("Click O to exit"));

    if (selected_outlet > 0) {
      _display.fillTriangle(2, 32, 12, 22, 12, 42, WHITE);
    }

    if (selected_outlet < OUTLETS - 1) {
      _display.fillTriangle(126, 32, 116, 22, 116, 42, WHITE);
    }
  }

  void _draw_time_config() {
    _display.setTextSize(1);
    _display.setTextColor(SSD1306_WHITE);
    _display.setCursor(0, 0);
    _display.println(F("< Set time"));
    _display.setCursor(10, _display.height() / 2);

    if (_config_time_select == 0) {  // Mode: Init
      _datetime = get_current_datetime();
      _config_time_select = 1;  // Mode: Select field e.g year, month
    }

    String yearStr = String(_datetime.year, DEC);
    String monthStr = (_datetime.month < 10 ? "0" : "") + String(_datetime.month, DEC);
    String dayStr = (_datetime.day < 10 ? "0" : "") + String(_datetime.day, DEC);
    String hourStr = (_datetime.hour < 10 ? "0" : "") + String(_datetime.hour, DEC);
    String minuteStr = (_datetime.minute < 10 ? "0" : "") + String(_datetime.minute, DEC);
    String secondStr = (_datetime.second < 10 ? "0" : "") + String(_datetime.second, DEC);
    String formattedTime = yearStr + "." + monthStr + "." + dayStr + " " + hourStr + ":" + minuteStr;
    _display.println(formattedTime);

    uint8_t x, w;

    if (_config_time_select == 1) {  // Highligh Year
      x = 8;
      w = 27;
    } else if (_config_time_select == 2) {  // Highligh Month
      x = 38;
      w = 15;
    } else if (_config_time_select == 3) {  // Highligh Day
      x = 56;
      w = 15;
    } else if (_config_time_select == 4) {  // Highligh Hour
      x = 74;
      w = 15;
    } else if (_config_time_select == 5) {  // Highligh Minute
      x = 92;
      w = 15;
    }

    if (_edit_datetime_value) {
      _display.fillRect(x, 30, w, 11, SSD1306_INVERSE);
    } else {
      _display.drawRect(x, 30, w, 11, SSD1306_INVERSE);
      _display.setCursor(7, 52);
      _display.println(F("< Hold O to apply >"));
    }
  }



  void _draw_locked_screen(void) {
    _display.drawBitmap(48, 17, icon_lock, 32, 32, WHITE);
    _display.setTextSize(1);
    _display.setTextColor(SSD1306_WHITE);
    _display.setCursor(16, 52);
    _display.println(F("Hold O to unlock"));
  }

  void _draw_time_in_bar(void) {
    _display.setTextSize(1);
    _display.setTextColor(SSD1306_WHITE);
    _display.setCursor(1, 0);

    if (replace_battery_message) {
      _display.println("Change clock battery!");
      return;
    }

    _datetime = get_current_datetime();
    String yearStr = String(_datetime.year, DEC);
    String monthStr = (_datetime.month < 10 ? "0" : "") + String(_datetime.month, DEC);
    String dayStr = (_datetime.day < 10 ? "0" : "") + String(_datetime.day, DEC);
    String hourStr = (_datetime.hour < 10 ? "0" : "") + String(_datetime.hour, DEC);
    String minuteStr = (_datetime.minute < 10 ? "0" : "") + String(_datetime.minute, DEC);
    String secondStr = (_datetime.second < 10 ? "0" : "") + String(_datetime.second, DEC);
    String formattedTime = yearStr + "." + monthStr + "." + dayStr + " " + hourStr + ":" + minuteStr;

    _display.println(formattedTime);
  }

  void invalidate(void) {
    _last_active_time = millis();
    _invalidate = true;
  }

  uint8_t get_max_days() {
    switch (_datetime.month) {
      case 1:
      case 3:
      case 5:
      case 7:
      case 8:
      case 10:
      case 12:
        return 31;
      case 4:
      case 6:
      case 9:
      case 11:
        return 30;
      case 2:
        return ((_datetime.year % 4 == 0 && (_datetime.year % 100 != 0 || _datetime.year % 400 == 0))) ? 29 : 28;
      default:
        return -1;
    }
  }
  uint8_t _get_uint_length(uint16_t v) {
    if (v <= 9) return 1;
    else if (v <= 99) return 2;
    else if (v <= 999) return 3;
    else if (v <= 9999) return 4;
    else return 5;
  }
};

Display Display;

#endif