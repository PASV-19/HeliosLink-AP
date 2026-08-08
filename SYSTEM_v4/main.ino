#include <Servo.h>
#include "SystemManager.h"

SystemManager systemManager;

void setup() {
    Serial.begin(9600);
    systemManager.begin();
}

void loop() {
    systemManager.update();
}
