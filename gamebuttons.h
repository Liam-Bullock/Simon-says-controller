/** @file   gamebuttons.h
    @author Liam Bullock and Anton Waldmann
    @date   15 Oct 2021
    @brief  Header Program for all game buttons
*/
#ifndef GAMEBUTTONS_H
#define GAMEBUTTONS_H

uint8_t gamebuttons_navswitch_process(void);

void gamebuttons_init(void);

uint8_t gamebuttons_level_select(uint8_t level);

uint8_t gamebuttons_nav_push(void);

uint8_t gamebuttons_button_pressed (void);

#endif
