/* 
 * cosmicray-play.c - Play an audio file on a cosmicray event.
 * usage: cosmicray-play
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
void my_interrupt(int i) {
  system("aplay audio/other.wav > /dev/null 2>&1 &");
}

void my_interrupt_0 (void) {
  system("aplay audio/channel0.wav > /dev/null 2>&1 &");
}

void my_interrupt_1 (void) {
  system("aplay audio/channel1.wav > /dev/null 2>&1 &");
}

void my_interrupt_2 (void) {
  system("aplay audio/channel2.wav > /dev/null 2>&1 &");
}

void my_interrupt_3 (void) {
  system("aplay audio/channel3.wav > /dev/null 2>&1 &");
}

void my_interrupt_4 (void) { my_interrupt(4); }
void my_interrupt_5 (void) { my_interrupt(5); }
void my_interrupt_6 (void) { my_interrupt(6); }
void my_interrupt_7 (void) { my_interrupt(7); }

int main(int argc, char **argv) {
  wiringPiSetup();
  
  /* check command line arguments */
  if (argc != 1) {
    fprintf(stderr,"usage: %s\n", argv[0]);
    exit(0);
  }

  wiringPiISR (0, INT_EDGE_RISING, &my_interrupt_0) ;
  wiringPiISR (1, INT_EDGE_RISING, &my_interrupt_1) ;
  wiringPiISR (2, INT_EDGE_RISING, &my_interrupt_2) ;
  wiringPiISR (3, INT_EDGE_RISING, &my_interrupt_3) ;
  wiringPiISR (4, INT_EDGE_RISING, &my_interrupt_4) ;
  wiringPiISR (5, INT_EDGE_RISING, &my_interrupt_5) ;
  wiringPiISR (6, INT_EDGE_RISING, &my_interrupt_6) ;
  wiringPiISR (7, INT_EDGE_RISING, &my_interrupt_7) ;

  for(;;){
    delay(100);
  }
  return 0;
}
