#pragma once
#include <Arduino.h>
#include "INA219Manager.h"

class EnergyMonitor {
public:
    EnergyMonitor(INA219Manager& ina);

    void begin();

    float getProduction();
    float getConsumption();

private:
    INA219Manager& inaManager;
};
