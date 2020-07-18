#include <stdio.h>
#include "AutoMalloc.h"

int main() {
	printf("Welcome to auto-malloc\n");
	//am_close();
	//am_status();
	am_start();
	am_status();
	am_close();
}
