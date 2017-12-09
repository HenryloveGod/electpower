//
//  main645.h
//  electpower
//
//  Created by 雷邓 on 17/2/27.
//  Copyright © 2017年 雷邓. All rights reserved.
//

#ifndef main645_h
#define main645_h

#include <stdio.h>

#include "../PubFunctions.h"

#endif /* main645_h */



//数据区解析结果格式
typedef struct DataDes_struct{
    char *HexKey;
    char *HexValue;
    char *HexSEQ;
    char *HexERR;
    char *res_addr;
}DataDes_struct_t;


//控制域解析结果格式
typedef struct ControlDes_struct{
    char Direction_D7;
    char ClientRes_D6;
    char SubFrmFlg_D5;
    char *FunctBit_D;
}ControlDes_struct_t;

typedef struct HexDivide645_struct{
    char *input;//input digit string
    char *protocol;//645,1376 protocol
    //Hex chars divide
    char *HexStt; 		//68
    char *addr;			//地址
    char *HexStt2;		//68
    char *HexControl;	//控制域
    int DataLen;			//长度
    char *HexData;		//数据
    char *HexDataMinus33;		//减33的数据
    char *HexCS;		//校验CS
    char *HexEnd;		//16结束
    
    //解析结果
    char *addrDes;
    char *section;
    ControlDes_struct_t *ControlDes;	//控制域解析结果
    DataDes_struct_t *DataDes;		//数据区解析结果


    char *description; //最终描述


}HexDivide645_struct_t;


/*
 * main
 * */
HexDivide645_struct_t *main645(char *HexCell);



