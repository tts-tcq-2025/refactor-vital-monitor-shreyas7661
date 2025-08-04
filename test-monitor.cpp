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
