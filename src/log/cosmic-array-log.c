/* 
 * cosmic-array-log.c - Print event log
 * usage: cosmic-array-log
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <wiringPi.h>

/*  error - wrapper for perror */
void error(char *msg) {
  perror(msg);
  exit(0);
}

/* interrupt functions */
void my_interrupt(int i) {
  struct timespec tms;
  if (clock_gettime(CLOCK_REALTIME,&tms)) {
    return -1;
  }
  printf("%d.%09d %d\n",
	 tms.tv_sec,
	 tms.tv_nsec);

}

void my_interrupt_0 (void) { my_interrupt(0); }
void my_interrupt_1 (void) { my_interrupt(1); }
void my_interrupt_2 (void) { my_interrupt(2); }
void my_interrupt_3 (void) { my_interrupt(3); }
void my_interrupt_4 (void) { my_interrupt(4); }
void my_interrupt_5 (void) { my_interrupt(5); }
void my_interrupt_6 (void) { my_interrupt(6); }
void my_interrupt_7 (void) { my_interrupt(7); }

int main(int argc, char **argv) {
  wiringPiSetup();
  
  /* check command line arguments */
  if (argc != 2) {
    fprintf(stderr,"usage: %s <file>\n", argv[0]);
    fprintf(stderr,"  Append event to file.\n";
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
