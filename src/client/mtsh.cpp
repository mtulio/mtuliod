/*
 * mtsh.cpp
 *
 *  Created on: 28 de set de 2015
 *      Author: mtulio
 */

/* C libs */
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>

/* C++ libs */
#include <iostream>
#include <cstdio>
#include <string>
#include <vector>

/* Project libs */
#include <mtsh.h>
#include <mtuliosh.h>

/* Read a string, and return a pointer to it.  Returns NULL on EOF. */
char *MTsh::mtsh_readline(void)
{
    static char *line = NULL;
    if (line) {
        free (line);
        line = NULL;
    }

    line = readline (SH_STR_PREFIX);

    /* if (line && *line)
        add_history (line);*/

    return (line);
}

/* Exec a command. */
int MTsh::mtsh_exec(char *line)
{
	std::cout<<"mtsh_exec"<<std::endl;
	std::string str_cmd, str_arg;
	int ret = 0;
	//std::cout<<"line: "<<line<<std::endl;


	//TODO: parse_cmd
	if (MTsh::mtsh_strSplitLine(line, str_cmd, str_arg)) {
		std::cout<<"Error Split String"<<std::endl;
		return (1);
	}

	//TODO: exec_func
	ret = MTsh::mtsh_execFunc(str_cmd, str_arg);
	if (!ret) {
		std::cout<<"Error Exec function"<<std::endl;
		return 1;
	}

	return 0;
}

/* Split a command (first string) to argument (all others) */
#include <vector>

int MTsh::mtsh_strSplitLine(char *line, std::string str_cmd, std::string str_arg)
{
	std::cout<<"mtsh_strSplitLine()"<<std::endl;

//	int count = 0;
//	std::string buf; // Have a buffer string
//	std::stringstream ss; // Insert the string into a stream
//
//	std::vector<std::string> tokens; // Create vector to hold our words
//
//	std::cout<<line<<std::endl;
//	ss<<line;
//
//	return 1;
//
//	str_cmd.clear();
//	str_arg.clear();
//
//    std::cout<<"line: "<<line<<std::endl;
//    std::cout<<"str_cmd: "<<str_cmd<<std::endl;
//    std::cout<<"str_arg: "<<str_arg<<std::endl;
//
//    while (ss >> buf) {
//        tokens.push_back(buf);
//        if (count==0)
//        	str_cmd.copy(buf, buf.length(), 0);
//        else
//        	str_arg=str_arg+" "+buf;
//    }

    return 1;
}

/* Exec a command according str_cmd */
int MTsh::mtsh_execFunc(std::string str_cmd, std::string str_arg)
{
	std::cout<<"mtsh_execFunc"<<std::endl;

	return 1;

}

