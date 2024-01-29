#pragma once
#pragma region // DO NOT TOUCH
#ifndef TELEMETRY_FUNCTIONS_H
#define TELEMETRY_FUNCTIONS_H

#include "json_parser.h" // YOU CAN ADD OTHER HEADERS UNDERNEATH OR ABOVE

/**
 * @file
 * @brief Functions to display and filter telemetry data.
 */

/**
 * @brief Display all telemetry data.
 *
 * This function prints all telemetry data to the console.
 *
 * @param telemetryArray An array of TelemetryData structures.
 * @param arraySize The size of the telemetryArray.
 */
void displayAllData(TelemetryData *telemetryArray, int arraySize);

/**
 * @brief Filter telemetry data by sensor type.
 *
 * This function prompts the user to enter a sensor type and
 * then prints telemetry data for the specified sensor type.
 *
 * @param telemetryArray An array of TelemetryData structures.
 * @param arraySize The size of the telemetryArray.
 */
void filterBySensorType(TelemetryData *telemetryArray, int arraySize);

#pragma endregion // DO NOT TOUCH

// YOUR CODE BELOW THIS LINE

#endif // TELEMETRY_FUNCTIONS_H