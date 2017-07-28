.PHONY: all test clean

all: cosmic-array-play

cosmic-array-play: cosmic-array-play.c
	gcc -Wall -o $@ $< -lwiringPi
	-cp cosmic-array-play ../../bin

clean:
	@rm cosmic-array-play

