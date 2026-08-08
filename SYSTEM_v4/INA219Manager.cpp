#include "INA219Manager.h"

void INA219Manager::begin() {
    Wire.begin();
    inaProd.begin();
    inaCons.begin();
}

float INA219Manager::readAveragedPower(Adafruit_INA219& sensor) {
    const int samples = 5;
    float sum = 0;

    for (int i = 0; i < samples; i++) {
        sum += sensor.getPower_mW() / 1000.0; // convert to W
    }

    return sum / samples;
}

float INA219Manager::getProductionPower() {
    return readAveragedPower(inaProd);
}

float INA219Manager::getConsumptionPower() {
    return readAveragedPower(inaCons);
}
