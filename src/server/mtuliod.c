/*
 * mtuliod.c
 *
 *  Created on: 18 de out de 2015
 *      Author: mtulio
 */

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>

#include<pthread.h>

#include <mtuliod.h>
#include <mtd_lib.h>
#include <mtd_stdout.h>
#include <mtuliod_server.h>
#include <mtd_server_config.h>



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

	/* Init structs  */
	if (!mtd_config) {
		mtd_config = (mtd_srv_cfg_t *)malloc(sizeof(mtd_srv_cfg_t));
		memset (mtd_config, 0, sizeof(mtd_srv_cfg_t));
	}

	if (!mtd_opts) {
		mtd_opts = (mtd_options_t *)malloc(sizeof(mtd_options_t));
		memset (mtd_opts, 0, sizeof(mtd_options_t));
	}


	/* Might to be read from command line */
	//sprintf(mtd_config.config_file, "conf/mtuliod.conf");

	if (mtd_lib_fileExist("/etc/mtuliod/mtuliod.conf") == RET_OK) {
		sprintf(mtd_config->config_file, "/etc/mtuliod/mtuliod.conf");
	} else if (mtd_lib_fileExist("mtuliod.conf") == RET_OK) {
		sprintf(mtd_config->config_file, "mtuliod.conf");
	} else if (mtd_lib_fileExist("conf/mtuliod.conf") == RET_OK) {
		sprintf(mtd_config->config_file, "conf/mtuliod.conf");
	} else {
		mtd_stdout_print("# Configuration file was not found\n");
		goto GT_EXIT;
	}

	sprintf(mtd_config->log_file, "mtuliod.log");
	mtd_opts->log = FLAG_ENABLED;
	//mtd_config->test = 0;

	mtd_stdout_print("\t*** Starting MTULIOd Server *** \n");

	/* Load configuration file  */
	ret = mtd_srv_config_main(mtd_config);
	if (ret != 0) {
		mtd_stdout_print("# Error opening config file\n");
		goto GT_EXIT;
	}

	/* Start TCP server */
	ret = mtd_srv_main(mtd_config);

	GT_EXIT:
	/* Free structure */
	if (mtd_config)
		free (mtd_config);

	exit (ret);
}
