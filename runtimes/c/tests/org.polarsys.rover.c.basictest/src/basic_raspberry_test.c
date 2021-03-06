/*
 * Copyright (c) 2016 Eclipse Foundation and others.
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v1.0
 * which accompanies this distribution, and is available at
 * http://www.eclipse.org/legal/epl-v10.html
 *
 * Authors:
 *    Gaël Blondelle - initial implementation
 * Contributors:
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "basic_psys_rover.h"

void say(char *text){
   char buffer[1024];

   strcpy(buffer,"flite -voice rms -t \"");
   strcat(buffer, text);
   strcat(buffer,"\"");

   system(buffer);
}

void autopark() {
	int i;
	for (i = 0; i < 3; i = i + 1)
			{
		turn(BACKWARD, RIGHT, FULL_SPEED);
	}

	for (i = 0; i < 1; i = i + 1) {
		go(BACKWARD, LOW_SPEED);
	}

	for (i = 0; i < 3; i = i + 1) {
		turn(BACKWARD, LEFT, FULL_SPEED);
	}

	for (i = 0; i < 1; i = i + 1)
			{
		turn(FORWARD, RIGHT, FULL_SPEED);
	}

	for (i = 0; i < 1; i = i + 1) {
		go(BACKWARD, LOW_SPEED);
	}

	stop();
}

void getDistanceTrain(int channel,int rounds){
	int i;
	for (i=0 ; i<rounds ; i++){
		printf("Distance channel (cm) %d:%f\n",channel,getDistance(channel));
		delay(500);
	}
}

int main(void) {

	printf("Raspberry Pi Basic Rover test \n");

	init();
	int running = 1;

	while (running) {
		int c = getchar();

		switch (c) {
		case 'q':
			running = 0;
			break;
		case 'p':
			autopark();
			break;
		case 'i':
			go(FORWARD, FULL_SPEED);
			break;
		case 'u':
			turn(FORWARD, LEFT, FULL_SPEED);
			break;
		case 'k':
			go(BACKWARD, FULL_SPEED);
			break;
		case 'o':
			turn(FORWARD, RIGHT, FULL_SPEED);
			break;
		case 'j':
			turn(BACKWARD, LEFT, FULL_SPEED);
			break;
		case 'l':
			turn(BACKWARD, RIGHT, FULL_SPEED);
			break;
		case 'c':
			getTemperature();
			break;
		case 'd':
			printf("Distance channel %d:%f\n",0,getDistance(0));
			break;
		case 'e':
			printf("Distance channel %d:%f\n",1,getDistance(1));
			break;
		case 'r':
			getDistanceTrain(0,10);
			break;
		case 'f':
			getDistanceTrain(1,10);
			break;
		case 'h':
			getHumidity();
			break;
		case 's':
			stop();
			break;
		case 't':
			toggle_light();
			break;
		case 'w':
			say("Good morning! I am the PolarSys Rover!");
			break;
		}
	}

	printf("Raspberry Pi Basic Rover exit\n");

	stop();

	return EXIT_SUCCESS;
}

