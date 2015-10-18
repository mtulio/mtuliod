/*
 * mtuliod.h
 *
 *  Created on: 27 de set de 2015
 *      Author: mtulio
 */

#ifndef SRC_INCLUDE_MTULIOD_H_
#define SRC_INCLUDE_MTULIOD_H_

#include <mtd_defs.h>

/* Server config file structure */
typedef struct {
	char config_file[100];
	char bind_ip4addr[16];
	char bind_port[8];
	char log_file[100];
	char secret[16];
	unsigned int max_pool_conn;
} mtd_srv_cfg_t;

mtd_srv_cfg_t *mtd_config;

/* Available commands */
typedef enum {
	CMD_HELP,
	CMD_HOSTNAME,
	CMD_EXIT,
	CMD_SETPASSWD
} mtuliod_cmds_t;

/* Return codes */
#define EXIT_ERR	-1
#define EXIT_OK		0

#define RET_OK			EXIT_OK
#define RET_ERR			1
#define RET_NOTFOUND	10
#define RET_IOERR		20

/* Max buffer size */
#define MAX_BUFF_SIZE	200
#define MAX_CONFIG_SIZE_ATTR	64
#define MAX_CONFIG_SIZE_VALUE	256

/* CLI */
#define PFIX_CLI "[MTd]"

/* Global options */
//typedef enum {
//	FLAG_DAEMON
//} mtd_opt_flag;

#define FLAG_DISABLED	0
#define FLAG_ENABLED	1

typedef struct {
	uint16_t daemon;
	uint16_t log;
} mtd_options_t;

mtd_options_t *mtd_opts;


#endif /* SRC_INCLUDE_MTULIOD_H_ */
