#pragma once
#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include "BatteryManager.h"

class APIServer {
public:
    APIServer(AsyncWebServer& server, BatteryManager& battery);

    void begin();

private:
    AsyncWebServer& server;
    BatteryManager& batteryManager;
};
