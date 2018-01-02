.PHONY: all test clean

all: cosmic-array-log

cosmic-array-log: cosmic-array-log.c
	gcc -Wall -o $@ $< -lwiringPi
	-cp cosmic-array-log ../../bin

clean:
	@rm cosmic-array-log

