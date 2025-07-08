#ifndef __BUTTON_H__
#define __BUTTON_H__

#define LONG_PRESS_TIME 2000

enum ButtonState {
  NONE,
  CLICK,
  LONG_PRESS
};

class Button {
public:
  Button(uint8_t pin) {
    _pin = pin;
  }

  void init() {
    pinMode(_pin, INPUT_PULLUP);
  }

  ButtonState get_state() {
    if (!_state_received) {
      _state_received = true;
      return _button_state;
    }
    return NONE;
  }

  bool hold() {
    return _long_press_done;
  }

  void tick() {
    if (!digitalRead(_pin)) {
      if (_long_press_done) {
        return;
      }
      if (!_pressed) {
        _press_time = millis();
        _pressed = true;
      } else {  // Handle long press
        if (millis() - _press_time >= LONG_PRESS_TIME) {
          _button_state = LONG_PRESS;
          _pressed = false;
          _press_time = 0;
          _state_received = false;
          _long_press_done = true;
        }
      }
    } else {  // Handle simple click when the button released
      _long_press_done = false;
      if (_pressed) {
        _button_state = CLICK;
        _press_time = 0;
        _state_received = false;
        _pressed = false;
      }
    }
  }
private:
  uint8_t _pin;
  uint32_t _press_time = 0;
  ButtonState _button_state = NONE;
  bool _state_received = true;
  bool _pressed = false;
  bool _long_press_done = false;
};

#endif