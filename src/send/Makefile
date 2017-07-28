.PHONY: all test clean

all: cosmic-array-send

test: cosmic-array-send-test

cosmic-array-send: cosmic-array-send.c
	gcc -Wall -o $@ $< -lwiringPi -lm
	-cp $@ ../../bin/

cosmic-array-send-test: cosmic-array-send-test.c
	gcc -Wall -o $@ $< -lm
	-cp $@ ../../bin/

clean:
	@rm cosmic-array-send
	@rm cosmic-array-send-test

