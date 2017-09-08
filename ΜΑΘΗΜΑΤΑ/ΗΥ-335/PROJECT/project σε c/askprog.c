/* 
 * Based on example source code from 
 * "TCP/IP Sockets in C: Practical Guide for Programmers" 
 * by Michael J. Donahoo and Kenneth L. Calvert.
 */

#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAXPENDING 5    /* Maximum outstanding connection requests */
#define RCVBUFSIZE 10240   /* Size of receive buffer */
int servSock;                    /* Socket descriptor for server */
int clntSock;                    /* Socket descriptor for client */
struct sockaddr_in ServAddr;     /* Local address */
struct sockaddr_in ClntAddr;     /* Client address */
unsigned short ServPort;         /* Server port */
unsigned int clntLen;            /* Length of client address data structure */
char echoBuffer[RCVBUFSIZE];     /* Buffer for echo string */
int recvMsgSize;                 /* Size of received message */
char sentBuffer[RCVBUFSIZE];     /* string gia apostolh */
int sentMsgSize;                 /* size tou parapanw */

#define mailservIP "147.52.82.100"
#define mailServPort 25

int sock;					/* to socket tou mail server */
struct sockaddr_in mailServAddr; /* mail server */

#define MAXLINES 1000
char mail_message[MAXLINES][RCVBUFSIZE];
int message_lines = 0;

#define CR 13 
#define LF 10 
#define SP 32 
/* kwdikoi entolwn */
#define INVALID -1
#define HELP 1
#define HELO 2
#define MAIL 3
#define RCPT 4
#define DATA 5
#define QUIT 6
#define VRFY 7
#define EXPN 8
#define NOOP 9
#define TELEIA 10


int comcode;	/* kodikos trexousas entolis */
int state;		/* trexousa katastasi tis fsm 
				   1-WAIT, 2-HELO, 3-MAIL, 4-RCPT, 5-DATA, 6-QUIT */

void sent_client(char *s) 
{
	strcpy(sentBuffer,s);
	sentMsgSize = strlen(sentBuffer);
	if (send(clntSock, sentBuffer, sentMsgSize, 0) != sentMsgSize) 
	{
		printf("send() failed");
	  	exit(-1);
	}
}

int find_command_code(char *s) 
{
	if (strcmp("HELP", s)==0) return HELP;
	if (strcmp("HELO", s)==0) return HELO;
	if (strcmp("MAIL", s)==0) return MAIL;
	if (strcmp("RCPT", s)==0) return RCPT;
	if (strcmp("DATA", s)==0) return DATA;
	if (strcmp("QUIT", s)==0) return QUIT;
	if (strcmp("VRFY", s)==0) return VRFY;
	if (strcmp("EXPN", s)==0) return EXPN;
	if (strcmp("NOOP", s)==0) return NOOP;
	if (strcmp(".", s)==0) return TELEIA;
	return INVALID;
}

int main(int argc, char *argv[])
{
	int i;
	
    if (argc != 2)     /* Test for correct number of arguments */
    {
        fprintf(stderr, "Usage:  %s <Server Port>\n", argv[0]);
        exit(1);
    }

    ServPort = atoi(argv[1]);  /* First arg:  local port */

    /* Create socket for incoming connections */
    if ((servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) 
	{
        printf("socket() failed");
		exit(-1);
    }
      
    /* Construct local address structure */
    memset(&ServAddr, 0, sizeof(ServAddr));   /* Zero out structure */
    ServAddr.sin_family = AF_INET;                /* Internet address family */
    ServAddr.sin_addr.s_addr = htonl(INADDR_ANY); /* Any incoming interface */
    ServAddr.sin_port = htons(ServPort);      /* Local port */

    /* Bind to the local address */
    if (bind(servSock, (struct sockaddr *) &ServAddr, sizeof(ServAddr)) < 0) 
	{
        printf("bind() failed");
		exit(-1);
    }

    /* Mark the socket so it will listen for incoming connections */
    if (listen(servSock, MAXPENDING) < 0) {
        printf("listen() failed");
	exit(-1);
    }

//    for (;;) { /* Run forever */
        /* Set the size of the in-out parameter */
        clntLen = sizeof(ClntAddr);

        /* Wait for a client to connect */
        if ((clntSock = accept(servSock, (struct sockaddr *) &ClntAddr, 
                               &clntLen)) < 0) 
		{
            printf("accept() failed");
	    	exit(-1);
    	}
//	}

    /* clntSock is connected to a client! */
    printf("Handling client %s\n", inet_ntoa(ClntAddr.sin_addr));

	state = HELO; comcode = INVALID;
	printf("State %d:\n", state);

    /* Receive message from client
    if ((recvMsgSize = recv(clntSock, echoBuffer, RCVBUFSIZE, 0)) < 0) 
	{
        printf("recv() failed");
     	exit(-1);
	}
 */
	
	/* Send received string and receive again until end of transmission */
	while (1) { //(recvMsgSize > 0) {    /* zero indicates end of transmission */

		/* Receive message from client */
		if ((recvMsgSize = recv(clntSock, echoBuffer, RCVBUFSIZE, 0)) < 0) 
		{
		    printf("recv() failed");
		 	exit(-1);
		}
	
		/* bres ti entoli einai */
		char *s, *f;
		s = echoBuffer;
		f = strchr(s, CR);					/* swstos termatismos tou string */
		if (f!=NULL)
			*f='\0';
		f = strchr(s, SP);			/* evresi space */
		if (f!=NULL) 
			*f='\0';
		comcode = find_command_code(s);	

	/* ENTOLES POU DEN EPIREAZOUN TIS KATASTASEIS TIS MHXANIS */
		if (comcode==HELP)
		{
			sent_client("214 This is my smtp server \n");	
		} 
		else if (comcode==NOOP)
		{
			sent_client("250 Ok\n");	
		}
		else if(comcode==VRFY)
		{
		}
		else if (comcode==EXPN)
		{
		}
		else {		
			/* KATASTASEIS FSM */
			switch (state) 
			{
				case HELO:
					if (comcode==INVALID) 
						sent_client("500 Command unrecognized\n");				
					else if (comcode==HELO)
					{
						/* prosthiki sto mail message */
						sprintf(mail_message[message_lines], "HELO csd.uoc.gr\n");
						message_lines++;
					
						sent_client("250 Pleased to meet you\n");
						state = MAIL;
					} 				
					else 
						sent_client("503 Polite people say HELO first\n");				
					break;

				case MAIL:
					s = f+1;
					if (comcode==INVALID) 
						sent_client("500 Command unrecognized\n");				
					else if (comcode==MAIL)
					{
						if (f==NULL) 
							sent_client("501 Sytax error in parameters\n");
						else 
						{
							f = strstr(s, "FROM:");		/* evresi FROM: */
							if (f==NULL) 
								sent_client("501 Sytax error in parameters\n");
							else 
							{
								s = f+1;
								f = strstr(s, "<");	/* evresi email */
								if (f==NULL)
									sent_client("501 Sytax error in parameters\n");
								else 
								{
									s = f; 		/* to s deixnei sto email */
									/* prosthiki sto mail message */
									sprintf(mail_message[message_lines], "MAIL FROM:%s\n", s);
									message_lines++;
								
									sent_client("250 Sender ok\n");
									state = RCPT;						
								}
							}
						}
					} 					
					else 
						sent_client("503 Need MAIL\n");				
					break;

				case RCPT:
					s = f+1;
					if (comcode==INVALID) 
						sent_client("500 Command unrecognized\n");				
					else if (comcode==MAIL)
					{
						sent_client("503 Sender already specified.\n");				
					}
					else if (comcode==RCPT)
					{
						if (f==NULL) 
							sent_client("501 Sytax error in parameters\n");
						else 
						{
							f = strstr(s, "TO:");		/* evresi FROM: */
							if (f==NULL) 
								sent_client("501 Sytax error in parameters\n");
							else 
							{
								s = f+1;
								f = strstr(s, "<");	/* evresi email */
								if (f==NULL)
									sent_client("501 Sytax error in parameters\n");
								else 
								{
									s = f; 		/* to s deixnei sto email */
									/* prosthiki sto mail message */
									sprintf(mail_message[message_lines], "RCPT TO:%s\n", s);
									message_lines ++;
								
									sent_client("250 Recipient ok\n");
									state = RCPT;						
								}
							}
						}
					} 
					else if (comcode==DATA)
					{
						/* prosthiki sto mail message */
						sprintf(mail_message[message_lines], "DATA\n");
						message_lines ++;				
					
						sent_client("354 Enter mail, end with \".\" on a line by itself\n");
						state = DATA;
					}					
					else
						sent_client("503 Need RCPT\n");	
					break;

				case DATA:
					/* prosthiki sto mail message */
					sprintf(mail_message[message_lines], "%s\n", s);
					message_lines++;
			
					if (comcode==TELEIA)
					{
						/* prosthiki sto mail message */					
						sprintf(mail_message[message_lines], "QUIT\n");
						message_lines ++;	
									
						printf("=====================\nmail mesage:\n");
						/* apostoli minimatos mail_message */					
						for(i=0; i<message_lines; i++)
							printf("%s",mail_message[i]);					
						printf("=====================\n");
													
						printf("Forwarding message to mail.uoc.gr...\n");
						/* Create a reliable, stream socket using TCP */
						if((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) 
						{
							printf("socket() failed\n");
							exit(-1);
						}
						/* Construct the serveraddress structure */
						memset(&mailServAddr, 0,sizeof(mailServAddr)); /* Zero out structure */
						mailServAddr.sin_family = AF_INET; /* Internet address family */
						mailServAddr.sin_addr.s_addr= inet_addr(mailservIP);/*Server IP address */
						mailServAddr.sin_port = htons(mailServPort); /* Server port */
						/* Establish the connection to the echo server */
						if(connect(sock, (struct sockaddr *) &mailServAddr, sizeof(mailServAddr)) < 0) 
						{
							printf("connect() failed");
							exit(-1);
						}

						/* apostoli minimatos mail_message */					
						for (i=0; i<message_lines; i++) 
						{
							/* Send the string to the server */
							sentMsgSize = strlen(mail_message[i]);
							if(send(sock, mail_message[i], sentMsgSize, 0) != sentMsgSize) {
								printf("send() sent a different number of bytes than expected");
							}		
						
						}		
						
						/* Receive up to the buffer size bytes from the sender */
						memset(&echoBuffer, 0, sizeof(echoBuffer));
						recvMsgSize = recv(sock, echoBuffer, RCVBUFSIZE - 1, 0);
						if (recvMsgSize < 0) {
							printf("recv() failed or connection closed prematurely");
							exit(-1);
						} 							
						while (recvMsgSize > 0) 
						{
							printf("%s",echoBuffer);
							memset(&echoBuffer, 0, sizeof(echoBuffer));
							recvMsgSize = recv(sock, echoBuffer, RCVBUFSIZE - 1, 0);
							if (recvMsgSize < 0) {
								printf("recv() failed or connection closed prematurely");
								exit(-1);
							} 								
						}
						
						printf("Forwarding message completed.\n");
						close(sock);
					
						sent_client("250 Message accepted for delivery\n");
						state = QUIT;
					}		
					break;

				case QUIT:
					if (comcode==INVALID) 
						sent_client("500 Command unrecognized\n");	
					else if (comcode==QUIT)
					{
						sent_client("221 Bye\n");	
						exit(0);
					}
					break;

				default:
					printf("ERROR: invalid state. Exiting\n");
					exit(1);
					break;
			} /* telos tis switch */
			
			
		} /* telos tou if comcode==xxxx */

		printf("State %d, Command code %d\n", state, comcode);
			
	}

	close(clntSock);    /* Close client socket */

    /* NOT REACHED */
    return 0;
}

