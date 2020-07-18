#include "AutoMalloc.h"
#include <stdio.h>
#include <stdbool.h>

static bool isRunning = false;

void am_start() {
	isRunning = true;
	printf("Started\n");
}

void am_close() {
	if (!isRunning) {
		printf("ERROR: Cannot close AutoMalloc before starting!\n");
		return;
	}
	printf("Closed\n");
}

void am_status() {
	if (!isRunning) {
		printf("Not running\n");
		return;
	}

	printf("Running\n");
}
