//
//  main645.c
//  electpower
//
//  Created by 雷邓 on 17/2/27.
//  Copyright © 2017年 雷邓. All rights reserved.
//

#include <string.h>

#include "../DLT645/app645.h"
#include "../PubFunctions.h"
#include "../main.h"
#include "../safe.h"



static HexDivide645_struct_t *CellDivide;

/*
 * Application PART
 * 应用层
 * */


char *app_pick()
{
	char *r;

	/* * SERVER REQUEST * */

	char *hexctl;
	int dlen;
	hexctl = CellDivide->HexControl;
	dlen = CellDivide->DataLen;

	//7.1 读数据
	if( strcmp(hexctl,"11") == 0 &&  dlen > 4 ){
		return app_s_request_data71(CellDivide);
	}
	//7.1 回复
	else if(strcmp(hexctl,"91") ==0 && dlen > 4){
		return app_c_answer_data71(CellDivide);
	}
	//7.1 回复后续
	else if(strcmp(hexctl,"B1") ==0 && dlen > 4){
		return app_c_answer_data_flw71(CellDivide);
	}
	//7.1 异常
	else if(strcmp(hexctl,"D1") ==0 && dlen == 1){
		return app_c_abnormal71(CellDivide);
	}
	//7.2 读后续数据
	else if(strcmp(hexctl,"12") ==0 && dlen == 5){
		return app_s_request_data_flw72(CellDivide);
	}
	//7.2 回复
	else if(strcmp(hexctl,"92") ==0 && dlen > 5){
		return app_c_send_data_flw72(CellDivide);
	}
	//7.2 回复后续
	else if(strcmp(hexctl,"B2") ==0 && dlen > 5){
		return app_c_send_data_flwflw72(CellDivide);
	//7.2 异常回复
	}
	else if(strcmp(hexctl,"D2") ==0 && dlen == 1){
			return app_c_abnormal72(CellDivide);
	}
	//7.3 写数据
	else if(strcmp(hexctl,"14") ==0 && dlen == 12){
		return "function 7.3 write on going";
	}
	//7.3 回复
	else if(strcmp(hexctl,"94") ==0 && dlen == 0){
		return "function 7.3 normal response e on going";
	}
	//7.3 异常回复
	else if(strcmp(hexctl,"D4") ==0 && dlen == 1){
			return app_c_abnormal73(CellDivide);
	}
	//7.4 读通信地址
	else if(strcmp(hexctl,"13") ==0 && dlen == 0){
		return app_s_request_data74(CellDivide);
	}
	//7.4 回复
	else if(strcmp(hexctl,"93") ==0 && dlen == 6){
		return app_c_send_data74(CellDivide);
	}

	//没有找到
	else{
		safe_asprintf(&r,"NOT support CONTROL [%s] LEN [%d]",hexctl, dlen);
		return r;
	}

}


ControlDes_struct_t *get_ctl_des(char *HexCtl)
{
	ControlDes_struct_t *ctl_struct = safe_malloc(sizeof(ControlDes_struct_t));

	char *bins = string2bins(HexCtl);

	ctl_struct->Direction_D7 = *bins;
	ctl_struct->ClientRes_D6 = *(bins+1);
	ctl_struct->SubFrmFlg_D5 = *(bins+2);
	ctl_struct->FunctBit_D = safe_strdup(bins+3);

	return ctl_struct;
}


int check_cell_bytes(HexDivide645_struct_t *cell)
{
	int flg=0;
	if(strcmp(cell->HexStt,"68")!=0 || strcmp(cell->HexStt2,"68")!=0 || strcmp(cell->HexEnd,"16")!=0)
		flg=-1;

	return flg;
}




/*
 * main
 * */
HexDivide645_struct_t *main645(char *HexCell)
{
	//判断字符是否合法
    if( false == IsCellLegal(HexCell) ){
        return NULL;
    }
	int celllen=strlen(HexCell);	//cell长度

    CellDivide=safe_malloc(sizeof(HexDivide645_struct_t));

    //存储基本信息
    CellDivide->input = safe_strdup(HexCell);
    CellDivide->protocol="DL/T-645-2007";
    
    //分割
    CellDivide->HexStt = GetStringFromCell(HexCell,1,2);
    CellDivide->addr=GetStringFromCell(HexCell, 3, 14);
    CellDivide->HexStt2=GetStringFromCell(HexCell, 15, 16);
    CellDivide->HexControl=GetStringFromCell(HexCell, 17, 18);
    CellDivide->DataLen=hex2int(GetStringFromCell(HexCell, 19, 20));
    if(CellDivide->DataLen >0){
    	CellDivide->HexData = GetStringFromCell(HexCell, 21, celllen-4);
    	CellDivide->HexDataMinus33=string_minus33(CellDivide->HexData);
    }
    CellDivide->HexCS=GetStringFromCell(HexCell, celllen-3, celllen-2);
    CellDivide->HexEnd=GetStringFromCell(HexCell, celllen-1,celllen);
    
    if(check_cell_bytes(CellDivide) !=0)
    	return NULL;


    //控制域解析

    CellDivide->addrDes = string_reverse(CellDivide->addr);
    CellDivide->ControlDes= get_ctl_des(CellDivide->HexControl);
    CellDivide->DataDes = safe_malloc(sizeof(DataDes_struct_t));

    //根据信息获取最终数据描述
    CellDivide->description = app_pick();

    return CellDivide;
    
}
