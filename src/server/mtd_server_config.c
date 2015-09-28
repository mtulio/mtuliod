/* Parse and load config from file */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include <mtuliod.h>

/* Function to be defined on .h */
int mtd_srv_config_main(mtd_srv_cfg_t *mtd_config);
int mtd_srv_config_readData(mtd_srv_cfg_t *mtd_config);

/* Mainc server config file
 * - Check file exist
 * - Parse config file to struct
 */
int mtd_srv_config_main(mtd_srv_cfg_t *mtd_config)
{
	FILE *fd_config;

	/* Check file exist */
	fd_config = fopen(mtd_config->config_file, "r");
	if (fd_config) {
		printf(" # Configuration file was found [%s]", mtd_config->config_file);
		if (fd_config)
				fclose(fd_config);
	} else {
		//perror("Cannot open config file. Error ");
		printf(" %% Unable to find config file [%s]\n", mtd_config->config_file);
		return EXIT_ERR;
	}

	/* Reading data */
	printf(" reading...\n");
	if (mtd_srv_config_readData(mtd_config) != 0 )
			return RET_ERR;

	/* End closing all pointers */
	finish:

	return RET_OK;
}

/**
* Function to read data from config file.
* @param mtd_config is a struct with server configuration file
* @see
* @return a int with status of operation
*/
int mtd_srv_config_readData(mtd_srv_cfg_t *mtd_config)
{
	FILE *fd_config;

	char str_buff[MAX_BUFF_SIZE];
	char str_attr[MAX_BUFF_SIZE];
	char str_value[MAX_BUFF_SIZE];
	memset (str_buff, 0, sizeof(str_buff));

	/* Read file */
	fd_config = fopen(mtd_config->config_file, "r");
	if (fd_config) {

		// read each line
		while (fgets (str_buff, MAX_BUFF_SIZE, fd_config))
		{
			//printf(" [config_file] line: %s ", str_buff);

//			if (mtdLib_strings_lineIsEmpy(str_buff) == 0)
//				continue;
//			if (mtdLib_strings_lineIsComment(str_buff) == 0)
//				continue;

			if (mtdLib_strings_splitByDelimiter(str_buff, '=', &str_attr, &str_value) == 0) {

				if (strncmp(str_attr, "IPADDR", strlen("IPADDR")) == 0) { // IPADDR
					strcpy(mtd_config->bind_ip4addr, str_value);
					printf(" '-> IPADDR \t\t = [%s] \n", mtd_config->bind_ip4addr);
				}
				else if (strncmp(str_attr, "PORT", strlen("PORT")) == 0) { // PORT
					strcpy(mtd_config->bind_port, str_value);
					printf(" '-> PORT \t\t = [%s] \n", mtd_config->bind_port);
				}
				else if (strncmp(str_attr, "LOG_FILE", strlen("LOG_FILE")) == 0) { // LOG_FILE
					strcpy(mtd_config->log_file, str_value);
					printf(" '-> LOG_FILE \t\t = [%s] \n", mtd_config->log_file);
				}
				else if (strncmp(str_attr, "MAX_POOL_CONN", strlen("MAX_POOL_CONN")) == 0) { // MAX_POOL_CONN
					mtd_config->max_pool_conn = atoi(str_attr); //strcpy(mtd_config->max_pool_conn, str_value);
					printf(" '-> MAX_POOL_CONN \t = [%d] \n", mtd_config->max_pool_conn);
				}
			}
		}

		fclose (fd_config);
	} else {
		printf(" [config_file] unable to open file: %s ", mtd_config->config_file);
	}


	//printf("ret[%d]", mtd_srv_config_file_load (mtd_config));

	return RET_OK;
}

/**/
/*int mtdLib_strings_lineIsEmpy(char *line)
{

}*/
