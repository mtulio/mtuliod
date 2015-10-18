/* Parse and load config from file */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <mtuliod.h>
#include <mtd_lib.h>
#include <mtd_stdout.h>
#include <mtd_server_config.h>


/*
* Read main server config file and return it to struct.
* @param mtd_config is a struct with server configuration file
* @see main()
* @return a int with status of operation
*/
int mtd_srv_config_main(mtd_srv_cfg_t *mtd_config)
{
	FILE *fd_config;
	char str_log[MAX_BUFF_SIZE];
	bzero(str_log, sizeof(str_log));

	/* Check file exist */
	fd_config = fopen(mtd_config->config_file, "r");
	if (fd_config) {
		sprintf(str_log, " # Configuration file was found [%s]", mtd_config->config_file);
		mtd_stdout_print(str_log);
		if (fd_config)
				fclose(fd_config);
	} else {
		sprintf(str_log, " %% Unable to find config file [%s]\n", mtd_config->config_file);
		mtd_stdout_print(str_log);
		return EXIT_ERR;
	}

	/* Reading data from file */
	sprintf(str_log, " reading...\n");
	mtd_stdout_print(str_log);

	if (mtd_srv_config_readData(mtd_config) != 0 )
			return RET_ERR;

	/* End closing all pointers */
	finish:

	return RET_OK;
}

/*
* Function to read data from config file.
* @param mtd_config is a struct with server configuration file
* @see mtd_srv_config_main()
* @return a int with status of operation
*/
int mtd_srv_config_readData(mtd_srv_cfg_t *mtd_config)
{
	FILE *fd_config;
	int ret = 0;

	char *str_attr;
	char *str_value;
	char str_buff[MAX_BUFF_SIZE];
	//char str_attr[MAX_BUFF_SIZE];
	//char str_value[MAX_BUFF_SIZE];
	char str_log[MAX_BUFF_SIZE];

	memset (str_buff, 0, sizeof(str_buff));
	str_attr = (char *)malloc(sizeof(char)*MAX_CONFIG_SIZE_ATTR);
	str_value = (char *)malloc(sizeof(char)*MAX_CONFIG_SIZE_VALUE);
	bzero (str_attr, sizeof(str_attr));
	bzero (str_value, sizeof(str_value));

	/* Read file */
	fd_config = fopen(mtd_config->config_file, "r");
	if (fd_config) {

		// read each line
		while (fgets (str_buff, MAX_BUFF_SIZE, fd_config))
		{
			memset (str_attr, 0, sizeof(str_attr));
			memset (str_value, 0, sizeof(str_value));
			//printf(" [config_file] line: %s ", str_buff);

			if (mtdLib_strings_lineIsEmpty(str_buff) == RET_OK)
				continue;
			if (mtdLib_strings_lineIsComment(str_buff) == RET_OK)
				continue;

			if (mtdLib_strings_splitByToken(str_buff, "=", str_attr, str_value) == 0) {

				mtd_lib_strings_trimNewLine(str_attr);
				mtd_lib_strings_trimNewLine(str_value);

				if (strncmp(str_attr, "IPADDR", strlen("IPADDR")) == 0) { // IPADDR
					strcpy(mtd_config->bind_ip4addr, str_value);

					//printf(" '-> IPADDR \t\t = [%s] \n", mtd_config->bind_ip4addr);
					sprintf(str_log, " '-> IPADDR \t\t = [%s] \n", mtd_config->bind_ip4addr);
					mtd_stdout_print(str_log);
				}
				else if (strncmp(str_attr, "PORT", strlen("PORT")) == 0) { // PORT
					strcpy(mtd_config->bind_port, str_value);

					//printf(" '-> PORT \t\t = [%s] \n", mtd_config->bind_port);
					sprintf(str_log, " '-> PORT \t\t = [%s] \n", mtd_config->bind_port);
					mtd_stdout_print(str_log);
				}
				else if (strncmp(str_attr, "LOG_FILE", strlen("LOG_FILE")) == 0) { // LOG_FILE
					strcpy(mtd_config->log_file, str_value);

					if (mtd_lib_fileExist(mtd_config->log_file) != RET_OK) {
						strcpy(mtd_config->log_file, "mtuliod.log");
					}
					//printf(" '-> LOG_FILE \t\t = [%s] \n", mtd_config->log_file);
					sprintf(str_log, " '-> LOG_FILE \t\t = [%s] \n", mtd_config->log_file);
					mtd_stdout_print(str_log);
				}
				else if (strncmp(str_attr, "MAX_POOL_CONN", strlen("MAX_POOL_CONN")) == 0) { // MAX_POOL_CONN
					mtd_config->max_pool_conn = atoi(str_attr); //strcpy(mtd_config->max_pool_conn, str_value);

					//printf(" '-> MAX_POOL_CONN \t = [%d] \n", mtd_config->max_pool_conn);
					sprintf(str_log, " '-> MAX_POOL_CONN \t = [%d] \n", mtd_config->max_pool_conn);
					mtd_stdout_print(str_log);
				}
				else if (strncmp(str_attr, "SECRET", strlen("SECRET")) == 0) { // SECRET
					strcpy(mtd_config->secret, str_value);

					//printf(" '-> SECRET \t\t = [%s] \n", mtd_config->secret);
					sprintf(str_log, " '-> SECRET \t\t = [%s] \n", mtd_config->secret);
					mtd_stdout_print(str_log);
				}
			}
		}
		fclose (fd_config);
	} else {
		sprintf(str_log, " #% [config_file] unable to open file: %s ", mtd_config->config_file);
		mtd_stdout_print(str_log);
		ret = RET_ERR;
		goto GT_FINAL;
	}

	//printf("ret[%d]", mtd_srv_config_file_load (mtd_config));
	ret = RET_OK;

	GT_FINAL:
	if (str_attr)
		free (str_attr);
	if (str_value)
		free (str_value);

	return ret;
}

