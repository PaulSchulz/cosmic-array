/* 
 * cosmic-array-log.c - Print event log
 * usage: cosmic-array-log
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <inttypes.h>
#include <math.h>
#include <time.h>

#include <wiringPi.h>

/*  error - wrapper for perror */
void error(char *msg) {
  perror(msg);
  exit(0);
}

void log_event(int i) {
  struct timespec tms;
  clock_gettime(CLOCK_REALTIME,&tms);
  printf("%"PRIdMAX".%06li %d\n",
	 (intmax_t)tms.tv_sec,
	 (long int)round(tms.tv_nsec/1000),
	 i);
  fflush(stdout);
}

/* interrupt functions */
/*
   Only three interrupts are used.
   Event Channels, and interrupts
     Red(0)   - 0
     Green(1) - 3 (was 1, but this is used by I2S interface)
     Blue(2)  - 2
*/
void my_interrupt_0 (void) { log_event(0); }
void my_interrupt_2 (void) { log_event(2); }
void my_interrupt_3 (void) { log_event(1); }

int main(int argc, char **argv) {
  wiringPiSetup();
  
  /* check command line arguments */
  if (argc != 1) {
    fprintf(stderr,"usage: %s\n", argv[0]);
    fprintf(stderr,"  Print event messages with timetamp.\n");
    exit(0);
  }

  wiringPiISR (0, INT_EDGE_RISING, &my_interrupt_0) ;
  wiringPiISR (2, INT_EDGE_RISING, &my_interrupt_2) ;
  wiringPiISR (3, INT_EDGE_RISING, &my_interrupt_3) ;

  for(;;){
    delay(1000);
  }
  return 0;
}
