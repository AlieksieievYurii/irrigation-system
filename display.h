#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define DISPLAY_ADDRESS 0x3C

#define OLED_RESET -1

#define NUMBER_OF_SCREENS 4

#define NO_SCREEN_SELECTED 0x0
#define SCREEN_SCHEDULE 0x1
#define SCREEN_FORECAST 0x2
#define SCREEN_SET_TIME 0x3
#define SCREEN_TRIGGER 0x4
#define SCREEN_CONFIG 0x5
#define SCREEN_NO_WATER 0x6

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

const unsigned char icon_config[] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xe0, 0x00, 0x00, 0x0f, 0xf0, 0x00, 0x00, 0x0f, 0xf0, 0x00,
  0x00, 0x0f, 0xf0, 0x00, 0x00, 0x1f, 0xf8, 0x00, 0x0e, 0x7f, 0xfe, 0x78, 0x1f, 0xff, 0xff, 0xfc,
  0x3f, 0xff, 0xff, 0xfc, 0x7f, 0xff, 0xff, 0xfe, 0x7f, 0xfc, 0x3f, 0xfe, 0x7f, 0xf0, 0x0f, 0xfe,
  0x3f, 0xe0, 0x07, 0xfc, 0x1f, 0xc0, 0x03, 0xf8, 0x0f, 0xc0, 0x03, 0xf0, 0x0f, 0xc0, 0x03, 0xf0,
  0x0f, 0xc0, 0x03, 0xf0, 0x0f, 0xc0, 0x03, 0xf0, 0x1f, 0xc0, 0x03, 0xf8, 0x3f, 0xe0, 0x07, 0xfc,
  0x7f, 0xf0, 0x0f, 0xfe, 0x7f, 0xfc, 0x3f, 0xfe, 0x7f, 0xff, 0xff, 0xfe, 0x3f, 0xff, 0xff, 0xfc,
  0x1f, 0xff, 0xff, 0xfc, 0x0e, 0x7f, 0xfe, 0x78, 0x00, 0x1f, 0xf8, 0x00, 0x00, 0x0f, 0xf0, 0x00,
  0x00, 0x0f, 0xf0, 0x00, 0x00, 0x0f, 0xf0, 0x00, 0x00, 0x07, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00
};

const unsigned char icon_forecast[] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xff, 0xff, 0xe0,
  0x0f, 0xff, 0xff, 0xf0, 0x1f, 0xff, 0xff, 0xf8, 0x1f, 0xff, 0xff, 0xf8, 0x1e, 0x00, 0x00, 0x78,
  0x1e, 0x00, 0x00, 0x78, 0x1e, 0x00, 0xff, 0x78, 0x1e, 0x00, 0xff, 0x78, 0x1e, 0x00, 0xff, 0x78,
  0x1e, 0x00, 0x00, 0x78, 0x1e, 0x00, 0x00, 0x78, 0x1e, 0x00, 0x00, 0x78, 0x1e, 0x0f, 0xf0, 0x78,
  0x1e, 0x0f, 0xf0, 0x78, 0x1e, 0x00, 0x00, 0x78, 0x1e, 0x00, 0x00, 0x78, 0x1e, 0x00, 0x00, 0x78,
  0x1e, 0xff, 0x00, 0x78, 0x1e, 0xff, 0x00, 0x78, 0x1e, 0x00, 0x00, 0x78, 0x1e, 0x00, 0x00, 0x78,
  0x1e, 0x00, 0x00, 0x78, 0x1f, 0xff, 0xff, 0xf8, 0x1f, 0xff, 0xff, 0xf8, 0x0f, 0xff, 0xff, 0xf0,
  0x07, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};



class Display {
public:
  typedef DateTimeInfo (*Callback)();
  typedef uint32_t (*Days)();
  typedef void (*ApplyDateTimeCallback)(DateTimeInfo);
  typedef void (*SaveSchedule)(uint8_t);
  typedef void (*SaveConfig)();
  ScheduleSet* schedule_sets = nullptr;
  Config* config = nullptr;

  Callback get_current_datetime = nullptr;
  Days get_days_time = nullptr;
  ApplyDateTimeCallback apply_datetime = nullptr;
  SaveSchedule save_schedule = nullptr;
  SaveConfig save_config = nullptr;
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

  void print_throughput(void) {
    if (_throughput_timestamp == 0)
      _throughput_timestamp = millis();
    else {
      _time = (uint32_t)(millis() - _throughput_timestamp);

      if (_time < 500)  // Ignore until the motor starts working
        return;
      _time = _time + buff - 500;

      if (millis() - l >= 900) {
        _throughput = (_time / 1000) * config->throughput;
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

  void show_no_water(bool active) {
    _screen_no_water_update_time = 0;
    if (active) {
      _wake_up();
      _screen = SCREEN_NO_WATER;
      invalidate();
    } else {
      _screen_locked = true;
      _screen = NO_SCREEN_SELECTED;
      invalidate();
    }
  }

  void disable() {
    if (_disabled)
      return;
    _disabled = true;
    if (!_sleep_mode)
      invalidate();
  }
  void enable() {
    if (!_disabled)
      return;
    _disabled = false;
    if (!_sleep_mode)
      invalidate();
  }

  void left() {
    if (_last_active_time == 0 || _screen_locked || _disabled) {  // If the display is in sleeping mode, just activate
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
    } else if (_screen == SCREEN_FORECAST) {
      if (_forecast_schedule > 0) {
        _forecast_schedule--;
      }
    } else if (_screen == SCREEN_CONFIG) {
      if (_config_edit_mode) {
        _update_config_value(true);
      } else if (_config_cursor > 0) {
        _config_cursor--;
      }
    }

    invalidate();
  }

  void right() {
    if (_last_active_time == 0 || _screen_locked || _disabled) {  // If the display is in sleeping mode, just activate
      invalidate();
      return;
    }

    if (_screen == NO_SCREEN_SELECTED) {
      if (_screen_select_cursor < NUMBER_OF_SCREENS)
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
    } else if (_screen == SCREEN_FORECAST) {
      if (_forecast_schedule < OUTLETS - 1) {
        _forecast_schedule++;
      }
    } else if (_screen == SCREEN_CONFIG) {
      if (_config_edit_mode) {
        _update_config_value(false);
      } else if (_config_cursor < 1) {
        _config_cursor++;
      }
    }

    invalidate();
  }

  void click() {
    if (_last_active_time == 0 || _screen_locked || _disabled) {  // If the display is in sleeping mode, just activate
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
    } else if (_screen == SCREEN_CONFIG) {
      _config_edit_mode = !_config_edit_mode;
    } else if (_screen == SCREEN_FORECAST) {
      _screen = NO_SCREEN_SELECTED;
      _forecast_schedule = 0;
    }

    invalidate();
  }

  void long_click() {
    if (_last_active_time == 0 || _sleep_mode || _disabled) {  // If the display is in sleeping mode, just activate
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
        _schedule_set = 0;
      }
    } else if (_screen == SCREEN_CONFIG) {
      save_config();
      _screen = NO_SCREEN_SELECTED;
      _config_cursor = 0;
    }

    invalidate();
  }

  void tick(void) {
    if (_screen == SCREEN_NO_WATER && millis() - _screen_no_water_update_time >= 10000) {
      invalidate();
      _screen_no_water_update_time = millis();
    }

    if (!_sleep_mode && _last_active_time != 0 && millis() - _last_active_time >= 10000) {
      _sleep();
      _last_active_time = 0;
      _screen_locked = true;
      return;
    }

    trigger_run = !_screen_locked && _screen == SCREEN_TRIGGER;

    if (_invalidate) {
      if (_sleep_mode) {
        _wake_up();
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

  uint32_t _throughput_timestamp = 0;
  uint32_t _time = 0;
  uint32_t l = 0;
  uint32_t buff = 0;
  float _throughput = 0;

  uint32_t _screen_no_water_update_time = 0;

  bool _disabled = false;

  uint8_t _config_cursor = 0;
  bool _config_edit_mode = false;

  uint8_t _forecast_schedule = 0;

  void _wake_up(void) {
    _display.ssd1306_command(SSD1306_DISPLAYON);
    _sleep_mode = false;
  }

  void _sleep() {
    _display.ssd1306_command(SSD1306_DISPLAYOFF);
    _sleep_mode = true;
  }

  void _draw() {
    _display.clearDisplay();
    if (_screen == SCREEN_NO_WATER) {
      _draw_time_in_bar();
      _draw_no_water_screen();
    } else if (_disabled) {
      _draw_time_in_bar();
      _draw_screen_disabled();
    } else if (_screen_locked) {
      _draw_time_in_bar();
      _draw_locked_screen();
    } else if (_screen == NO_SCREEN_SELECTED) {
      _draw_time_in_bar();
      _draw_menu();
    } else if (_screen == SCREEN_SCHEDULE) {
      _draw_screen_schedule();
    } else if (_screen == SCREEN_FORECAST) {
      _draw_screen_forecast();
    } else if (_screen == SCREEN_SET_TIME) {
      _draw_time_config();
    } else if (_screen == SCREEN_TRIGGER) {
      _draw_trigger();
    } else if (_screen == SCREEN_CONFIG) {
      _draw_config();
    }
    _display.display();
  }

  void _draw_screen_forecast() {
    _display.setTextSize(1);
    _display.setTextColor(SSD1306_WHITE);
    _display.setCursor(0, 0);
    _display.println(F("< Forecast"));

    _display.setTextSize(2);
    _display.setCursor(30, 16);
    char character = (char)65 + _forecast_schedule;
    _display.print(character);

    _display.setTextSize(1);
    uint32_t today = get_days_time();
    ScheduleSet* schedule = &schedule_sets[_forecast_schedule];

    _display.setTextSize(2);
    _display.setCursor(72, 16);
    _display.println(F(schedule->active ? "ON" : "OFF"));

    uint32_t days_diff = (today > schedule->_timestamp_days)
                           ? (today - schedule->_timestamp_days)
                           : (schedule->_timestamp_days - today);

    uint32_t next = 0;
    if (days_diff == 0){
      next = schedule->_timestamp_days + schedule->days;
    }else {
      uint32_t delta = days_diff % schedule->days;
      next = (delta != 0 ? today + (schedule->days - delta) : today);
    }

    _display.setTextSize(1);
    for (uint8_t i = 0; i < 3; i++) {
      _display.setCursor(16, 36 + (9 * i));
      uint32_t next_trigger = next + i * schedule->days;
      if (next_trigger == today) {
        _display.printf("Today at  %d:%d", schedule->hour, schedule->minute);
      } else {
        DateTime date = DateTime((next_trigger * SECONDS_PER_DAY) + SECONDS_FROM_1970_TO_2000);
        _display.printf("%d.%d.%d %d:%d", date.year(), date.month(), date.day(), schedule->hour, schedule->minute);
      }
    }

    if (_forecast_schedule > 0) {
      _display.fillTriangle(0, 32, 10, 22, 10, 42, WHITE);
    }

    if (_forecast_schedule < OUTLETS - 1) {
      _display.fillTriangle(127, 32, 117, 22, 117, 42, WHITE);
    }
  }

  void _draw_screen_disabled() {
    _display.setTextSize(1);
    _display.setTextColor(SSD1306_WHITE);
    _display.setCursor(16, 18);
    _display.println(F("Screen disabled!"));
    _display.setCursor(22, 36);
    _display.println(F("Please wait..."));
  }

  void _draw_no_water_screen(void) {
    _display.setTextSize(2);
    _display.setTextColor(SSD1306_WHITE);
    _display.setCursor(10, 20);
    _display.println(F("No Water!"));
    _display.setCursor(8, 48);
    _display.setTextSize(1);
    _display.println(F("Refill and press O"));
  }

  void _draw_menu() {
    _display.setTextSize(1);
    _display.setTextColor(SSD1306_WHITE);

    uint8_t screen = _screen_select_cursor + 1;
    if (screen == SCREEN_SCHEDULE) {
      _display.drawBitmap(48, 17, icon_schedule, 32, 32, WHITE);
      _display.setCursor(40, 52);
      _display.println(F("Schedule"));
    } else if (screen == SCREEN_SET_TIME) {
      _display.drawBitmap(48, 17, icon_time, 32, 32, WHITE);
      _display.setCursor(40, 52);
      _display.println(F("Set time"));
    } else if (screen == SCREEN_TRIGGER) {
      _display.drawBitmap(48, 17, icon_trigger, 32, 32, WHITE);
      _display.setCursor(43, 52);
      _display.println(F("Trigger"));
    } else if (screen == SCREEN_CONFIG) {
      _display.drawBitmap(48, 17, icon_config, 32, 32, WHITE);
      _display.setCursor(19, 52);
      _display.println(F("Advanced Config"));
    } else if (screen == SCREEN_FORECAST) {
      _display.drawBitmap(48, 17, icon_forecast, 32, 32, WHITE);
      _display.setCursor(40, 52);
      _display.println(F("Forecast"));
    }

    if (_screen_select_cursor > 0) {
      _display.fillTriangle(2, 32, 12, 22, 12, 42, WHITE);
    }

    if (_screen_select_cursor < NUMBER_OF_SCREENS) {
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
    float v = schedule->volume * VOLUME_SCALE;
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

  void _draw_config() {
    _display.setTextSize(1);
    _display.setTextColor(SSD1306_WHITE);
    _display.setCursor(0, 0);
    _display.println(F("< Config"));

    _display.setCursor(2, 18);
    _display.println(F("WCI:    sec"));
    _display.setCursor(config->water_check_interval > 9 ? 32 : 38, 18);
    _display.println(config->water_check_interval);

    _display.setCursor(2, 27);
    _display.println(F("THPT:       L/sec"));
    _display.setCursor(38, 27);
    _display.println(config->throughput, 3);

    uint8_t x, y, w;

    if (_config_cursor == 0) {
      y = 16;
      x = config->water_check_interval > 9 ? 30 : 36;
      w = config->water_check_interval > 9 ? 15 : 9;
    } else if (_config_cursor == 1) {
      y = 25;
      x = 36;
      w = 32;
    }

    if (_config_edit_mode)
      _display.fillRect(x, y, w, 11, SSD1306_INVERSE);
    else
      _display.drawRect(x, y, w, 11, SSD1306_INVERSE);

    _display.setCursor(7, 52);
    _display.println(F("< Hold O to apply >"));
  }

  void _save_schedule(void) {
    if (_schedule_change_status == SCHEDULE_UNSAVED) {
      save_schedule(_schedule_set);
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
        else new_volume = MAX_VOLUME;
      } else {
        if (new_volume < MAX_VOLUME)
          new_volume++;
        else new_volume = 0;
      }
      schedule->volume = new_volume;
    }
  }

  void _update_config_value(bool decrease) {
    if (decrease) {
      if (_config_cursor == 0 && config->water_check_interval > 3) {  // Water Check Interval
        config->water_check_interval--;
      } else if (_config_cursor == 1 && config->throughput > MIN_CONFIG_THROUGHPUT) {  // THROUGHPUT
        config->throughput -= 0.001;
      }
    } else {
      if (_config_cursor == 0 && config->water_check_interval < 60) {  // Water Check Interval
        config->water_check_interval++;
      } else if (_config_cursor == 1 && config->throughput < MAX_CONFIG_THROUGHPUT) {  // THROUGHPUT
        config->throughput += 0.001;
      }
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

    if (_config_time_select == 1) {  // Highlight Year
      x = 8;
      w = 27;
    } else if (_config_time_select == 2) {  // Highlight Month
      x = 38;
      w = 15;
    } else if (_config_time_select == 3) {  // Highlight Day
      x = 56;
      w = 15;
    } else if (_config_time_select == 4) {  // Highlight Hour
      x = 74;
      w = 15;
    } else if (_config_time_select == 5) {  // Highlight Minute
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