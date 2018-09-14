//
//  dlt645_07.h
//  dltdog
//
//  Created by 雷邓 on 2018/7/30.
//  Copyright © 2018年 雷邓. All rights reserved.
//

#ifndef dlt645_07_h
#define dlt645_07_h

#include "mytypes.h"
#include <stdio.h>


#define HEX_STT 68
#define HEX_STT2 68
#define HEX_END 16

#define DLT_MSG_ADDR_LENGTH 6

#define hstt1(msghex) msghex[0]
#define hstt2(msghex) msghex[7]

#define get_ctl_host_client(msghex) msghex[8] & 0x80
#define get_ctl_normal_yes_no(msghex) msghex[8] & 0x40
#define get_ctl_fram_follow_no_yes(msghex) msghex[8] & 0x20
#define get_ctl_method(msghex) msghex[8] & 0x1f

#define D07_CTL_METHOD_RESV             0x00
#define D07_CTL_METHOD_BROAD_TIME       0x08
#define D07_CTL_METHOD_READ_DATA        0x11
#define D07_CTL_METHOD_READ_DATA_FLLW   0x12
#define D07_CTL_METHOD_READ_DATA_CMM    0x13
#define D07_CTL_METHOD_WRTE_DATA        0x14
#define D07_CTL_METHOD_WRTE_DATA_ADDR   0x15
#define D07_CTL_METHOD_FROZEN_CMD       0x16
#define D07_CTL_METHOD_MODIFY_BAUNDARY  0x17
#define D07_CTL_METHOD_MODIFY_PWD       0x18
#define D07_CTL_METHOD_CLEAR_MAX_DEMAND 0x19
#define D07_CTL_METHOD_CLEAR_METER      0x1A
#define D07_CTL_METHOD_CLEAR_EVENT      0x1B

#define get_msg_data_len(msghex) msghex[10]

#define CONFIG_CAT_A1 0x00
#define CONFIG_CAT_A2 0x01
#define CONFIG_CAT_A3 0x02
#define CONFIG_CAT_A4 0x03
#define CONFIG_CAT_A5 0x04
#define CONFIG_CAT_A6 0x05
#define CONFIG_CAT_A7 0x06

#define CONFIG_FILE_A1 "./config/dl645_07_a1.csv"
#define CONFIG_FILE_A2 "./config/dl645_07_a2.csv"
#define CONFIG_FILE_A3 "./config/dl645_07_a3.csv"
#define CONFIG_FILE_A4 "./config/dl645_07_a4.csv"
#define CONFIG_FILE_A5 "./config/dl645_07_a5.csv"
#define CONFIG_FILE_A6 "./config/dl645_07_a6.csv"
#define CONFIG_FILE_A7 "./config/dl645_07_a7.csv"


#define UNIT_KWH        0x01    //kWh
#define UNIT_KVA        0x02    //kVA
#define UNIT_KVAR       0x03    //kvar
#define UNIT_KVAH       0x04    //kVAh
#define UNIT_KVARH      0x05    //kvarh
#define UNIT_DATE       0x06    //日期,年月日时分
#define UNIT_VALUE_DATE 0x07    //year_date ，包含日期的数据
#define UNIT_V          0x10    //V
#define UNIT_A          0x11    //A
#define UNIT_PERCENT    0X12    //%
#define UNIT_TIMES      0X13    //次
#define UNIT_UNKNOW     0xFF    //未知



int config_init(void);
void config_test(void);


typedef struct _st_unit_hex_des {
    u08bits hex;
    s08bits * hex_des;  //描述
}st_unit_hex_des_t;





/*
    数据单元
    数据标识 数据值
 */

typedef struct _st_d07_data_cat{
    
    u32bits key_hex;
    u08bits len;
    u08bits * value_hex;
    s08bits * key_des;
    s08bits * value_des;
    
    struct _st_d07_data_cat *next;
    
}st_data07_kv_t;


/*
    主结构 68 addr 68 len 数据
 */
typedef struct _st_config_msg{
    u08bits ctl_from_host_or_client;
    u08bits ctl_response_normal_or_no;
    u08bits ctl_frame_with_follow_no_or_yes;
    u08bits ctl_method_hex;
    u08bits * msg;
    u08bits msg_len;
    s08bits * ctl_des;
    u08bits addr[6];
    u08bits data_len;
    st_data07_kv_t * data;
}st_config07_msg_t;





typedef struct _st_config07_data_kv {
    u08bits key[4];     //数据标识 DI3,DI2,DI1,DI0
    u08bits key_type;   // 03-> key[2]为变量，嵌入到data_des ...中。04->;
    u08bits key_stt;    //key中 1...0A   1
    u08bits key_end;    //key中 1...0A   0A
    u08bits length;     //数据长度
    u08bits unit;       //单位
    s08bits * des;      //中文描述 带...要替换
    struct _st_config07_data_kv *next;
}st_config07_data_kv_t;




st_config07_msg_t * d07_msg_depart_main(u08bits * msghex);

#endif /* dlt645_07_h */
