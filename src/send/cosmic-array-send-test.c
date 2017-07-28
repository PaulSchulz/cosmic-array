/* 
 * udpsend-test.c - A simple UDP client
 * usage: udpclient <host> <port> <sensor-name>
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

// #include <wiringPi.h> 

#include <inttypes.h>
#include <math.h>
#include <time.h>

// Maximum message size
#define BUFSIZE 1024
#define STRSIZE 32

int                 sockfd, portno, n;
int                 serverlen; 
struct sockaddr_in  serveraddr;
struct hostent     *server;
char               *hostname;
char                buf[BUFSIZE];

char                myhostname[STRSIZE];
char               *sensor;

/* Time functions */
long            ms; // Milliseconds
time_t          s;  // Seconds
struct timespec spec;

/* UDP protocol */
long            serialnumber = 0;

/* error - wrapper for perror */
void error(char *msg) {
  perror(msg);
  exit(0);
}


int main(int argc, char **argv) {
     
  /* check command line arguments */
  if (argc != 4) {
    fprintf(stderr,"usage: %s <hostname> <port> <sensor-name>\n", argv[0]);
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
  
  /* get a message from the user */
  // bzero(buf, BUFSIZE);
  // printf("Please enter msg: ");
  // fgets(buf, BUFSIZE, stdin);

  for(;;){
    clock_gettime(CLOCK_REALTIME, &spec);
    serialnumber++;
    s  = spec.tv_sec;
    ms = round(spec.tv_nsec / 1.0e3); // Convert nanoseconds to microseconds

    sprintf(buf, "%s %"PRIdMAX".%06ld %d %ld%s",
	    sensor,
	    (intmax_t)s, ms,
	    1,
	    serialnumber,
	    "\n");
    //strcpy(buf,"TEST");
  
    /* send the message to the server */
    serverlen = sizeof(serveraddr);
    n = sendto(sockfd, buf, strlen(buf), 0,
	       (struct sockaddr *) &serveraddr, serverlen);
    if (n < 0)
      error("ERROR in sendto");

    printf("."); fflush(stdout);
    sleep(1);
  }
  return 0;
}
