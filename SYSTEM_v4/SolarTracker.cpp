#include "SolarTracker.h"

SolarTracker::SolarTracker(LDRManager& ldr, ServoManager& servo)
    : ldrManager(ldr), servoManager(servo) {}

void SolarTracker::begin() {
    servoManager.setAngle(currentAngle);
}

bool SolarTracker::update() {
    unsigned long now = millis();

    // Enforce delay between movements
    if (now - lastMoveTime < TRACK_DELAY) {
        return false;
    }

    int l45 = ldrManager.readLDR45();
    int l90 = ldrManager.readLDR90();
    int l135 = ldrManager.readLDR135();

    int newAngle = decideAngle(l45, l90, l135);

    if (newAngle != currentAngle) {
        servoManager.setAngle(newAngle);
        currentAngle = newAngle;
        lastMoveTime = now;

        Serial.println("[TRACKER] Movement applied");
        return true;
    }

    return false;
}

int SolarTracker::decideAngle(int l45, int l90, int l135) {

    // ===== HYSTERESIS (keep current position if still valid) =====

    if (currentAngle == 45 &&
        l45 > l90 - LDR_THRESHOLD &&
        l45 > l135 - LDR_THRESHOLD) {
        return 45;
    }

    if (currentAngle == 135 &&
        l135 > l90 - LDR_THRESHOLD &&
        l135 > l45 - LDR_THRESHOLD) {
        return 135;
    }

    if (currentAngle == 90 &&
        l90 > l45 - LDR_THRESHOLD &&
        l90 > l135 - LDR_THRESHOLD) {
        return 90;
    }

    // ===== DOMINANCE CHECK (strict) =====

    if ((l45 > l90 + LDR_THRESHOLD) && (l45 > l135 + LDR_THRESHOLD)) {
        return 45;
    }

    if ((l135 > l90 + LDR_THRESHOLD) && (l135 > l45 + LDR_THRESHOLD)) {
        return 135;
    }

    if ((l90 > l45 + LDR_THRESHOLD) && (l90 > l135 + LDR_THRESHOLD)) {
        return 90;
    }

    // No strong signal → keep current
    return currentAngle;
}

int SolarTracker::getCurrentAngle() {
    return currentAngle;
}