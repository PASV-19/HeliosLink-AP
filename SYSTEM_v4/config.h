#pragma once

// =========================
// WIFI CONFIGURATION
// =========================
#define AP_SSID        "HELIOSLINK"
#define AP_PASSWORD    "contraseña"

#define STA_SSID       "nombre_de_red"
#define STA_PASSWORD   "contraseña"

// =========================
// API CONFIGURATION
// =========================
#define API_BASE_URL   "http://IP_del_servidor:8000/api/telemetry/"
#define API_TOKEN      "Token_de_autenticación"

// =========================
// HARDWARE PINS
// =========================
#define LDR_45_PIN     34
#define LDR_90_PIN     35
#define LDR_135_PIN    32

#define SERVO_PIN      13
#define BATTERY_PIN    33

// =========================
// INA219 ADDRESSES
// =========================
#define INA219_PROD_ADDR  0x40
#define INA219_CONS_ADDR  0x41

// =========================
// TIMING (ms)
// =========================
#define ENERGY_INTERVAL     15000      // 15s
#define DEVICES_INTERVAL    15000    // 1h_3600000

// =========================
// SOLAR TRACKING
// =========================
#define LDR_THRESHOLD       100
#define TRACK_DELAY         4000       // ms between movements

// =========================
// BATTERY (Lead-Acid 12V)
// =========================
#define BATTERY_MAX_VOLTAGE 12.7
#define BATTERY_MIN_VOLTAGE 11.6

// Voltage divider ratio (R1=30k, R2=7.5k → factor = 5)
#define VOLTAGE_DIVIDER_FACTOR 5.0

// ADC
#define ADC_RESOLUTION     4095.0
#define ADC_REFERENCE      3.3
