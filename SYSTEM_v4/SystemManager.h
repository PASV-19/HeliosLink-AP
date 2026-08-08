#pragma once
#include "Scheduler.h"
#include "config.h"

// Debugging includes
#include "LDRManager.h"
#include "ServoManager.h"
#include "INA219Manager.h"
#include "BatteryManager.h"
#include "SolarTracker.h"
#include "EnergyMonitor.h"
#include "DeviceRegistry.h"

// Includes for the Network Layer
#include "WiFiManager.h"
#include "APIClient.h"
#include <ESPAsyncWebServer.h>
#include "APIServer.h"
#include "WebServerManager.h"

class SystemManager {
public:
    void begin();
    void update();

private:
    Scheduler scheduler;

    // Drivers -> for debugging
    LDRManager ldrManager;
    ServoManager servoManager;
    INA219Manager inaManager;
    BatteryManager batteryManager;

    // Services -> for debugging
    SolarTracker* solarTracker;
    EnergyMonitor* energyMonitor;
    DeviceRegistry deviceRegistry;

    // Network Members
    WiFiManager wifiManager;
    APIClient apiClient;
    AsyncWebServer server = AsyncWebServer(80);
    APIServer* apiServer;
    WebServerManager* webServerManager;
  
    // Static wrappers for scheduler
    static void energyTask();
    static void devicesTask();

    // Internal handlers
    void handleEnergy();
    void handleDevices();

    // Singleton-like access
    static SystemManager* instance;
};
