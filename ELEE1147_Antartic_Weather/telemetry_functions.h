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

/**
 * @brief Filter telemetry data by sensor ID.
 *
 * This function prompts the user to enter a sensor ID and
 * then prints telemetry data for the specified sensor ID.
 *
 * @param telemetryArray An array of TelemetryData structures.
 * @param arraySize The size of the telemetryArray.
 */
void filterBySensorID(TelemetryData *telemetryArray, int arraySize);

/**
 * @brief Filter telemetry data by location name.
 *
 * This function prompts the user to enter a location name and
 * then prints telemetry data for the specified location.
 *
 * @param telemetryArray An array of TelemetryData structures.
 * @param arraySize The size of the telemetryArray.
 */
void filterByLocation(TelemetryData *telemetryArray, int arraySize);

void filterByTimeStamp(TelemetryData *telemetryArray,
                       int arraySize); // this doesn't work atm

time_t convertTimestamp(char *timestamp);

time_t getStartTimestamp(TelemetryData *telemetryArray, int arraySize);
time_t getEndTimestamp(TelemetryData *telemetryArray, int arraySize);

#endif // TELEMETRY_FUNCTIONS_H