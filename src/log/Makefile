.PHONY: all test clean

all: cosmic-array-log

cosmic-array-log: cosmic-array-log.c
	gcc -Wall -o $@ $< -lm -lwiringPi
	-cp cosmic-array-log ../../bin

clean:
	@rm cosmic-array-log

