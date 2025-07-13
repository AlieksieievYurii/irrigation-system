#ifndef __QUEUE_H__
#define __QUEUE_H__

#define OUT_E 32
#define OUT_S0 27
#define OUT_S1 26
#define OUT_S2 25
#define OUT_S3 33

#define MOTOR_PIN 2

#define NO_TARGET_OUTLET 0xFF

#define DELAY_BEFORE_PUMPING 500

struct Item {
  uint8_t outlet = 0xFF;
  uint32_t volume;
};

class Core {
public:
  Config* config = nullptr;

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

  void start_pumping(uint8_t outlet) {
    if (_opening_outlet_timestamp == 0) {
      _opening_outlet_timestamp = millis();
      open_outlet(outlet);
    } else if (millis() - _opening_outlet_timestamp >= DELAY_BEFORE_PUMPING) {
      digitalWrite(MOTOR_PIN, HIGH);
    }
  }

  void stop_pumping() {
    close_outlet();
    digitalWrite(MOTOR_PIN, LOW);
    _opening_outlet_timestamp = 0;
  }

  void suspend() {
    if (!is_pumping()) {
      return;
    }
    _left_time = _stop_time - millis();
    Serial.printf("Pumping suspended. Left Time: %d s\n", _left_time / 1000);
    _suspended = true;
  }

  void resume() {
    if (is_pumping()) {
      return;
    }
    _stop_time = millis() + _left_time;
    _suspended = false;
  }

  bool is_processing(void) {
    return _count != 0 || _target_outlet != NO_TARGET_OUTLET;
  }

  bool is_pumping() {
    return _target_outlet != NO_TARGET_OUTLET && !_suspended;
  }

  bool add(uint8_t outlet, uint32_t volume) {
    if (_count >= OUTLETS)
      return false;

    // Since the 'add' function is called multiple times just for one schedule,
    // add time constrain to avoid queueing the same schedule.
    if (_registered[outlet] != 0 && millis() - _registered[outlet] <= 90000)
      return false;

    Serial.printf("Plumping planed> O: %d, V: %d\n", outlet, volume);

    _queue[_tail].outlet = outlet;
    _queue[_tail].volume = volume;
    _tail = (_tail + 1) % OUTLETS;
    _count++;
    _registered[outlet] = millis();

    Serial.printf("Queued O: %d V: %d\n", outlet, volume);

    return true;
  }

  void tick() {
    if (_delay != 0 && (int32_t)(millis() - _delay) <= 500) {
      return;
    }
    _delay = 0;

    if (_count > 0 && _target_outlet == NO_TARGET_OUTLET) {
      _target_outlet = _queue[_head].outlet;
      _volume = _queue[_head].volume;
      _head = (_head + 1) % OUTLETS;
      _count--;
      uint32_t duration = ((_volume * VOLUME_SCALE) / config->throughput * 1000) + DELAY_BEFORE_PUMPING;  // Compansate the delay
      _stop_time = millis() + duration;
      Serial.printf("It will take: %d s\n", (long)(_stop_time - millis()) / 1000);
    }

    if (_target_outlet != NO_TARGET_OUTLET) {
      if (_suspended) {
        stop_pumping();
        return;
      }
      if ((int32_t)(millis() - _stop_time) >= 0) {
        stop_pumping();
        Serial.printf("STOP O: %d\n", _target_outlet);
        _target_outlet = NO_TARGET_OUTLET;
        _delay = millis();
      } else {
        start_pumping(_target_outlet);
      }
    }
  }

private:
  Item _queue[OUTLETS] = {};
  uint8_t _tail = 0;
  uint8_t _head = 0;
  uint8_t _count = 0;

  uint8_t _target_outlet = NO_TARGET_OUTLET;
  uint32_t _volume;
  uint32_t _stop_time;
  uint32_t _delay;
  uint32_t _left_time = 0;
  bool _suspended = false;

  uint32_t _registered[OUTLETS] = { 0 };

  uint32_t _opening_outlet_timestamp = 0;
};

#endif __QUEUE_H__