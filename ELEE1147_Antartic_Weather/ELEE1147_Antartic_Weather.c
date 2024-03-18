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
    printf("1 - Display data\n");
    printf("2 - Weather Conditions\n");
    printf("3 - Statistics Functions\n");
    printf("4 - Export to CSV\n");
    printf("5 - Exit\n");

    printf("\nEnter your choice (1-5): ");

#if (_MSC_VER > 1600)

    status = scanf_s("%d", &choice);

    while (status != 1) {
      while ((garbage = getchar()) != EOF && garbage != '\n')
        ;
      printf("Invalid input... please enter a number : ");
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
      filterMenu(telemetryArray, arraySize);  // access filter menu
      break;
    case 2:
      weatherConditions(telemetryArray, arraySize);  // access weather conditions menu
      break;
    case 3:
      statisticsFunctions(telemetryArray, arraySize);  // access stats menu
      break;
    case 4:
      exportCSV(telemetryArray, arraySize);  // access export csv menu
      break;
    case 5:
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