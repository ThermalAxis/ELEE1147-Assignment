#include "json_parser.h"
#include "telemetry_functions.h"
#include "statistics_functions.h"
#include "exportCSV.h"
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
    printf("2. Weather Conditions\n");
    printf("3. Filter by Location\n");
    printf("4. Filter by Sensor Type\n");
    printf("5. Filter by Sensor ID\n");
    printf("6. Statistics Functions\n");
    printf("7. Export to CSV\n");
    printf("8. Exit\n");

    printf("Enter your choice (1-8): ");

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
      weatherConditions(telemetryArray, arraySize);
      break;
    case 3:
      filterByLocation(telemetryArray, arraySize);
      break;
    case 4:
      filterBySensorType(telemetryArray, arraySize);
      break;
    case 5:
      filterBySensorID(telemetryArray, arraySize);
      break;
    case 6:
      printf("Not yet implemented.\n");
      break;
    case 7:
      exportCSV(telemetryArray, arraySize);
      break;
    case 8:
      printf("Exiting Telemetry Data Explorer. Goodbye!\n");
      // Don't forget to free allocated memory if needed
      free(telemetryArray);
      return 0;
    default:
      printf("Invalid choice. Please enter a number between 1 and 8.\n");
    }
  }
  return 0;
}