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
#include <getopt.h>

#include "epplib/epp_api645.h"
#include "epplib/safe.h"


typedef struct cell_opts{
	char *cell;
	int protocol;/*	0: 645-2007;1:645-1997;*/

}cell_opts_t;


void showresult(HexDivide645_struct_t *cell)
{
    printf("测试结果:\r\n"
    		"Section:[%s] \r\n"
    		"CONTROL[%s] Decrioptionp[]\r\n"
    		"LEN[%d]\r\n"
    		"Description %s\r\n",
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

void usage(){
	printf("Usage etc:\n run -p 0 -c 68473512030000689118343539383333333333333333333333333333333333333333e016 \r\n");
	printf("-p protocol[0:644-2007;1:645-1997]\r\n");
	printf("-c Hex Content Data\r\n");
}


void paras_commandline(int argc,char **argv,cell_opts_t *opt)
{
    int c;

    while (-1 != (c = getopt(argc, argv, "p:c:h"))) {
        switch (c) {
        case 'h':
            usage();
            exit(1);
            break;

        case 'p':
            if (optarg) {
            	opt->protocol=atoi(optarg);
            }
            break;
        case 'c':
            if (optarg) {
            	opt->cell=strdup(optarg);
            }
            break;

        default:
            usage();
            exit(1);
            break;
        }
    }

    if ((argc - optind) <= 0) {
        usage();
        exit(1);
    }
}








int main(int argc, char * argv[])
{

	cell_opts_t *new_cell;

	new_cell = (cell_opts_t *)safe_malloc(sizeof(cell_opts_t));


    if(!new_cell->cell || argc <2){
    	new_cell->cell = "68473512030000689118343539383333333333333333333333333333333333333333e016";
    	new_cell->protocol = 0;
    } else {
    	paras_commandline(argc,argv,new_cell);
    }
    

    printf("USAGE run protocol cell \r\n");
    printf("start to divide:\r\n%s \r\n",new_cell->cell);


    if(new_cell->protocol == 0){
    	handle645(new_cell->cell);
		handle645("68473512030000689218343539383333333333333333333333333333333333333333e016");
		handle645("68473512030000689418343539383333333333333333333333333333333333333333e016");
    }
    return 0;
}




