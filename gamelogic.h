/** @file   gamelogic.h
    @author Liam Bullock and Anton Waldmann
    @date   15 Oct 2021
    @brief  Header program for game logic
*/
#ifndef GAMELOGIC_H
#define GAMELOGIC_H

// Sets the users result (e.g pass is completed)
typedef enum {
	fail = 0,
	pass = 1,
	inital = 2
} gameresult_t;

// Sets game difficulty
typedef enum {
	E = 0,
	M = 1,
	H = 2
} leveldiff_t;

leveldiff_t gamelogic_level_select(void);

gameresult_t gamelogic_process(leveldiff_t diff);

void gamelogic_wait_start(gameresult_t gamestate);

#endif
