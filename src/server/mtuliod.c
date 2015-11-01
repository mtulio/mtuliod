/*
 * mtuliod.c
 *
 *  Created on: 18 de out de 2015
 *      Author: mtulio
 */

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#include <mtuliod.h>
#include <mtd_lib.h>
#include <mtd_stdout.h>
#include <mtuliod_server.h>
#include <mtuliod_signal.h>
#include <mtd_server_config.h>

/* Global config */
mtd_srv_cfg_t *mtd_config;

/* Global options */
mtd_options_t *mtd_opts;

/* Global return control */
short int ret = -1;


/**********************************************************/
/*
 *  Initialize main configuration reading from file and
 *  setting up structures.
 *
 * */
int mtuliod_initConfig(void)
{
	//int ret = -1;

	/* Server config file */
	if (!mtd_config) {
		mtd_config = (mtd_srv_cfg_t *)malloc(sizeof(mtd_srv_cfg_t));
		memset (mtd_config, 0, sizeof(mtd_srv_cfg_t));
	}

	if (!mtd_opts) {
		mtd_opts = (mtd_options_t *)malloc(sizeof(mtd_options_t));
		memset (mtd_opts, 0, sizeof(mtd_options_t));
	}


	/* Might to be read from command line */
	if (mtd_lib_fileExist("/etc/mtuliod/mtuliod.conf") == RET_OK) {
		sprintf(mtd_config->config_file, "/etc/mtuliod/mtuliod.conf");

	} else if (mtd_lib_fileExist("mtuliod.conf") == RET_OK) {
		sprintf(mtd_config->config_file, "mtuliod.conf");

	} else if (mtd_lib_fileExist("conf/mtuliod.conf") == RET_OK) {
		sprintf(mtd_config->config_file, "conf/mtuliod.conf");

	} else {
		mtd_stdout_print("#% ERROR - Configuration file was not found\n");
		return (-1);

	}

	sprintf(mtd_config->log_file, "mtuliod.log");
	mtd_opts->log = FLAG_ENABLED;

	mtd_stdout_print("\t*** Starting MTULIOd Server *** \n");

	/* Load configuration file  */
	ret = mtd_srv_config_main(mtd_config);
	if (ret != 0) {
		mtd_stdout_print("#% ERROR - opening config file\n");
		return ret;
	}

	return 0;
}

/* Clean config / free structs */
void mtuliod_end(void)
{
	mtd_stdout_print("#>> Cleaning server config <<#\n");

	/* Free structures */
	if (mtd_config)
		free (mtd_config);

	if (mtd_opts)
		free (mtd_opts);

}

/*
* Main function - might to be change when daemon function will be created.
* @param argc number of arguments in argv vector
* @param argv vector with arguments sent by command line
* @return a int to OS with status of execution program, zero is success
*/
int main(int argc , char *argv[])
{

	/* Init main config file */
	if ( (ret = mtuliod_initConfig()) != 0 )
		goto GT_EXIT;

	/* Create a daemon */
	if ( (ret = mtd_lib_daemon_init (1, 0)) < 0)
	{
		mtd_stdout_msg(ret);
		//mtd_stdout_print("#% ERROR MTuliod daemon failed ");
		exit (1);
	}
	else {
		mtuliod_signal_main ();
	}

	/* Start TCP server */
	if ( (ret = mtd_srv_main(mtd_config)) != 0 )
		mtd_stdout_print("#% ERROR - starting TCP server\n");


	/* END */
	GT_EXIT:
	/* Free structures */
//	if (mtd_config)
//		free (mtd_config);
//
//	if (mtd_opts)
//		free (mtd_opts);
//
	mtuliod_end();

	exit (ret);
}
