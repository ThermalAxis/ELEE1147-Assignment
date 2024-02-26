#include "statistics_functions.h"
#include <stdio.h>
#include <string.h>

int statisticsFunctions(TelemetryData* telemetryArray, int arraySize)
{
	int statisticsChoice;
	system("cls"); // clear the terminal
	printf("==== Statistics for telemetry data ====\n");
	printf("1 - Statistics of all data\n");
	printf("2 - Statistics by Location\n");
	printf("3 - Statistics by Sensor Type\n");
	printf("4 - Statistics by Sensor ID\n");

	printf("\nEnter your choice (1-4): ");

	scanf_s("%d", &statisticsChoice);

	switch (statisticsChoice) {
	default:
		printf("Invalid selection, returning to main menu.");
		return;
	case 1:
		printf("all data");
		return 0;
	case 2:
		printf("location");
		return 0;
	case 3:
		printf("sensor type");
		return 0;
	case 4:
		printf("sensor ID");
		return 0;
	}
}