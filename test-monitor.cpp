#include <gtest/gtest.h>
#include "./monitor.h"

// ---------- VitalsOK tests ----------
TEST(Monitor, AllVitalsWithinRange) {
  ASSERT_TRUE(vitalsOk(98.6, 70, 95));
}

TEST(Monitor, TemperatureTooLow) {
  ASSERT_FALSE(vitalsOk(94.9, 70, 95));
}

TEST(Monitor, TemperatureTooHigh) {
  ASSERT_FALSE(vitalsOk(102.1, 70, 95));
}

TEST(Monitor, PulseRateTooLow) {
  ASSERT_FALSE(vitalsOk(98.6, 59, 95));
}

TEST(Monitor, PulseRateTooHigh) {
  ASSERT_FALSE(vitalsOk(98.6, 101, 95));
}

TEST(Monitor, Spo2TooLow) {
  ASSERT_FALSE(vitalsOk(98.6, 70, 89));
}

// ---------- Warning tests ----------
TEST(Monitor, TemperatureWarningLow) {
  float upper = 102.0f;
  float warningTolerance = 0.015f * upper; // 1.53
  float warningValue = 95.0f + warningTolerance / 2; // Mid warning range low
  ASSERT_TRUE(checkVital("Temperature", warningValue, {95.0f, upper}));
}

TEST(Monitor, TemperatureWarningHigh) {
  float upper = 102.0f;
  float warningTolerance = 0.015f * upper; // 1.53
  float warningValue = upper - warningTolerance / 2; // Mid warning range high
  ASSERT_TRUE(checkVital("Temperature", warningValue, {95.0f, upper}));
}

TEST(Monitor, PulseRateWarningLow) {
  float upper = 100.0f;
  float warningTolerance = 0.015f * upper; // 1.5
  float warningValue = 60.0f + warningTolerance / 2; // Mid warning range low
  ASSERT_TRUE(checkVital("Pulse Rate", warningValue, {60.0f, upper}));
}

TEST(Monitor, PulseRateWarningHigh) {
  float upper = 100.0f;
  float warningTolerance = 0.015f * upper; // 1.5
  float warningValue = upper - warningTolerance / 2; // Mid warning range high
  ASSERT_TRUE(checkVital("Pulse Rate", warningValue, {60.0f, upper}));
}

TEST(Monitor, Spo2WarningLow) {
  float upper = 100.0f;
  float warningTolerance = 0.015f * upper; // 1.5
  float warningValue = 90.0f + warningTolerance / 2; // Mid warning range low
  ASSERT_TRUE(checkVital("Oxygen Saturation", warningValue, {90.0f, upper}));
}

TEST(Monitor, Spo2WarningHigh) {
  float upper = 100.0f;
  float warningTolerance = 0.015f * upper; // 1.5
  float warningValue = upper - warningTolerance / 2; // Mid warning range high
  ASSERT_TRUE(checkVital("Oxygen Saturation", warningValue, {90.0f, upper}));
}

// ---------- Pure function tests ----------
TEST(Evaluator, VitalInRange) {
  VitalLimits limits = {60, 100};
  ASSERT_EQ(evaluateVital(80, limits), VITAL_OK);
}

TEST(Evaluator, VitalTooLow) {
  VitalLimits limits = {60, 100};
  ASSERT_EQ(evaluateVital(50, limits), VITAL_LOW);
}

TEST(Evaluator, VitalTooHigh) {
  VitalLimits limits = {60, 100};
  ASSERT_EQ(evaluateVital(110, limits), VITAL_HIGH);
}

// ---------- Individual Vital Test ----------
TEST(CheckVital, PulseLowTriggersAlert) {
  ASSERT_FALSE(checkVital("Pulse Rate", 55, {60, 100}));
}

TEST(CheckVital, TemperatureWithinRangePasses) {
  ASSERT_TRUE(checkVital("Temperature", 98.6, {95, 102}));
}
