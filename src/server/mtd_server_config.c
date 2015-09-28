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


///* Split string from delimiter and save it on:
// * str_A : left string from delimiter
// * str_B : right string from delimiter
// */
//int mtdLib_strings_splitByDelimiter (char *str_buff, char *delimiter, char *str_A, char *str_B)
//{
//	char str_tmp[MAX_BUFF_SIZE];
//	memset(str_tmp, 0, strlen(str_tmp));
//
//	int countd;
//	int pos, posd;
//	countd = pos = posd = 0;
//
//	for (pos=0, posd=0; pos<=strlen(str_buff); pos++) {
//		// check delimiter
//		if (str_buff[pos] == delimiter) {
//			if (countd == 0) {
//				strcpy(str_A, str_tmp);
//				countd++;
//			}
//			memset(str_tmp, 0, strlen(str_tmp));
//			posd=0;
//		}
//		else {
//			// Skip string delimiter \n and \0
//			if ((str_buff[pos] == 0xa) || (str_buff[pos] == 0x0))
//				continue;
//			else { // save to buffer
//				str_tmp[posd] = str_buff[pos];
//				posd++;
//			}
//		}
//	}
//
//	//countd = 0 : delimiter not found
//	if (countd == 0) {
//		strcpy(str_A, str_tmp);
//		strcpy(str_B, "unknown");
//		return RET_NOTFOUND;
//	}
//	else { // update copy attribute value from buffer
//		strcpy(str_B, str_tmp);
//		return RET_OK;
//	}
//}



/**
* Function to read an string from a first line of file name (path FQDN of FS).
* @param filename char with path of file on Linux System
* @see show_boot_cmd
* @return a char with string read from file.
*/
//void mtdLib_file_FileReadLine (char *filename, char *buff)
//{
//	FILE *fd_config;
//	memset(buff, 0, sizeof(buff));
//
//	/* Read file */
//	fd_config = fopen(filename, "r");
//	if (fd_config) {
//		fscanf (fd_config, "%s", buff);
//		fclose (fd_config);
//	} else {
//
//		printf(" %% Unable to find file [%s]\n", filename);
//		return EXIT_ERR;
//	}
//
//	return RET_OK;
//}
