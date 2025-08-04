#include "./monitor.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <string>

using std::cout;
using std::flush;
using std::string;
using std::this_thread::sleep_for;
using std::chrono::seconds;

void blinkingAlert() {
  for (int i = 0; i < 6; ++i) {
    cout << "\r* " << flush;
    this_thread::sleep_for(seconds(1));
    cout << "\r *" << flush;
    this_thread::sleep_for(seconds(1));
  }
}

VitalStatus evaluateVital(float value, const VitalLimits& limits) {
  if (value < limits.lower) return VITAL_LOW;
  if (value > limits.upper) return VITAL_HIGH;
  return VITAL_OK;
}

bool checkVital(const string& name, float value, const VitalLimits& limits) {
  VitalStatus status = evaluateVital(value, limits);

  if (status == VITAL_OK) return true;

  const char* messages[] = {
    "",                 // VITAL_OK
    " is too low!\n",   // VITAL_LOW
    " is too high!\n"   // VITAL_HIGH
  };

  cout << name << messages[status];
  blinkingAlert();
  return false;
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
