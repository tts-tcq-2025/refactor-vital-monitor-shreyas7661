#include "./monitor.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <map>
#include <string>
#include <functional>

using namespace std;
using namespace std::chrono;

void blinkingAlert() {
  for (int i = 0; i < 6; ++i) {
    cout << "\r* " << flush;
    this_thread::sleep_for(seconds(1));
    cout << "\r *" << flush;
    this_thread::sleep_for(seconds(1));
  }
}

// Pure logic to check a vital against limits
VitalStatus evaluateVital(float value, const VitalLimits& limits) {
  if (value < limits.lower) return VITAL_LOW;
  if (value > limits.upper) return VITAL_HIGH;
  return VITAL_OK;
}

// Handles a vital: checks it and alerts if out of range
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

// Public interface
bool vitalsOk(float temperature, float pulseRate, float spo2) {
  bool temperatureOk = checkVital("Temperature", temperature, {95.0, 102.0});
  bool pulseRateOk = checkVital("Pulse Rate", pulseRate, {60.0, 100.0});
  bool spo2Ok = checkVital("Oxygen Saturation", spo2, {90.0, 100.0});

  return temperatureOk && pulseRateOk && spo2Ok;
}
