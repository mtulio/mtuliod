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

#include <algorithm>  /* transform function */

/* Project libs */
#include <mtsh.h>
#include <mtsh_cmd.h>
#include <mtuliosh.h>

using namespace std;

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
	if (MTsh::mtsh_strSplitLine(line, &str_cmd, &str_arg)) {
		std::cout<<"Error Split String"<<std::endl;
		return (1);
	}

	//TODO: exec_func
	ret = MTsh::mtsh_execFunc(str_cmd, str_arg);
	if (ret != 0) {
		std::cout<<"Error Exec function"<<std::endl;
		return 1;
	}

	return 0;
}

/* Split a command (first string) to argument (all others) */
#include <vector>

/* Split line by delimiter '': */
int MTsh::mtsh_strSplitLine(char *line, std::string *str_cmd, std::string *str_arg)
{
	std::cout<<"mtsh_strSplitLine()"<<std::endl;


    //std::string s = "scott>=tiger teste";
	std::string s(line);
    std::string delim = ":";

    int start = 0U;
    int end = s.find(delim);
    while (end != std::string::npos)
    {
        //std::cout << s.substr(start, end - start) << std::endl;
        *str_cmd = s.substr(start, end - start);
        start = end + delim.length();
        end = s.find(delim, start);
    }

    //std::cout << s.substr(start, end)<<std::endl;
    *str_arg = s.substr(start, end);

    //str_cmd.erase(remove_if(str_cmd.begin(), str_cmd.end(), isspace), str_cmd.end());


    // Check string is empty
    if (str_cmd->empty()) {
    	//str_cmd->copy(str_arg, str_arg->length(), 0);
    	*str_cmd = *str_arg;
    	str_arg->erase();
    	//return 10;
    }

    std::cout<<"mtsh_strSplitLine(str_cmd) : ["<<*str_cmd<<"]"<<std::endl;
    std::cout<<"mtsh_strSplitLine(str_arg) : ["<<*str_arg<<"]"<<std::endl;


    /*if (str_arg->empty())
    	return 11;*/

    return 0;
}

/* Exec a command according str_cmd */
int MTsh::mtsh_execFunc(std::string str_cmd, std::string str_arg)
{
	std::cout<<"mtsh_execFunc"<<std::endl;

	/* Convert string to lower case */
	std::transform(str_cmd.begin(), str_cmd.end(), str_cmd.begin(), ::tolower);
	std::transform(str_arg.begin(), str_arg.end(), str_arg.begin(), ::tolower);

	if ( (str_cmd.compare(CMD_QUIT) == 0) ||
			 (str_cmd.compare(CMD_EXIT) == 0) ) {

		std::cout<<" ## Command FOUND: ["<<str_cmd<<"]"<<std::endl;
		std::cout<<" ## Exitig program..."<<std::endl;
		return 0;
	}
	else if ( str_cmd.compare(CMD_QUIT) == 0) {
		std::cout<<" ## Command FOUND: ["<<str_cmd<<"]"<<std::endl;

		std::cout<<" ## ** MTsh HELP Menu ** "<<std::endl<<std::endl;
		std::cout<<" ##\t[exit|quit] \t : Exit this program"<<std::endll;

	} else {
		std::cout<<"#% Command NOT FOUND: ["<<str_cmd<<"] not found"<<std::endl;
	}

	return 1;

}

