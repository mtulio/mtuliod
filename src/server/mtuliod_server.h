/*
 * mtuliod_server.h
 *
 *  Created on: 17 de out de 2015
 *      Author: mtulio
 */

#ifndef _MTULIOD_SERVER_H_
#define _MTULIOD_SERVER_H_

int mtd_srv_init(mtd_srv_cfg_t *mtd_config, struct sockaddr_in *server, int *socket_desc);
void *mtd_srv_connection_handler(void *socket_data);
int mtd_srv_main(mtd_srv_cfg_t *mtd_config);
//int main(int argc , char *argv[]);

#endif /* _MTULIOD_SERVER_H_ */
