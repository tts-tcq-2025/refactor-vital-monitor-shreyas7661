#include "./monitor.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <string>

using namespace std;
using namespace std::chrono;

// Blinking alert animation (I/O side effect)
void blinkingAlert() {
  for (int i = 0; i < 6; ++i) {
    cout << "\r* " << flush;
    this_thread::sleep_for(seconds(1));
    cout << "\r *" << flush;
    this_thread::sleep_for(seconds(1));
  }
}

// Evaluate a vital sign against limits (pure function)
VitalStatus evaluateVital(float value, const VitalLimits& limits) {
  if (value < limits.lower) return VITAL_LOW;
  if (value > limits.upper) return VITAL_HIGH;
  return VITAL_OK;
}

// Check a single vital and alert if out of range (I/O + logic)
bool checkVital(const string& name, float value, const VitalLimits& limits) {
  VitalStatus status = evaluateVital(value, limits);

  if (status == VITAL_OK) return true;

  if (status == VITAL_LOW) {
    cout << name << " is too low!\n";
  } else if (status == VITAL_HIGH) {
    cout << name << " is too high!\n";
  }
  blinkingAlert();
  return false;
}

// Individual checks with minimal complexity
bool checkTemperature(float temperature) {
  return checkVital("Temperature", temperature, {95.0f, 102.0f});
}

bool checkPulseRate(float pulseRate) {
  return checkVital("Pulse Rate", pulseRate, {60.0f, 100.0f});
}

bool checkSpo2(float spo2) {
  return checkVital("Oxygen Saturation", spo2, {90.0f, 100.0f});
}

// Public API to check all vitals, combining individual checks
bool vitalsOk(float temperature, float pulseRate, float spo2) {
  return checkTemperature(temperature) && checkPulseRate(pulseRate) && checkSpo2(spo2);
}
