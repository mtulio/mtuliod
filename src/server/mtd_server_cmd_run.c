#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include <mtuliod.h>
#include <mtd_server_cmd_run.h>

extern mtd_srv_cfg_t *mtd_config;

/*
* Run a HOSTNAME command to get a System hostname.
* @param char msg_cmd with message command
* @param char message is a message to be returned to socket client
* @see mtd_srv_cmd_parseMessage()
* @return a int with status of operation, 0 success
*/
int mtd_server_cmd_run_HOSTNAME(char *msg_cmd, char *msg_out)
{
	FILE *fd;
	char str_cmd[MAX_BUFF_SIZE], str_buf[MAX_BUFF_SIZE];
	memset (str_cmd, 0, MAX_BUFF_SIZE);

	/* Create a command */
	sprintf(str_cmd, "hostname");

	/* Run a command */
	fd = popen(str_cmd, "r");
	if (!fd) {
		sprintf(msg_out, "%s_%s ERR%% Error reading hostname.", PFIX_CLI, msg_cmd);
		return 1;
	}

    /* Get command stdout */
    while (fgets (str_buf, sizeof (str_buf), fd) <= 0);

	/* Close fd that ran a command */
    pclose (fd);

	sprintf(msg_out, "%s_%s  OK# Hostname is: %s", PFIX_CLI, msg_cmd, str_buf);

	printf("\n msg[%s]", msg_cmd);
	return 0;
}


/*
* Run a SETPASS command to set a root password
* @param char msg_cmd with message command
* @param char message is a message to be returned to socket client
* @see mtd_srv_cmd_parseMessage()
* @return a int with status of operation, 0 success
* @usage setpass SECRET USER NEW_PASS
*/
int mtd_server_cmd_run_SETPASS(char *msg_line, char *msg_out)
{
	FILE *fd;
	char str_cmd[MAX_BUFF_SIZE], str_buf[MAX_BUFF_SIZE];
	int tmp_argc, argc;
	int len_str = 0;

	memset (str_cmd, 0, MAX_BUFF_SIZE);
	memset (str_buf, 0, MAX_BUFF_SIZE);
	argc = len_str = 0;

	/* Get vector size */
	tmp_argc = mtdLib_str_getColNumbers(msg_line, ' ');

	/* alloc mem vector */
	char *argv[tmp_argc];
	for (int i = 0; i < tmp_argc; i++) {
		argv[i] = (char *)malloc( (sizeof(msg_line)));
		memset(argv[i], sizeof(argv[i]), 0);
	}

    /* Get arguments to vector */
	parsedargs(msg_line, &argc, argv);

	/* SHOW  argv */
	//printf("=> argc(%d)\n", argc);
    /*for (int i = 0; i < argc; i++)
      printf("[%s]\n",argv[i]);*/


	/* Check args
	 * argv[0]: cmd
	 * argv[1]: SECRET
	 * argv[2]: username
	 * argv[3]: NEW_PASSWORD
	 * */
	if (argc < 4) {
		sprintf(msg_out, "%s_%s ERR%% cmd [SETPASS]: missing arguments. See HELP.\n",
				PFIX_CLI, argv[0]);
		return 2;
	} else if (argc > 4) {
		sprintf(msg_out, "%s_%s ERR%% cmd [SETPASS]: number of args was exceed the allowed [%d]. See HELP\n",
				PFIX_CLI, argv[0], argc);
		return 3;
	}

	/* Strings trim line */
	/*printf(" __FUNCTION__(%s) 0 - trim argv[0]=%s\n", __FUNCTION__, argv[0]);
    printf(" __FUNCTION__(%s) 0 - trim argv[3]=%s\n", __FUNCTION__, argv[1]);
	printf(" __FUNCTION__(%s) 0 - trim argv[2]=%s\n", __FUNCTION__, argv[2]);
    printf(" __FUNCTION__(%s) 0 - trim argv[1]=%s\n", __FUNCTION__, argv[3]);*/
    mtd_lib_strings_trimLine (argv[0]);
    mtd_lib_strings_trimLine (argv[1]);
    mtd_lib_strings_trimLine (argv[2]);
    mtd_lib_strings_trimLine (argv[3]);

	/* TODO: validate SECRET with config file */
    /*if (strcmp(argv[1], mtd_config->secret) != 0) {
		sprintf(msg_out, "%s_%s ERR%% cmd [SETPASS]: Wrong SECRET [%s]. See HELP\n",
				PFIX_CLI, argv[0], argv[1]);
		return 5;
    }*/

	/* Create a command */
	sprintf(str_cmd, "echo '%s' |passwd --stdin %s >/dev/null 2>&1; echo $?;", argv[3], argv[2]);

	/* Run a command */
	fd = popen(str_cmd, "r");
	if (!fd) {
		sprintf(msg_out, "%s_%s ERR%% Error running command [SETPASS].\n", PFIX_CLI, argv[0]);
		return 1;
	}

    /* Get command stdout */
    while (fgets (str_buf, sizeof (str_buf), fd) <= 0);

	/* Close fd that ran a command */
    pclose (fd);

    /* Check result */
//	printf("\n 3 msg_line[%s] tmp_argc=[%i] argc=[%i] str_cmd[%s] str_buf[%s] str_buf.len[%d]\n",
//			msg_line, tmp_argc, argc, str_cmd, str_buf, strlen(str_buf));

    mtd_lib_strings_trimLine (str_buf);
//    printf(" __FUNCTION__(%s) 5.2 - str_buf(%s) len(%d)\n", __FUNCTION__, str_buf, strlen(str_buf));

    /* TODO: check all available paswd errors code */
    if (strlen(str_buf) == 3) { // error code was found
    	if (strncmp(str_buf, "254", strlen(str_buf)) == 254)
    		sprintf(msg_out, "%s_%s  ERR# cmd [SETPASS] result: Only 'root' is alllowed to change password [%i] \n",
    				PFIX_CLI, argv[0], atoi(str_buf));
    	else if (atoi(str_buf) == 252)
    		sprintf(msg_out, "%s_%s  ERR# cmd [SETPASS] result: User [%s] not found [%i] \n",
    				PFIX_CLI, argv[0], argv[2], atoi(str_buf));
    }
    else
		sprintf(msg_out, "%s_%s   OK# SETPASS result is: SUCCESS [%s] \n", PFIX_CLI, argv[0], str_buf);

    /* free */
    for (int i = 0; i < argc; i++)
    	free(argv[i]);

	return 0;

}
