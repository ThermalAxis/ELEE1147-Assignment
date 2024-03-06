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

void filterByTimeStamp(TelemetryData *telemetryArray, int arraySize) {
  struct timestamp {
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
  };

  struct timestamp startTimeStamp;
  struct timestamp endTimeStamp;

  char startTime[20];
  char endTime[20];
  printf("Enter the start timestamp to filter in the format "
         "'YYYY-MM-DDTHH:MM:SSZ'\n");
  printf("Start time: ");
  scanf_s("%s", startTime, sizeof(startTime));


 /* sscanf_s(startTime, "%4d-%2d-%2dT%2d:%2d:%2d", &startTimeStamp.year,
           &startTimeStamp.month, &startTimeStamp.day, &startTimeStamp.hour,
           &startTimeStamp.minute, &startTimeStamp.second);
  sscanf_s(endTime, "%4d-%2d-%2dT%2d:%2d:%2d", &endTimeStamp.year,
           &endTimeStamp.month, &endTimeStamp.day, &endTimeStamp.hour,
           &endTimeStamp.minute, &endTimeStamp.second);*/

  printf("Inut Start Time: %s\n", startTime);
  // printf("End: %s\n", endTime);

  printf("Start timestamp:\n");
  printf(
      "Year: %d \nMonth: %d \nDay: %d \nHour: %d \nMinute: %d \nSecond: %d\n",
      startTimeStamp.year, startTimeStamp.month, startTimeStamp.day,
      startTimeStamp.hour, startTimeStamp.minute, &startTimeStamp.second);

  // printf("Telemetry Data for Time range '%s':\n", locationName);
  // for (int i = 0; i < arraySize; ++i) {
  //     if (strcmp(telemetryArray[i].location, locationName) == 0) {
  //         printf("Timestamp: %s, SensorID: %s, SensorType: %s, Location: %s,
  //         "
  //             "Measurement: %.2f, "
  //             "Status: %s\n",
  //             telemetryArray[i].timestamp, telemetryArray[i].sensorID,
  //             telemetryArray[i].sensorType, telemetryArray[i].location,
  //             telemetryArray[i].measurement, telemetryArray[i].status);
  //     }
  // }

  system("pause");
  return;
}