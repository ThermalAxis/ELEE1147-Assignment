#include "exportCSV.h"
#include <stdio.h>
#include <string.h>

void exportCSV(TelemetryData *telemetryArray, int arraySize) {

  FILE *outputFile;
  // Open output file for writing
  outputFile = fopen("export.csv", "w");
  if (outputFile == NULL) {
    perror("Error opening output file");
    return 1; // Exit with an error code
  }

  printf("Do you want to filter the data first? [Y/n]\n");
  while (getchar() != '\n')
    ; // clear previous carriage return
  char exportSelect;
  scanf_s("%c", &exportSelect);

  if (exportSelect == 'n' || exportSelect == 'N') {
    // Write all data to the output file

    printf("Writing data...");
    if (fprintf(outputFile, "Timestamp, sensorID, SensorType, Location, "
                            "Measurement, Status\n") < 0) {
      // Handle output error using perror()
      perror("Error writing output to file");
      fclose(outputFile); // Close the output file before exiting
      return 1;           // Exit with an error code
    } else {
      for (int i = 0; i < arraySize; ++i) {
        fprintf(outputFile, "%s,%s,%s,%s,%.2f,%s\n",
                telemetryArray[i].timestamp, telemetryArray[i].sensorID,
                telemetryArray[i].sensorType, telemetryArray[i].location,
                telemetryArray[i].measurement, telemetryArray[i].status);
      }
    }
    fclose(outputFile); // Close outputFile
    printf("\nCSV file export successful!\n\n");

    return 0; // Exit successfully
  } else if (exportSelect == 'y' || exportSelect == 'Y') {
    // filter data and export to file.
    int exportFilter;
    printf("Select a filter type:\n");
    printf("1 - Filter by Location\n");
    printf("2 - Filter by Sensor Type\n");
    printf("3 - Filter by Sensor ID\n");

    scanf("%d", &exportFilter);

    switch (exportFilter) {
    default:
      printf("Invalid selection.");
      return;
    case 0:
      printf("Invalid selection.");
      return;
    case 1:
      printf("Filter by Location.\n");
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
            fprintf(outputFile, "%s,%s,%s,%s,%.2f,%s\n",
                    telemetryArray[i].timestamp, telemetryArray[i].sensorID,
                    telemetryArray[i].sensorType, telemetryArray[i].location,
                    telemetryArray[i].measurement, telemetryArray[i].status);
          }
        }
        fclose(outputFile); // Close outputFile
        printf("\nCSV file export successful!\n\n");
        return;
      }
      return;

    case 2:
      printf("Filter by Sensor Type.\n");
      char sensorType[20];
      printf("Enter the sensor type to filter: ");

#if (_MSC_VER > 1600)
      scanf_s("%19s", sensorType,
              (unsigned)(sizeof(sensorType) / sizeof(sensorType[0])));
#else
      scanf("%19s", sensorType);
#endif

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
            fprintf(outputFile, "%s,%s,%s,%s,%.2f,%s\n",
                    telemetryArray[i].timestamp, telemetryArray[i].sensorID,
                    telemetryArray[i].sensorType, telemetryArray[i].location,
                    telemetryArray[i].measurement, telemetryArray[i].status);
          }
        }
        fclose(outputFile); // Close outputFile
        printf("\nCSV file export successful!\n\n");
        return;
      }

    case 3:
      printf("Filter by Sensor ID.\n");
      char sensorID[10];
      printf("Enter the sensor ID to filter: ");

#if (_MSC_VER > 1600)
      scanf_s("%9s", sensorID,
              (unsigned)(sizeof(sensorID) / sizeof(sensorID[0])));
#else
      scanf("%9s", sensorType);
#endif

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
            fprintf(outputFile, "%s,%s,%s,%s,%.2f,%s\n",
                    telemetryArray[i].timestamp, telemetryArray[i].sensorID,
                    telemetryArray[i].sensorType, telemetryArray[i].location,
                    telemetryArray[i].measurement, telemetryArray[i].status);
          }
        }
        fclose(outputFile); // Close outputFile
        printf("\nCSV file export successful!\n\n");

        return;
      }
    }
  } else {
    printf("Invalid input, returning to main menu.\n\n");
    return 0;
  }
}