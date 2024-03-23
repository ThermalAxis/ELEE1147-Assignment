#pragma once
#ifndef STATISTICS_FUNCTIONS_H
#define STATISTICS_FUNCTIONS_H
#define _CRT_SECURE_NO_WARNINGS

#include "json_parser.h" // YOU CAN ADD OTHER HEADERS UNDERNEATH OR ABOVE

struct sensorStats {
  double sum;
  int count;
  double mean;
  double STdev;
  double min;
  double max;
  double range;
};

int statisticsFunctions(TelemetryData *telemetryArray, int arraySize);

void allStats(TelemetryData *telemetryArray, int arraySize);
void locationStats(TelemetryData *telemetryArray, int arraySize,
                   char *locationName);
void sensorIDStats(TelemetryData *telemetryArray, int arraySize);

double meanLocationNameTime(TelemetryData *telemetryArray, int arraySize,
                            char *sensorType, char *locationName,
                            time_t startOffset);

struct sensorStats getSensorTypeStats(TelemetryData *telemetryArray,
                                      int arraySize, char *sensorType);

void locationTimeStats(TelemetryData *telemetryArray, int arraySize);

struct sensorStats getLocationStats(TelemetryData *telemetryArray,
                                    int arraySize, char *sensorType,
                                    char *locationName);

struct sensorStats getLocationTimeStats(TelemetryData *telemetryArray,
                                        int arraySize, char *sensorType,
                                        char *locationName,
                                        time_t startTimeEpoch,
                                        time_t endTimeEpoch);

struct sensorStats getSensorIDStats(TelemetryData *telemetryArray,
                                    int arraySize, char *sensorID);

#endif