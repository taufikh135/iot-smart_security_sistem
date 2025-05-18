#pragma once
#include <Arduino.h>
#include <ESP32Servo.h>

class ServoControl {
  public:
    ServoControl(uint8_t dataPin);
    void begin();
    void open();
    void close();

  private:
    Servo servo;
    uint8_t pin;
};