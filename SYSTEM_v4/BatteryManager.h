#pragma once
#include <Arduino.h>
#include "config.h"

class BatteryManager {
public:
    void begin();

    float getVoltage();
    int getPercentage();

private:
    float readAveragedVoltage();
    int mapVoltageToPercentage(float voltage);
};
