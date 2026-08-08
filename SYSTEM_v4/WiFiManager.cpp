#include "WiFiManager.h"

void WiFiManager::begin() {
    Serial.println("=== WIFI INIT ===");

    // AP mode
    WiFi.softAP(AP_SSID, AP_PASSWORD);
    Serial.print("AP IP: ");
    Serial.println(WiFi.softAPIP());

    // STA mode
    WiFi.begin(STA_SSID, STA_PASSWORD);
    Serial.print("Connecting to STA");

    int attempts = 0;
    while (WiFi.status() != WL_CONNECTED && attempts < 10) {
        delay(500);
        Serial.print(".");
        attempts++;
    }

    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("\nConnected to STA");
        Serial.print("STA IP: ");
        Serial.println(WiFi.localIP());
    } else {
        Serial.println("\nSTA connection failed");
    }
}

void WiFiManager::update() {
    if (WiFi.status() != WL_CONNECTED) {
        unsigned long now = millis();

        if (now - lastReconnectAttempt > 10000) {
            Serial.println("[WiFi] Reconnecting...");
            WiFi.begin(STA_SSID, STA_PASSWORD);
            lastReconnectAttempt = now;
        }
    }
}

bool WiFiManager::isConnected() {
    return WiFi.status() == WL_CONNECTED;
}
