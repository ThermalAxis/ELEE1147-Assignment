#include "statistics_functions.h"
#include <stdio.h>
#include <string.h>
#include <math.h>

int statisticsFunctions(TelemetryData* telemetryArray, int arraySize)
{
	int statisticsChoice;
	system("cls");
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
		system("timeout /T 30");
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
	double windspeedTotal = sumSensorType(telemetryArray, arraySize, "WindSpeed");
	int windspeedCount = countSensorType(telemetryArray, arraySize, "WindSpeed");
	double windspeedMean = windspeedTotal / windspeedCount;
	double windspeedSTDev = stdevSensorType(telemetryArray, arraySize, "WindSpeed");

	double pressureTotal = sumSensorType(telemetryArray, arraySize, "Pressure");
	int pressureCount = countSensorType(telemetryArray, arraySize, "Pressure");
	double pressureMean = pressureTotal / pressureCount;
	double pressureSTDev = stdevSensorType(telemetryArray, arraySize, "Pressure");

	double temperatureTotal = sumSensorType(telemetryArray, arraySize, "Temperature");
	int temperatureCount = countSensorType(telemetryArray, arraySize, "Temperature");
	double temperatureMean = temperatureTotal / temperatureCount;
	double temperatureSTDev = stdevSensorType(telemetryArray, arraySize, "Temperature");

	double visibilityTotal = sumSensorType(telemetryArray, arraySize, "Visibility");
	int visibilityCount = countSensorType(telemetryArray, arraySize, "Visibility");
	double visibilityMean = visibilityTotal / visibilityCount;
	double visibilitySTDev = stdevSensorType(telemetryArray, arraySize, "Visibility");

	double UVradiationTotal = sumSensorType(telemetryArray, arraySize, "UVRadiation");
	int UVradiationCount = countSensorType(telemetryArray, arraySize, "UVRadiation");
	double UVradiationMean = UVradiationTotal / UVradiationCount;
	double UVradiationSTDev = stdevSensorType(telemetryArray, arraySize, "UVRadiation");

	printf("\n\tWindspeed (km/h) Pressure (hPa)\tTemperature (C)\tVisibility (m)\tUV Index\n");
	printf("Total:\t%.1f\t\t %.1f\t%.1f\t%.1f\t%.1f\n", windspeedTotal, pressureTotal, temperatureTotal, visibilityTotal, UVradiationTotal);
	printf("Mean:\t%.1f\t\t %.1f\t\t%.1f\t\t%.1f\t\t%.1f\n", windspeedMean, pressureMean, temperatureMean, visibilityMean, UVradiationMean);
	printf("Stdev\t%.1f\t\t %.1f\t\t%.1f\t\t%.1f\t\t%.1f\n", windspeedSTDev, pressureSTDev, temperatureSTDev, visibilitySTDev, UVradiationSTDev);
}

double sumSensorType(TelemetryData* telemetryArray, int arraySize, char* sensorType) {
	double total = 0;
	for (int i = 0; i < arraySize; ++i) {
		if (strcmp(telemetryArray[i].sensorType, sensorType) == 0) {
			total += telemetryArray[i].measurement;
		}
	}
	return total;
}

int countSensorType(TelemetryData* telemetryArray, int arraySize, char* sensorType) {
	int count = 0;
	for (int i = 0; i < arraySize; ++i) {
		if (strcmp(telemetryArray[i].sensorType, sensorType) == 0) {
			count++;
		}
	}
	return count;
}

double stdevSensorType(TelemetryData* telemetryArray, int arraySize, char *sensorType) {
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
	return sqrt(stdev/count);
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