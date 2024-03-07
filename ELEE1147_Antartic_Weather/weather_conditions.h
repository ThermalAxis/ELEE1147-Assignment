#pragma once
#ifndef WEATHER_CONDITIONS_H
#define WEATHER_CONDITIONS_H
#define _CRT_SECURE_NO_WARNINGS

#include "json_parser.h" // YOU CAN ADD OTHER HEADERS UNDERNEATH OR ABOVE

void weatherConditions(TelemetryData *telemetryArray, int arraySize);

void allCond(TelemetryData *telemetryArray, int arraySize);
void locationCond(TelemetryData *telemetryArray, int arraySize);

void getLocationCondTime(TelemetryData *telemetryArray, int arraySize,
                         char *locationName, time_t startOffset);

void hourlyConditions(TelemetryData *telemetryArray, int arraySize,
                      char *location, const time_t startTimeEpoch,
                      const time_t endTimeEpoch);

char *getWeatherConditions(double sensorPressure, double sensorTemperature,
                           double sensorWindSpeed, double sensorVisibility,
                           double sensorUVRadiation);

void timeframeLocationConditions(TelemetryData *telemetryArray, int arraySize);

#endif