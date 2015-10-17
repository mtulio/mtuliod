/* 
 * String manipulation functions
 * Created by: Marco Túlio
 * */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
		if (str_buff[pos] == delimiter) {
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


//***************/
static int setargs(char *args, char **argv)
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
void parsedargs(char *args, int *argc, char *av[])
 {
    char **argv = NULL;
    int    argn = 0;

    if (args && *args
     && (args = strdup(args))
     && (argn = setargs(args,NULL))
     && (argv = malloc((argn+1) * sizeof(char *)))) {
       *argv++ = args;
       argn = setargs(args,argv);
    }

    if (args && !argv) free(args);

    *argc = argn;

    /* Copy to original argv (av) */
    for (int i = 0; i < argn; i++)
    	strncpy(av[i], argv[i], strlen(argv[i]));

}

 void freeparsedargs(char **argv)
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
void mtd_lib_strings_trimLine (char *str)
{
  char msgBuff[strlen(str)];
  memset(msgBuff, '\0', strlen(msgBuff));
  for (int pos=0; pos<strlen(str); pos++) {
    /*printf("F[%s] char[%p]\n", __FUNCTION__, str[pos]);*/

 	/* Check on alphanumeric chars plus '.' on ASCII table */
 	if ( ( (str[pos]==0x2e) ||
 			(str[pos]>=0x30 && str[pos]<=0x39) ||
			(str[pos]>=0x41 && str[pos]<=0x5A) ||
			(str[pos]>=0x61 && str[pos]<=0x7A)) ) {

 		msgBuff[pos]=str[pos];
 	}
 	else {
 		msgBuff[pos]='\0';
 		break;
 	}
  }

  strncpy(str, msgBuff, strlen(str));
}


