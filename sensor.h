#ifndef __SENSOR_H__
#define __SENSOR_H__

class Sensor {
public:
  Sensor(uint8_t pin) {
    _pin = pin;
  }

  void init(void) {
    pinMode(_pin, INPUT_PULLDOWN);
  }

  bool no_water() {
    return _no_water;
  }

  void tick(void) {
    bool state = digitalRead(_pin);
    if (state != _previous_state) {  // HIGH no water
      t = millis();
      _previous_state = state;
    } else if (millis() - t > 500) {
      _no_water = _previous_state;
      t = 0;
    }
  }
private:
  uint8_t _pin = 0;
  uint32_t t = 0;
  bool _no_water = false;
  bool _previous_state = false;
};

#endif __SENSOR_H__