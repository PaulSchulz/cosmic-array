/* 
 * udpclient.c - A simple UDP client
 * usage: udpclient <host> <port>
 *
 * Reference: https://www.cs.cmu.edu/afs/cs/academic/class/15213-f99/www/class26/
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#define BUFSIZE 1024

/* 
 * error - wrapper for perror
 */
void error(char *msg) {
  perror(msg);
  exit(0);
}

int main(int argc, char **argv) {
  int                 sockfd, portno, n;
  int                 serverlen; 
  struct sockaddr_in  serveraddr;
  struct hostent     *server;
  char               *hostname;
  char                buf[BUFSIZE];

  /* check command line arguments */
  if (argc != 3) {
    fprintf(stderr,"usage: %s <hostname> <port>\n", argv[0]);
    exit(0);
  }
  hostname = argv[1];
  portno = atoi(argv[2]);

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
  bzero(buf, BUFSIZE);
  printf("Please enter msg: ");
  fgets(buf, BUFSIZE, stdin);

  /* send the message to the server */
  serverlen = sizeof(serveraddr);
  n = sendto(sockfd, buf, strlen(buf), 0,
	     (struct sockaddr *) &serveraddr, serverlen);
  if (n < 0)
    error("ERROR in sendto");

  /* print the server's reply */
  n = recvfrom(sockfd, buf, strlen(buf), 0,
	       (struct sockaddr *) &serveraddr, &serverlen);
  if (n < 0)
    error("ERROR in recvfrom");
  printf("Echo from server: %s", buf);
  return 0;
}
/*
 * isr.c:
 *Wait for Interrupt test program - ISR method
 *
 *How to test:
 *  Use the SoC's pull-up and pull down resistors that are avalable
 *on input pins. So compile & run this program (via sudo), then
 *in another terminal:
 *gpio mode 0 up
 *gpio mode 0 down
 *at which point it should trigger an interrupt. Toggle the pin
 *up/down to generate more interrupts to test.
 *
 * Copyright (c) 2013 Gordon Henderson.
 ***********************************************************************
 * This file is part of wiringPi:
 *https://projects.drogon.net/raspberry-pi/wiringpi/
 *
 *    wiringPi is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU Lesser General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    wiringPi is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public License
 *    along with wiringPi.  If not, see <http://www.gnu.org/licenses/>.
 ***********************************************************************
 */

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <wiringPi.h>


// globalCounter:
//Global variable to count interrupts
//Should be declared volatile to make sure the compiler doesn't cache it.

static volatile int globalCounter [8] ;


/*
 * myInterrupt:
 *********************************************************************************
 */

void myInterrupt0 (void) { ++globalCounter [0] ; }
void myInterrupt1 (void) { ++globalCounter [1] ; }
void myInterrupt2 (void) { ++globalCounter [2] ; }
void myInterrupt3 (void) { ++globalCounter [3] ; }
void myInterrupt4 (void) { ++globalCounter [4] ; }
void myInterrupt5 (void) { ++globalCounter [5] ; }
void myInterrupt6 (void) { ++globalCounter [6] ; }
void myInterrupt7 (void) { ++globalCounter [7] ; }


/*
*********************************************************************************
* main
*********************************************************************************
*/

int main (void)
{
  int gotOne, pin ;
  int myCounter [8] ;

  for (pin = 0 ; pin < 8 ; ++pin)
    globalCounter [pin] = myCounter [pin] = 0 ;

  wiringPiSetup () ;

  wiringPiISR (0, INT_EDGE_FALLING, &myInterrupt0) ;
  wiringPiISR (1, INT_EDGE_FALLING, &myInterrupt1) ;
  wiringPiISR (2, INT_EDGE_FALLING, &myInterrupt2) ;
  wiringPiISR (3, INT_EDGE_FALLING, &myInterrupt3) ;
  wiringPiISR (4, INT_EDGE_FALLING, &myInterrupt4) ;
  wiringPiISR (5, INT_EDGE_FALLING, &myInterrupt5) ;
  wiringPiISR (6, INT_EDGE_FALLING, &myInterrupt6) ;
  wiringPiISR (7, INT_EDGE_FALLING, &myInterrupt7) ;

  for (;;)
    {
      gotOne = 0 ;
      printf ("Waiting ... ") ; fflush (stdout) ;

      for (;;)
	{
	  for (pin = 0 ; pin < 8 ; ++pin)
	    {
	      if (globalCounter [pin] != myCounter [pin])
		{
		  printf (" Int on pin %d: Counter: %5d\n", pin, globalCounter [pin]) ;
		  myCounter [pin] = globalCounter [pin] ;
		  ++gotOne ;
		}
	    }
	  if (gotOne != 0)
	    break ;
	}
    }

  return 0 ;
}
