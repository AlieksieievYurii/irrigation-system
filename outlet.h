#ifndef __OUTLET_H__
#define __OUTLET_H__

#define OUT_E 32
#define OUT_S0 27
#define OUT_S1 26
#define OUT_S2 25
#define OUT_S3 33

#define MOTOR_PIN 2

class Outlets {
public:
  void init(void) {
    pinMode(OUT_S0, OUTPUT);
    pinMode(OUT_S1, OUTPUT);
    pinMode(OUT_S2, OUTPUT);
    pinMode(OUT_S3, OUTPUT);
    pinMode(OUT_E, OUTPUT);

    pinMode(MOTOR_PIN, OUTPUT);
  }

  void open_outlet(uint8_t o) {
    digitalWrite(OUT_S0, o & 0x01);
    digitalWrite(OUT_S1, (o >> 1) & 0x01);
    digitalWrite(OUT_S2, (o >> 2) & 0x01);
    digitalWrite(OUT_S3, (o >> 3) & 0x01);

    digitalWrite(OUT_E, HIGH);
  }

  void close_outlet(void) {
    digitalWrite(OUT_E, LOW);
  }

  void start(uint8_t outlet) {
    if (_timestamp == 0) {
      _timestamp = millis();
      open_outlet(outlet);
    }else if (millis() - _timestamp >= 500) {
      digitalWrite(MOTOR_PIN, HIGH);
    }
  }

  void proccesed_volume() {

  }

  void stop() {
    close_outlet();
    digitalWrite(MOTOR_PIN, LOW);
    _timestamp = 0;
  }

  void tick() {

  }
private:
  uint32_t _timestamp = 0;
};

#endif __OUTLET_H__