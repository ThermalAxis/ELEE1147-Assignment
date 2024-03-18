#include "statistics_functions.h"
#include "telemetry_functions.h"
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

int statisticsFunctions(TelemetryData *telemetryArray, int arraySize) {
  int statisticsChoice;
  system("cls");
  printf("==== Statistics for telemetry data ====\n");
  printf("1 - Statistics of all data\n");
  printf("2 - Statistics by Location\n");
  printf("3 - Statistics by Sensor ID\n");
  printf("4 - Statistics by Time and Location\n");
  printf("5 - Main menu\n");

  printf("\nEnter your choice (1-5): ");

  scanf_s("%d", &statisticsChoice);

  switch (statisticsChoice) {
  default:
    printf("Invalid selection, returning to main menu.");
    return;
  case 1:
    allStats(telemetryArray, arraySize);
    printf("\nPress any key to return to main menu...");
    system("pause>nul");
    return 0;
  case 2:
    char locationName[34];
    printf("Enter the Location to filter statistics: ");
    while (getchar() != '\n')
      ;
    // get location name from user
    scanf_s("%33[^\n]", locationName,
            (unsigned)(sizeof(locationName) / sizeof(locationName[0])));
    system("cls");
    locationStats(
        telemetryArray, arraySize,
        locationName); // call location stats functions with location argument
    printf("\nPress any key to return to main menu...");
    system("pause>nul");
    return 0;
  case 3:
    sensorIDStats(telemetryArray, arraySize); // call sensorID stats function
    printf("\nPress any key to return to main menu...");
    system("pause>nul");
    return 0;
  case 4:
    locationTimeStats(telemetryArray,
                      arraySize); // call locationTime stats function
    printf("\nPress any key to return to main menu...");
    system("pause>nul");
    return 0;
  case 5:
    return 0;
  }
}

void allStats(TelemetryData *telemetryArray, int arraySize) {

  // define locations
  char locations[5][34] = {{"Casey Station"},
                           {"Amundsen-Scott South Pole Station"},
                           {"Rothera Research Station"},
                           {"McMurdo Station"},
                           {"Palmer Station"}};

  // get stats structs for each sensor type
  struct sensorStats windspeedStats =
      getSensorTypeStats(telemetryArray, arraySize, "WindSpeed");
  struct sensorStats pressureStats =
      getSensorTypeStats(telemetryArray, arraySize, "Pressure");
  struct sensorStats temperatureStats =
      getSensorTypeStats(telemetryArray, arraySize, "Temperature");
  struct sensorStats visibilityStats =
      getSensorTypeStats(telemetryArray, arraySize, "Visibility");
  struct sensorStats uvRadiationStats =
      getSensorTypeStats(telemetryArray, arraySize, "UVRadiation");

  system("cls");
  printf("\n==== Statistics for all data ====\n");
  printf("\tWindspeed (km/h) Pressure (hPa)\tTemperature (C)\tVisibility "
         "(m)\tUV Index\n");
  // printf("Total:\t%.1f\t\t %.1f\t%.1f\t%.1f\t%.1f\n", windspeedStats.sum,
  //        pressureStats.sum, temperatureStats.sum, visibilityStats.sum,
  //        uvRadiationStats.sum);
  printf("Mean:\t%.1f\t\t %.1f\t\t%.1f\t\t%.1f\t\t%.1f\n", windspeedStats.mean,
         pressureStats.mean, temperatureStats.mean, visibilityStats.mean,
         uvRadiationStats.mean);
  printf("Stdev:\t%.1f\t\t %.1f\t\t%.1f\t\t%.1f\t\t%.1f\n",
         windspeedStats.STdev, pressureStats.STdev, temperatureStats.STdev,
         visibilityStats.STdev, uvRadiationStats.STdev);

  for (int i = 0; i < 5; i++) {
    locationStats(telemetryArray, arraySize,
                  locations[i]); // cycle through locations
  }
}

void locationStats(TelemetryData *telemetryArray, int arraySize,
                   char *locationName) {

  // get stats structs for location passes into the function
  struct sensorStats windspeedStats =
      getLocationStats(telemetryArray, arraySize, "WindSpeed", locationName);
  struct sensorStats pressureStats =
      getLocationStats(telemetryArray, arraySize, "Pressure", locationName);
  struct sensorStats temperatureStats =
      getLocationStats(telemetryArray, arraySize, "Temperature", locationName);
  struct sensorStats visibilityStats =
      getLocationStats(telemetryArray, arraySize, "Visibility", locationName);
  struct sensorStats uvRadiationStats =
      getLocationStats(telemetryArray, arraySize, "UVRadiation", locationName);

  // system("cls");
  printf("\n==== Statistics for %s ====", locationName);
  printf("\n\tWindspeed (km/h) Pressure (hPa)\tTemperature (C)\tVisibility "
         "(m)\tUV Index\n");
  // printf("Total:\t%.1f\t\t %.1f\t%.1f\t\t%.1f\t\t%.1f\n", windspeedStats.sum,
  //        pressureStats.sum, temperatureStats.sum, visibilityStats.sum,
  //        uvRadiationStats.sum);
  printf("Mean:\t%.1f\t\t %.1f\t\t%.1f\t\t%.1f\t\t%.1f\n", windspeedStats.mean,
         pressureStats.mean, temperatureStats.mean, visibilityStats.mean,
         uvRadiationStats.mean);
  printf("Stdev:\t%.1f\t\t %.1f\t\t%.1f\t\t%.1f\t\t%.1f\n",
         windspeedStats.STdev, pressureStats.STdev, temperatureStats.STdev,
         visibilityStats.STdev, uvRadiationStats.STdev);
}

void sensorIDStats(TelemetryData *telemetryArray, int arraySize) {
  char sensorID[10];
  char sensorType[20];
  printf("Enter the Sensor ID to filter statistics: ");
  scanf_s("%9s", sensorID, (unsigned)(sizeof(sensorID) / sizeof(sensorID[0])));
  // get sensor ID from user
  struct sensorStats sensorIDStats =
      getSensorIDStats(telemetryArray, arraySize, sensorID);

  // int count = 0;
  for (int i = 0; i < arraySize; ++i) {
    if (strcmp(telemetryArray[i].sensorID, sensorID) == 0) {
      // count++;
      strcpy(sensorType, telemetryArray[i].sensorType);
      break;
    }
  }

  // printf("Count is %d", count);

  system("cls");
  printf("==== Statistics for %s ====\n", sensorID);
  printf("\t%s\n", sensorType);
  // printf("Total:\t%.1f\n", sensorIDStats.sum);
  printf("Mean:\t%.1f\n", sensorIDStats.mean);
  printf("Stdev\t%.1f\n", sensorIDStats.STdev);
}

void locationTimeStats(TelemetryData *telemetryArray, int arraySize) {
  char locationName[34];

  printf("Enter the Location to filter statistics: ");
  while (getchar() != '\n')
    ;
  scanf_s("%33[^\n]", locationName,
          (unsigned)(sizeof(locationName) / sizeof(locationName[0])));

  // define time structures & input strings
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

  // printf("start epoch is: %ld\nend epoch is: %ld\n", startTimeEpoch,
  // endTimeEpoch);

  struct sensorStats windspeedStats =
      getLocationTimeStats(telemetryArray, arraySize, "WindSpeed", locationName,
                           startTimeEpoch, endTimeEpoch);
  struct sensorStats pressureStats =
      getLocationTimeStats(telemetryArray, arraySize, "Pressure", locationName,
                           startTimeEpoch, endTimeEpoch);
  struct sensorStats temperatureStats =
      getLocationTimeStats(telemetryArray, arraySize, "Temperature",
                           locationName, startTimeEpoch, endTimeEpoch);
  struct sensorStats visibilityStats =
      getLocationTimeStats(telemetryArray, arraySize, "Visibility",
                           locationName, startTimeEpoch, endTimeEpoch);
  struct sensorStats uvRadiationStats =
      getLocationTimeStats(telemetryArray, arraySize, "UVRadiation",
                           locationName, startTimeEpoch, endTimeEpoch);

  system("cls");
  printf("\n==== Statistics for %s between %s & %s ====", locationName,
         startTime, endTime);
  printf("\n\tWindspeed (km/h) Pressure (hPa)\tTemperature (C)\tVisibility "
         "(m)\tUV Index\n");
  // printf("Total:\t%.1f\t\t %.1f\t%.1f\t\t%.1f\t\t%.1f\n", windspeedStats.sum,
  //        pressureStats.sum, temperatureStats.sum, visibilityStats.sum,
  //        uvRadiationStats.sum);
  printf("Mean:\t%.1f\t\t %.1f\t\t%.1f\t\t%.1f\t\t%.1f\n", windspeedStats.mean,
         pressureStats.mean, temperatureStats.mean, visibilityStats.mean,
         uvRadiationStats.mean);
  printf("Stdev:\t%.1f\t\t %.1f\t\t%.1f\t\t%.1f\t\t%.1f\n",
         windspeedStats.STdev, pressureStats.STdev, temperatureStats.STdev,
         visibilityStats.STdev, uvRadiationStats.STdev);
}

struct sensorStats getLocationStats(TelemetryData *telemetryArray,
                                    int arraySize, char *sensorType,
                                    char *locationName) {
  struct sensorStats stats;
  double stdev = 0;
  stats.sum = 0;
  stats.count = 0;
  stats.STdev = 0;

  for (int i = 0; i < arraySize; ++i) {
    if (strcmp(telemetryArray[i].sensorType, sensorType) == 0 &&
        strcmp(telemetryArray[i].location, locationName) == 0) {
      stats.sum += telemetryArray[i].measurement;
      stats.count++;
    }
  }

  stats.mean = stats.sum / stats.count;

  for (int i = 0; i < arraySize; i++) {
    if (strcmp(telemetryArray[i].sensorType, sensorType) == 0 &&
        strcmp(telemetryArray[i].location, locationName) == 0) {
      stdev += pow(telemetryArray[i].measurement - stats.mean, 2);
    }
  }
  stats.STdev = sqrt(stdev / stats.count);

  return stats;
}

struct sensorStats getLocationTimeStats(TelemetryData *telemetryArray,
                                        int arraySize, char *sensorType,
                                        char *locationName,
                                        time_t startTimeEpoch,
                                        time_t endTimeEpoch) {
  struct sensorStats stats;
  double stdev = 0;
  stats.sum = 0;
  stats.count = 0;
  stats.STdev = 0;

  for (int i = 0; i < arraySize; ++i) {
    if (strcmp(telemetryArray[i].sensorType, sensorType) == 0 &&
        strcmp(telemetryArray[i].location, locationName) == 0 &&
        convertTimestamp(telemetryArray[i].timestamp) >= startTimeEpoch &&
        convertTimestamp(telemetryArray[i].timestamp) <= endTimeEpoch) {
      stats.sum += telemetryArray[i].measurement;
      stats.count++;
    }
  }

  stats.mean = stats.sum / stats.count;

  for (int i = 0; i < arraySize; i++) {
    if (strcmp(telemetryArray[i].sensorType, sensorType) == 0 &&
        strcmp(telemetryArray[i].location, locationName) == 0 &&
        convertTimestamp(telemetryArray[i].timestamp) >= startTimeEpoch &&
        convertTimestamp(telemetryArray[i].timestamp) <= endTimeEpoch) {
      stdev += pow(telemetryArray[i].measurement - stats.mean, 2);
    }
  }
  stats.STdev = sqrt(stdev / stats.count);

  return stats;
}

struct sensorStats getSensorTypeStats(TelemetryData *telemetryArray,
                                      int arraySize, char *sensorType) {
  struct sensorStats stats;
  double stdev = 0;
  stats.sum = 0;
  stats.count = 0;
  stats.STdev = 0;

  for (int i = 0; i < arraySize; ++i) {
    if (strcmp(telemetryArray[i].sensorType, sensorType) == 0) {
      stats.sum += telemetryArray[i].measurement;
      stats.count++;
    }
  }

  stats.mean = stats.sum / stats.count;

  for (int i = 0; i < arraySize; i++) {
    if (strcmp(telemetryArray[i].sensorType, sensorType) == 0) {
      stdev += pow(telemetryArray[i].measurement - stats.mean, 2);
    }
  }
  stats.STdev = sqrt(stdev / stats.count);

  return stats;
}

struct sensorStats getSensorIDStats(TelemetryData *telemetryArray,
                                    int arraySize, char *sensorID) {
  struct sensorStats stats;
  double stdev = 0;
  stats.sum = 0;
  stats.count = 0;
  stats.STdev = 0;

  for (int i = 0; i < arraySize; ++i) {
    if (strcmp(telemetryArray[i].sensorID, sensorID) == 0) {
      stats.sum += telemetryArray[i].measurement;
      stats.count++;
    }
  }

  stats.mean = stats.sum / stats.count;

  for (int i = 0; i < arraySize; i++) {
    if (strcmp(telemetryArray[i].sensorID, sensorID) == 0) {
      stdev += pow(telemetryArray[i].measurement - stats.mean, 2);
    }
  }
  stats.STdev = sqrt(stdev / stats.count);

  return stats;
}

double meanLocationNameTime(TelemetryData *telemetryArray, int arraySize,
                            char *sensorType, char *locationName,
                            time_t startOffset) {
  double total = 0;
  int count = 0;
  for (int i = 0; i < arraySize; ++i) {
    if (strcmp(telemetryArray[i].sensorType, sensorType) == 0 &&
        strcmp(telemetryArray[i].location, locationName) == 0 &&
        convertTimestamp(telemetryArray[i].timestamp) >= startOffset &&
        convertTimestamp(telemetryArray[i].timestamp) <=
            (startOffset + (3600 * 6) - 1)) {
      total += telemetryArray[i].measurement;
      count++;
    }
  }
  // printf("Mean at %s for %s between %ld and %ld is %d", locationName,
  // sensorType, startOffset, endOffset, total / count);
  return total / count;
}