#include "APIClient.h"

void APIClient::postJSON(String payload) {
    if (WiFi.status() != WL_CONNECTED) {
        Serial.println("[API] No WiFi connection");
        return;
    }

    HTTPClient http;
    http.begin(API_BASE_URL);

    http.addHeader("Authorization", String("Token ") + API_TOKEN);
    http.addHeader("Content-Type", "application/json");

    int responseCode = http.POST(payload);

    Serial.print("[API] Response code: ");
    Serial.println(responseCode);

    if (responseCode > 0) {
        String response = http.getString();
        Serial.println(response);
    }

    http.end();
}

void APIClient::sendEnergy(float production, float consumption) {
    String payload = "{";
    payload += "\"energy_production\":" + String(production) + ",";
    payload += "\"energy_consumption\":" + String(consumption);
    payload += "}";

    Serial.println("[API] Sending energy...");
    postJSON(payload);
}

void APIClient::sendAngle(int angle) {
    String payload = "{";
    payload += "\"angle\":" + String(angle);
    payload += "}";

    Serial.println("[API] Sending angle...");
    postJSON(payload);
}

void APIClient::sendDevices(Device* devices, int count) {
    String payload = "{ \"devices\": [";

    for (int i = 0; i < count; i++) {
        payload += "{";
        payload += "\"ip\":\"" + devices[i].ip + "\",";
        payload += "\"mac\":\"" + devices[i].mac + "\",";
        payload += "\"name\":\"" + devices[i].name + "\"";
        payload += "}";

        if (i < count - 1) payload += ",";
    }

    payload += "]}";

    Serial.println("[API] Sending devices...");
    postJSON(payload);
}
