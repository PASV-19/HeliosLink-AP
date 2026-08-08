#pragma once
#include <Arduino.h>
#include <Servo.h>
#include "config.h"

class ServoManager {
public:
    void begin();
    void setAngle(int angle);
    int getCurrentAngle();

private:
    Servo servo;
    int currentAngle = 90;
};
