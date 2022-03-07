/** @file   displayarrow.h
    @author Liam Bullock and Anton Waldmann
    @date   15 Oct 2021
    @brief  Header Program for all displays for the game
*/
#ifndef GAMEDISPLAY_H
#define GAMEDISPLAY_H

void gamedisplay_init(void);

void gamedisplay_clear(void); 

void gamedisplay_led_on(void);

void gamedisplay_led_off(void);

void gamedisplay_arrow_north(void);

void gamedisplay_arrow_south(void);

void gamedisplay_arrow_east(void);

void gamedisplay_arrow_west(void);

void gamedisplay_centre_symbol(void); 

void gamedisplay_tinygl_char_init(void);

void gamedisplay_character(char character);

void gamedisplay_tinygl_init(char display_message[], uint16_t rate);

void gamedisplay_printlevel(uint8_t givenlevel[], uint8_t levelsize, uint16_t gamespeed);

#endif
