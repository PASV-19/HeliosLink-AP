#include "ServoManager.h"

void ServoManager::begin() {
    servo.attach(SERVO_PIN);
    servo.write(currentAngle);
}

void ServoManager::setAngle(int angle) {
    if (angle < 0) angle = 0;
    if (angle > 180) angle = 180;

    if (angle != currentAngle) {
        servo.write(angle);
        currentAngle = angle;
    }
}

int ServoManager::getCurrentAngle() {
    return currentAngle;
}
