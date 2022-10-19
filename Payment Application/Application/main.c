/*
 * main.c
 *
 *  Created on: Sep 7, 2022
 *      Author: moham
 */
#include "Application.h"

int main() {
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
	appStart();
	return 0;
};

