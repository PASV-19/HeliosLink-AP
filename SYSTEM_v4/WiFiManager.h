#pragma once
#include <Arduino.h>
#include <WiFi.h>
#include "config.h"

class WiFiManager {
public:
    void begin();
    void update();

    bool isConnected();

private:
    unsigned long lastReconnectAttempt = 0;
};
