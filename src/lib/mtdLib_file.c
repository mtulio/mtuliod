/*
 * mtdLib_file.c
 *
 *  Created on: 27 de set de 2015
 *      Author: mtulio
 */

#include <stdlib.h>
#include <string.h>

/** NOT USED
* Function to read an string from a first line of file name (path FQDN of FS).
* @param filename char with path of file on Linux System
* @see show_boot_cmd
* @return a char with string read from file.
*/
void mtd_lib_str_readLineFile (char *filename, char *buff)
{
	FILE *fd_config;
	memset(buff, 0, sizeof(buff));

	/* Read file */
	fd_config = fopen(filename, "r");
	if (fd_config) {
		fscanf (fd_config, "%s", buff);
		fclose (fd_config);
	} else {

		printf(" %% Unable to find file [%s]\n", filename);
		return EXIT_ERR;
	}

	return RET_OK;
}



