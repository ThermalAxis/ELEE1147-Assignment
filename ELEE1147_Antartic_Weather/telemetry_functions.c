#include "telemetry_functions.h"
#include <stdio.h>
#include <string.h>
#include <time.h>

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

int filterMenu(TelemetryData *telemetryArray, int arraySize) {

  int filterChoice;
  system("cls");
  printf("==== Display telemetry data ====\n");
  printf("1 - Display All Data\n");
  printf("2 - Filter data by Location\n");
  printf("3 - Filter by Sensor Type\n");
  printf("4 - Filter by Sensor ID\n");
  printf("5 - Filter by Time\n");
  printf("6 - Main menu\n");

  printf("\nEnter your choice (1-6): ");

  scanf_s("%d", &filterChoice);

  switch (filterChoice) {
  default:
    printf("Invalid selection, returning to main menu.");
    system("timeout /T 3>nul");
    return 0;
  case 1:
    displayAllData(telemetryArray, arraySize);
    printf("Press any key to return to main menu...");
    system("pause>nul");
    return 0;
  case 2:
    filterByLocation(telemetryArray, arraySize);
    printf("\nPress any key to return to main menu...");
    system("pause>nul");
    return 0;
  case 3:
    filterBySensorType(telemetryArray, arraySize);
    printf("Press any key to return to main menu...");
    system("pause>nul");
    return 0;
  case 4:
    filterBySensorID(telemetryArray, arraySize);
    printf("\nPress any key to return to main menu...");
    system("pause>nul");
    return 0;
  case 5:
    filterByTime(telemetryArray, arraySize);
    return 0;
  case 6:
    return 0;
  }
}

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

int filterByTime(TelemetryData *telemetryArray, int arraySize) {

  struct tm startTimeSelect;
  struct tm endTimeSelect;
  time_t startTimeEpoch;
  time_t endTimeEpoch;
  char startTime[20];
  char endTime[20];

  time_t startTimeDataEpoch = getStartTimestamp(telemetryArray, arraySize);
  struct tm startTimeStampData;
  time_t endTimeDataEpoch = getEndTimestamp(telemetryArray, arraySize);
  struct tm endTimeStampData;
  localtime_s(&startTimeStampData, &startTimeDataEpoch);
  localtime_s(&endTimeStampData, &endTimeDataEpoch);

  printf("Enter the start timestamp in the format "
         "'YYYY-MM-DDTHH:MM:SS' between %04d-%02d-%02dT%02d:%02d:%02dZ & "
         "%04d-%02d-%02dT%02d:%02d:%02dZ\n",
         startTimeStampData.tm_year += 1900, startTimeStampData.tm_mon += 1,
         startTimeStampData.tm_mday, startTimeStampData.tm_hour,
         startTimeStampData.tm_min, startTimeStampData.tm_sec,
         endTimeStampData.tm_year += 1900, endTimeStampData.tm_mon += 1,
         endTimeStampData.tm_mday, endTimeStampData.tm_hour,
         endTimeStampData.tm_min, endTimeStampData.tm_sec);

  printf("Start time: ");
  scanf_s("%s", startTime, sizeof(startTime));

  printf("Enter the end timestamp to filter in the format "
         "'YYYY-MM-DDTHH:MM:SS'\n");
  printf("End time: ");
  scanf_s("%s", endTime, sizeof(endTime));

  if (convertTimestamp(endTime) < startTimeDataEpoch ||
      convertTimestamp(startTime) > endTimeDataEpoch) {
    printf("No data available for the selected timeframe!\nReturning to the "
           "main menu.");
    system("timeout /T 3");
    return -1;
  }

  sscanf_s(startTime, "%d-%d-%dT%d:%d:%d", &startTimeSelect.tm_year,
           &startTimeSelect.tm_mon, &startTimeSelect.tm_mday,
           &startTimeSelect.tm_hour, &startTimeSelect.tm_min,
           &startTimeSelect.tm_sec);
  sscanf_s(endTime, "%d-%d-%dT%d:%d:%d", &endTimeSelect.tm_year,
           &endTimeSelect.tm_mon, &endTimeSelect.tm_mday,
           &endTimeSelect.tm_hour, &endTimeSelect.tm_min,
           &endTimeSelect.tm_sec);

  startTimeSelect.tm_year -= 1900;
  startTimeSelect.tm_mon -= 1;

  endTimeSelect.tm_year -= 1900;
  endTimeSelect.tm_mon -= 1;

  startTimeEpoch = mktime(&startTimeSelect);
  endTimeEpoch = mktime(&endTimeSelect);

  printf("start epoch is: %ld\nend epoch is: %ld", startTimeEpoch,
         endTimeEpoch);

  printf("==== Telemetry Data for Time range '%s' to '%s' ====\n\n", startTime,
         endTime);

  for (int i = 0; i < arraySize; ++i) {
    if (convertTimestamp(telemetryArray[i].timestamp) >= startTimeEpoch &&
        convertTimestamp(telemetryArray[i].timestamp) <= endTimeEpoch) {
      printf("Timestamp: %s, SensorID: %s, SensorType: %s, Location: %s,"
             "Measurement: %.2f, "
             "Status: %s\n",
             telemetryArray[i].timestamp, telemetryArray[i].sensorID,
             telemetryArray[i].sensorType, telemetryArray[i].location,
             telemetryArray[i].measurement, telemetryArray[i].status);
    }
  }
  printf("\nPress any key to return to main menu...");
  system("pause>nul");
  return 0;
}

time_t convertTimestamp(char *timestamp) {
  struct tm datetime;
  // printf("timestamp is %s\n", timestamp);
  sscanf_s(timestamp, "%d-%d-%dT%d:%d:%d", &datetime.tm_year, &datetime.tm_mon,
           &datetime.tm_mday, &datetime.tm_hour, &datetime.tm_min,
           &datetime.tm_sec);

  datetime.tm_year -= 1900;
  datetime.tm_mon -= 1;

  time_t epoch = mktime(&datetime);

  return epoch;
}

time_t getStartTimestamp(TelemetryData *telemetryArray, int arraySize) {
  time_t startTimeEpoch = convertTimestamp(telemetryArray[0].timestamp);

  // find earliest timestamp
  for (int i = 0; i < arraySize; i++) {
    time_t currentEpoch = convertTimestamp(telemetryArray[i].timestamp);
    if (currentEpoch < startTimeEpoch) {
      startTimeEpoch = currentEpoch;
    }
  }
  return startTimeEpoch;
}

time_t getEndTimestamp(TelemetryData *telemetryArray, int arraySize) {
  time_t endTimeEpoch = 0;

  // find latest timestamp
  for (int i = 0; i < arraySize; i++) {
    time_t currentEpoch = convertTimestamp(telemetryArray[i].timestamp);
    if (currentEpoch > endTimeEpoch) {
      endTimeEpoch = currentEpoch;
    }
  }
  return endTimeEpoch;
}
