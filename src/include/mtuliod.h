/*
 * mtuliod.h
 *
 *  Created on: 27 de set de 2015
 *      Author: mtulio
 */

#ifndef SRC_INCLUDE_MTULIOD_H_
#define SRC_INCLUDE_MTULIOD_H_

/* Config file structure */
typedef struct {
	char config_file[100];
	char bind_ip4addr[16];
	char bind_port[8];
	char log_file[100];
	char secret[16];
	unsigned int max_pool_conn;
	int test;
} mtd_srv_cfg_t;

mtd_srv_cfg_t *mtd_config;

/* Available commands */
typedef enum {
	cmd_help,
	cmd_hostname,
	cmd_exit,
	cmd_setpasswd
} mtuliod_cmds;

/* Return codes */
#define EXIT_ERR	-1
#define EXIT_OK		0

#define RET_OK			EXIT_OK
#define RET_ERR			1
#define RET_NOTFOUND	10

/* Max buffer size */
#define MAX_BUFF_SIZE	200

/* CLI */
#define PFIX_CLI "[MTd]"


#endif /* SRC_INCLUDE_MTULIOD_H_ */
