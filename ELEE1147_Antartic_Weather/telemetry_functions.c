#include "telemetry_functions.h"
#include <stdio.h>
#include <string.h>

#pragma region // DO NOT TOUCH
void displayAllData(TelemetryData *telemetryArray, int arraySize) {
  printf("All Telemetry Data:\n");
  for (int i = 0; i < arraySize; ++i) {
    printf("SensorID: %s, SensorType: %s, Location: %s, Measurement: %.2f, "
           "Status: %s\n",
           telemetryArray[i].sensorID, telemetryArray[i].sensorType,
           telemetryArray[i].location, telemetryArray[i].measurement,
           telemetryArray[i].status);
  }
  printf("\n\n\nArraySize: %i\n\n", arraySize);
}

void filterBySensorType(TelemetryData *telemetryArray, int arraySize) {
  char sensorType[20];
  printf("Enter the sensor type to filter: ");

#if (_MSC_VER > 1600)
  scanf_s("%19s", sensorType,
          (unsigned)(sizeof(sensorType) / sizeof(sensorType[0])));
#else
  scanf("%19s", sensorType);
#endif

  printf("Telemetry Data for Sensor Type '%s':\n", sensorType);
  for (int i = 0; i < arraySize; ++i) {
    if (strcmp(telemetryArray[i].sensorType, sensorType) == 0) {
      printf("SensorID: %s, SensorType: %s, Location: %s, Measurement: %.2f, "
             "Status: %s\n",
             telemetryArray[i].sensorID, telemetryArray[i].sensorType,
             telemetryArray[i].location, telemetryArray[i].measurement,
             telemetryArray[i].status);
    }
  }
  printf("\n\n\nArraySize: %i\n\n", arraySize);
}

#pragma endregion // END OF DO NOT TOUCH

// YOUR CODE BELOW THIS LINE

void filterBySensorID(TelemetryData *telemetryArray, int arraySize) {
  char sensorID[10];
  printf("Enter the Sensor ID to filter: ");

#if (_MSC_VER > 1600)
  scanf_s("%9s", sensorID, (unsigned)(sizeof(sensorID) / sizeof(sensorID[0])));
#else
  scanf("%9s", sensorID);
#endif

  printf("Telemetry Data for Sensor ID '%s':\n", sensorID);
  for (int i = 0; i < arraySize; ++i) {
    if (strcmp(telemetryArray[i].sensorID, sensorID) == 0) {
      printf("SensorID: %s, SensorType: %s, Location: %s, Measurement: %.2f, "
             "Status: %s\n",
             telemetryArray[i].sensorID, telemetryArray[i].sensorType,
             telemetryArray[i].location, telemetryArray[i].measurement,
             telemetryArray[i].status);
    }
  }
  // printf("\n\n\nArraySize: %i\n\n", arraySize);
}

void filterByLocation(TelemetryData *telemetryArray, int arraySize) {
  char locationName[34];
  printf("Enter the Location to filter: ");

#if (_MSC_VER > 1600)
  while (getchar() != '\n')
    ; // clear previous carriage return
  scanf_s("%33[^\n]", locationName,
          (unsigned)(sizeof(locationName) / sizeof(locationName[0])));
#else
  scanf("%33[^\n]", locationName);
#endif

  printf("Telemetry Data for Location '%s':\n", locationName);
  for (int i = 0; i < arraySize; ++i) {
    if (strcmp(telemetryArray[i].location, locationName) == 0) {
      printf("Timestamp: %s, SensorID: %s, SensorType: %s, Location: %s, "
             "Measurement: %.2f, "
             "Status: %s\n",
             telemetryArray[i].timestamp, telemetryArray[i].sensorID,
             telemetryArray[i].sensorType, telemetryArray[i].location,
             telemetryArray[i].measurement, telemetryArray[i].status);
    }
  }
}
