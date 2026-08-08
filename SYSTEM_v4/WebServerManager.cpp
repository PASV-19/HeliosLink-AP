#include "WebServerManager.h"

WebServerManager::WebServerManager(BatteryManager& battery, EnergyMonitor& energy)
    : batteryManager(battery), energyMonitor(energy) {}

void WebServerManager::begin(AsyncWebServer& server) {

    server.on("/", HTTP_GET, [this](AsyncWebServerRequest *request) {
        request->send(200, "text/html", buildHTML());
    });

    server.on("/status", HTTP_GET, [this](AsyncWebServerRequest *request) {

        float production = energyMonitor.getProduction();
        float consumption = energyMonitor.getConsumption();
        int battery = batteryManager.getPercentage();

        String panelStatus = (production > consumption) ? "charging" : "idle";

        String json = "{";
        json += "\"battery\":" + String(battery) + ",";
        json += "\"production\":" + String(production) + ",";
        json += "\"consumption\":" + String(consumption) + ",";
        json += "\"status\":\"" + panelStatus + "\"";
        json += "}";

        request->send(200, "application/json", json);
    });
}

String WebServerManager::buildHTML() {
    String html = R"rawliteral(
    <!DOCTYPE html>
    <html>
    <head>
        <title>HELIOSLINK</title>
        <script>
            async function updateData() {
                const res = await fetch('/status');
                const data = await res.json();

                document.getElementById('battery').innerText = data.battery + '%';
                document.getElementById('prod').innerText = data.production + ' W';
                document.getElementById('cons').innerText = data.consumption + ' W';
                document.getElementById('status').innerText = data.status;
            }

            setInterval(updateData, 2000);
            window.onload = updateData;
        </script>
    </head>
    <body>
        <h1>HELIOSLINK SYSTEM</h1>

        <p><b>Battery:</b> <span id="battery">--</span></p>
        <p><b>Production:</b> <span id="prod">--</span></p>
        <p><b>Consumption:</b> <span id="cons">--</span></p>
        <p><b>Status:</b> <span id="status">--</span></p>

        <br>
        <a href="http://192.168.43.150/graf-info">Back to Server</a>
    </body>
    </html>
    )rawliteral";

    return html;
}