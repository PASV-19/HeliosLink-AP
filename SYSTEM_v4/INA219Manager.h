#pragma once
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_INA219.h>
#include "config.h"

class INA219Manager {
public:
    void begin();

    float getProductionPower();
    float getConsumptionPower();

private:
    Adafruit_INA219 inaProd = Adafruit_INA219(INA219_PROD_ADDR);
    Adafruit_INA219 inaCons = Adafruit_INA219(INA219_CONS_ADDR);

    float readAveragedPower(Adafruit_INA219& sensor);
};
