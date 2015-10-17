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

#include <mtuliod.h>
#include <mtuliod_server.h>

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
    int ret = -99;

    //Create socket
    *socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (*socket_desc == -1)
    {
        printf("Could not create socket");
    }

    /* Creating sockaddr_in structure - check data from config file */
    server->sin_family = AF_INET;

    //TODO: bind on IP defined on config file
    server->sin_addr.s_addr = INADDR_ANY;
    //server->sin_addr.s_addr = INADDR_LOOPBACK;

    //server->sin_addr.s_addr = htons(atoi(mtd_config->bind_ip4addr));
    /*int ipAddr = server->sin_addr.s_addr;
    char str[INET_ADDRSTRLEN];
    inet_ntop( AF_INET, &ipAddr, str, INET_ADDRSTRLEN );
    printf("\n\tstr_ip=[%s] [%s] [%i]=[%i]\n", str, mtd_config->bind_ip4addr, ipAddr, atoi(mtd_config->bind_ip4addr));*/

    //server->sin_port = htons( 8888 );
    server->sin_port = htons( atoi(mtd_config->bind_port) );


    printf(" # Starting Server on address %x:%x ... ",
    		ntohl(server->sin_addr.s_addr), ntohs(server->sin_port) );
    fflush(stdout);

    // Bind
    ret = bind(*socket_desc,(struct sockaddr *)server , sizeof(*server) );
    if( ret<0 )
    {
        //print the error message
        perror(" # [FAIL] Bind failed. Error");
        return ret;
    }

    //Listen
    return listen(*socket_desc , 3);
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
    int socket = *(int*)socket_data;
    int read_size = 0;
    int terminate_client = 0;
    int nb = 0;

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
    	read_size = recv(socket , client_message , MAX_BUFF_SIZE , 0);
		if ((read_size) > 0) {

			printf(" # [HandlerID: %x] Receive message: %s", socket, client_message);

			/* Parse each message sent by clients - each <ENTER> from telnet */
    		if (mtd_srv_cmd_parseMessage(client_message) == 99 ) { // loop 'til QUIT
    			printf(" # [HandlerID: %x] Closing connection by command QUIT\n", socket);
				fflush(stdout);
				terminate_client=1;
				continue; // goto next loop
    		}

    		//Send the message back to client
            nb = write(socket, client_message , strlen(client_message));
            printf(" # [HandlerID: %x] Answer message was sent with success. Bytes=[%d]\n", socket, nb);

    		//clear the message buffer
    		memset(client_message, 0, MAX_BUFF_SIZE);

    	    message = "[MTd]$ ";
    	    nb = write(socket , message , strlen(message));

    	    printf(" # [HandlerID: %x] Console message was sent with success, waiting new cmds. Bytes=[%d]\n", socket, nb);
    	}
    	else {
    		puts(" %% Term received");
    		terminate_client=1;
    	}
    } while (!terminate_client);

    //puts("1 exit rcv");

    if(read_size == 0)
    {
        puts(" %% Client disconnected");
        fflush(stdout);
    }
    else if(read_size == -1)
    {
        perror(" %% Recv failed");
    }

    countConn--;

    //pthread_exit(0);
    // Close TCP socket for client
    if (socket) close(socket);

    /*if (socket) puts(" %% Client not disconnected.");
    else puts(" %% Client disconnected.");*/
    //printf(" # [HandlerID: %x] Client disconnected\n", socket);
	fflush(stdout);

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
    int socket_desc , client_sock , len;
    struct sockaddr_in server , client;
    pthread_t thread_id;

    //mtd_srv_client_t mtd_srv_client;

    socket_desc = countConn = 0;
    len = sizeof(struct sockaddr_in);

	// Start server
	if ( mtd_srv_init(mtd_config, &server, &socket_desc) == 0 ) {
	    printf (" [Success] \n");
	} else {
		fflush(stdout); printf(" %% Error starting server \n");
		exit(1);
	}

	// Client

    //Accept and incoming connection
    puts(" # Waiting for incoming connections...");

	while( (client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&len)) )
    {
        countConn++;
    	printf(" # Receiving connection [%d] ... ", countConn);

        if( pthread_create( &thread_id , NULL , mtd_srv_connection_handler , (void*)&client_sock) < 0)
        {
            perror(" [FAIL] could not create thread");
            return 1;
        }
        else
        	printf("[OK] [Handler assigned: %x]\n", client_sock);
    }

    if (client_sock < 0)
    {
        perror(" %% Accept failed ");
        return 1;
    }

    return 0;
}

/*
* Main function - might to be change when daemon function will be created.
* @param argc number of arguments in argv vector
* @param argv vector with arguments sent by command line
* @return a int to OS with status of execution program, zero is success
*/
int main(int argc , char *argv[])
{
	int ret;

	/* Server config file */
	//mtd_srv_cfg_t *mtd_config;

	/* Init envs */
	if (!mtd_config) {
		mtd_config = (mtd_srv_cfg_t *)malloc(sizeof(mtd_srv_cfg_t));
		memset (mtd_config, 0, sizeof(mtd_srv_cfg_t));
	}

	/* Might to be read from command line */
	//sprintf(mtd_config.config_file, "conf/mtuliod.conf");
	sprintf(mtd_config->config_file, "conf/mtuliod.conf");
	//sprintf(mtd_config.log_file, "mtuliod.log");
	mtd_config->test = 0;

	/* Load configuration file  */
	ret = mtd_srv_config_main(mtd_config);
	if (ret != 0) {
		printf("# Error opening config file\n");
		exit(ret);
	}

	/* Start TCP server */
	mtd_srv_main(mtd_config);

	/* Free structure */
	if (mtd_config)
		free (mtd_config);

	exit (0);
}
