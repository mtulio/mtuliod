#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define PFIX_CLI "[MTd]"
#define MAX_BUF_SIZE 200

#include <mtuliod.h>
#include <mtd_server_cmd_run.h>

/* CMD: Get hostname */
/*
* Run a HOSTNAME command to get a System hostname.
* @param char msg_cmd with message command
* @param char message is a message to be returned to socket client
* @see mtd_srv_cmd_parseMessage()
* @return a int with status of operation, 0 success
*/
int mtd_server_cmd_run_HOSTNAME(char *msg_cmd, char *message)
{
	FILE *fd;
	char str_cmd[MAX_BUF_SIZE], str_buf[MAX_BUF_SIZE];
	memset (str_cmd, 0, MAX_BUF_SIZE);

	/* Create a command */
	sprintf(str_cmd, "hostname");

	/* Run a command */
	fd = popen(str_cmd, "r");
	if (!fd) {
		sprintf(message, "%s_%s ERR%% Error reading hostname.", PFIX_CLI, msg_cmd);
		return 1;
	}

    /* Get command stdout */
    while (fgets (str_buf, sizeof (str_buf), fd) <= 0);

    pclose (fd);

	sprintf(message, "%s_%s  OK# Hostname is: %s", PFIX_CLI, msg_cmd, str_buf);
	return 0;

}
