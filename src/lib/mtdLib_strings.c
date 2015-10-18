/* 
 * String manipulation functions
 * Created by: Marco Túlio
 * */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <ctype.h>  /*isspace()*/

#include <mtuliod.h>

/* Function to get number of Columns by delimiter from an string */
int mtdLib_str_getColNumbers(char *array, char delimiter)
{
	int pos, count;
	pos = count = 1;
	for (pos=0; array[pos]!='\0'; pos++)
		if (array[pos] == delimiter)
			count++;

	// check line is not finishing with delimiter. Eg. delimiter=',': [A,B,]
//	if (array[pos-1]!=delimiter)
//		count++;

	return count;
}

/* Get integer value from column by position of delimiter - number of
 * column could be get by function mtdLib_str_getColNumbers() */
void mtdLib_str_getColByDelPos_int(char *array_in, char delimiter, int posDel, int *resp)
{
	int count=1; // considering that exist at least delimiter

	char *buff;
	buff = malloc(sizeof(char *)*strlen(array_in));
	memset(buff,strlen(buff),'\0');

	for (int posA=0, posB=0; posA<strlen(array_in); posA++) {
		if (array_in[posA]==delimiter)
			count++;
		else
			if (count==posDel) { // save data of Column
				buff[posB]=array_in[posA];
				posB++;
			}
	}
	*resp=atoi(buff);
	//printf("%s(resp[%d]) buff(%s)\n", __FUNCTION__, resp, buff);
	if (buff) free(buff);

	return;
}

/* Get integer value from column by position of delimiter - number of
 * column could be get by function mtdLib_str_getColNumbers() */
//void mtdLib_str_getColByDelPos_str(char *array_in, char delimiter, int posDel, char **resp)
void mtdLib_str_getColByDelPos_str(char *array_in, char delimiter, int posDel, char *resp)
{
	int count=0; // considering that exist at least delimiter

	//printf("\n %s : %s", __FUNCTION__, array_in);

	char *buff;
	buff = (char *)malloc(sizeof(array_in));
	memset(buff, sizeof(array_in),0);

	for (int pos=0, posB=0; pos<strlen(array_in); pos++) {
		if (array_in[pos]==delimiter)
			count++;
		else
			if (count==posDel) { // save data of Column
				buff[posB]=array_in[pos];
				posB++;
			}
	}
	strcpy(resp, buff);
	printf("\n %s(resp[%s]) buff(%s)", __FUNCTION__, resp, buff);
	if (buff) free(buff);

	return;
}


//mtdLib_str_getStrlenByDelPos(msg_cmd, ' ', argc);
int mtdLib_str_getStrlenByDelPos(char *array_in, char delimiter, int posDel)
{
	int count=0; // considering that exist at least delimiter
	int str_len = 0;

	//printf("\n %s : %s", __FUNCTION__, array_in);

//	char *buff;
//	buff = (char *)malloc(sizeof(array_in));
//	memset(buff, sizeof(array_in),0);

	for (int pos=0, posB=0; pos<strlen(array_in); pos++) {
		if (array_in[pos]==delimiter)
			count++;
		else
			if (count==posDel) { // save data of Column
				str_len++;
			}
	}
//	strcpy(resp, buff);
	printf("\n %s(array_in[%s]) len(%d)", __FUNCTION__, array_in, str_len);
//	if (buff) free(buff);

	return str_len;
}

/* Split string from delimiter and save it on:
 * str_A : left string from delimiter
 * str_B : right string from delimiter
 */
/* TODO: check strtok function to avoid above*/
int mtdLib_strings_splitByDelimiter (char *str_buff, char *delimiter, char *str_A, char *str_B)
{
	char str_tmp[MAX_BUFF_SIZE];
	memset(str_tmp, 0, strlen(str_tmp));

	int countd;
	int pos, posd;
	countd = pos = posd = 0;

	for (pos=0, posd=0; pos<=strlen(str_buff); pos++) {
		// check delimiter
		if (str_buff[pos] == *delimiter) {
			if (countd == 0) {
				strcpy(str_A, str_tmp);
				countd++;
			}
			memset(str_tmp, 0, strlen(str_tmp));
			posd=0;
		}
		else {
			// Skip string delimiter \n and \0
			if ((str_buff[pos] == 0xa) || (str_buff[pos] == 0x0))
				continue;
			else { // save to buffer
				str_tmp[posd] = str_buff[pos];
				posd++;
			}
		}
	}

	//countd = 0 : delimiter not found
	if (countd == 0) {
		strcpy(str_A, str_tmp);
		strcpy(str_B, "unknown");
		return RET_NOTFOUND;
	}
	else { // update copy attribute value from buffer
		strcpy(str_B, str_tmp);
		return RET_OK;
	}
}


int mtdLib_strings_splitByToken (char *str_line, char *delimiter, char *str_A, char *str_B)
{

	char *str1, *str2, *token, *subtoken;
	char *saveptr1, *saveptr2;
	int j;

	for (j = 1, str1 = str_line; ; j++, str1 = NULL) {
          token = strtok_r(str1, delimiter, &saveptr1);
          if (token == NULL)
              break;

          if (j == 1)
        	  strncpy(str_A, token, strlen(token));
          else if (j==2)
        	  strncpy(str_B, token, strlen(token));
          else
        	  break;

//          printf("%d, strA=%s\n", j, str_A);
//          printf("%d, strB=%s\n", j, str_B);

//          for (str2 = token; ; str2 = NULL) {
//              subtoken = strtok_r(str2, argv[3], &saveptr2);
//              if (subtoken == NULL)
//                  break;
//              printf(" --> %s\n", subtoken);
//          }
      }

	if ((strlen(str_A) && strlen(str_B)) > 0)
		return RET_OK;
	else
		return RET_ERR;
}

/* Check if line is an comment '#' */
int mtdLib_strings_lineIsComment(char *str_line)
{
	if (strlen(str_line) > 1) {
		/* Check comment */
		if (str_line[0] == '#')
			return RET_OK;
		else if (str_line[0] == '/')
			return RET_OK;
		else if (str_line[0] == ';')
			return RET_OK;
	}

	return RET_ERR;
}

/* Check if line is an comment '#' */
int mtdLib_strings_lineIsEmpty(char *str_line)
{
	if (strlen(str_line) > 1)
		return RET_ERR;

	return RET_OK;
}

//***************/
static int mtd_strings_parsedSetArgs(char *args, char **argv)
{
	int count = 0;
	while (isspace(*args)) ++args;
	while (*args) {
		if (argv) argv[count] = args;
		while (*args && !isspace(*args)) ++args;
		if (argv && *args) *args++ = '\0';
		while (isspace(*args)) ++args;
		count++;
	}
	return count;
}

//char **parsedargs(char *args, int *argc, char *argv)
void mtd_strings_parsedArgs(char *args, int *argc, char *av[])
{
	char **argv = NULL;
	int    argn = 0;

	if (args && *args
			&& (args = strdup(args))
			&& (argn = mtd_strings_parsedSetArgs(args, NULL))
			&& (argv = malloc((argn+1) * sizeof(char *))))
	{

		*argv++ = args;
		argn = mtd_strings_parsedSetArgs(args, argv);
	}

	if (args && !argv)
		free(args);

	*argc = argn;

    /* Copy to original argv (av) */
	for (int i = 0; i < argn; i++)
		strncpy(av[i], argv[i], strlen(argv[i]));
}

 void mtd_strings_parsedFree(char **argv)
 {
   if (argv) {
     free(argv[-1]);
     free(argv-1);
   }
 }


 /*
 * Trim a string (removing new line delimited).
 * @param char message is a string to trim
 * @see mtd_server_cmd_run_SETPASS()
 * @return none
 */
//void mtd_lib_strings_trimLine (char *str)
//{
//  char msgBuff[strlen(str)];
//  memset(msgBuff, '\0', strlen(msgBuff));
//  for (int pos=0; pos<strlen(str); pos++) {
//    /*printf("F[%s] char[%p]\n", __FUNCTION__, str[pos]);*/
//
// 	/* Check on alphanumeric chars plus '.' on ASCII table */
// 	if ( ( (str[pos]==0x2e) ||
// 			(str[pos]>=0x30 && str[pos]<=0x39) ||
//			(str[pos]>=0x41 && str[pos]<=0x5A) ||
//			(str[pos]>=0x61 && str[pos]<=0x7A)) ) {
//
// 		msgBuff[pos]=str[pos];
// 	}
// 	else {
// 		msgBuff[pos]='\0';
// 		break;
// 	}
//  }
//
//  strncpy(str, msgBuff, strlen(str));
//}

/*
* Trim a string (removing new line delimited).
* @param char message is a string to trim
* @see mtd_server_cmd_run_SETPASS()
* @return none
*/
void mtd_lib_strings_trimNewLine (char *str)
{
	  char msgBuff[strlen(str)];
	  memset(msgBuff, '\0', strlen(msgBuff));
	  for (int pos=0; pos<strlen(str); pos++) {
	    /*printf("F[%s] char[%p]\n", __FUNCTION__, str[pos]);*/

	 	/* Check on alphanumeric chars plus '.' on ASCII table */
	 	if ( !(str[pos]==0xA) ) {
	 		msgBuff[pos]=str[pos];
	 	}
	 	else {
	 		msgBuff[pos]='\0';
	 		break;
	 	}
	  }

	  strncpy(str, msgBuff, strlen(str));
}

/* Print a IP address from a human-view */
void mtd_lib_strings_showIp(int ip, char *str)
{
	unsigned char bytes[4];
    bzero(str, sizeof(str));

    bytes[0] = ip & 0xFF;
    bytes[1] = (ip >> 8) & 0xFF;
    bytes[2] = (ip >> 16) & 0xFF;
    bytes[3] = (ip >> 24) & 0xFF;

    sprintf(str, "%d.%d.%d.%d", bytes[3], bytes[2], bytes[1], bytes[0]);
}
