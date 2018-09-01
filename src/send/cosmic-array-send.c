/* 
 * cosmic-array-send.c - A simple UDP client
 * usage: cosmic-array-send <server> <port> <sensor-name>
 *
 * Original Reference: https://www.cs.cmu.edu/afs/cs/academic/class/15213-f99/www/class26/
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#include <wiringPi.h>

#include <inttypes.h>
#include <math.h>
#include <time.h>

// Maximum message size
#define BUFSIZE 1024
#define STRSIZE 32

// Debug
int debug=1;

// global_counter:
// Global counter to count interupts
// Should be declared volatile to make sure that the compiler doesn't cache it.
static volatile int global_counter[8];

/* UDP Socket */
int                 sockfd, portno, n;

struct sockaddr_in  serveraddr;
int                 serverlen; 

struct hostent     *server;
char               *hostname;
char                buf[BUFSIZE];

char                myhostname[STRSIZE];

char               *sensor;

/*  error - wrapper for perror */
void error(char *msg) {
  perror(msg);
  exit(0);
}

/* Output */
void send_packet (char *sensor, time_t s, long ms, int event, int counter){
  char buf[BUFSIZE];
  
  sprintf(buf, "%s %"PRIdMAX".%06ld %d %d%s",
	  sensor,
	  (intmax_t)s, ms,
	  event,
	  global_counter[event],
	  "\n");
  
  /* send the message to the server */
  serverlen = sizeof(serveraddr);
  n = sendto(sockfd, buf, strlen(buf), 0,
	     (struct sockaddr *) &serveraddr, serverlen);
  if (n < 0)
    error("ERROR in sendto");

  if (debug==1){
    fprintf(stderr,"%s",buf);
  }
}

/* interrupt function */
void my_interrupt(int i){
  /* Time functions */
  long            ms; // Milliseconds
  time_t          s;  // Seconds
  struct timespec spec;

  ++global_counter[i];
  
  clock_gettime(CLOCK_REALTIME, &spec);
  s  = spec.tv_sec;
  ms = round(spec.tv_nsec / 1.0e3); // Convert nanoseconds to microseconds

  send_packet(sensor,s,ms,i,global_counter[i]);
}

void my_interrupt_0 (void) { my_interrupt(0); }
// void my_interrupt_1 (void) { my_interrupt(1); }
void my_interrupt_2 (void) { my_interrupt(2); }
void my_interrupt_3 (void) { my_interrupt(1); }
// void my_interrupt_4 (void) { my_interrupt(4); }
// void my_interrupt_5 (void) { my_interrupt(5); }
// void my_interrupt_6 (void) { my_interrupt(6); }
// void my_interrupt_7 (void) { my_interrupt(7); }

int main(int argc, char **argv) {
  int pin;

  /* setup */
  for (pin = 0; pin < 8; pin++)
    global_counter[pin] = 0;

  wiringPiSetup();
  
  /* check command line arguments */
  if (argc != 4) {
    fprintf(stderr,"usage: %s <server> <port> <sensor-name>\n", argv[0]);
    exit(0);
  }
  hostname = argv[1];
  portno = atoi(argv[2]);
  sensor = argv[3];

  sethostname(myhostname,STRSIZE);

  /* socket: create the socket */
  sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  if (sockfd < 0)
    error("ERROR opening socket");

  /* gethostbyname: get the server's DNS entry */
  server = gethostbyname(hostname);
  if (server == NULL) {
    fprintf(stderr,"ERROR, no such host as %s\n", hostname);
    exit(0);
  }

  /* build the server's Internet address */
  bzero((char *) &serveraddr, sizeof(serveraddr));
  serveraddr.sin_family = AF_INET;
  bcopy((char *)server->h_addr,
	(char *)&serveraddr.sin_addr.s_addr, server->h_length);
  serveraddr.sin_port = htons(portno);
  
  wiringPiISR(0, INT_EDGE_RISING, &my_interrupt_0);
  // wiringPiISR(1, INT_EDGE_RISING, &my_interrupt_1);
  wiringPiISR(2, INT_EDGE_RISING, &my_interrupt_2);
  wiringPiISR(3, INT_EDGE_RISING, &my_interrupt_3);
  // wiringPiISR(4, INT_EDGE_RISING, &my_interrupt_4);
  // wiringPiISR(5, INT_EDGE_RISING, &my_interrupt_5);
  // wiringPiISR(6, INT_EDGE_RISING, &my_interrupt_6);
  // wiringPiISR(7, INT_EDGE_RISING, &my_interrupt_7);

  for(;;){
    delay(100);
  }
  return 0;
}
