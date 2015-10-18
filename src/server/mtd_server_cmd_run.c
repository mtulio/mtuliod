
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include <mtd_lib.h>

#include <mtuliod.h>
#include <mtd_server_cmd_run.h>
#include <mtd_stdout.h>

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

	//printf("\n msg[%s]", msg_cmd);
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
	int argc, len_str, ret;

	memset (str_cmd, 0, MAX_BUFF_SIZE);
	memset (str_buf, 0, MAX_BUFF_SIZE);
	argc = len_str = 0;
	ret = RET_ERR;

	/* Get vector size */
	argc = mtdLib_str_getColNumbers(msg_line, ' ');

	/* alloc mem vector */
	char *argv[argc];
	for (int i = 0; i < argc; i++) {
		argv[i] = (char *)malloc( (sizeof(msg_line)));
		//memset(argv[i], sizeof(argv[i]), 0);
		bzero(argv[i], sizeof(argv[i]));
	}

    /* Get arguments to vector */
	mtd_strings_parsedArgs(msg_line, &argc, argv);

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

		ret = RET_ERR;
		goto GT_FINAL;
		//return 2;
	} else if (argc > 4) {
		sprintf(msg_out, "%s_%s ERR%% cmd [SETPASS]: number of args was exceed the allowed [%d]. See HELP\n",
				PFIX_CLI, argv[0], argc);

		ret = RET_ERR;
		goto GT_FINAL;
		//return 3;
	}

	/* Strings trim line */
	/*printf(" __FUNCTION__(%s) 0 - trim argv[0]=%s\n", __FUNCTION__, argv[0]);
    printf(" __FUNCTION__(%s) 0 - trim argv[3]=%s\n", __FUNCTION__, argv[1]);
	printf(" __FUNCTION__(%s) 0 - trim argv[2]=%s\n", __FUNCTION__, argv[2]);
    printf(" __FUNCTION__(%s) 0 - trim argv[1]=%s\n", __FUNCTION__, argv[3]);*/
	mtd_lib_strings_trimNewLine (argv[0]);
	mtd_lib_strings_trimNewLine (argv[1]);
	mtd_lib_strings_trimNewLine (argv[2]);
	mtd_lib_strings_trimNewLine (argv[3]);

	/* TODO: validate SECRET with config file */
    if (strcmp(argv[1], mtd_config->secret) != 0) {
		sprintf(msg_out, "%s_%s ERR%% cmd [SETPASS]: Wrong SECRET [%s]. See HELP\n",
				PFIX_CLI, argv[0], argv[1]);

		ret = RET_ERR;
		goto GT_FINAL;
		//return 5;
    }

	/* Create a command */
	sprintf(str_cmd, "echo '%s' |passwd --stdin %s >/dev/null 2>&1; echo $?;", argv[3], argv[2]);

	/* Run a command */
	fd = popen(str_cmd, "r");
	if (!fd) {
		sprintf(msg_out, "%s_%s ERR%% Error running command [SETPASS](passwd).\n", PFIX_CLI, argv[0]);

		ret = RET_ERR;
		goto GT_FINAL;
		//return 1;
	}

    /* Get command stdout */
    while (fgets (str_buf, sizeof (str_buf), fd) <= 0);

	/* Close fd that ran a command */
    if (fd)
    	pclose (fd);

    /* Check result of comand */
    mtd_lib_strings_trimNewLine (str_buf);

    /* TODO: check all available paswd errors code */
    if (atoi(str_buf) == 0 ){
    	sprintf(msg_out, "%s_%s   OK# SETPASS result is: SUCCESS [%s] \n",
    			PFIX_CLI, argv[0], str_buf);

    	ret = RET_OK;
    }
    else { // error code was found
    	if (strncmp(str_buf, "254", strlen(str_buf)) == 254)
    		sprintf(msg_out, "%s_%s  ERR# cmd [SETPASS] result: Only 'root' is alllowed to change password [%i] \n",
    				PFIX_CLI, argv[0], atoi(str_buf));
    	else if (atoi(str_buf) == 252)
    		sprintf(msg_out, "%s_%s  ERR# cmd [SETPASS] result: User [%s] not found [%i] \n",
    				PFIX_CLI, argv[0], argv[2], atoi(str_buf));

    	ret = RET_ERR;
    }

    GT_FINAL:
	sprintf(str_buf, " # cmd[SETPASS] %s() : %s", __FUNCTION__, msg_out);
	mtd_stdout_print(str_buf);

    /* free */
    for (int i = 0; i < argc; i++)
    	free(argv[i]);

	return ret;
}
