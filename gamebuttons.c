/** @file   gamebuttons.c
    @author Liam Bullock and Anton Waldmann
    @date   15 Oct 2021
    @brief  Program for all game buttons
*/
#include "system.h"
#include "navswitch.h"
#include "gamedisplay.h"
#include "pio.h"
#include "button.h"
#include "gamebuttons.h"

#define BUTTON_PIO PIO_DEFINE (PORT_D, 7)

// Initalise buttons
void gamebuttons_init(void)
{
    pio_config_set(BUTTON_PIO, PIO_INPUT);
	navswitch_init();
}

// Return when start button pressed
uint8_t gamebuttons_button_pressed(void)
{
   return pio_input_get(BUTTON_PIO);
}

// Return when nav button is pressed
uint8_t gamebuttons_nav_push(void) 
{
	return navswitch_push_event_p(NAVSWITCH_PUSH);
}

//Shows player input and returns arrow value
uint8_t gamebuttons_navswitch_process(void) 
{
	uint8_t navinput;
	// While loop runs permanantly checking input from user
	while (1)
	{
		navswitch_update();
		
		// Each if statement checks the button that is pushed and updates display
		if(navswitch_push_event_p(NAVSWITCH_NORTH)) {
			while (!navswitch_release_event_p(NAVSWITCH_NORTH)) {
				gamedisplay_arrow_north();
				navswitch_update();
			}
			navinput = 1;
			break;
		}
		
		if(navswitch_push_event_p(NAVSWITCH_EAST)) {
			while (!navswitch_release_event_p(NAVSWITCH_EAST)) {
				gamedisplay_arrow_east();
				navswitch_update();
			}
			navinput = 2;
			break;
		}
		
		if(navswitch_push_event_p(NAVSWITCH_SOUTH)) {
			while (!navswitch_release_event_p(NAVSWITCH_SOUTH)) {
				gamedisplay_arrow_south();
				navswitch_update();
			}
			navinput = 3;
			break;
		}
		
		if(navswitch_push_event_p(NAVSWITCH_WEST)) {
			while (!navswitch_release_event_p(NAVSWITCH_WEST)) {
				gamedisplay_arrow_west();
				navswitch_update();
			}
			navinput = 4;
			break;
		}
		
		if(navswitch_push_event_p(NAVSWITCH_PUSH)) {
			while (!navswitch_release_event_p(NAVSWITCH_PUSH)) {
				gamedisplay_centre_symbol();
				navswitch_update();
			}
			navinput = 5;
			break;
		}
	}
	return navinput;
}

// Scrolls through levels 
uint8_t gamebuttons_level_select(uint8_t level)
{
	navswitch_update();
        
	// Scrolls up through level selector
    if(navswitch_push_event_p(NAVSWITCH_NORTH)) {
    	if (level < 2) {
    		level = (level + 1);
    	}
    }
        
	// Scrolls down through level selector
    if(navswitch_push_event_p(NAVSWITCH_SOUTH)) {
     	level = (level - 1);
    }
	return level % 3;
}
