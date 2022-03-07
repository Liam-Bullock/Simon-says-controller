# File:   Makefile
# Author: Liam Bullock and Anton Waldmann
# Date:   14 Oct 2021
# Descr:  Makefile for memory game

# Definitions.
CC = avr-gcc
CFLAGS = -mmcu=atmega32u2 -Os -Wall -Wstrict-prototypes -Wextra -g -I. -I../../utils -I../../fonts -I../../drivers -I../../drivers/avr
OBJCOPY = avr-objcopy
SIZE = avr-size
DEL = rm


# Default target.
all: game.out

# User made object files.
game.o: game.c ../../drivers/avr/system.h gamelogic.h gamedisplay.h
	$(CC) -c $(CFLAGS) $< -o $@
	
gamebuttons.o: gamebuttons.c ../../drivers/avr/system.h ../../drivers/navswitch.h gamedisplay.h gamebuttons.h ../../drivers/avr/pio.h ../../drivers/button.h
	$(CC) -c $(CFLAGS) $< -o $@	

gamedisplay.o: gamedisplay.c ../../drivers/avr/system.h ../../drivers/avr/pio.h ../../drivers/ledmat.h ../../drivers/display.h gamedisplay.h ../../utils/pacer.h ../../utils/tinygl.h ../../fonts/font5x7_1.h ../../utils/font.h 
	$(CC) -c $(CFLAGS) $< -o $@
	
gamelogic.o: gamelogic.c ../../drivers/avr/system.h gamedisplay.h gamebuttons.h gamelogic.h ../../utils/pacer.h ../../utils/tinygl.h
	$(CC) -c $(CFLAGS) $< -o $@

# System/driver object files.
ledmat.o: ../../drivers/ledmat.c ../../drivers/avr/pio.h ../../drivers/avr/system.h ../../drivers/ledmat.h
	$(CC) -c $(CFLAGS) $< -o $@
	
system.o: ../../drivers/avr/system.c ../../drivers/avr/system.h
	$(CC) -c $(CFLAGS) $< -o $@

pio.o: ../../drivers/avr/pio.c ../../drivers/avr/pio.h ../../drivers/avr/system.h
	$(CC) -c $(CFLAGS) $< -o $@
	
navswitch.o: ../../drivers/navswitch.c ../../drivers/avr/delay.h ../../drivers/avr/pio.h ../../drivers/avr/system.h ../../drivers/navswitch.h
	$(CC) -c $(CFLAGS) $< -o $@
	
display.o: ../../drivers/display.c ../../drivers/avr/system.h ../../drivers/display.h ../../drivers/ledmat.h
	$(CC) -c $(CFLAGS) $< -o $@

pacer.o: ../../utils/pacer.c ../../drivers/avr/system.h ../../drivers/avr/timer.h ../../utils/pacer.h
	$(CC) -c $(CFLAGS) $< -o $@

button.o: ../../drivers/button.c ../../drivers/avr/pio.h ../../drivers/avr/system.h ../../drivers/button.h
	$(CC) -c $(CFLAGS) $< -o $@

tinygl.o: ../../utils/tinygl.c ../../drivers/avr/system.h ../../drivers/display.h ../../utils/font.h ../../utils/tinygl.h
	$(CC) -c $(CFLAGS) $< -o $@
	
font.o: ../../utils/font.c ../../drivers/avr/system.h ../../utils/font.h
	$(CC) -c $(CFLAGS) $< -o $@

timer.o: ../../drivers/avr/timer.c ../../drivers/avr/timer.h ../../drivers/avr/system.h
	$(CC) -c $(CFLAGS) $< -o $@

# Link: Creates output file from object files described above.
game.out: game.o system.o gamebuttons.o gamedisplay.o ledmat.o pio.o navswitch.o display.o gamelogic.o pacer.o tinygl.o font.o button.o timer.o
	$(CC) $(CFLAGS) $^ -o $@ -lm
	$(SIZE) $@


# Target: clean project.
.PHONY: clean
clean: 
	-$(DEL) *.o *.out *.hex


# Target: program project.
.PHONY: program
program: game.out
	$(OBJCOPY) -O ihex game.out game.hex
	dfu-programmer atmega32u2 erase; dfu-programmer atmega32u2 flash game.hex; dfu-programmer atmega32u2 start
