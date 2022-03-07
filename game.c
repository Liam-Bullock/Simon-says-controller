/** @file   game.c
    @author Liam Bullock and Anton Waldmann
    @date   15 Oct 2021
    @brief  Main program to run the game
*/
#include "system.h"
#include "gamebuttons.h"
#include "gamelogic.h"
#include "gamedisplay.h"

// Initalises the main functions
void all_game_init(void) {
  gamebuttons_init();
  gamedisplay_init();
}

// Main to run the game and other modules
int main(void)
{
    system_init ();
    all_game_init();

    gameresult_t gamestate = 2;
    leveldiff_t diff;
    
    while (1) // Loop on game
    {
		gamelogic_wait_start(gamestate);
		diff = gamelogic_level_select();
		gamestate = gamelogic_process(diff);
    }
}
