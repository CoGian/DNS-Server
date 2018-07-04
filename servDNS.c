// servDNS.cpp : Defines the entry point for the console application.
//


#include "cnaiapi.h"
#include "stdio.h"
#include <stdlib.h>
#include "string.h" 

#define BUFFSIZE		256
#define SIZE 5  

typedef struct storage {
	char      name[30]; //domain names
	computer  computer; //IPs 
} storage;


int	recvln(connection, char *, int);
int readln(char *, int);
void add(storage store[], char compname[], computer comp, int *free); 

/*-----------------------------------------------------------------------
*
* Program: servDNS
* Purpose: wait for a connection from a clDNS & and send IPs . 
* Usage:   servDNS 
*
*-----------------------------------------------------------------------
*/



int main()
{
	connection	conn;
	int		len;
	char	buff[BUFFSIZE];
	storage store[SIZE]; 
	int free = 0;


	(void)printf("DNS Server Waiting For Connection.\n");

	/* wait for a connection from a clDNS*/

	conn = await_contact((appnum)20000);
	if (conn < 0)
		exit(1);

	(void)printf("Connection Established.\n");
	(void)fflush(stdout);

	/* iterate, reading from the client and the local user */

	while ((len = recvln(conn, buff, BUFFSIZE)) > 0) {
		int i  = 0 ; 
		
		buff[len-1] = '\0';
		
		/*comparing to find  if domain is  local */ 
		for ( ;i < SIZE; i++)
		{
		
			if ( strcmp(store[i].name, buff)==0 )
				break;
			
		}

		
		switch (i)
		{
			struct in_addr addr;
		   case SIZE:
		   {
			   computer comp;
			   char compbuff[BUFFSIZE];
			  
			 

			  

			   /* checking if IP address exists */
			   if ((comp = cname_to_comp(buff)) != -1)
			   {

				   /*making IP address to take the right form */ 
				   addr.s_addr = comp; 
				   (void)sprintf(compbuff, "%s", inet_ntoa(addr)); 
				   (void)add(store, buff, comp, &free);
				   (void)strcat(compbuff, " non-LOCAL\n");
				   (void)send(conn, compbuff, strlen(compbuff), 0);



			   }
			   else
			   {


				   (void)ltoa(comp, compbuff, 10);
				   (void)strcat(compbuff, " UNKNOWN\n");
				   (void)send(conn, compbuff, strlen(compbuff), 0);

			   }



			   break;
		   }
		  default:
				
			  /*making IP address to take the right form */
			  addr.s_addr = store[i].computer;
			  (void)sprintf(buff, "%s", inet_ntoa(addr));
			  (void)strcat(buff, " LOCAL\n");
			  (void)send(conn, buff, strlen(buff), 0);
		}

	}

	/* iteration ends when EOF found on stdin or  connection */
	(void)send_eof(conn);
	(void)printf("\nConnection Closed.\n\n");
	return 0;

}


/* this is just a fuction witch adds in the arrays of storage and compstarage */ 
void add(storage store[], char compname[] ,  computer comp, int *free )
{

	

	if (*free ==  SIZE)
	{
		(void)strcpy(store[0].name, compname);
		store[0].name[strlen(compname)] = '\0';
		store[0].computer = comp;
		
	}
	else
	{
		(void)strcpy(store[*free].name, compname);
		store[*free].name[strlen(compname)] = '\0';
		store[*free].computer = comp;
		*free  = *free + 1 ;
	}
	

}


/*------------------------------------------------------------------------
 * readln - read from stdin until newline or EOF, or buffer is full.
 * Flush to newline or EOF and return on full buffer. Returns data length.
 *------------------------------------------------------------------------
 */
int
readln(char *buff, int buffsz)
{
	char	*bp = buff, c;
	int	n;

	while(bp - buff < buffsz && 
	      (n = read(STDIN_FILENO, bp, 1)) > 0) {
		if (*bp++ == '\n')
			return (bp - buff);
	}

	if (n < 0)
		return -1;

	if (bp - buff == buffsz)
		while (read(STDIN_FILENO, &c, 1) > 0 && c != '\n');

	return (bp - buff);
}

/*------------------------------------------------------------------------
 * recvln - recv from socket until newline or EOF is encountered
 * Flush to newline or EOF and return on full buffer. Returns data length.
 *------------------------------------------------------------------------
 */
int
recvln(connection conn, char *buff, int buffsz)
{
	char	*bp = buff, c;
	int	n;

	while(bp - buff < buffsz && 
	      (n = recv(conn, bp, 1, 0)) > 0) {
		if (*bp++ == '\n')
			return (bp - buff);
	}

	if (n < 0)
		return -1;

	if (bp - buff == buffsz)
		while (recv(conn, &c, 1, 0) > 0 && c != '\n');

	return (bp - buff);
}
