#pragma once
#include <string>

struct VitalLimits {
  float lower;
  float upper;
};

enum VitalStatus {
  VITAL_OK,
  VITAL_LOW,
  VITAL_HIGH,
  VITAL_WARNING_LOW,
  VITAL_WARNING_HIGH
};

// Pure function to evaluate a vital including warning levels
VitalStatus evaluateVital(float value, const VitalLimits& limits);

// Public function
bool vitalsOk(float temperature, float pulseRate, float spo2);

// For testing individual vitals or expansion
bool checkVital(const std::string& name, float value, const VitalLimits& limits);
