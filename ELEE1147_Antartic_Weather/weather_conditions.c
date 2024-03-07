#include "weather_conditions.h"
#include "statistics_functions.h"
#include "telemetry_functions.h"
#include <stdio.h>
#include <string.h>
#include <time.h>

void weatherConditions(TelemetryData *telemetryArray, int arraySize) {

  int weatherChoice;
  system("cls");
  printf("==== Weather conditions for telemetry data ====\n");
  printf("1 - Weather conditions of all data\n");
  printf("2 - Weather conditions by Location\n");
  printf("3 - Main menu\n");

  printf("\nEnter your choice (1-3): ");

  scanf_s("%d", &weatherChoice);

  switch (weatherChoice) {
  default:
    printf("Invalid selection, returning to main menu.");
    system("timeout /T 3>nul");
    return 0;
  case 1:
    allCond(telemetryArray, arraySize);
    system("timeout /T 30");
    return 0;
  case 2:
    locationCond(telemetryArray, arraySize);
    system("timeout /T 30");
    return 0;
  case 3:
    return 0;
  }
}

void allCond(TelemetryData *telemetryArray, int arraySize) {
  char locations[5][34] = {{"Casey Station"},
                           {"Amundsen-Scott South Pole Station"},
                           {"Rothera Research Station"},
                           {"McMurdo Station"},
                           {"Palmer Station"}};

  time_t startTimeEpoch = convertTimestamp(telemetryArray[0].timestamp);
  time_t endTimeEpoch = 0;

  // find earliest timestamp
  for (int i = 0; i < arraySize; i++) {
    time_t currentEpoch = convertTimestamp(telemetryArray[i].timestamp);

    if (difftime(currentEpoch, startTimeEpoch) < 0) {
      startTimeEpoch = currentEpoch;
    }
  }

  // find latest timestamp
  for (int i = 0; i < arraySize; i++) {
    time_t currentEpoch = convertTimestamp(telemetryArray[i].timestamp);

    if (difftime(currentEpoch, endTimeEpoch) > 0) {
      endTimeEpoch = currentEpoch;
    }
  }

  struct tm startTime;
  localtime_s(&startTime, &startTimeEpoch);
  struct tm startTimeDay = startTime;
  startTimeDay.tm_hour = 00;
  startTimeDay.tm_min = 00;
  startTimeDay.tm_sec = 00;
  time_t startDayEpoch = mktime(&startTimeDay);
  struct tm endTime;
  localtime_s(&endTime, &endTimeEpoch);

  //printf("\nStart epoch: %ld\n", startTimeEpoch);
  //printf("\nStart day epoch: %ld\n", startDayEpoch);
  //printf("\nStart day epoch offset 6: %ld\n", startDayEpochOffset06);
  //printf("\nStart day epoch offset 12: %ld\n", startDayEpochOffset12);
  //printf("\nStart day epoch offset 18: %ld\n", startDayEpochOffset18);
  //printf("\nStart day epoch offset 24: %ld\n", startDayEpochOffset24);

  //printf("End epoch: %ld\n\n", endTimeEpoch);
  //printf("Year: %d\n", endTime.tm_year + 1900);
  //printf("Month: %d\n", endTime.tm_mon + 1);
  //printf("Day: %d\n", endTime.tm_mday);
  //printf("Hour: %d\n", endTime.tm_hour);
  //printf("Minute: %d\n", endTime.tm_min);
  //printf("Second: %d\n", endTime.tm_sec);

  /*
  calculate 6-hourly weather conditions in all data
  convert epoch back to structure
  0000-0559 , 0600-1159 , 1200-1759 , 1800-2359

  each station per day

  */
      for (int i = 0; i < 5; i++) {
          time_t startDayEpochOffset = startDayEpoch;
          time_t endDayEpochOffset = startDayEpochOffset + ((3600 * 6) - 1);
          while (endDayEpochOffset < endTimeEpoch) {
              for (int k = 0; k < 4; k++) {
                  //printf("int j = %d\n", j);
                  getLocationCondTime(telemetryArray, arraySize, locations[i], startDayEpochOffset);
                  startDayEpochOffset = startDayEpochOffset + (3600 * 6);
                  endDayEpochOffset = startDayEpochOffset + ((3600 * 6) - 1);
              }
          }
          printf("\n");
      }
  return;
}

void locationCond(TelemetryData *telemetryArray, int arraySize) {
  char locationName[34];

  printf("Enter the Location to calculate weather conditions: ");
  while (getchar() != '\n')
    ;
  scanf_s("%33[^\n]", locationName,
          (unsigned)(sizeof(locationName) / sizeof(locationName[0])));
  getLocationCond(telemetryArray, arraySize, locationName);
}

void getLocationCond(TelemetryData *telemetryArray, int arraySize,
                     char *locationName) {
  char weatherConditions[10];

  double windspeedMean =
      meanLocationName(telemetryArray, arraySize, "WindSpeed", locationName);
  double pressureMean =
      meanLocationName(telemetryArray, arraySize, "Pressure", locationName);
  double temperatureMean =
      meanLocationName(telemetryArray, arraySize, "Temperature", locationName);
  double visibilityMean =
      meanLocationName(telemetryArray, arraySize, "Visibility", locationName);
  double UVradiationMean =
      meanLocationName(telemetryArray, arraySize, "UVRadiation", locationName);

  strcpy(weatherConditions,
         getWeatherConditions(pressureMean, temperatureMean, windspeedMean,
                              visibilityMean, UVradiationMean));

  printf("Weather conditions at %s are %s\n", locationName, weatherConditions);
}

void getLocationCondTime(TelemetryData* telemetryArray, int arraySize,
    char* locationName, time_t startOffset) {

    char weatherConditions[10];
    struct tm startTime;
    struct tm endTime;

    localtime_s(&startTime, &startOffset);

    time_t endOffset = startOffset + ((3600 * 6) - 1);
    localtime_s(&endTime, &endOffset);

    //printf("location name is: %s, start time is: %ld\n", locationName, startOffset);

    double windspeedMean =
        meanLocationNameTime(telemetryArray, arraySize, "WindSpeed", locationName, startOffset);
    double pressureMean =
        meanLocationNameTime(telemetryArray, arraySize, "Pressure", locationName, startOffset);
    double temperatureMean =
        meanLocationNameTime(telemetryArray, arraySize, "Temperature", locationName, startOffset);
    double visibilityMean =
        meanLocationNameTime(telemetryArray, arraySize, "Visibility", locationName, startOffset);
    double UVradiationMean =
        meanLocationNameTime(telemetryArray, arraySize, "UVRadiation", locationName, startOffset);

    strcpy(weatherConditions,
        getWeatherConditions(pressureMean, temperatureMean, windspeedMean,
            visibilityMean, UVradiationMean));
    printf("Weather conditions at %s are %s between %04d-%02d-%02dT%02d:%02d:%02dZ and %04d-%02d-%02dT%02d:%02d:%02dZ\n", 
        locationName, weatherConditions,
        startTime.tm_year += 1900, startTime.tm_mon += 1, startTime.tm_mday, startTime.tm_hour, startTime.tm_min, startTime.tm_sec,
        endTime.tm_year += 1900, endTime.tm_mon += 1, endTime.tm_mday, endTime.tm_hour, endTime.tm_min, endTime.tm_sec);
}

char *getWeatherConditions(double sensorPressure, double sensorTemperature,
                           double sensorWindSpeed, double sensorVisibility,
                           double sensorUVRadiation) {
  char result[10];
  if (sensorPressure >= 1000 && sensorPressure <= 1000 &&
      sensorTemperature >= -20 && sensorTemperature <= -1 &&
      sensorWindSpeed >= 10 && sensorWindSpeed <= 50 &&
      sensorVisibility >= 5000 && sensorVisibility <= 10000 &&
      sensorUVRadiation >= 7 && sensorUVRadiation <= 10) {
    strcpy(result, "Clear");
    // printf("Clear\n");
  } else if (sensorPressure >= 995 && sensorPressure <= 1015 &&
             sensorTemperature >= -80 && sensorTemperature <= -19 &&
             sensorWindSpeed >= 30 && sensorWindSpeed <= 150 &&
             sensorVisibility >= 300 && sensorVisibility <= 4999 &&
             sensorUVRadiation >= 5 && sensorUVRadiation <= 8) {
    strcpy(result, "Icy Windy");
    // printf("Icy Windy\n");
  } else if (sensorPressure >= 980 && sensorPressure <= 1000 &&
             sensorTemperature >= -20 && sensorTemperature <= -10 &&
             sensorWindSpeed >= 50 && sensorWindSpeed <= 80 &&
             sensorVisibility >= 0 && sensorVisibility <= 100 &&
             sensorUVRadiation >= 0 && sensorUVRadiation <= 1) {
    strcpy(result, "Blizzard");
    // printf("Blizzard\n");
  } else if (sensorPressure >= 800 && sensorPressure <= 970 &&
             sensorTemperature >= -5 && sensorTemperature <= 0 &&
             sensorWindSpeed >= 10 && sensorWindSpeed <= 20 &&
             sensorVisibility >= 0 && sensorVisibility <= 200 &&
             sensorUVRadiation >= 1 && sensorUVRadiation <= 3) {
    strcpy(result, "Snowing");
    // printf("Snowing\n");
  } else {
    strcpy(result, "Unknown");
    // printf("Unknown\n");
  }
  return result;
}

/*
Yes I know that my code is messy and unoptimised.
*/