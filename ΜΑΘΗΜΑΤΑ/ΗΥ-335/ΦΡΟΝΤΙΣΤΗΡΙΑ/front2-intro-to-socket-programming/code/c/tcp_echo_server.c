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

#define MAXPENDING 5  /* Maximum outstanding connection requests */
#define RCVBUFSIZE 32 /* Size of receive buffer */

int main(int argc, char *argv[])
{
    int servSock;                /* Socket descriptor for server */
    int clntSock;                /* Socket descriptor for client */
    struct sockaddr_in ServAddr; /* Local address */
    struct sockaddr_in ClntAddr; /* Client address */
    unsigned short ServPort;     /* Server port */
    unsigned int clntLen;        /* Length of client address data structure */
    char echoBuffer[RCVBUFSIZE]; /* Buffer for echo string */
    int recvMsgSize;             /* Size of received message */

    if (argc != 2) /* Test for correct number of arguments */
    {
        fprintf(stderr, "Usage:  %s <Server Port>\n", argv[0]);
        exit(1);
    }

    ServPort = atoi(argv[1]); /* First arg:  local port */

    /* Create socket for incoming connections */
    if ((servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
    {
        printf("socket() failed");
        exit(-1);
    }

    /* Construct local address structure */
    memset(&ServAddr, 0, sizeof(ServAddr));       /* Zero out structure */
    ServAddr.sin_family = AF_INET;                /* Internet address family */
    ServAddr.sin_addr.s_addr = htonl(INADDR_ANY); /* Any incoming interface */
    ServAddr.sin_port = htons(ServPort);          /* Local port */

    /* Bind to the local address */
    if (bind(servSock, (struct sockaddr *)&ServAddr, sizeof(ServAddr)) < 0)
    {
        printf("bind() failed");
        exit(-1);
    }

    /* Mark the socket so it will listen for incoming connections */
    if (listen(servSock, MAXPENDING) < 0)
    {
        printf("listen() failed");
        exit(-1);
    }

    for (;;)
    { /* Run forever */
        /* Set the size of the in-out parameter */
        clntLen = sizeof(ClntAddr);

        /* Wait for a client to connect */
        if ((clntSock = accept(servSock, (struct sockaddr *)&ClntAddr,
                               &clntLen)) < 0)
        {
            printf("accept() failed");
            exit(-1);
        }

        /* clntSock is connected to a client! */

        printf("Handling client %s\n", inet_ntoa(ClntAddr.sin_addr));

        /* Receive message from client */
        if ((recvMsgSize = recv(clntSock, echoBuffer, RCVBUFSIZE, 0)) < 0)
        {
            printf("recv() failed");
            exit(-1);
        }

        // printf("Received: %s\n",echoBuffer); // print the received message

        /* Send received string and receive again until end of transmission */
        while (recvMsgSize > 0)
        { /* zero indicates end of transmission */
            /* Echo message back to client */
            if (send(clntSock, echoBuffer, recvMsgSize, 0) != recvMsgSize)
            {
                printf("send() failed");
                exit(-1);
            }

            /* See if there is more data to receive */
            if ((recvMsgSize = recv(clntSock, echoBuffer, RCVBUFSIZE, 0)) < 0)
            {
                printf("recv() failed");
                exit(-1);
            }
        }

        close(clntSock); /* Close client socket */
    }
    /* NOT REACHED */
}