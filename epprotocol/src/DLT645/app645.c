/*
 * app645.c
 *
 *  Created on: 2017年5月6日
 *      Author: dl
 */

#include "../DLT645/app645.h"

#include "../safe.h"

/*
 * 7.1 读数据
 * */
char *app_s_request_data71(HexDivide645_struct_t *Cell)
{
	Cell->section = "SERVER 读数据71";
	char *final_res;
	Cell->DataDes->HexKey = string_reverse(GetStringFromCell(Cell->HexDataMinus33,1,8));
	int load_qty = Cell->DataLen -4;
	if(load_qty ==1)
		safe_asprintf(&final_res,"datakey [%s] , record number is %d",Cell->DataDes->HexKey,load_qty);
	else if(load_qty == 6){
		char *timedes;
		safe_asprintf(&final_res,"datakey [%s] , record number is %d",Cell->DataDes->HexKey,load_qty);
	}
	return final_res;
}
char *app_c_answer_data71(HexDivide645_struct_t *Cell)
{
	Cell->section = "client 回复71";
	char *final_res;
	Cell->DataDes->HexKey = string_reverse(GetStringFromCell(Cell->HexDataMinus33,1,8));
	int valuelen = Cell->DataLen -4;
	Cell->DataDes->HexValue = GetStringFromCell(Cell->HexDataMinus33,9,8+2*valuelen);
	safe_asprintf(&final_res,"datakey [%s] , datavalue [%s]",Cell->DataDes->HexKey,Cell->DataDes->HexValue );
	return final_res;
}
char *app_c_answer_data_flw71(HexDivide645_struct_t *Cell)
{
	Cell->section = "client 回复flw71";
	return app_c_answer_data71(Cell);
}
char *app_c_abnormal71(HexDivide645_struct_t *Cell)
{
	Cell->section = "client 回复app_c_abnormal71";
	char *final_res;
	Cell->DataDes->HexERR = string_reverse(GetStringFromCell(Cell->HexDataMinus33,1,2));
	safe_asprintf(&final_res,"ERR [%s]",Cell->DataDes->HexERR);
	return final_res;
}
/*
 * 7.2 读后续数据
 * */
char *app_s_request_data_flw72(HexDivide645_struct_t *Cell)
{
	Cell->section = "Server  读后续数据";
	char *final_res;
	Cell->DataDes->HexKey = string_reverse(GetStringFromCell(Cell->HexDataMinus33,1,8));
	Cell->DataDes->HexSEQ = GetStringFromCell(Cell->HexDataMinus33,9,10);
	safe_asprintf(&final_res,"datakey [%s] , seq %s",Cell->DataDes->HexKey,Cell->DataDes->HexSEQ);
	return final_res;
}
//7.2 应答
char *app_c_send_data_flw72(HexDivide645_struct_t *Cell)
{
	Cell->section = "client 应答";
	char *final_res;
	Cell->DataDes->HexKey = string_reverse(GetStringFromCell(Cell->HexDataMinus33,1,8));
	int valuelen = Cell->DataLen -5;
	Cell->DataDes->HexValue = GetStringFromCell(Cell->HexDataMinus33,9,8+2*valuelen);
	Cell->DataDes->HexSEQ = GetStringFromCell(Cell->HexDataMinus33,9+2*valuelen,10+2*valuelen);
	safe_asprintf(&final_res,"datakey [%s] , datavalue [%s] dataSEQ [%s]",Cell->DataDes->HexKey,Cell->DataDes->HexValue,Cell->DataDes->HexSEQ );
	return final_res;
}
//7.2 后续应答
char *app_c_send_data_flwflw72(HexDivide645_struct_t *Cell)
{
	return app_c_send_data_flw72(Cell);
}
//7.2 异常应答
char *app_c_abnormal72(HexDivide645_struct_t *Cell)
{
	return app_c_abnormal71(Cell);
}
//7.3 异常应答
char *app_c_abnormal73(HexDivide645_struct_t *Cell)
{
	return app_c_abnormal71(Cell);
}
/*
 * 7.4 读读通信地址
 * */
char *app_s_request_data74(HexDivide645_struct_t *Cell)
{
	return "读通信地址";
}
//7.4 通信地址应答
char *app_c_send_data74(HexDivide645_struct_t *Cell)
{
	char *final_res;
	Cell->DataDes->res_addr = string_reverse(GetStringFromCell(Cell->HexDataMinus33,1,12));
	safe_asprintf(&final_res,"addr : %s",Cell->DataDes->res_addr);
	return final_res;
}
