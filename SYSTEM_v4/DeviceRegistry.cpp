#include "DeviceRegistry.h"

void DeviceRegistry::begin() {
    clear();
}

void DeviceRegistry::clear() {
    count = 0;
}

void DeviceRegistry::addDevice(String name, String mac, String ip) {
    devices[count++] = {name, mac, ip};
}

int DeviceRegistry::getDeviceCount() {
    return count;
}

Device* DeviceRegistry::getDevices() {
    return devices;
}
