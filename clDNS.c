/* DNSclient.c */

#include <stdlib.h>
#include <stdio.h>
#include <cnaiapi.h>

#define BUFFSIZE	256
#define INPUT_PROMPT		"Input   > "
#define RECEIVED_PROMPT		"Received> "


int recvln(connection, char *, int);
int readln(char *, int);

/*-----------------------------------------------------------------------
 *
 * Program: clDNS
 * Purpose: contact a dns server and send domain names
 * Note:    Appnum is standard 20000
 *         
 *
 *-----------------------------------------------------------------------
 */
int
main(int argc, char *argv[])
{

  	computer	comp;
	connection	conn;
	char		buff[BUFFSIZE];
	int		len;


	if (argc != 2) {
		(void)fprintf(stderr, "usage: %s <compname> \n",
			argv[0]);
		exit(1);
	}


	/* convert arguments to binary computer and appnum */
	
	comp = cname_to_comp(argv[1]);

	
	/* contact the DNS server */

	
	conn = make_contact(comp,(appnum)20000);
	if (conn < 0) 
		exit(1);


	(void)printf("Connection Established.\n");
	(void)printf(INPUT_PROMPT);
	(void)fflush(stdout);
	
	/* iterate, reading from local user and then from DNSserver */
	while ((len = readln(buff, BUFFSIZE)) > 0) {
		
		buff[len] = '\n';
		len++; 
	

		(void)send(conn, buff, len , 0);
		
		
		/* receive and print a line from the DNSserver */
		if ((len = recvln(conn, buff, BUFFSIZE)) < 1)
			break;
		(void)printf(RECEIVED_PROMPT);
		(void)fflush(stdout);
		(void)write(STDOUT_FILENO, buff, len);

		(void)printf(INPUT_PROMPT);
		(void)fflush(stdout);
	}

	/* iteration ends when stdin or the connection indicates EOF */

	(void)printf("\nConnection Closed.\n");
	(void)send_eof(conn);
	exit(0);

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

