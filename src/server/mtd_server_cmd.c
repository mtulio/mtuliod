#include <stdio.h>
#include <string.h>

#include <mtuliod.h>
#include <mtd_server_cmd.h>

/*
* Parse message sent by socket
* @param char message with message sent by socket (all line)
* @see mtd_srv_connection_handler()
* @return a int with status of operation, 0 success and 99 exit (quit message)
*/
int mtd_srv_cmd_parseMessage(char *message/*, char *message_out*/)
{
	char msg_cmd[strlen(message)];
	//memset(message_out, 0 , strlen(MAX_BUFF_SIZE));

	// Getting CMD line w/o special characters
	mtd_srv_cmd_strTrim (message, msg_cmd);

	// Check command to run
	if ((strncmp(msg_cmd, "HELP", 4) == 0) ||
			(strncmp(msg_cmd, "help", 4) == 0)) {
		sprintf(message, "[MTd]_HELP# MTulioD HELP menu: \n"
				"\t '-> HELP	: Show this menu. \n"
				"\t '-> HOSTNAME	: Get hostname info.\n"
				"\t '-> QUIT	: Close connection.\n", msg_cmd);
	}
	else if ((strncmp(msg_cmd, "QUIT", 4) == 0) ||
			(strncmp(msg_cmd, "quit", 4) == 0)) {

		// destroy structs of this connections
		sprintf(message, "[MTd]_%s# Closing connection.\n", msg_cmd);
		return 99;
	}
	else if ((strncmp(msg_cmd, "HOSTNAME", 8) == 0) ||
			(strncmp(msg_cmd, "hostname", 8) == 0) ) {
    	//sprintf(message, "[MTd]_%s# Command [%s] accepted.\n", msg_cmd, msg_cmd);

		return mtd_server_cmd_run_HOSTNAME(msg_cmd, message);
    }
    else {
    	sprintf(message, "[MTd]_ERR%% Command [%s] NOT FOUND.\n", msg_cmd);
    }

	return 0;
}


/*  Trim string - remove \n */
/*
* Trim a message sent by client (removing end of line delimited).
* @param char message is a string with original message from client
* @param char msgBuff is a string without \n delimiter
* @see mtd_srv_cmd_parseMessage()
* @return none
*/
void mtd_srv_cmd_strTrim (char *message, char *msgBuff)
{

	memset(msgBuff, '\0', strlen(msgBuff));
	/*strcpy(msgBuff, message);
	printf("\nF1[%s]: message(%s)", __FUNCTION__, message);*/

	for (int pos=0; pos<=strlen(message); pos++) {
		/*printf("F[%s] char[%p]", __FUNCTION__, message[pos]);*/
		msgBuff[pos]=message[pos];
		if (message[pos]==0xd) {
			msgBuff[pos]='\0';
			break;
		}
	}

	/*strncpy(message, msgBuff, strlen(msgBuff));
	fflush(stdout);
	printf("\nF2[%s]: msgBuff(%s) message(%s) ", __FUNCTION__, msgBuff, message);
	fflush(stdout);*/

	return;
}
