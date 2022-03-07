/** @file   gamelogic.c
    @author Liam Bullock and Anton Waldmann
    @date   15 Oct 2021
    @brief  Program for game logic
*/
#include "system.h"
#include "gamedisplay.h"
#include "gamebuttons.h"
#include "gamelogic.h"
#include <avr/io.h>
#include "pacer.h"
#include "tinygl.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define PACER_RATE 500

static uint8_t gamescore = 0;

// Creates random level with size
uint8_t *level_creator(uint8_t levelSize)
{
   	uint8_t *randArray = malloc(levelSize);

	if(!randArray) {
		return NULL;
   	}

   	for(uint8_t i = 0; i < levelSize; i++) {
   		randArray[i] = (rand() % 5) + 1;   //Generate number between 0 to 5
   	}

   	return randArray;
}

// Fuction to process display of level and receive user input
gameresult_t gamelogic_level_process(uint8_t *level, uint8_t levelSize)
{
	uint8_t isplaying = 1;
	uint8_t currentlevel = 1;
	gameresult_t result = pass;
	
	uint16_t gamespeed;	
	uint8_t given_pos;
	
	while (isplaying == 1 && levelSize >= currentlevel)
	{
		if (currentlevel <= 5) {
			gamespeed = 1000;
		} else if (currentlevel > 5 && currentlevel <= 10 ) {
			gamespeed = 600;
		} else {
			gamespeed = 400;
		}

		gamedisplay_printlevel(level, currentlevel, gamespeed);
		gamedisplay_led_on();

		for (uint8_t i = 0; i < currentlevel; i++) {
			given_pos = gamebuttons_navswitch_process();

			if (given_pos != level[i]) {
				isplaying = 0;
				result = fail;
				break;
			} 
		}
		gamescore++;
		currentlevel++;
		gamedisplay_led_off();
	}
	
	if (!result) {
		gamescore--;
	}
	return result;
}

// Has three messages which display to the user depending on their state in the game
void gamelogic_wait_start(gameresult_t gamestate)
{
	pacer_init(PACER_RATE);

	if (gamestate == 2) {
		gamedisplay_tinygl_init("PRESS TO START",500);
	} else if (gamestate == 0) {
		char message[20];
		sprintf(message, "YOU LOSE! SCORE: %d", gamescore);
		gamedisplay_tinygl_init(message,500);
	} else {
		gamedisplay_tinygl_init("YOU WIN! PLAY AGAIN?",500);
	}
	gamescore = 0;
	
	// for button press onces then end end function
	while (1)
    {
        pacer_wait();
        tinygl_update();
        if (gamebuttons_button_pressed())
        {
        	gamedisplay_clear(); 
			tinygl_clear();
            break;
        }
    }
}

// Calls display function showing levels returning selected difficulty
leveldiff_t gamelogic_level_select(void) 
{
	tinygl_clear();
	gamedisplay_tinygl_char_init();
	
	char difficulty[] = {'E','M','H'};
	leveldiff_t selected; 
	uint8_t leveldiff = 0;

	// While shows the levels until nav button is pressed
	while(!gamebuttons_nav_push())
    {
        tinygl_update();
        leveldiff = gamebuttons_level_select(leveldiff);
        gamedisplay_character(difficulty[leveldiff]);
    }
    
    selected = leveldiff;
	return selected;
}

// Calls appropriate level depending on difficulty chosen
gameresult_t gamelogic_process(leveldiff_t diff)
{
	gameresult_t gameresult;
	uint8_t levelSize;

	if (diff == 0) {
		levelSize = 5;
	} else if (diff == 1) {
		levelSize = 10;
	} else {
	 	levelSize = 15;
	}

	uint8_t *level = level_creator(levelSize);
	gameresult = gamelogic_level_process(level, levelSize);
	free(level);
	
	return gameresult;
}

