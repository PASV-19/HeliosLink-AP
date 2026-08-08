#pragma once
#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include "BatteryManager.h"
#include "EnergyMonitor.h"

class WebServerManager {
public:
    // Constructor WITH dependencies
    WebServerManager(BatteryManager& battery, EnergyMonitor& energy);

    void begin(AsyncWebServer& server);

private:
    BatteryManager& batteryManager;
    EnergyMonitor& energyMonitor;

    String buildHTML();
};