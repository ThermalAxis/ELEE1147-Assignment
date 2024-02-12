#include "exportCSV.h"
#include <stdio.h>
#include <string.h>

void exportCSV(TelemetryData* telemetryArray, int arraySize)
{
	/*printf("There's nothing here yet. OwO\n");*/
	FILE *outputFile;
	// Open output file for writing
	outputFile = fopen("export.csv", "w");
	if (outputFile == NULL) {
		perror("Error opening output file");
		return 1; // Exit with an error code
	}

	// Write to the output file
	if (fprintf(outputFile, "Timestamp, sensorID, SensorType, Location, Measurement, Status\n") < 0) {
		// Handle output error using perror()
		perror("Error writing output to file");
		fclose(outputFile); // Close the output file before exiting
		return 1; // Exit with an error code
	}
	else {
		for (int i = 0; i < arraySize; ++i) {
			fprintf(outputFile, "%s,%s,%s,%s,%.2f,%s\n",
				telemetryArray[i].timestamp, telemetryArray[i].sensorID, telemetryArray[i].sensorType,
				telemetryArray[i].location, telemetryArray[i].measurement, telemetryArray[i].status);
		}
	}

	fclose(outputFile); // Close outputFile file2

	printf("\nCSV file export successful!\n");

	return 0; // Exit successfully

}