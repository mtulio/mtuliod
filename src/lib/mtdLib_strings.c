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
	pos = count = 0;
	for (pos=0; array[pos]!='\0'; pos++)
		if (array[pos] == delimiter)
			count++;

	// check line is not finishing with delimiter. Eg. delimiter=',': [A,B,]
	if (array[pos-1]!=delimiter)
		count++;

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


/* Split string from delimiter and save it on:
 * str_A : left string from delimiter
 * str_B : right string from delimiter
 */
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
