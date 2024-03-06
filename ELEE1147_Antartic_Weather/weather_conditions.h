#pragma once
#ifndef WEATHER_CONDITIONS_H
#define WEATHER_CONDITIONS_H
#define _CRT_SECURE_NO_WARNINGS

#include "json_parser.h" // YOU CAN ADD OTHER HEADERS UNDERNEATH OR ABOVE

void weatherConditions(TelemetryData *telemetryArray, int arraySize);

void allCond(TelemetryData* telemetryArray, int arraySize);

void getLocationCond(TelemetryData* telemetryArray, int arraySize, char* locationName);
char* getWeatherConditions(double sensorPressure, double sensorTemperature, double sensorWindSpeed, double sensorVisibility, double sensorUVRadiation);

#endif