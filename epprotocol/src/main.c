//
//  main.c
//  electpower
//
//  Created by 雷邓 on 17/2/27.
//  Copyright © 2017年 雷邓. All rights reserved.
//

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "DLT645/main645.h"



void showresult(HexDivide645_struct_t *cell)
{
    printf("result:\r\nSection : [%s] CONTROL [%s] LEN [%d]\r\n Description %s\r\n",
    		cell->section,
    		cell->HexControl,
			cell->DataLen,
			cell->description);
}


void handle645(char *cell)
{
	HexDivide645_struct_t *divide645;
    divide645 = main645(cell);
    showresult(divide645);

}


int main(int argc, char * argv[])
{
    char *cell;
    char * protocol;

    protocol =(char *) argv[1];
    cell = argv[2];
    if(!cell || argc <2)
    	cell = "68473512030000689118343539383333333333333333333333333333333333333333e016";
    protocol = "645";
    
    printf("start to divide:\r\n%s \r\n",cell);


    if(strcmp(protocol,"645") == 0){
    	handle645(cell);
		handle645("68473512030000689218343539383333333333333333333333333333333333333333e016");
		handle645("68473512030000689418343539383333333333333333333333333333333333333333e016");
    }
    return 0;
}




