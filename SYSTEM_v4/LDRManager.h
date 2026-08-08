#pragma once
#include <Arduino.h>
#include "config.h"

class LDRManager {
public:
    void begin();

    int readLDR45();
    int readLDR90();
    int readLDR135();

private:
    int readAverage(int pin);
};
