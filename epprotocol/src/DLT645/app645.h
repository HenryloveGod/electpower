

#include "./main645.h"


/*
 * 7.1 读数据
 * */
char *app_s_request_data71(HexDivide645_struct_t *Cell);
char *app_c_answer_data71(HexDivide645_struct_t *Cell);
char *app_c_answer_data_flw71(HexDivide645_struct_t *Cell);
char *app_c_abnormal71(HexDivide645_struct_t *Cell);
/*
 * 7.2 读后续数据
 * */
char *app_s_request_data_flw72(HexDivide645_struct_t *Cell);
//7.2 应答
char *app_c_send_data_flw72(HexDivide645_struct_t *Cell);
//7.2 后续应答
char *app_c_send_data_flwflw72(HexDivide645_struct_t *Cell);
//7.2 异常应答
char *app_c_abnormal72(HexDivide645_struct_t *Cell);
//7.3 异常应答
char *app_c_abnormal73(HexDivide645_struct_t *Cell);
/*
 * 7.4 读读通信地址
 * */
char *app_s_request_data74(HexDivide645_struct_t *Cell);
//7.4 通信地址应答
char *app_c_send_data74(HexDivide645_struct_t *Cell);
