#include "exportCSV.h"
#include "json_parser.h"
#include "statistics_functions.h"
#include "telemetry_functions.h"
#include "weather_conditions.h"

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
    system("cls");
    printf("==== Telemetry Data Explorer ====\n");
    printf("1. Display All Data\n");
    printf("2. Weather Conditions\n");
    printf("3. Filter by Location\n");
    printf("4. Filter by Sensor Type\n");
    printf("5. Filter by Sensor ID\n");
    printf("6. Filter by Time\n");
    printf("7. Statistics Functions\n");
    printf("8. Export to CSV\n");
    printf("9. Exit\n");

    printf("\nEnter your choice (1-9): ");

#if (_MSC_VER > 1600)

    status = scanf_s("%d", &choice);

    while (status != 1) {
      while ((garbage = getchar()) != EOF && garbage != '\n')
        ;
      printf("Invalid input... please enter a number: ");
      status = scanf_s("%d", &choice);
    }

#else
    scanf("%d", &choice);
    while (status != 1) {
      while ((garbage = getchar()) != EOF && garbage != '\n')
        ;
      printf("Invalid input... please enter a number: ");
      status = scanfs("%d", &choice);
    }
#endif

    switch (choice) {
    case 1:
      displayAllData(telemetryArray, arraySize);
      printf("Press any key to return to main menu...");
      system("pause>nul");
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
      filterByTimeStamp(telemetryArray, arraySize);
      break;
    case 7:
      statisticsFunctions(telemetryArray, arraySize);
      break;
    case 8:
      exportCSV(telemetryArray, arraySize);
      system("timeout /T 3 >nul");
      break;
    case 9:
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