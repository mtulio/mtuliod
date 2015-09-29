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

	cout<<"line: "<<mtsh_readline()<<endl;

	exit(0);
}

