#include "BatteryManager.h"

void BatteryManager::begin() {
    pinMode(BATTERY_PIN, INPUT);
}

float BatteryManager::readAveragedVoltage() {
    const int samples = 20;
    float sum = 0;

    for (int i = 0; i < samples; i++) {
        sum += analogRead(BATTERY_PIN);
        delay(2); // allow ADC stabilization
    }

    float adcValue = sum / samples;

    float v_adc = (adcValue / ADC_RESOLUTION) * ADC_REFERENCE;
    float v_battery = v_adc * VOLTAGE_DIVIDER_FACTOR;

    return v_battery;
}

float BatteryManager::getVoltage() {
    return readAveragedVoltage();
}

int BatteryManager::mapVoltageToPercentage(float voltage) {
    if (voltage >= BATTERY_MAX_VOLTAGE) return 100;
    if (voltage <= BATTERY_MIN_VOLTAGE) return 0;

    // Linear interpolation
    float percentage = (voltage - BATTERY_MIN_VOLTAGE) /
                       (BATTERY_MAX_VOLTAGE - BATTERY_MIN_VOLTAGE);

    return (int)(percentage * 100.0);
}

int BatteryManager::getPercentage() {
    float voltage = getVoltage();
    return mapVoltageToPercentage(voltage);
}
