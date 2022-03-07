/** @file   gamedisplay.c
    @author Liam Bullock and Anton Waldmann
    @date   15 Oct 2021
    @brief  Program for all displays for the game
*/
#include "system.h"
#include "pio.h"
#include "ledmat.h"
#include "display.h"
#include "gamedisplay.h"
#include "pacer.h"
#include "tinygl.h"
#include "../fonts/font5x7_1.h"

#define MESSAGE_RATE 20
#define TIMER1_PRESCALE 1024
#define LED_PIO PIO_DEFINE (PORT_C, 2)
#define COLUMN 5

// Initalise timer
void _timer_init(void) {
	TCCR1A = 0x00;
    TCCR1B = 0X05;
    TCCR1C = 0X00;
}

// Initalise LED and set as low
void gamedisplay_init(void)
{
    ledmat_init();
    pio_config_set(LED_PIO, PIO_OUTPUT_LOW);
}

// Initalise tinygl character
void gamedisplay_tinygl_char_init(void)
{
	tinygl_init(500);
    tinygl_font_set(&font5x7_1);
    tinygl_text_speed_set(MESSAGE_RATE);
}

// Initalise tinygl string
void gamedisplay_tinygl_init(char display_message[], uint16_t rate)
{
    tinygl_init(rate);
    tinygl_font_set(&font5x7_1);
    tinygl_text_speed_set(MESSAGE_RATE);
    tinygl_text_mode_set(TINYGL_TEXT_MODE_SCROLL);
    tinygl_text(display_message);
}

// Turn LED on
void gamedisplay_led_on(void)
{
    pio_output_high(LED_PIO);
}

// Turn LED off
void gamedisplay_led_off(void)
{
    pio_output_low(LED_PIO);
}

//Bitmaps for the displays
static const uint8_t up_arrow_bitmap[] =
{
    0x04, 0x02, 0x1F, 0x02, 0x04
};

static const uint8_t down_arrow_bitmap[] =
{
    0x10, 0x20, 0x7C, 0x20, 0x10
};

static const uint8_t right_arrow_bitmap[] =
{
    0x08, 0x08, 0x2A, 0x1C, 0x08
};

static const uint8_t left_arrow_bitmap[] =
{
    0x08, 0x1C, 0x2A, 0x08, 0x08
};

static const uint8_t centre_symbol_bitmap[] = 
{
    0x00, 0x1C, 0x1C, 0x1C, 0x00
};

static const uint8_t clear_bitmap[] =
{
    0x00, 0x00, 0x00, 0x00, 0x00
};

// Functions to update the columns to make display appear
void gamedisplay_arrow_north(void) 
{
	//Runs for loop displaying each column value for associated display
	for (uint8_t i = 0; i < COLUMN; i++) {
		ledmat_display_column(up_arrow_bitmap[i], i);
	}	
	gamedisplay_clear();
}

void gamedisplay_arrow_south(void) 
{
    for (uint8_t i = 0; i < COLUMN; i++) {
		ledmat_display_column(down_arrow_bitmap[i], i);
	}
	gamedisplay_clear();
}

void gamedisplay_arrow_east(void) 
{
    for (uint8_t i = 0; i < COLUMN; i++) {
		ledmat_display_column(right_arrow_bitmap[i], i);
	}
	gamedisplay_clear();
}

void gamedisplay_arrow_west(void) 
{
	for (uint8_t i = 0; i < COLUMN; i++) {
		ledmat_display_column(left_arrow_bitmap[i], i);
	}
	gamedisplay_clear();
	
}

void gamedisplay_centre_symbol(void) 
{
	for (uint8_t i = 0; i < COLUMN; i++) {
		ledmat_display_column(centre_symbol_bitmap[i], i);
	}
	gamedisplay_clear();
}

void gamedisplay_clear(void) 
{
	for (uint8_t i = 0; i < COLUMN; i++) {
		ledmat_display_column(clear_bitmap[i], i);
	}

}

// Function which takes the bitmaps for the display and prints it for time duration
void gamedisplay_printlevel(uint8_t givenlevel[], uint8_t levelsize, uint16_t gamespeed) {
	
	_timer_init();
	// Time value for length of time arrow is displayed - varies on the difficulty
	uint16_t timeValue1 = (gamespeed * (F_CPU / TIMER1_PRESCALE) / 1000);
	uint16_t timeValue2 = (200 * (F_CPU / TIMER1_PRESCALE) / 1000);
	
	for (uint8_t i = 0; i < levelsize; i++) {
		TCNT1 = 0;

		while(TCNT1 < timeValue2)
		{
			gamedisplay_clear();
		}

		//Each if statement takes the value for the display e.g north = 1 and runs in loop to kep it on for time value
		if (givenlevel[i] == 1) {
			TCNT1 = 0;

			while(TCNT1 < timeValue1)
			{
				gamedisplay_arrow_north();
			}
		}
		if (givenlevel[i] == 2) {
			TCNT1 = 0;

			while(TCNT1 < timeValue1)
			{
				gamedisplay_arrow_east();
			}
		}
		if (givenlevel[i] == 3) {
			TCNT1 = 0;

			while(TCNT1 < timeValue1)
			{
				gamedisplay_arrow_south();
			}
		}
		if (givenlevel[i] == 4) {
			TCNT1 = 0;

			while(TCNT1 < timeValue1)
			{
				gamedisplay_arrow_west();
			}
		}
		if (givenlevel[i] == 5) {
			TCNT1 = 0;

			while(TCNT1 < timeValue1)
			{
				gamedisplay_centre_symbol();
			}
		}
	}
}

//Puts character into buffer
void gamedisplay_character(char character)
{
    char buffer[2];
    buffer[0] = character;
    buffer[1] = '\0';
    tinygl_text (buffer);
}

