/*
 * mtuliosh.cpp
 * 	Main of SHELL command.
 *
 *  Created on: 28 de set de 2015
 *      Author: mtulio
 */

/* C libs */
//#include <stdio.h>
//#include <stdlib.h>
//
//#include <readline/readline.h>

/* C++ libs */
#include <iostream>
#include <cstdio>
#include <cstdlib>

/* Project libs */
#include "mtuliosh.h"
#include "mtsh.h"

using namespace std;


/*
 * Create objects to keep the shell and its configuration
 */
int main(void)
{
	MTsh mtsh ("mtulio.conf");
	char *line_read;

	//TODO: Init vectors, lists and commands structs

	/* Main loop command. */
	while ((line_read = mtsh.mtsh_readline()) != NULL)
		mtsh.mtsh_exec(line_read);

	printf ("\n");

	exit(0);
}

