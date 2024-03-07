#pragma once
#ifndef STATISTICS_FUNCTIONS_H
#define STATISTICS_FUNCTIONS_H
#define _CRT_SECURE_NO_WARNINGS

#include "json_parser.h" // YOU CAN ADD OTHER HEADERS UNDERNEATH OR ABOVE

int statisticsFunctions(TelemetryData *telemetryArray, int arraySize);

void allStats(TelemetryData *telemetryArray, int arraySize);
void locationStats(TelemetryData *telemetryArray, int arraySize);
void sensorIDStats(TelemetryData *telemetryArray, int arraySize);

double meanLocationName(TelemetryData *telemetryArray, int arraySize,
                        char *sensorType, char *locationName);
double meanLocationNameTime(TelemetryData* telemetryArray, int arraySize,
    char* sensorType, char* locationName, time_t startOffset);

double sumSensorType(TelemetryData *telemetryArray, int arraySize,
                     char *sensorType);
int countSensorType(TelemetryData *telemetryArray, int arraySize,
                    char *sensorType);
double stdevSensorType(TelemetryData *telemetryArray, int arraySize,
                       char *sensorType);

double sumLocationName(TelemetryData *telemetryArray, int arraySize,
                       char *sensorType, char *locationName);
int countLocationName(TelemetryData *telemetryArray, int arraySize,
                      char *sensorType, char *locationName);
double stdevLocationName(TelemetryData *telemetryArray, int arraySize,
                         char *sensorType, char *locationName);

double sumSensorID(TelemetryData *telemetryArray, int arraySize,
                   char *sensorID);
int countSensorID(TelemetryData *telemetryArray, int arraySize, char *sensorID);
double stdevSensorID(TelemetryData *telemetryArray, int arraySize,
                     char *sensorType);

#endif