/* Functions for reading the power sensors. */

#include <stdio.h>

static float read_sensor(char *node, char unit)
{
	FILE *f = NULL;
	char path[50];
	snprintf(path, sizeof(path), "/sys/bus/i2c/drivers/INA231/%s/sensor_%c", node, unit);
	f = fopen(path, "r");
	if (f == NULL) {
		perror("Could not open sensor node");
		return -1;
	}

	float result = -1;
	if (fscanf(f, "%f", &result) != 1) {
		fprintf(stderr, "Sensor reading failed");
	}

	fclose(f);
	return result;
}

float read_a15_power()
{
	return read_sensor("2-0040", 'W');
}

float read_a7_power()
{
	return read_sensor("2-0045", 'W');
}

int read_a15_temperature()
{
	FILE *f = NULL;
	f = fopen("/sys/devices/virtual/thermal/thermal_zone0/temp", "r");
	if (f == NULL) {
		perror("Could not open temperature sensor node");
		return -1;
	}

	int result = -1;
	if (fscanf(f, "%i", &result) != 1) {
		fprintf(stderr, "Temperature sensor reading failed");
	} else {
		result /= 1000;
	}

	fclose(f);
	return result;
}
