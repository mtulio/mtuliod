/*
 * mtd_server_cmd.h
 *
 *  Created on: 17 de out de 2015
 *      Author: mtulio
 */

#ifndef SRC_SERVER_MTD_SERVER_CMD_H_
#define SRC_SERVER_MTD_SERVER_CMD_H_

int mtd_srv_cmd_parseMessage(char *message/*, char *message_out*/);
void mtd_srv_cmd_strTrim (char *message, char *msgBuff);


#endif /* SRC_SERVER_MTD_SERVER_CMD_H_ */
