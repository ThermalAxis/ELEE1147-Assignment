#pragma once
#ifndef EXPORT_CSV_H
#define EXPORT_CSV_H

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "json_parser.h" // YOU CAN ADD OTHER HEADERS UNDERNEATH OR ABOVE

void exportCSV(TelemetryData *telemetryArray, int arraySize);

#endif