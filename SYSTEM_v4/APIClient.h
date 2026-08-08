#pragma once
#include <Arduino.h>
#include <HTTPClient.h>
#include <WiFi.h>
#include "config.h"
#include "DeviceRegistry.h"

class APIClient {
public:
    void sendEnergy(float production, float consumption);
    void sendAngle(int angle);
    void sendDevices(Device* devices, int count);

private:
    void postJSON(String payload);
};
