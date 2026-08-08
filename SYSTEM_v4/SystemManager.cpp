#include "SystemManager.h"
#include <Arduino.h>

SystemManager* SystemManager::instance = nullptr;

void SystemManager::begin() {
    instance = this;

    //Added lines for debugging
    Serial.println("=== HELIOS SYSTEM INIT ===");

    // Initialize drivers
    ldrManager.begin();
    servoManager.begin();
    inaManager.begin();
    batteryManager.begin();

    // Initialize services
    solarTracker = new SolarTracker(ldrManager, servoManager);
    solarTracker->begin();

    energyMonitor = new EnergyMonitor(inaManager);
    energyMonitor->begin();

    deviceRegistry.begin();

    // Add fake devices for testing
    deviceRegistry.addDevice("ESP_1", "AA:BB:CC:DD:EE:FF", "192.168.1.10");
    // deviceRegistry.addDevice("ESP_2", "11:22:33:44:55:66", "192.168.1.11");

    // Scheduler (short intervals for testing)
    //scheduler.addTask(5000, energyTask);   // every 5s (instead of 15s)
    //scheduler.addTask(15000, devicesTask); // every 15s (instead of 1h)

    // Register scheduled tasks
    scheduler.addTask(ENERGY_INTERVAL, energyTask);
    scheduler.addTask(DEVICES_INTERVAL, devicesTask);

    Serial.println("System initialized.\n");

    wifiManager.begin();

    apiServer = new APIServer(server, batteryManager);
    apiServer->begin();

    webServerManager = new WebServerManager(batteryManager, *energyMonitor);
    webServerManager->begin(server);

    server.begin();
}

void SystemManager::update() {
    scheduler.run();

    // Continuous tracking -> Added for debugging
    if (solarTracker->update()) {
        int angle = solarTracker->getCurrentAngle();

        Serial.println("[TRACKER] Angle changed:");
        Serial.println(angle);
        apiClient.sendAngle(angle);
    }
    wifiManager.update();
}

// =========================
// STATIC CALLBACKS
// =========================

void SystemManager::energyTask() {
    if (instance) instance->handleEnergy();
}

void SystemManager::devicesTask() {
    if (instance) instance->handleDevices();
}

// =========================
// TASK HANDLERS (to be filled later)
// =========================

void SystemManager::handleEnergy() {
//    Serial.println("[System] Energy task triggered"); -> commented for debugging
    // Will call EnergyMonitor + APIClient
    float production = energyMonitor->getProduction();
    float consumption = energyMonitor->getConsumption();
    float voltage = batteryManager.getVoltage();
    int battery = batteryManager.getPercentage();

    Serial.println("=== ENERGY REPORT ===");
    Serial.print("Production (W): ");
    Serial.println(production);

    Serial.print("Consumption (W): ");
    Serial.println(consumption);

    Serial.print("Battery Voltage (V): ");
    Serial.println(voltage);

    Serial.print("Battery (%): ");
    Serial.println(battery);

    Serial.println("=====================\n");

    apiClient.sendEnergy(production, consumption);
}

void SystemManager::handleDevices() {
//    Serial.println("[System] Devices task triggered"); -> commented for debugging
    // Will call DeviceRegistry + APIClient
    Serial.println("=== DEVICES REPORT ===");

    int count = deviceRegistry.getDeviceCount();
    Device* devices = deviceRegistry.getDevices();

    for (int i = 0; i < count; i++) {
        Serial.print("Name: ");
        Serial.println(devices[i].name);

        Serial.print("IP: ");
        Serial.println(devices[i].ip);

        Serial.print("MAC: ");
        Serial.println(devices[i].mac);

        Serial.println("---");
    }

    Serial.println("=====================\n");

    apiClient.sendDevices(devices, count);
}