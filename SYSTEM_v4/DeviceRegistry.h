#pragma once
#include <Arduino.h>
#include "config.h"

struct Device {
    String name;
    String mac;
    String ip;
};

class DeviceRegistry {
public:
    void begin();

    void clear();
    void addDevice(String name, String mac, String ip);

    int getDeviceCount();
    Device* getDevices();
};
