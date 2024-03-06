#include "statistics_functions.h"
#include "weather_conditions.h"
#include <stdio.h>
#include <string.h>
#include <time.h>

void weatherConditions(TelemetryData* telemetryArray, int arraySize) {
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

void allCond(TelemetryData* telemetryArray, int arraySize) {
    char locations[5][34] = { {"Casey Station"},
                             {"Amundsen-Scott South Pole Station"},
                             {"Rothera Research Station"},
                             {"McMurdo Station"},
                             {"Palmer Station"} };

    char *testTimestamp = "2024-01-01T00:00:01";
    struct tm convertedTime = convertTimestamp(testTimestamp);

    printf(
        "Year: %d \nMonth: %d \nDay: %d \nHour: %d \nMinute: %d \nSecond: %d\n",
        convertedTime.tm_year += 1900,
        convertedTime.tm_mon += 1, convertedTime.tm_mday, convertedTime.tm_hour,
        convertedTime.tm_min, convertedTime.tm_sec);

    system("pause");

  for (int i = 0; i < 5; i++) {
    getLocationCond(telemetryArray, arraySize, locations[i]);
  }
  return;
}

struct tm convertTimestamp(char* timestamp) {
    struct tm datetime;
    printf("timestamp is %s\n", timestamp);
    sscanf_s(timestamp, "%d-%d-%dT%d:%d:%d", &datetime.tm_year,
        &datetime.tm_mon, &datetime.tm_mday, &datetime.tm_hour,
        &datetime.tm_min, &datetime.tm_sec);

    //printf(
    //    "Year: %d \nMonth: %d \nDay: %d \nHour: %d \nMinute: %d \nSecond: %d\n",
    //    datetime.tm_year,
    //    datetime.tm_mon, datetime.tm_mday, datetime.tm_hour,
    //    datetime.tm_min, datetime.tm_sec);

    datetime.tm_year -= 1900;
    datetime.tm_mon -= 1;

    return datetime;
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