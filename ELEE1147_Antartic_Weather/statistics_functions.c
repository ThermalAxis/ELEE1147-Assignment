#include "statistics_functions.h"
#include "telemetry_functions.h"
#include <math.h>
#include <stdio.h>
#include <string.h>

int statisticsFunctions(TelemetryData *telemetryArray, int arraySize) {
  int statisticsChoice;
  system("cls");
  printf("==== Statistics for telemetry data ====\n");
  printf("1 - Statistics of all data\n");
  printf("2 - Statistics by Location\n");
  printf("3 - Statistics by Sensor ID\n");
  printf("4 - Main menu\n");

  printf("\nEnter your choice (1-4): ");

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
    scanf_s("%33[^\n]", locationName,
            (unsigned)(sizeof(locationName) / sizeof(locationName[0])));
    system("cls");
    locationStats(telemetryArray, arraySize, locationName);
    printf("\nPress any key to return to main menu...");
    system("pause>nul");
    return 0;
  case 3:
    sensorIDStats(telemetryArray, arraySize);
    printf("\nPress any key to return to main menu...");
    system("pause>nul");
    return 0;
  case 4:
    return 0;
  }
}

void allStats(TelemetryData *telemetryArray, int arraySize) {

  char locations[5][34] = {{"Casey Station"},
                           {"Amundsen-Scott South Pole Station"},
                           {"Rothera Research Station"},
                           {"McMurdo Station"},
                           {"Palmer Station"}};

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
  printf("Stdev\t%.1f\t\t %.1f\t\t%.1f\t\t%.1f\t\t%.1f\n", windspeedStats.STdev,
         pressureStats.STdev, temperatureStats.STdev, visibilityStats.STdev,
         uvRadiationStats.STdev);

  for (int i = 0; i < 5; i++) {
    locationStats(telemetryArray, arraySize, locations[i]);
  }
}

void locationStats(TelemetryData *telemetryArray, int arraySize,
                   char *locationName) {

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
  printf("Stdev\t%.1f\t\t %.1f\t\t%.1f\t\t%.1f\t\t%.1f\n", windspeedStats.STdev,
         pressureStats.STdev, temperatureStats.STdev, visibilityStats.STdev,
         uvRadiationStats.STdev);
}

void sensorIDStats(TelemetryData *telemetryArray, int arraySize) {
  char sensorID[10];
  char sensorType[20];
  printf("Enter the Sensor ID to filter statistics: ");
  scanf_s("%9s", sensorID, (unsigned)(sizeof(sensorID) / sizeof(sensorID[0])));

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