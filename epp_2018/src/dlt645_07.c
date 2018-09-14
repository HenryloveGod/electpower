//
//  dlt645_07.c
//  dltdog
//
//  Created by 雷邓 on 2018/7/30.
//  Copyright © 2018年 雷邓. All rights reserved.
//

#include "dlt645_07.h"


#define get_data_key(msghex,stt) get_array_by_msg(msghex,stt,4)


static st_unit_hex_des_t ctl_method_des[]={
    {D07_CTL_METHOD_RESV,"保留"},
    {D07_CTL_METHOD_BROAD_TIME,"广播校时"},
    {D07_CTL_METHOD_READ_DATA,"读数据"},
    {D07_CTL_METHOD_READ_DATA_FLLW,"读后续数据"},
    {D07_CTL_METHOD_READ_DATA_CMM,"读通信数据"},
    {D07_CTL_METHOD_WRTE_DATA,"写数据"},
    {D07_CTL_METHOD_WRTE_DATA_ADDR,"写通信数据"},
    {D07_CTL_METHOD_FROZEN_CMD,"冻结命令"},
    {D07_CTL_METHOD_MODIFY_BAUNDARY,"更改通信速率"},
    {D07_CTL_METHOD_MODIFY_PWD,"修改密码"},
    {D07_CTL_METHOD_CLEAR_MAX_DEMAND,"最大需量清零"},
    {D07_CTL_METHOD_CLEAR_METER,"电表清零"},
    {D07_CTL_METHOD_CLEAR_EVENT,"事件清零"},
    {0,NULL},
};

static st_unit_hex_des_t ctl_pre_des[]={
    {0x00,"主站 无后续帧"},
    {0x20,"主站 有后续帧"},
    {0x80,"从站 正确应答 无后续帧"},
    {0xc0,"从站 错误应答 无后续帧"},
    {0xa0,"从站 正确应答 有后续帧"},
    {0xe0,"从站 错误应答 有后续帧"},
    {0x00,NULL}
};

static struct _st_unit_st{
    u08bits unit;
    s08bits * des;
}unit_des[]={
    {UNIT_KWH,"kWh"},
    {UNIT_KVA,"kVA"},
    {UNIT_KVAR,"kvar"},
    {UNIT_KVAH,"kVAh"},
    {UNIT_KVARH,"kvarh"},
    {UNIT_VALUE_DATE,"value_date"},//日期,年月日时分
    {UNIT_V,"V"},
    {UNIT_A,"A"},
    {UNIT_PERCENT,"%"},
    {UNIT_TIMES,"次"},
    {0,NULL}

};


static struct _st_cat_defines{
    u08bits di3;
    st_config07_data_kv_t *config;
    s08bits *config_file;
}cat_configs[]={
    {CONFIG_CAT_A1,NULL,CONFIG_FILE_A1},
    {CONFIG_CAT_A2,NULL,CONFIG_FILE_A2},
    {CONFIG_CAT_A3,NULL,CONFIG_FILE_A3},
    {CONFIG_CAT_A4,NULL,CONFIG_FILE_A4},
    {CONFIG_CAT_A5,NULL,CONFIG_FILE_A5},
    {CONFIG_CAT_A6,NULL,CONFIG_FILE_A6},
    {CONFIG_CAT_A7,NULL,CONFIG_FILE_A7},
    {0xFF,NULL,NULL}
};


/************************
 *  LOAD CONFIG
 * *******************************/

s08bits ** get_line_array(s08bits *line,char * det){

    s08bits **res_array=(s08bits **) malloc(10 * sizeof(s08bits *));

    bzero(res_array,sizeof(10 * sizeof(s08bits *)+1));

    int i = 1;
    res_array[0] = NULL; //待free;

    res_array[i] = strsep(&line,det);
    
    for(;res_array[i] != NULL;){

        if (i >9){
            perror("over 9");
            exit(EXIT_FAILURE);
        }  
        i++;
        res_array[i] = strsep(&line,det);        
    }

    return res_array;

}




//获取数据单位
u08bits get_unit(s08bits *unit){

    int i = 0;

    for(;unit_des[i].des !=NULL;i++){
        if(strstr(unit,unit_des[i].des) !=NULL){
            return unit_des[i].unit;
        }
    }

    return UNIT_UNKNOW;
}

// 把字符串 转化为 16进制
int set_cat_key(s08bits *line[],st_config07_data_kv_t *cat){

    cat->key[0] = strtol(line[1] ,NULL,16);
    cat->key[1] = strtol(line[2] ,NULL,16);
    cat->key[2] = strtol(line[3] ,NULL,16);
    cat->key[3] = strtol(line[4] ,NULL,16);

    if((cat->key_type= strtol(line[8],NULL,16))>0){
        if(cat->key_type >4) return -1;
            s08bits *stt ,*tmp;
            stt = tmp = line[(cat->key_type & 0x07)];

            if((tmp =strstr(stt,"...")) != NULL){
                cat->key_stt = strtol(stt,NULL,16);
                cat->key_end = strtol(tmp+3,NULL,16);
                cat->key[cat->key_type-1] = 0xee; //默认设定为0xee
            }
         
    }
    cat->next = NULL;
    return 0;

}

void free_line(s08bits **line_arr){

    int i = 8;

    for(;i !=0;i--)
      free(line_arr[i]);

}


//设置数据单元
st_config07_data_kv_t * set_cat_unit(s08bits * line){
    st_config07_data_kv_t *new_cat = (st_config07_data_kv_t *) malloc(sizeof(st_config07_data_kv_t));
    
    bzero(new_cat,sizeof(st_config07_data_kv_t));

    s08bits **line_arr =  get_line_array(line,",");

    set_cat_key(line_arr,new_cat);

    new_cat->length = strtol(line_arr[6],NULL,16);
    new_cat->unit = get_unit(line_arr[7]);
    new_cat->des = strdup(line_arr[9]);

    return new_cat;

}

//配置初始化
st_config07_data_kv_t * cat_config_init(char *path ){
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    st_config07_data_kv_t * cat_cnf=NULL ,*tmp_cat = NULL;

    fp = fopen(path, "rb");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    while ((read = getline(&line, &len, fp)) != -1) {
        printf("%s", line);
        if (NULL == cat_cnf)
            tmp_cat = cat_cnf = set_cat_unit(line);
        else{
            tmp_cat->next = set_cat_unit(line);
            tmp_cat =  tmp_cat->next;
            tmp_cat ->next = NULL;
        }
    }

    fclose(fp);
    if (line)
        free(line);
    //exit(EXIT_SUCCESS);

    return cat_cnf;

}

//测试配置
void test(u08bits config_cat){

    st_config07_data_kv_t *config = cat_configs[config_cat].config;

    st_config07_data_kv_t *tmp_cnf = config;

    while(tmp_cnf){
        printf("%02x,%02x,%02x,%02x,type[%02x],length[%d],stt[%d],end[%d], des[%s]\n",
            tmp_cnf->key[0],tmp_cnf->key[1],tmp_cnf->key[2],tmp_cnf->key[3],tmp_cnf->key_type,
            tmp_cnf->length,tmp_cnf->key_stt,tmp_cnf->key_end,
            tmp_cnf->des);

        tmp_cnf = tmp_cnf->next;
    }
    
}

// 配置初始化
int config_init(void){

    int i=0;

    for(;cat_configs[i].di3 != 0xFF;i++){
        cat_configs[i].config = cat_config_init(cat_configs[i].config_file);
    }
    return 0;
}
//测试
void config_test(void){
    test(CONFIG_CAT_A1);
    test(CONFIG_CAT_A2);
    test(CONFIG_CAT_A3);
    test(CONFIG_CAT_A4);
    test(CONFIG_CAT_A5);
    test(CONFIG_CAT_A6);
}



/********************************************************************/





static u08bits * get_array_by_msg(u08bits *msg,u08bits stt,u08bits size){
    int i =0;
    u08bits *res =malloc(size+1) ;
    bzero(res,size);
    for(;i<size;i++){
        res[i]=msg[i+stt];
    }

    return (u08bits *)res;
}





static char * get_ctl_pre_des(u08bits hex){
    int i=0;
    for(;ctl_pre_des[i].hex_des != NULL;i++){
        if(ctl_pre_des[i].hex == hex) return ctl_pre_des[i].hex_des;
    }
    return "unknow";
}

static char * get_ctl_method_des(u08bits hex){
    int i=0;
    for(;ctl_method_des[i].hex_des != NULL;i++){
        if(ctl_method_des[i].hex == hex) return ctl_method_des[i].hex_des;
    }
    return "unknow";
}



// void find_unit_key(st_data07_kv_t *st_data,int position,st_config07_data_kv_t *dkv){


//     u08bits num;
//     st_config07_data_kv_t *tdkv;
//     int flg = 0;

//     if (position != -1){
//         num = ((u08bits *)st_data->key_hex)[position];
//     }
//     tdkv = dkv;
//     ((u08bits *)st_data->key_hex)[position] = 0xee;

    
//     while(tdkv){
//         if(st_data->key_hex == ((u32bits *)tdkv->key)[0]){
//             flg = 1;
//             st_data->len = tdkv->length;
//             st_data->value_hex = get_array_by_msg(msghex,data_mk_stt + 4,st_data->len);
//             char des[1024]={0};
//             memcpy(des,st_data->key_hex,4);
//             memcpy(des+4,tdkv->des,strlen(tdkv->des));
//             des[4 + strlen(tdkv->des)]=':';
//             memcpy(des + 5 + strlen(tdkv->des),st_data->value_hex,st_data->len);
//             memcpy(des + 5 + strlen(tdkv->des) + st_data->len,tdkv->unit,st_data->len);
//             break;
//         }

//         tdkv = tdkv->next;
//     }




    
// }



static st_data07_kv_t * set_msg_data(u08bits msghex,int stt,int *out_stt){

    st_data07_kv_t *st_data= malloc(sizeof(st_data07_kv_t));
    bzero(st_data,sizeof(st_data07_kv_t));
    
    st_data->key_hex =((u32bits *)get_array_by_msg(msghex,stt,4))[0];
    
    st_config07_data_kv_t *dkv = cat_configs[((u08bits *)st_data->key_hex)[0]];


    st_config07_data_kv_t *t_dkv = dkv;

    int flg = 0;
    while(t_dkv){
        if(st_data->key_hex == ((u32bits *)t_dkv->key)[0]){
            flg = 1;
            st_data->len = t_dkv->length;
            st_data->value_hex = get_array_by_msg(msghex,data_mk_stt + 4,st_data->len);
            char des[1024]={0};
            memcpy(des,st_data->key_hex,4);
            memcpy(des+4,t_dkv->des,strlen(t_dkv->des));
            des[4 + strlen(t_dkv->des)]=':';
            memcpy(des + 5 + strlen(t_dkv->des),st_data->value_hex,st_data->len);
            memcpy(des + 5 + strlen(t_dkv->des) + st_data->len,t_dkv->unit,st_data->len);

            st_data->des

            break;
        }

        t_dkv = t_dkv->next;
    }

    if (flg == 0){

        



    }



}




st_config07_msg_t * d07_msg_depart_main(u08bits * msghex){
    
    st_config07_msg_t *cat;
    int i;
    
    cat = malloc(sizeof(st_config07_msg_t));
    cat->msg = msghex;
    cat->msg_len = sizeof(msghex);
    
    for(i=0;i<7;i++){
        cat->addr[i] = msghex[i];
    }
    cat->ctl_from_host_or_client = get_ctl_host_client(msghex);
    cat->ctl_response_normal_or_no = get_ctl_normal_yes_no(msghex);
    cat->ctl_frame_with_follow_no_or_yes = get_ctl_fram_follow_no_yes(msghex);
    cat->ctl_method_hex = get_ctl_method(msghex);
    
    char t_des[100]="\0";
    sprintf(t_des,"%s %s",
            get_ctl_pre_des(cat->ctl_from_host_or_client + cat->ctl_response_normal_or_no + cat->ctl_frame_with_follow_no_or_yes),
            get_ctl_method_des(cat->ctl_method_hex)
            );
    cat->ctl_des = malloc(strlen(t_des)+1);

    strncpy(cat->ctl_des,t_des,(strlen(t_des)+1));
    
    cat->data_len = get_msg_data_len(msghex);
    
    int data_mk_stt = 10;// 68 addr 68 ctl len data cs 16
    while(cat->data_len >0 && data_mk_stt < cat->msg_len){
        
        st_data07_kv_t *st_data= malloc(sizeof(st_data07_kv_t));
        bzero(st_data,sizeof(st_data07_kv_t));
        
        st_data->cat_key_hex =((u32bits *)get_data_key(msghex,data_mk_stt))[0];
        
        
    }
    return cat;
}
