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
		allStats(telemetryArray, arraySize);
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

allStats(TelemetryData* telemetryArray, int arraySize)
{
	double windspeedTotal = 0, pressureTotal = 0, temperatureTotal = 0, visibilityTotal = 0, UVradiationTotal = 0;
	int windspeedNum = 0, pressureNum = 0, temperatureNum = 0, visibilityNum = 0, UVradiationNum = 0;

	for (int i = 0; i < arraySize; ++i) {
		if (strcmp(telemetryArray[i].sensorType, "WindSpeed") == 0) {
			windspeedTotal =+ telemetryArray[i].measurement;
			windspeedNum++;
		}
		else if(strcmp(telemetryArray[i].sensorType, "Pressure") == 0) {
			pressureTotal =+ telemetryArray[i].measurement;
			pressureNum++;
		}
		else if (strcmp(telemetryArray[i].sensorType, "Temperature") == 0) {
			temperatureTotal =+ telemetryArray[i].measurement;
			temperatureNum++;
		}
		else if (strcmp(telemetryArray[i].sensorType, "Visibility") == 0) {
			visibilityTotal =+ telemetryArray[i].measurement;
			visibilityNum++;
		}
		else if (strcmp(telemetryArray[i].sensorType, "UVRadiation") == 0) {
			UVradiationTotal =+ telemetryArray[i].measurement;
			UVradiationNum++;
		}
	}

	prinf("Totals:\n");
	printf("Windspeed: %d, Pressure: %d, Temperature: %d, Visibility: %d, UVRadiation: %d", windspeedTotal, pressureTotal, temperatureTotal, visibilityTotal, UVradiationTotal);

}






locationStats()
{

}

sensorTypeStats()
{

}

sensorIDStats()
{

}