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

/* Exec a command parsing it. */
void *MTsh::mtsh_exec(char *line)
{
	std::cout<<"line: "<<line<<std::endl;
    return 0;
}
