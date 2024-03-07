#include "statistics_functions.h"
#include "telemetry_functions.h"
#include "weather_conditions.h"
#include <stdio.h>
#include <string.h>
#include <time.h>

/*
Yes I know that my code is messy and unoptimised.
*/

void weatherConditions(TelemetryData *telemetryArray, int arraySize) {

  int weatherChoice;
  system("cls");
  printf("==== Weather conditions for telemetry data ====\n");
  printf("1 - Display hourly weather conditions for all locations\n");
  printf("2 - Display hourly weather conditions by location\n");
  // printf("3 - Display weather conditions for a specific timeframe and
  // location\n");
  printf("3 - Main menu\n");

  printf("\nEnter your choice (1-3): ");

  scanf_s("%d", &weatherChoice);

  switch (weatherChoice) {
  default:
    printf("Invalid selection, returning to main menu.");
    system("timeout /T 3>nul");
    return 0;
  case 1:
    system("cls");
    allCond(telemetryArray, arraySize);
    printf("\nPress any key to return to main menu...");
    system("pause>nul");
    return 0;
  case 2:
    system("cls");
    locationCond(telemetryArray, arraySize);
    system("pause>nul");
    return 0;
    /* case 3:
         timeframeLocationConditions(telemetryArray, arraySize);
         system("pause>nul");
       return 0;*/
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

  time_t startTimeEpoch = getStartTimestamp(telemetryArray, arraySize);
  time_t endTimeEpoch = getEndTimestamp(telemetryArray, arraySize);

  struct tm startTime;
  localtime_s(&startTime, &startTimeEpoch);
  struct tm startTimeDay = startTime;
  startTimeDay.tm_hour = 00;
  startTimeDay.tm_min = 00;
  startTimeDay.tm_sec = 00;
  time_t startDayEpoch = mktime(&startTimeDay);
  struct tm endTime;
  localtime_s(&endTime, &endTimeEpoch);

  for (int i = 0; i < 5; i++) {
    hourlyConditions(telemetryArray, arraySize, locations[i], startDayEpoch,
                     endTimeEpoch);
  }

  return;
}

void locationCond(TelemetryData *telemetryArray, int arraySize) {
  char locationName[34];

  printf("Enter the Location to display weather conditions: ");
  while (getchar() != '\n')
    ;
  scanf_s("%33[^\n]", locationName,
          (unsigned)(sizeof(locationName) / sizeof(locationName[0])));
  hourlyConditions(telemetryArray, arraySize, locationName,
                   getStartTimestamp(telemetryArray, arraySize),
                   getEndTimestamp(telemetryArray, arraySize));
}

void timeframeLocationConditions(TelemetryData *telemetryArray, int arraySize) {
  char locationName[34], startTimeStr[20], endTimeStr[20];
  time_t startTimeSelect;
  time_t endTimeSelect;
  printf("Enter the location to display weather conditions: ");
  while (getchar() != '\n')
    ;
  scanf_s("%33[^\n]", locationName,
          (unsigned)(sizeof(locationName) / sizeof(locationName[0])));

  printf("Enter the start timestamp to filter in the format "
         "'YYYY-MM-DDTHH:MM:SSZ'\n");
  printf("Start time: ");
  scanf_s("%s", startTimeStr, sizeof(startTimeStr));
  startTimeSelect = convertTimestamp(startTimeStr);

  printf("Enter the end timestamp to filter in the format "
         "'YYYY-MM-DDTHH:MM:SSZ'\n");
  printf("End time: ");
  scanf_s("%s", endTimeStr, sizeof(endTimeStr));
  endTimeSelect = convertTimestamp(endTimeStr);

  if (endTimeSelect < startTimeSelect) {
    printf("End date cannot be before start date!");
  }

  printf("locationName = %s, startTimeSelect = %ld, endtimeSelect = %ls",
         locationName, startTimeSelect, endTimeSelect);

  hourlyConditions(telemetryArray, arraySize, locationName, startTimeSelect,
                   endTimeSelect);
}

void hourlyConditions(TelemetryData *telemetryArray, int arraySize,
                      char *location, const time_t startTimeEpoch,
                      const time_t endTimeEpoch) {
  printf("\n==== %s ====\n", location);
  time_t startDayEpochOffset = startTimeEpoch;
  time_t endDayEpochOffset = startDayEpochOffset + ((3600 * 1) - 1);
  while (endDayEpochOffset < endTimeEpoch) {
    for (int k = 0; k < 24; k++) {
      // printf("int j = %d\n", j);
      getLocationCondTime(telemetryArray, arraySize, location,
                          startDayEpochOffset);
      startDayEpochOffset = startDayEpochOffset + (3600 * 1);
      endDayEpochOffset = startDayEpochOffset + ((3600 * 1) - 1);
    }
  }
  // printf("\n");
}

void getLocationCondTime(TelemetryData *telemetryArray, int arraySize,
                         char *locationName, time_t startOffset) {

  char weatherConditions[10];
  struct tm startTime;
  struct tm endTime;

  localtime_s(&startTime, &startOffset);

  time_t endOffset = startOffset + ((3600 * 6) - 1);
  localtime_s(&endTime, &endOffset);

  // printf("location name is: %s, start time is: %ld\n", locationName,
  // startOffset);

  double windspeedMean = meanLocationNameTime(
      telemetryArray, arraySize, "WindSpeed", locationName, startOffset);
  double pressureMean = meanLocationNameTime(
      telemetryArray, arraySize, "Pressure", locationName, startOffset);
  double temperatureMean = meanLocationNameTime(
      telemetryArray, arraySize, "Temperature", locationName, startOffset);
  double visibilityMean = meanLocationNameTime(
      telemetryArray, arraySize, "Visibility", locationName, startOffset);
  double UVradiationMean = meanLocationNameTime(
      telemetryArray, arraySize, "UVRadiation", locationName, startOffset);

  strcpy(weatherConditions,
         getWeatherConditions(pressureMean, temperatureMean, windspeedMean,
                              visibilityMean, UVradiationMean));
  printf("%04d-%02d-%02d %02d:%02d - %s\n", startTime.tm_year += 1900,
         startTime.tm_mon += 1, startTime.tm_mday, startTime.tm_hour,
         startTime.tm_min, weatherConditions);

  // printf("%04d-%02d-%02dT%02d:%02d:%02dZ to %04d-%02d-%02dT%02d:%02d:%02dZ
  // %s\n",
  //     startTime.tm_year += 1900, startTime.tm_mon += 1, startTime.tm_mday,
  //     startTime.tm_hour, startTime.tm_min, startTime.tm_sec, endTime.tm_year
  //     += 1900, endTime.tm_mon += 1, endTime.tm_mday, endTime.tm_hour,
  //     endTime.tm_min, endTime.tm_sec, weatherConditions);
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