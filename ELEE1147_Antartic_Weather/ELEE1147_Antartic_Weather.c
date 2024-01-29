#include "json_parser.h"
#include "telemetry_functions.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
#pragma region // DO NOT TOUCH
  int choice, garbage, status;
  const char *filename = "telemetry_data.json";
  int arraySize;
  TelemetryData *telemetryArray;
  parseTelemetryDataFromFile(filename, &telemetryArray, &arraySize);
#pragma endregion // END OF DO NOT TOUCH

  // Main menu
  while (1) {
    printf("==== Telemetry Data Explorer ====\n");
    printf("1. Display All Data\n");
    printf("2. Filter by Sensor Type\n");
    printf("3. Exit\n");

    printf("Enter your choice (1-3): ");

#if (_MSC_VER > 1600)
    
    status = scanf_s("%d", &choice);
   
    while (status != 1) {
        while ((garbage = getchar()) != EOF && garbage != '\n');
        printf("Invalid input... please enter a number: ");
        status = scanf_s("%d", &choice);
    }

#else
    scanf("%d", &choice);
    while (status != 1) {
        while ((garbage = getchar()) != EOF && garbage != '\n');
        printf("Invalid input... please enter a number: ");
        status = scanfs("%d", &choice);
    }
#endif

    switch (choice) {
    case 1:
      displayAllData(telemetryArray, arraySize);
      break;
    case 2:
      filterBySensorType(telemetryArray, arraySize);
      break;
    case 3:
      printf("Exiting Telemetry Data Explorer. Goodbye!\n");
      // Don't forget to free allocated memory if needed
      free(telemetryArray);
      return 0;
    default:
      printf("Invalid choice. Please enter a number between 1 and 3.\n");
    }
  }
  return 0;
}