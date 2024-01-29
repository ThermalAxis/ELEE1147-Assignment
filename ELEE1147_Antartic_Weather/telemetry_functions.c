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
