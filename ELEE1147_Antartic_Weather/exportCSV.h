#pragma once
#ifndef EXPORT_CSV_H
#define EXPORT_CSV_H

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "json_parser.h" // YOU CAN ADD OTHER HEADERS UNDERNEATH OR ABOVE

int exportCSV(TelemetryData *telemetryArray, int arraySize);

int exportAll(TelemetryData *telemetryArray, int arraySize);
int exportLocation(TelemetryData *telemetryArray, int arraySize,
                   char *locationName);
int exportSensorType(TelemetryData *telemetryArray, int arraySize,
                     char *sensorType);
int exportSensorID(TelemetryData *telemetryArray, int arraySize,
                   char *sensorID);

#endif