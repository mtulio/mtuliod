/*
 * mtsh.h
 *
 *  Created on: 28 de set de 2015
 *      Author: mtulio
 */

#ifndef SRC_CLIENT_MTSH_H_
#define SRC_CLIENT_MTSH_H_

#include<string>

/* Defuns */
#define	CMD_STR_VERSION		"version"

/* Class MTsh */
class MTsh
{
	private :
		std::string config_file;

	public :
		MTsh(std::string config_file) { this->config_file=config_file; };
		~MTsh(){};

		//std::string *mtsh_readline(void);
		char *mtsh_readline(void);
		int mtsh_exec(char *line);
		int mtsh_strSplitLine(char *line, std::string str_cmd, std::string str_arg);
		int mtsh_execFunc(std::string str_cmd, std::string str_arg);

};
//char * mtsh_readline();


#endif /* SRC_CLIENT_MTSH_H_ */
