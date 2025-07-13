#ifndef __BUZZER_H__
#define __BUZZER_H__

#define BUZZER_PIN 12

class Buzzer {
public:
  void init() {
    pinMode(BUZZER_PIN, OUTPUT);
  }

  void beep() {
    _stop_at = millis() + 150;
  }

  void beeping() {
    _b = true;
  }

  void reset(void) {
    _b = false;
    _stop_at = 0;
    digitalWrite(BUZZER_PIN, LOW);
  }

  void long_beep() {
    _stop_at = millis() + 400;
  }

  void tick() {

    if (_b && millis() - _t >= 500) {
      digitalWrite(BUZZER_PIN, !digitalRead(BUZZER_PIN));
      _t = millis();
    }

    if (!_b && _stop_at != 0) {
      digitalWrite(BUZZER_PIN, HIGH);
      if ((int32_t)(millis() - _stop_at) >= 0) {
        digitalWrite(BUZZER_PIN, LOW);
        _stop_at = 0;
      }
    }
  }

private:
  uint32_t _stop_at = 0;

  uint32_t _t = 0;
  bool _b = false;
};

Buzzer Buzzer;

#endif __BUZZER_H__