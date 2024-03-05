#pragma once
#ifndef STATISTICS_FUNCTIONS_H
#define STATISTICS_FUNCTIONS_H

#include "json_parser.h" // YOU CAN ADD OTHER HEADERS UNDERNEATH OR ABOVE

int statisticsFunctions(TelemetryData* telemetryArray, int arraySize);

double sumSensorType(TelemetryData* telemetryArray, int arraySize, char *sensorType);
int countSensorType(TelemetryData* telemetryArray, int arraySize, char* sensorType);

#endif