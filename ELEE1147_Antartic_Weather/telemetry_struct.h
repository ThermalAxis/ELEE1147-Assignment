#pragma once
#ifndef TELEMETRY_STRUCT_H
#define TELEMETRY_STRUCT_H

#define MAX_JSON_SIZE 16294 // Adjust this according to your expected JSON size

/**
 * @file
 * @brief Definition of the TelemetryData structure.
 */

/**
 * @struct TelemetryData
 * @brief Represents telemetry data from a sensor.
 *
 * This structure holds information about a sensor's telemetry data,
 * including sensor ID, type, location, timestamp, measurement, and status.
 */
typedef struct {
  char sensorID[10];   ///< Sensor ID, up to 10 characters.
  char sensorType[20]; ///< Type of the sensor, up to 20 characters.
  char location[34];   ///< Location of the sensor, up to 34 characters.
  char timestamp[20]; ///< Timestamp of the telemetry data, up to 20 characters.
  double measurement; ///< Measurement recorded by the sensor.
  char status[10];    ///< Status of the sensor, up to 10 characters.
} TelemetryData;

// YOUR CODE BELOW THIS LINE

#endif // end of TELEMETRY_STRUCT.H