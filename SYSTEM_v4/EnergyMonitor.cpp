#include "EnergyMonitor.h"

EnergyMonitor::EnergyMonitor(INA219Manager& ina)
    : inaManager(ina) {}

void EnergyMonitor::begin() {
    // nothing extra for now
}

float EnergyMonitor::getProduction() {
    return inaManager.getProductionPower();
}

float EnergyMonitor::getConsumption() {
    return inaManager.getConsumptionPower();
}
