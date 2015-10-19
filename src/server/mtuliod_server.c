/*
 * MTulio Server socket. handles multiple clients using threads.
 */

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>

#include<pthread.h>

#include <mtd_lib.h>

#include <mtuliod.h>
#include <mtuliod_server.h>
#include <mtd_stdout.h>
#include <mtd_server_cmd.h>

/* GLOBALS */
int countConn;

/*
* Init TCP Server. Create a socket and listeng to the port defined on configuration struct
* @param mtd_config is a struct with server configuration
* @param server is a socket struct
* @param socket_desc is a file descriptor with socket binding
* @see mtd_srv_main()
* @return a int with status of operation
*/
int mtd_srv_init(mtd_srv_cfg_t *mtd_config, struct sockaddr_in *server, int *socket_desc)
{
    int ret = -1;
	int enable_sock_reuse;

    char str[MAX_BUFF_SIZE], str_log[MAX_BUFF_SIZE];

    /* Create a INTERNET STREAM socket. 0 for socket() chose
     * right proto to use based on SOCK_STREAM type */
    *socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (*socket_desc == -1)
    {
    	mtd_stdout_print("Could not create socket");
    	return RET_ERR;
    }

    /* Option to enable socket reuse immediately when it be a TIME_WAIT conn,
     * preventing message 'Address already in use' */
    enable_sock_reuse = 1;

    /* Creating sockaddr_in structure */

    /* Socket family: (AF_INET) INTERNET*/
    server->sin_family = AF_INET;

    /* Configure IP addr to bind */
    //TODO: bind on IP defined on config file
    server->sin_addr.s_addr = INADDR_ANY;
    /*server->sin_addr.s_addr = INADDR_LOOPBACK;*/ // Loopback IP

    /* Port to be listen by server */
    server->sin_port = htons( atoi(mtd_config->bind_port) );

    /* Writing zero the rest of the structure */
    memset ( server->sin_zero, '\0', 8);

    /* Starting server/binf */
    mtd_lib_strings_showIp(ntohl(server->sin_addr.s_addr), str);

    sprintf(str_log, " # Starting Server on address %s:%d ... ", str, ntohs(server->sin_port) );
	mtd_stdout_print(str_log);

    // Associate socket to an PORT
    ret = bind(*socket_desc,(struct sockaddr *)server , sizeof(*server) );
    if( ret<0 )
    {
        //print the error message
        perror(" # [FAIL] Bind failed. Error");
    	mtd_stdout_print(" # [FAIL] Bind failed. Error");
        return ret;
    }

    /* Avoid message "socket already in use"
     * Allowing to reuse socket, set socket option: SO_REUSEADDR */
    if (setsockopt (*socket_desc,
    		SOL_SOCKET,
			SO_REUSEADDR,
			&enable_sock_reuse,
			sizeof(int)) !=0 )
    	perror(" #% Error setting reuse of socket: ");

    /* Listen on PORT defined on descriptor of socket.
     * Second argument is a number of conections that will be stay on the queue,
     * waiting for the accept() */
    return listen(*socket_desc , 5);
}

/*
* Connection handler. Handle each connection from clients.
* @param socket_data socket file descriptor
* @see mtd_srv_main()
* @return a int with status of operation
*/
void *mtd_srv_connection_handler(void *socket_data)
{
	//Get the socket descriptor
	char str_log[MAX_BUFF_SIZE];
    int socket = *(int*)socket_data;
    int terminate_client = 0;
    int nbytes = 0;

    char *message , client_message[MAX_BUFF_SIZE];

    //Send some messages to the client
	message = "[MTd] Hello! Welcome to MTd (MTulio Daemon)\n";
    write(socket, message , strlen(message));

    message = "[MTd] If you want to see all available commands. just type HELP and enjoy! ;D\n";
    write(socket , message , strlen(message));

    message = "[MTd]$ ";
    write(socket , message , strlen(message));

    //Receive a message from client
    do
    {
    	/* rcv() returns:
    	 *  >0 : received a message
    	 *  =0 : client closed the connection
    	 *  -1 : Error receiving message */
    	nbytes = recv(socket , client_message , MAX_BUFF_SIZE , 0);
		if ((nbytes) > 0) { // received message by client

			/* TODO: Use functions to get more information from client
			 * getpeername() to identify the session of client, also check:
			 * gethostbyaddr()
			 * gethostname()
			 * gethostbyname()
			*/

			sprintf(str_log, " # [HandlerID: %x] Receive message: %s", socket, client_message);
			mtd_stdout_print(str_log);

			/* Parse each message sent by clients - each <ENTER> from telnet */
    		if (mtd_srv_cmd_parseMessage(client_message) == 99 ) { // loop 'til QUIT
    			sprintf(str_log, " # [HandlerID: %x] Closing connection by command QUIT\n", socket);
    			mtd_stdout_print(str_log);
				//fflush(stdout);

				terminate_client=1;
				continue; // goto next loop
    		}

    		//Send the message back to client
            nbytes = write(socket, client_message , strlen(client_message));
            sprintf(str_log, " # [HandlerID: %x] Answer message was sent with success. Bytes=[%d]\n", socket, nbytes);
			mtd_stdout_print(str_log);

    		//clear the message buffer
    		memset(client_message, 0, MAX_BUFF_SIZE);

    	    message = "[MTd]$ ";
    	    nbytes = write(socket , message , strlen(message));

    	    sprintf(str_log, " # [HandlerID: %x] Console message was sent with success, waiting new cmds. Bytes=[%d]\n", socket, nbytes);
    	    mtd_stdout_print(str_log);
    	}
		else if (nbytes == 0) { // Client finish connection
    	    //puts(" %% Term received");
    		sprintf(str_log, " # [HandlerID: %x] Terminate connection received\n", socket);
    	    mtd_stdout_print(str_log);
    		terminate_client=1;
		}
		else {
    	    sprintf(str_log, " # [HandlerID: %x] Error receiving message from a client\n", socket);
    	    mtd_stdout_print(str_log);
    	}
    } while (!terminate_client);

    //puts("1 exit rcv");

    if(nbytes == 0)
    {
        //puts(" %% Client disconnected");
        sprintf(str_log, " # [HandlerID: %x] Client disconnected\n", socket);
		mtd_stdout_print(str_log);
        fflush(stdout);
    }
    else if(nbytes == -1)
    {
        //perror(" %% Recv failed");
        sprintf(str_log, " # [HandlerID: %x] Failed to receive message\n", socket);
		mtd_stdout_print(str_log);
    }

    countConn--;

    // Close TCP socket for client
    if (socket) close(socket);

    /*if (socket) puts(" %% Client not disconnected.");
    else puts(" %% Client disconnected.");*/

    return 0;
}


/*
* Init socket server and waiting for client connections
* @param socket_data socket file descriptor
* @see main()
* @return a int with status of operation
*/
int mtd_srv_main(mtd_srv_cfg_t *mtd_config)
{
    char str_log[MAX_BUFF_SIZE];
    int socket_desc , client_sock , len;
    struct sockaddr_in server, client;
    pthread_t thread_id;

    uint32_t in_addr;

    //mtd_srv_client_t mtd_srv_client;

    socket_desc = countConn = 0;
    len = sizeof(struct sockaddr_in);

	// Start server
	if ( mtd_srv_init(mtd_config, &server, &socket_desc) == 0 ) {
	    //printf (" [Success] \n");
		mtd_stdout_print(" [Success] \n");
	} else {
		//printf(" %% Error starting server \n");
		mtd_stdout_print(" %% Error starting server \n");
		exit(1);
	}

	/* Server accept incoming connections from clients */

	mtd_stdout_print(" # Waiting for incoming connections...\n");
	/* 'socket_desc' is a client connection file descriptor
	 * 'client' is a information of client connection
	 * 'len' is a size of connection struct (client)
	*/
	while( (client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&len)) )
    {
        countConn++;
    	in_addr = ntohl(client.sin_addr.s_addr);

        //sprintf(str_log, " # Receiving connection [%d] ... ", countConn);
    	sprintf(str_log, " # Receiving connection [%d] from IP[%d.%d.%d.%d] ... ",
    			countConn,
				(in_addr >> 24) & 0xFF,
				(in_addr >> 16) & 0xFF,
				(in_addr >> 8) & 0xFF,
				in_addr & 0xFF);
		mtd_stdout_print(str_log);

		//TODO: create a struct to handle client information (sockaddr struct, sock descriptor, handle id, ...)
		//TODO: Use select to manage all the connections and optimize the server
        if( pthread_create( &thread_id , NULL , mtd_srv_connection_handler , (void*)&client_sock) < 0)
        {
            //perror(" %% [FAIL] could not create thread");
            mtd_stdout_print(" [FAIL] could not create thread\n");
            return 1;
        }
        else {
        	sprintf(str_log, "[OK] [Handler assigned: %x]\n", client_sock);
        	mtd_stdout_print(str_log);
        }
    }

    if (client_sock < 0)
    {
        //perror(" %% Accept failed ");
        mtd_stdout_print(" [FAIL]  Accept failed \n");
        return 1;
    }

    /* Close server */
    if (socket_desc)
    	close(socket_desc);

    return 0;
}

