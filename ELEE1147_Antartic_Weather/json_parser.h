#pragma region // DO NOT TOUCH
#ifndef JSON_PARSER_H
#define JSON_PARSER_H

#include "cJSON.h"
#include "telemetry_struct.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @file
 * @brief Functions to parse telemetry data from a JSON file.
 */

/**
 * @brief Parse telemetry data from a JSON file.
 *
 * This function reads telemetry data from a JSON file, parses it using cJSON,
 * and populates an array of TelemetryData structures.
 *
 * @param filename The name of the JSON file to parse.
 * @param telemetryArray A pointer to the array of TelemetryData structures
 * (output).
 * @param arraySize A pointer to the size of the telemetryArray (output).
 */
void parseTelemetryDataFromFile(const char *filename,
                                TelemetryData **telemetryArray, int *arraySize);

#endif            // JSON_PARSER_H
#pragma endregion // END OF DO NOT TOUCH