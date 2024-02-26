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

  // printf("exportSelect is %c\n", exportSelect);

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

  } else {
    printf("Invalid input, returning to main menu.\n\n");
    return 0;
  }
}

// int exportAllData(TelemetryData *telemetryArray, int arraySize, FILE
// *outputFile) {
//     if (fprintf(
//         outputFile,
//         "Timestamp, sensorID, SensorType, Location, Measurement, Status\n") <
//         0) {
//         // Handle output error using perror()
//         perror("Error writing output to file");
//         fclose(outputFile); // Close the output file before exiting
//         return 1;           // Exit with an error code
//     }
//     else {
//         for (int i = 0; i < arraySize; ++i) {
//             fprintf(outputFile, "%s,%s,%s,%s,%.2f,%s\n",
//                 telemetryArray[i].timestamp,
//                 telemetryArray[i].sensorID, telemetryArray[i].sensorType,
//                 telemetryArray[i].location, telemetryArray[i].measurement,
//                 telemetryArray[i].status);
//         }
//     }
//     return 0;
// }

// void exportBySensorType(TelemetryData* telemetryArray, int arraySize, FILE*
// outputFile); {
//     char sensorType[20];
//     printf("Enter the sensor type to filter: ");
//
// #if (_MSC_VER > 1600)
//     scanf_s("%19s", sensorType,
//         (unsigned)(sizeof(sensorType) / sizeof(sensorType[0])));
// #else
//     scanf("%19s", sensorType);
// #endif
//
//     printf("Telemetry Data for Sensor Type '%s':\n", sensorType);
//     for (int i = 0; i < arraySize; ++i) {
//         if (strcmp(telemetryArray[i].sensorType, sensorType) == 0) {
//             printf("SensorID: %s, SensorType: %s, Location: %s, Measurement:
//             %.2f, "
//                 "Status: %s\n",
//                 telemetryArray[i].sensorID, telemetryArray[i].sensorType,
//                 telemetryArray[i].location, telemetryArray[i].measurement,
//                 telemetryArray[i].status);
//         }
//     }
//     return;
// }

// void exportBySensorID(TelemetryData* telemetryArray, int arraySize, FILE
// *outputFile) {
//     char sensorID[10];
//     printf("Enter the Sensor ID to filter: ");
//
// #if (_MSC_VER > 1600)
//     scanf_s("%9s", sensorID, (unsigned)(sizeof(sensorID) /
//     sizeof(sensorID[0])));
// #else
//     scanf("%9s", sensorID);
// #endif
//
//     printf("Telemetry Data for Sensor ID '%s':\n", sensorID);
//     for (int i = 0; i < arraySize; ++i) {
//         if (strcmp(telemetryArray[i].sensorID, sensorID) == 0) {
//             printf("SensorID: %s, SensorType: %s, Location: %s, Measurement:
//             %.2f, "
//                 "Status: %s\n",
//                 telemetryArray[i].sensorID, telemetryArray[i].sensorType,
//                 telemetryArray[i].location, telemetryArray[i].measurement,
//                 telemetryArray[i].status);
//         }
//     }
//     return;
// }
//
// void exportByLocation(TelemetryData* telemetryArray, int arraySize, FILE
// *outputFile) {
//     char locationName[34];
//     printf("Enter the Location to filter: ");
//
// #if (_MSC_VER > 1600)
//     while (getchar() != '\n')
//         ; // clear previous carriage return
//     scanf_s("%33[^\n]", locationName,
//         (unsigned)(sizeof(locationName) / sizeof(locationName[0])));
// #else
//     scanf("%33[^\n]", locationName);
// #endif
//
//     printf("Telemetry Data for Location '%s':\n", locationName);
//     for (int i = 0; i < arraySize; ++i) {
//         if (strcmp(telemetryArray[i].location, locationName) == 0) {
//             printf("Timestamp: %s, SensorID: %s, SensorType: %s, Location:
//             %s, "
//                 "Measurement: %.2f, "
//                 "Status: %s\n",
//                 telemetryArray[i].timestamp, telemetryArray[i].sensorID,
//                 telemetryArray[i].sensorType, telemetryArray[i].location,
//                 telemetryArray[i].measurement, telemetryArray[i].status);
//         }
//     }
//     return;
// }
