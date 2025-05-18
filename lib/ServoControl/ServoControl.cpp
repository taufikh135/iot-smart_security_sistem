#include "ServoControl.h"

ServoControl::ServoControl(uint8_t dataPin) {
  this->pin = dataPin;
}

void ServoControl::begin() {
  this->servo.attach(this->pin);
}

void ServoControl::open() {
    for (int pos = 0; pos <= 90; pos++) { // goes from 0 degrees to 180 degrees
        this->servo.write(pos);              // tell servo to go to position in variable 'pos'
        delay(15);                       // waits 15ms for the servo to reach the position
    }
}

void ServoControl::close() {
    for (int pos = 90; pos >= 0; pos--) { // goes from 180 degrees to 0 degrees
        this->servo.write(pos);              // tell servo to go to position in variable 'pos'
        delay(15);                       // waits 15ms for the servo to reach the position
    }
}