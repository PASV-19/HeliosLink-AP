#include "APIServer.h"

APIServer::APIServer(AsyncWebServer& srv, BatteryManager& battery)
    : server(srv), batteryManager(battery) {}

void APIServer::begin() {
    server.on("/battery", HTTP_GET, [this](AsyncWebServerRequest *request) {
        int battery = batteryManager.getPercentage();

        String response = "{ \"battery\": " + String(battery) + " }";

        request->send(200, "application/json", response);
    });
}
