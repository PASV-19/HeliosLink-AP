#pragma once
#include <Arduino.h>
#include "config.h"
#include "LDRManager.h"
#include "ServoManager.h"

class SolarTracker {
public:
    SolarTracker(LDRManager& ldr, ServoManager& servo);

    void begin();
    bool update();  // returns true if angle changed
    int getCurrentAngle();

private:
    LDRManager& ldrManager;
    ServoManager& servoManager;

    int currentAngle = 90;
    unsigned long lastMoveTime = 0;

    int decideAngle(int ldr45, int ldr90, int ldr135);
};
