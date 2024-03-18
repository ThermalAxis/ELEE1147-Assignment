#include "exportCSV.h"
#include <stdio.h>
#include <string.h>

int exportCSV(TelemetryData *telemetryArray, int arraySize) {

  int exportFilter;
  system("cls"); // clear the terminal
  printf("==== Filter telemetry data for CSV export ====\n");
  printf("1 - Export all data\n");
  printf("2 - Filter by Location\n");
  printf("3 - Filter by Sensor Type\n");
  printf("4 - Filter by Sensor ID\n");
  printf("5 - Main menu\n");

  printf("\nEnter your choice (1-5): ");

  scanf("%d", &exportFilter);

  switch (exportFilter) {
  default:
    printf("Invalid selection, returning to main menu.");
    system("timeout /T 3>nul");
    return;

  case 1:
    exportAll(telemetryArray, arraySize);
    system("timeout /T 3>nul");
    return 0;

  case 2:
    /*printf("Filter by Location.\n");*/
    char locationName[34];
    printf("Enter the Location name to filter: ");
#if (_MSC_VER > 1600)
    while (getchar() != '\n')
      ; // clear previous carriage return
    scanf_s("%33[^\n]", locationName,
            (unsigned)(sizeof(locationName) / sizeof(locationName[0])));
#else
    scanf("%33[^\n]", locationName);
#endif
    exportLocation(telemetryArray, arraySize, locationName);
    system("timeout /T 3>nul");
    return 0;

  case 3:
    // printf("Filter by Sensor Type.\n");
    char sensorType[20];
    printf("Enter the sensor type to filter: ");

#if (_MSC_VER > 1600)
    scanf_s("%19s", sensorType,
            (unsigned)(sizeof(sensorType) / sizeof(sensorType[0])));
#else
    scanf("%19s", sensorType);
#endif
    exportSensorType(telemetryArray, arraySize, sensorType);
    system("timeout /T 3>nul");
    return 0;

  case 4:
    // printf("Filter by Sensor ID.\n");
    char sensorID[10];
    printf("Enter the sensor ID to filter: ");

#if (_MSC_VER > 1600)
    scanf_s("%9s", sensorID,
            (unsigned)(sizeof(sensorID) / sizeof(sensorID[0])));
#else
    scanf("%9s", sensorType);
#endif

    exportSensorID(telemetryArray, arraySize, sensorID);
    system("timeout /T 3>nul");
    return 0;

  case 5:
    return 0;
  }
}

int exportAll(TelemetryData *telemetryArray, int arraySize) {

  FILE *outputFile;
  // Open output file for writing
  outputFile = fopen("export.csv", "w");
  if (outputFile == NULL) {
    perror("Error opening output file");
    return 1; // Exit with an error code
  }

  printf("Writing data...");
  if (fprintf(outputFile, "Timestamp, sensorID, SensorType, Location, "
                          "Measurement, Status\n") < 0) {
    // Handle output error using perror()
    perror("Error writing output to file");
    fclose(outputFile); // Close the output file before exiting
    return 1;           // Exit with an error code
  } else {
    for (int i = 0; i < arraySize; ++i) {
      fprintf(outputFile, "%s,%s,%s,%s,%f,%s\n", telemetryArray[i].timestamp,
              telemetryArray[i].sensorID, telemetryArray[i].sensorType,
              telemetryArray[i].location, telemetryArray[i].measurement,
              telemetryArray[i].status);
    }
  }
  fclose(outputFile); // Close outputFile
  system("cls");
  printf("CSV file export successful!\n\n");
  printf("Opening file...");
  system("start export.csv");
  return 0;
}

int exportLocation(TelemetryData *telemetryArray, int arraySize,
                   char *locationName) {

  FILE *outputFile;
  // Open output file for writing
  outputFile = fopen("export.csv", "w");
  if (outputFile == NULL) {
    perror("Error opening output file");
    return 1; // Exit with an error code
  }

  printf("Telemetry Data for Location '%s':\n", locationName);
  printf("Writing data...");
  if (fprintf(outputFile, "Timestamp, sensorID, SensorType, Location, "
                          "Measurement, Status\n") < 0) {
    // Handle output error using perror()
    perror("Error writing output to file");
    fclose(outputFile); // Close the output file before exiting
    return 1;           // Exit with an error code
  } else {
    for (int i = 0; i < arraySize; ++i) {
      if (strcmp(telemetryArray[i].location, locationName) == 0) {
        fprintf(outputFile, "%s,%s,%s,%s,%f,%s\n", telemetryArray[i].timestamp,
                telemetryArray[i].sensorID, telemetryArray[i].sensorType,
                telemetryArray[i].location, telemetryArray[i].measurement,
                telemetryArray[i].status);
      }
    }
    fclose(outputFile); // Close outputFile
    system("cls");
    printf("CSV file export for %s successful!\n\n", locationName);
    printf("Opening file...");
    system("start export.csv");
    system("timeout /T 3 >nul");
    return 0;
  }
}

int exportSensorType(TelemetryData *telemetryArray, int arraySize,
                     char *sensorType) {
  FILE *outputFile;
  // Open output file for writing
  outputFile = fopen("export.csv", "w");
  if (outputFile == NULL) {
    perror("Error opening output file");
    return 1; // Exit with an error code
  }

  printf("Telemetry Data for Sensor Type '%s':\n", sensorType);
  printf("Writing data...");
  if (fprintf(outputFile, "Timestamp, sensorID, SensorType, Location, "
                          "Measurement, Status\n") < 0) {
    // Handle output error using perror()
    perror("Error writing output to file");
    fclose(outputFile); // Close the output file before exiting
    return 1;           // Exit with an error code
  } else {
    for (int i = 0; i < arraySize; ++i) {
      if (strcmp(telemetryArray[i].sensorType, sensorType) == 0) {
        fprintf(outputFile, "%s,%s,%s,%s,%f,%s\n", telemetryArray[i].timestamp,
                telemetryArray[i].sensorID, telemetryArray[i].sensorType,
                telemetryArray[i].location, telemetryArray[i].measurement,
                telemetryArray[i].status);
      }
    }
    fclose(outputFile); // Close outputFile
    system("cls");
    printf("CSV file export for %s sensors successful!\n\n", sensorType);
    printf("Opening file...");
    system("start export.csv");
    system("timeout /T 3 >nul");
    return 0;
  }
}

int exportSensorID(TelemetryData *telemetryArray, int arraySize,
                   char *sensorID) {

  FILE *outputFile;
  // Open output file for writing
  outputFile = fopen("export.csv", "w");
  if (outputFile == NULL) {
    perror("Error opening output file");
    return 1; // Exit with an error code
  }

  printf("Telemetry Data for Sensor ID '%s':\n", sensorID);
  printf("Writing data...");
  if (fprintf(outputFile, "Timestamp, sensorID, SensorType, Location, "
                          "Measurement, Status\n") < 0) {
    // Handle output error using perror()
    perror("Error writing output to file");
    fclose(outputFile); // Close the output file before exiting
    return 1;           // Exit with an error code
  } else {
    for (int i = 0; i < arraySize; ++i) {
      if (strcmp(telemetryArray[i].sensorID, sensorID) == 0) {
        fprintf(outputFile, "%s,%s,%s,%s,%f,%s\n", telemetryArray[i].timestamp,
                telemetryArray[i].sensorID, telemetryArray[i].sensorType,
                telemetryArray[i].location, telemetryArray[i].measurement,
                telemetryArray[i].status);
      }
    }
    fclose(outputFile); // Close outputFile
    system("cls");
    printf("CSV file export for sensor %s successful!\n\n", sensorID);
    printf("Opening file...");
    system("start export.csv");
    system("timeout /T 3 >nul");
    return 0;
  }
}