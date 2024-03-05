#include "statistics_functions.h"
#include <stdio.h>
#include <string.h>
#include <math.h>

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
	double windspeedTotal, pressureTotal, temperatureTotal, visibilityTotal, UVradiationTotal;
	int windspeedCount, pressureCount, temperatureCount, visibilityCount, UVradiationCount;
	char sensorTypes[5][20] = {
		{"WindSpeed"},
		{"Pressure"},
		{"Temperature"},
		{"Visibility"},
		{"UVRadiation"},
	};

	for (int i = 0; i < 5; i++) {
		sumSensorType(telemetryArray, arraySize, sensorTypes[i]);
	}
	
	windspeedTotal = sumSensorType(telemetryArray, arraySize, "WindSpeed");
	windspeedCount = countSensorType(telemetryArray, arraySize, "WindSpeed");

	pressureTotal = sumSensorType(telemetryArray, arraySize, "Pressure");
	pressureCount = countSensorType(telemetryArray, arraySize, "Pressure");

	temperatureTotal = sumSensorType(telemetryArray, arraySize, "Temperature");
	temperatureCount = countSensorType(telemetryArray, arraySize, "Temperature");

	visibilityTotal = sumSensorType(telemetryArray, arraySize, "Visibility");
	visibilityCount = countSensorType(telemetryArray, arraySize, "Visibility");

	UVradiationTotal = sumSensorType(telemetryArray, arraySize, "UVRadiation");
	UVradiationCount = countSensorType(telemetryArray, arraySize, "UVRadiation");

	printf("Totals:\n");
	printf("Windspeed:%.2fkm/h, Pressure:%.2fhPa, Temperature:%.2fC, Visibility:%.2fm, UV Index:%.2f\n\n",
		windspeedTotal, pressureTotal, temperatureTotal, visibilityTotal, UVradiationTotal);

	printf("Averages:\n");
	printf("Windspeed:%.2fkm/h, Pressure:%.2fhPa, Temperature:%.2fC, Visibility:%.2fm, UV Index:%.2f\n\n",
		windspeedTotal / windspeedCount, pressureTotal / pressureCount, temperatureTotal / temperatureCount, visibilityTotal / visibilityCount, UVradiationTotal / UVradiationCount);

	printf("Standard Deviation:\n");

}


double sumSensorType(TelemetryData *telemetryArray, int arraySize, char *sensorType) {
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

double stDeviation(TelemetryData* telemetryArray, double sum, double mean, double count) {
	double stdev;
	for (int i = 0; i < count; i++) {
	}
}

	/*float calculateSD(float data[]) {
		float sum = 0.0, mean, SD = 0.0;
		int i;
		for (i = 0; i < 10; ++i) {
			sum += data[i];
		}
		mean = sum / 10;
		for (i = 0; i < 10; ++i) {
			SD += pow(data[i] - mean, 2);
		}
		return sqrt(SD / 10);
	}*/


locationStats()
{

}

sensorTypeStats()
{

}

sensorIDStats()
{

}