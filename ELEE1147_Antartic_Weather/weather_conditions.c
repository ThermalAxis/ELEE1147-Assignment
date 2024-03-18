
#include "statistics_functions.h"
#include "telemetry_functions.h"
#include "weather_conditions.h"
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>

void weatherConditions(TelemetryData *telemetryArray, int arraySize) {

  int weatherChoice;
  system("cls");
  printf("==== Weather conditions for telemetry data ====\n");
  printf("1 - Display hourly weather conditions for all locations\n");
  printf("2 - Display hourly weather conditions by location\n");
  printf("3 - Display hourly weather conditions for a specific timeframe and "
         "location\n");
  printf("4 - Main menu\n");

  printf("\nEnter your choice (1-4): ");

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
    printf("\nPress any key to return to main menu...");
    system("pause>nul");
    return 0;
  case 3:
    timeframeLocationConditions(telemetryArray, arraySize);
    printf("\nPress any key to return to main menu...");
    system("pause>nul");
    return 0;
  case 4:
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

  printf("Enter the Location to display weather conditions: ");
  while (getchar() != '\n')
    ;
  scanf_s("%33[^\n]", locationName,
          (unsigned)(sizeof(locationName) / sizeof(locationName[0])));
  hourlyConditions(telemetryArray, arraySize, locationName, startDayEpoch,
                   endTimeEpoch);
}

void timeframeLocationConditions(TelemetryData *telemetryArray, int arraySize) {
  char locationName[34];

  printf("Enter the Location to display weather conditions: ");
  while (getchar() != '\n')
    ;
  scanf_s("%33[^\n]", locationName,
          (unsigned)(sizeof(locationName) / sizeof(locationName[0])));

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

  hourlyConditions(telemetryArray, arraySize, locationName, startTimeEpoch,
                   endTimeEpoch);
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
    printf("----------------------------\n");
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

  double pressureMean = meanLocationNameTime(
      telemetryArray, arraySize, "Pressure", locationName, startOffset);
  double temperatureMean = meanLocationNameTime(
      telemetryArray, arraySize, "Temperature", locationName, startOffset);
  double windspeedMean = meanLocationNameTime(
      telemetryArray, arraySize, "WindSpeed", locationName, startOffset);
  double visibilityMean = meanLocationNameTime(
      telemetryArray, arraySize, "Visibility", locationName, startOffset);
  double UVradiationMean = meanLocationNameTime(
      telemetryArray, arraySize, "UVRadiation", locationName, startOffset);

  //printf("Pressure: %.2f\n", pressureMean);
  //printf("Temperature: %.2f\n", temperatureMean);
  //printf("WindSpeed: %.2f\n", windspeedMean);
  //printf("Visibility: %.2f\n", visibilityMean);
  //printf("UV Index: %.2f\n", UVradiationMean);

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
  if (sensorPressure >= 1000 && sensorPressure <= 1015 &&
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
  }
  else if (isnan(sensorPressure) || isnan(sensorTemperature) ||
      isnan(sensorWindSpeed) || isnan(sensorVisibility) ||
      isnan(sensorUVRadiation)) {
      strcpy(result, "No Data");
  } else {
    strcpy(result, "Unknown");
    // printf("Unknown\n");
  }
  return result;
}