#include "statistics_functions.h"
#include "telemetry_functions.h"
#include <math.h>
#include <stdio.h>
#include <string.h>

/*
this needs a LOT of optimisation
*/

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
    system("timeout /T 30");
    return 0;
  case 2:
    locationStats(telemetryArray, arraySize);
    system("timeout /T 30");
    return 0;
  case 3:
    sensorIDStats(telemetryArray, arraySize);
    system("timeout /T 30");
    return 0;
  case 4:
    return 0;
  }
}

void allStats(TelemetryData *telemetryArray, int arraySize) {
  double windspeedTotal = sumSensorType(telemetryArray, arraySize, "WindSpeed");
  int windspeedCount = countSensorType(telemetryArray, arraySize, "WindSpeed");
  double windspeedMean = windspeedTotal / windspeedCount;
  double windspeedSTDev =
      stdevSensorType(telemetryArray, arraySize, "WindSpeed");

  double pressureTotal = sumSensorType(telemetryArray, arraySize, "Pressure");
  int pressureCount = countSensorType(telemetryArray, arraySize, "Pressure");
  double pressureMean = pressureTotal / pressureCount;
  double pressureSTDev = stdevSensorType(telemetryArray, arraySize, "Pressure");

  double temperatureTotal =
      sumSensorType(telemetryArray, arraySize, "Temperature");
  int temperatureCount =
      countSensorType(telemetryArray, arraySize, "Temperature");
  double temperatureMean = temperatureTotal / temperatureCount;
  double temperatureSTDev =
      stdevSensorType(telemetryArray, arraySize, "Temperature");

  double visibilityTotal =
      sumSensorType(telemetryArray, arraySize, "Visibility");
  int visibilityCount =
      countSensorType(telemetryArray, arraySize, "Visibility");
  double visibilityMean = visibilityTotal / visibilityCount;
  double visibilitySTDev =
      stdevSensorType(telemetryArray, arraySize, "Visibility");

  double UVradiationTotal =
      sumSensorType(telemetryArray, arraySize, "UVRadiation");
  int UVradiationCount =
      countSensorType(telemetryArray, arraySize, "UVRadiation");
  double UVradiationMean = UVradiationTotal / UVradiationCount;
  double UVradiationSTDev =
      stdevSensorType(telemetryArray, arraySize, "UVRadiation");

  system("cls");
  printf("\n==== Statistics for all data ====\n");
  printf("\tWindspeed (km/h) Pressure (hPa)\tTemperature (C)\tVisibility "
         "(m)\tUV Index\n");
  printf("Total:\t%.1f\t\t %.1f\t%.1f\t%.1f\t%.1f\n", windspeedTotal,
         pressureTotal, temperatureTotal, visibilityTotal, UVradiationTotal);
  printf("Mean:\t%.1f\t\t %.1f\t\t%.1f\t\t%.1f\t\t%.1f\n", windspeedMean,
         pressureMean, temperatureMean, visibilityMean, UVradiationMean);
  printf("Stdev\t%.1f\t\t %.1f\t\t%.1f\t\t%.1f\t\t%.1f\n", windspeedSTDev,
         pressureSTDev, temperatureSTDev, visibilitySTDev, UVradiationSTDev);
}

void locationStats(TelemetryData *telemetryArray, int arraySize) {
  char locationName[34];
  printf("Enter the Location to filter statistics: ");
  while (getchar() != '\n')
    ;
  scanf_s("%33[^\n]", locationName,
          (unsigned)(sizeof(locationName) / sizeof(locationName[0])));

  double windspeedTotal =
      sumLocationName(telemetryArray, arraySize, "WindSpeed", locationName);
  int windspeedCount =
      countLocationName(telemetryArray, arraySize, "WindSpeed", locationName);
  double windspeedMean =
      meanLocationName(telemetryArray, arraySize, "WindSpeed", locationName);
  double windspeedSTDev =
      stdevLocationName(telemetryArray, arraySize, "WindSpeed", locationName);

  double pressureTotal =
      sumLocationName(telemetryArray, arraySize, "Pressure", locationName);
  int pressureCount =
      countLocationName(telemetryArray, arraySize, "Pressure", locationName);
  double pressureMean =
      meanLocationName(telemetryArray, arraySize, "Pressure", locationName);
  double pressureSTDev =
      stdevLocationName(telemetryArray, arraySize, "Pressure", locationName);

  double temperatureTotal =
      sumLocationName(telemetryArray, arraySize, "Temperature", locationName);
  int temperatureCount =
      countLocationName(telemetryArray, arraySize, "Temperature", locationName);
  double temperatureMean =
      meanLocationName(telemetryArray, arraySize, "Temperature", locationName);
  double temperatureSTDev =
      stdevLocationName(telemetryArray, arraySize, "Temperature", locationName);

  double visibilityTotal =
      sumLocationName(telemetryArray, arraySize, "Visibility", locationName);
  int visibilityCount =
      countLocationName(telemetryArray, arraySize, "Visibility", locationName);
  double visibilityMean =
      meanLocationName(telemetryArray, arraySize, "Visibility", locationName);
  double visibilitySTDev =
      stdevLocationName(telemetryArray, arraySize, "Visibility", locationName);

  double UVradiationTotal =
      sumLocationName(telemetryArray, arraySize, "UVRadiation", locationName);
  int UVradiationCount =
      countLocationName(telemetryArray, arraySize, "UVRadiation", locationName);
  double UVradiationMean =
      meanLocationName(telemetryArray, arraySize, "UVRadiation", locationName);
  double UVradiationSTDev =
      stdevLocationName(telemetryArray, arraySize, "UVRadiation", locationName);

  system("cls");
  printf("\n==== Statistics for %s ====", locationName);
  printf("\n\tWindspeed (km/h) Pressure (hPa)\tTemperature (C)\tVisibility "
         "(m)\tUV Index\n");
  printf("Total:\t%.1f\t\t %.1f\t%.1f\t\t%.1f\t\t%.1f\n", windspeedTotal,
         pressureTotal, temperatureTotal, visibilityTotal, UVradiationTotal);
  printf("Mean:\t%.1f\t\t %.1f\t\t%.1f\t\t%.1f\t\t%.1f\n", windspeedMean,
         pressureMean, temperatureMean, visibilityMean, UVradiationMean);
  printf("Stdev\t%.1f\t\t %.1f\t\t%.1f\t\t%.1f\t\t%.1f\n", windspeedSTDev,
         pressureSTDev, temperatureSTDev, visibilitySTDev, UVradiationSTDev);
}

void sensorIDStats(TelemetryData *telemetryArray, int arraySize) {
  char sensorID[10];
  char sensorType[20];
  printf("Enter the Sensor ID to filter statistics: ");
  scanf_s("%9s", sensorID, (unsigned)(sizeof(sensorID) / sizeof(sensorID[0])));

  double sensorTotal = sumSensorID(telemetryArray, arraySize, sensorID);
  int sensorCount = countSensorID(telemetryArray, arraySize, sensorID);
  double sensorMean = sensorTotal / sensorCount;
  double sensorSTDev = stdevSensorID(telemetryArray, arraySize, sensorID);

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
  printf("Total:\t%.1f\n", sensorTotal);
  printf("Mean:\t%.1f\n", sensorMean);
  printf("Stdev\t%.1f\n", sensorSTDev);
}

double sumSensorType(TelemetryData *telemetryArray, int arraySize,
                     char *sensorType) {
  double total = 0;
  for (int i = 0; i < arraySize; ++i) {
    if (strcmp(telemetryArray[i].sensorType, sensorType) == 0) {
      total += telemetryArray[i].measurement;
    }
  }
  return total;
}

int countSensorType(TelemetryData *telemetryArray, int arraySize,
                    char *sensorType) {
  int count = 0;
  for (int i = 0; i < arraySize; ++i) {
    if (strcmp(telemetryArray[i].sensorType, sensorType) == 0) {
      count++;
    }
  }
  return count;
}

double stdevSensorType(TelemetryData *telemetryArray, int arraySize,
                       char *sensorType) {
  double stdev = 0, average = 0, sum = 0;
  int count = 0;

  for (int i = 0; i < arraySize; i++) {
    if (strcmp(telemetryArray[i].sensorType, sensorType) == 0) {
      sum += telemetryArray[i].measurement;
      count++;
    }
  }
  average = sum / count;
  for (int i = 0; i < arraySize; i++) {
    if (strcmp(telemetryArray[i].sensorType, sensorType) == 0) {
      stdev += pow(telemetryArray[i].measurement - average, 2);
    }
  }
  return sqrt(stdev / count);
}

double meanLocationName(TelemetryData *telemetryArray, int arraySize,
                        char *sensorType, char *locationName) {
  double mean =
      sumLocationName(telemetryArray, arraySize, sensorType, locationName) /
      countLocationName(telemetryArray, arraySize, sensorType, locationName);
  return mean;
}

double meanLocationNameTime(TelemetryData* telemetryArray, int arraySize,
    char* sensorType, char* locationName, time_t startOffset) {
    double total = 0;
    int count = 0;
    for (int i = 0; i < arraySize; ++i) {
        if (strcmp(telemetryArray[i].sensorType, sensorType) == 0 &&
            strcmp(telemetryArray[i].location, locationName) == 0 &&
            convertTimestamp(telemetryArray[i].timestamp) >= startOffset &&
            convertTimestamp(telemetryArray[i].timestamp) <= (startOffset + (3600 * 6) - 1)) {
            total += telemetryArray[i].measurement;
            count++;
        }
    }
    //printf("Mean at %s for %s between %ld and %ld is %d", locationName, sensorType, startOffset, endOffset, total / count);
    return total/count;
}

double sumLocationName(TelemetryData *telemetryArray, int arraySize,
                       char *sensorType, char *locationName) {
  double total = 0;
  // int count = 0;
  for (int i = 0; i < arraySize; ++i) {
    if (strcmp(telemetryArray[i].sensorType, sensorType) == 0 &&
        strcmp(telemetryArray[i].location, locationName) == 0) {
      total += telemetryArray[i].measurement;
    }
  }
  // printf("Total for %s with sensor type %s is %f and count is %d\n",
  // locationName, sensorType, total);
  return total;
}

int countLocationName(TelemetryData *telemetryArray, int arraySize,
                      char *sensorType, char *locationName) {
  int count = 0;
  for (int i = 0; i < arraySize; ++i) {
    if (strcmp(telemetryArray[i].sensorType, sensorType) == 0 &&
        strcmp(telemetryArray[i].location, locationName) == 0) {
      count++;
    }
  }
  return count;
}

double stdevLocationName(TelemetryData *telemetryArray, int arraySize,
                         char *sensorType, char *locationName) {
  double stdev = 0, average = 0, sum = 0;
  int count = 0;

  for (int i = 0; i < arraySize; i++) {
    if (strcmp(telemetryArray[i].sensorType, sensorType) == 0 &&
        strcmp(telemetryArray[i].location, locationName) == 0) {
      sum += telemetryArray[i].measurement;
      count++;
    }
  }
  average = sum / count;
  for (int i = 0; i < arraySize; i++) {
    if (strcmp(telemetryArray[i].sensorType, sensorType) == 0 &&
        strcmp(telemetryArray[i].location, locationName) == 0) {
      stdev += pow(telemetryArray[i].measurement - average, 2);
    }
  }
  return sqrt(stdev / count);
}

double sumSensorID(TelemetryData *telemetryArray, int arraySize,
                   char *sensorID) {
  double total = 0;
  // int count = 0;
  for (int i = 0; i < arraySize; ++i) {
    if (strcmp(telemetryArray[i].sensorID, sensorID) == 0) {
      total += telemetryArray[i].measurement;
      // count++;
    }
  }
  // printf("Total for %s with sensor type %s is %f and count is %d\n",
  // sensorID, sensorType, total, count);
  return total;
}

int countSensorID(TelemetryData *telemetryArray, int arraySize,
                  char *sensorID) {
  int count = 0;
  for (int i = 0; i < arraySize; ++i) {
    if (strcmp(telemetryArray[i].sensorID, sensorID) == 0) {
      count++;
    }
  }
  return count;
}

double stdevSensorID(TelemetryData *telemetryArray, int arraySize,
                     char *sensorID) {
  double stdev = 0, average = 0, sum = 0;
  int count = 0;

  for (int i = 0; i < arraySize; i++) {
    if (strcmp(telemetryArray[i].sensorID, sensorID) == 0) {
      sum += telemetryArray[i].measurement;
      count++;
    }
  }
  average = sum / count;
  for (int i = 0; i < arraySize; i++) {
    if (strcmp(telemetryArray[i].sensorID, sensorID) == 0) {
      stdev += pow(telemetryArray[i].measurement - average, 2);
    }
  }
  return sqrt(stdev / count);
}