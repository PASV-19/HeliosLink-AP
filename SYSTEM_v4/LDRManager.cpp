#include "LDRManager.h"

void LDRManager::begin() {
    pinMode(LDR_45_PIN, INPUT);
    pinMode(LDR_90_PIN, INPUT);
    pinMode(LDR_135_PIN, INPUT);
}

int LDRManager::readAverage(int pin) {
    const int samples = 5;
    int sum = 0;

    for (int i = 0; i < samples; i++) {
        sum += analogRead(pin);
    }

    return sum / samples;
}

int LDRManager::readLDR45() {
    return readAverage(LDR_45_PIN);
}

int LDRManager::readLDR90() {
    return readAverage(LDR_90_PIN);
}

int LDRManager::readLDR135() {
    return readAverage(LDR_135_PIN);
}
