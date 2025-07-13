#ifndef __SENSOR_H__
#define __SENSOR_H__

#define SAMPLE_INTERVAL_MS 100

#define WATER_S 35

class Sensor {
public:
  void init(void) {
    pinMode(WATER_S, INPUT_PULLDOWN);
  }

  bool no_water() {
    return _water_present == false;
  }

  void start_measuring() {
    if (_measure)
      return;

    _measure = true;
    _check_timestamp = millis();
    _sample_timestamp = _check_timestamp;
    _water_present = true;
    _high_count = 0;
    _low_count = 0;
  }

  void set_check_inverval(uint8_t inverval_in_sec) {
    _check_inverval = inverval_in_sec * 1000;
    _samples_per_inverval = _check_inverval / SAMPLE_INTERVAL_MS;
  }

  void stop_measuring() {
    if (!_measure)
      return;

    _measure = false;
  }

  void tick(void) {
    if (!_measure)
      return;

    if (millis() - _sample_timestamp >= SAMPLE_INTERVAL_MS) {
      bool state = digitalRead(WATER_S);  // HIGH no water
      if (state) {
        _high_count++;
      } else {
        _low_count++;
      }
      _sample_timestamp = millis();
    }

    if (millis() - _check_timestamp >= _check_inverval) {
      float low_ration = (float)_low_count / _samples_per_inverval;
      float high_ration = (float)_high_count / _samples_per_inverval;
      if (high_ration > low_ration)
        _water_present = false;
      else
        _water_present = true;
      _low_count = 0;
      _high_count = 0;
      _check_timestamp = millis();
    }
  }
private:
  uint32_t _check_timestamp = 0;
  uint32_t _sample_timestamp = 0;
  uint32_t _low_count = 0;
  uint32_t _high_count = 0;
  uint32_t _check_inverval = 5000;
  float _samples_per_inverval;
  bool _water_present = true;
  bool _measure = false;
};

Sensor Sensor;

#endif __SENSOR_H__