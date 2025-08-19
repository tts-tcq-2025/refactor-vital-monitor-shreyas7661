#include "./monitor.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <string>

using namespace std;
using namespace std::chrono;

void blinkingAlert() {
  for (int i = 0; i < 6; ++i) {
    cout << "\r*  " << flush;
    this_thread::sleep_for(seconds(1));
    cout << "\r * " << flush;
    this_thread::sleep_for(seconds(1));
  }
}

VitalStatus evaluateVital(float value, const VitalLimits& limits) {
  float warningTolerance = 0.015f * limits.upper;

  if (value < limits.lower) return VITAL_LOW;
  if (value >= limits.lower && value < limits.lower + warningTolerance) return VITAL_WARNING_LOW;

  if (value > limits.upper) return VITAL_HIGH;
  if (value <= limits.upper && value > limits.upper - warningTolerance) return VITAL_WARNING_HIGH;

  return VITAL_OK;
}

bool checkVital(const string& name, float value, const VitalLimits& limits) {
  VitalStatus status = evaluateVital(value, limits);

  if (status == VITAL_OK) return true;

  const char* messages[] = {
    "",                          // VITAL_OK
    " is too low!\n",            // VITAL_LOW
    " is too high!\n",           // VITAL_HIGH
    " Warning: Approaching low!\n",  // VITAL_WARNING_LOW
    " Warning: Approaching high!\n"  // VITAL_WARNING_HIGH
  };

  cout << name << messages[status];

  if (status == VITAL_LOW || status == VITAL_HIGH) {
    blinkingAlert();
    return false;
  }

  // For warnings, notify but do not fail
  return true;
}

bool checkTemperature(float temperature) {
  return checkVital("Temperature", temperature, {95.0f, 102.0f});
}

bool checkPulseRate(float pulseRate) {
  return checkVital("Pulse Rate", pulseRate, {60.0f, 100.0f});
}

bool checkSpo2(float spo2) {
  return checkVital("Oxygen Saturation", spo2, {90.0f, 100.0f});
}

bool vitalsOk(float temperature, float pulseRate, float spo2) {
  return checkTemperature(temperature) && checkPulseRate(pulseRate) && checkSpo2(spo2);
}
