//
//  PubFunctions.c
//  electpower
//
//  Created by 雷邓 on 17/2/27.
//  Copyright © 2017年 雷邓. All rights reserved.
//
#include <stdio.h>
#include <errno.h>
#include <syslog.h>
#include <stdarg.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>
#include <mm_malloc.h>
#include <string.h>

#include "PubFunctions.h"
#include "main.h"
#include "safe.h"
#include "debug.h"


bool _IsCellLegal(const char *HexCell)
{
    char *tmp;
    
    tmp=safe_strdup(HexCell);
    while(*tmp){
        if( !((*tmp>='0' || *tmp<='9') ||  (*tmp>='a' || *tmp<='z') ||  (*tmp>='A' || *tmp<='Z') )){
            debug(LOG_ERR,"\r\nThe cell is illegal!\r\n%s \r\ninclude [%c] ",HexCell,*tmp);
            return false;
        }
        tmp++;
    }
    
    return true;
}


char *GetStringFromCell(const char *cell, int start,  int end)
{
    if( strlen(cell) < end || start < 1 || end < 1 || start >end ){
        debug(LOG_ERR,"the chars position[%d,%d] you fetch is over the length of [%s]",start,end,cell);
        return NULL;
    }
    
    int len=end-start +1;

    char *tmp_r = safe_malloc(len+1);
    int i=0;
    for( ; i<len && (*(tmp_r+i) = *(cell+start + i-1) );i++);
    *(tmp_r+i)='\0';
    return tmp_r;
}


char *char2bins(char ch)
{
	char* quads[] = {"0000", "0001", "0010", "0011", "0100", "0101",
	                     "0110", "0111", "1000", "1001", "1010", "1011",
	                     "1100", "1101", "1110", "1111"};
	char *res;
    if (ch >= '0' && ch <= '9')
    	res = quads[ch - '0'];
    if (ch >= 'A' && ch <= 'F')
    	res = quads[10 + ch - 'A'];
    if (ch >= 'a' && ch <= 'f')
    	res = quads[10 + ch - 'a'];

    return res;

}

char *string2bins(char *str)
{

	char *response=safe_malloc(sizeof(char *));
	for(;*str != '\0' && strncat(response,char2bins(*str),4);str++);

	return response;
}


char *string_reverse(char *tmp_str)
{
	if(!tmp_str)
		printf("reverse_string , paras is NULL! ERROR!");
	if((strlen(tmp_str) % 2) !=0 ){
		printf("reverse_string : error! %s len is %d",tmp_str,strlen(tmp_str));
	}

	char *addr;
	addr=safe_malloc(strlen(tmp_str)+1);

	int qty = strlen(tmp_str)/2;
	int i=0;
	for(;i<qty;i++){
		*(addr+2*i) = *(tmp_str+2*qty-2*i-2);
		*(addr+2*i+1) = *(tmp_str+2*qty-2*i-1);
	}

	return addr;
}


/**
 * hex2int
 * take a hex string and convert it to a 32bit number (max 8 hex digits)
 */
int hex2int(char *hex)
{
	int val = 0;

    while (*hex) {
        // get current character then increment
        int byte = *hex++;
        // transform hex character to the 4bit equivalent number, using the ascii table indexes
        if (byte >= '0' && byte <= '9') byte = byte - '0';
        else if (byte >= 'a' && byte <='f') byte = byte - 'a' + 10;
        else if (byte >= 'A' && byte <='F') byte = byte - 'A' + 10;
        // shift 4 to make space for new digit, and add the 4 bits of the new digit
        val = (val << 4) | (byte & 0xF);
    }

    return val;
}

char *string_minus33(char *str2s)
{
	if(!str2s)
		return NULL;

	if( (strlen(str2s) % 2) !=0 )
		return NULL;

	int l = strlen(str2s)/2;

	char *r = safe_strdup(str2s);

	int i=0;
	int tmp;
	char ch[3];
	for(;i<l && str2s[2*i+1] != '\0';i++){
		ch[0]=str2s[2*i];
		ch[1]=str2s[2*i+1];
		ch[2]='\0';
		tmp = hex2int(ch) -51; // minus 33H
		if(tmp<0)
			tmp = tmp+256;
		if(tmp<16)
			r[2*i] = '0';
		else
			r[2*i] = (char)(tmp/16+'0');
		r[2*i+1] = (char)(tmp%16+'0');
	}

	r[2*l]='\0';
	return r;
}

