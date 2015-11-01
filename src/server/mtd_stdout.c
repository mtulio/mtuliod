/*
 * mtd_stdout.c
 *
 *  Created on: 17 de out de 2015
 *      Author: mtulio
 */

#include<stdio.h>

#include <mtuliod.h>
#include <mtd_stdout.h>

extern mtd_options_t *mtd_opts;
extern mtd_srv_cfg_t *mtd_config;

/* Print message on stdout (when daemon mode is not enabled)*/
void mtd_stdout_print(char *line)
{
	FILE *fd;

	if (mtd_opts->daemon == FLAG_DISABLED)
		printf("%s", line);

	if (mtd_opts->log == FLAG_ENABLED) {
			fd = fopen(mtd_config->log_file, "a+");
			if (!fd) {
				printf(" %s() # Log file was not found [%s]",
						__FUNCTION__, mtd_config->config_file);
				return;
			}

			fprintf (fd, line);
			if (ferror(fd))
				printf(" %s() #% Error writing log file\n", __FUNCTION__);;

			if (fd)
				fclose (fd);
	}
    fflush(stdout);
}

/* Print error message */
void mtd_stdout_msg(int ret_code)
{
	switch (ret_code) {
	case RET_ERR_DM01:
		mtd_stdout_print ("# ERROR DAEMON: fork failed\n");
		break;
	case RET_ERR_DM02:
		mtd_stdout_print ("# ERROR DAEMON: setsid failed\n");
		break;
	default:
		mtd_stdout_print ("# Unknown message\n");
	}
}
