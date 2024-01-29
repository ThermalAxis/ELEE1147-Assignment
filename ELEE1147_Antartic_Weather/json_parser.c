#pragma region // DO NOT TOUCH

#include "cJSON.h"
#include "json_parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void parseTelemetryDataFromFile(const char *filename,
                                TelemetryData **telemetryArray,
                                int *arraySize) {

#if (_MSC_VER > 1600)
  FILE *file;
  if (fopen_s(&file, filename, "r") == 0 && file == NULL) {
    // Handle the error, for example:
    perror("Error opening file");
    // or
    fprintf(stderr, "Error opening file: %s\n", filename);
    // ...
  }
#else
  FILE *file = fopen(filename, "r");
#endif

  fseek(file, 0, SEEK_END);
  long fileSize = ftell(file);
  fseek(file, 0, SEEK_SET);

  char *jsonString = (char *)malloc(fileSize + 1);
  if (jsonString == NULL) {
    printf("Memory allocation failed. Exiting...\n");
    fclose(file);
    exit(EXIT_FAILURE);
  }

  fread(jsonString, 1, fileSize, file);
  jsonString[fileSize] = '\0'; // Null-terminate the string

  fclose(file);

  // Parse JSON using cJSON
  cJSON *json = cJSON_Parse(jsonString);
  if (json == NULL) {
    const char *error_ptr = cJSON_GetErrorPtr();
    if (error_ptr != NULL) {
      fprintf(stderr, "Error before: %s\n", error_ptr);
    }
    exit(EXIT_FAILURE);
  }

  cJSON *telemetryArrayJSON = cJSON_GetObjectItem(json, "telemetryData");
  if (telemetryArrayJSON == NULL || !cJSON_IsArray(telemetryArrayJSON)) {
    fprintf(stderr, "Error: telemetryData is not an array.\n");
    cJSON_Delete(json);
    exit(EXIT_FAILURE);
  }

  *arraySize = cJSON_GetArraySize(telemetryArrayJSON);
  *telemetryArray =
      (TelemetryData *)malloc(sizeof(TelemetryData) * (*arraySize));

  for (int i = 0; i < *arraySize; ++i) {
    cJSON *item = cJSON_GetArrayItem(telemetryArrayJSON, i);

#if (_MSC_VER > 1600) // UoG VS uses 1937
    #pragma warning disable 6386
    // Parse individual fields using strcpy_s, need to add +1 to size to account for null termination '\0'
    strcpy_s((*telemetryArray)[i].sensorID, sizeof((*telemetryArray)[i].sensorID)+1,
        cJSON_GetObjectItem(item, "sensorID")->valuestring);
    strcpy_s((*telemetryArray)[i].sensorType, sizeof((*telemetryArray)[i].sensorType)+1,
        cJSON_GetObjectItem(item, "sensorType")->valuestring);
    strcpy_s((*telemetryArray)[i].location, sizeof((*telemetryArray)[i].location)+1,
        cJSON_GetObjectItem(item, "location")->valuestring);
    strcpy_s((*telemetryArray)[i].timestamp, sizeof((*telemetryArray)[i].timestamp)+1,
        cJSON_GetObjectItem(item, "timestamp")->valuestring);
    (*telemetryArray)[i].measurement =
        cJSON_GetObjectItem(item, "measurement")->valuedouble;
    strcpy_s((*telemetryArray)[i].status, sizeof((*telemetryArray)[i].status)+1,
        cJSON_GetObjectItem(item, "status")->valuestring);
#else
    // Parse individual fields
    strcpy((*telemetryArray)[i].sensorID,
        cJSON_GetObjectItem(item, "sensorID")->valuestring);
    strcpy((*telemetryArray)[i].sensorType,
        cJSON_GetObjectItem(item, "sensorType")->valuestring);
    strcpy((*telemetryArray)[i].location,
        cJSON_GetObjectItem(item, "location")->valuestring);
    strcpy((*telemetryArray)[i].timestamp,
        cJSON_GetObjectItem(item, "timestamp")->valuestring);
    (*telemetryArray)[i].measurement =
        cJSON_GetObjectItem(item, "measurement")->valuedouble;
    strcpy((*telemetryArray)[i].status,
        cJSON_GetObjectItem(item, "status")->valuestring);
#endif
  }


  // Clean up cJSON structures
  cJSON_Delete(json);
  free(jsonString);
}
#pragma endregion // END OF DO NOT TOUCH