/* 
 * cosmic-array-play.c - Play an audio file on a cosmicray event.
 * usage: cosmic-array-play
 */
#include <stdio.h>
#include <stdlib.h>

#include <wiringPi.h>

/*  error - wrapper for perror */
void error(char *msg) {
  perror(msg);
  exit(0);
}

/* interrupt functions */

void my_interrupt_0 (void) {
  system("aplay audio/channel0.wav > /dev/null 2>&1 &");
}

void my_interrupt_2 (void) {
  system("aplay audio/channel2.wav > /dev/null 2>&1 &");
}

void my_interrupt_3 (void) {
  system("aplay audio/channel1.wav > /dev/null 2>&1 &");
}

int main(int argc, char **argv) {
  wiringPiSetup();
  
  /* check command line arguments */
  if (argc != 1) {
    fprintf(stderr,"usage: %s\n", argv[0]);
    exit(0);
  }

/* Interrupt lines used:
    red(0)   - pin 0
    green(1) - pin 3
    blue(2)  - pin 2
*/
  wiringPiISR(0, INT_EDGE_RISING, &my_interrupt_0);
  wiringPiISR(2, INT_EDGE_RISING, &my_interrupt_2);
  wiringPiISR(3, INT_EDGE_RISING, &my_interrupt_3);

  // Spin, with interupts running.
  for(;;){
    delay(100);
  }
  return 0;
}
