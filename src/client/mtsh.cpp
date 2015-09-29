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
#include <mtuliosh.h>

/* Read a string, and return a pointer to it.  Returns NULL on EOF. */
char * mtsh_readline(void)
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
