

#include <stdio.h>
#include <stdarg.h>
#include <string.h>


typedef enum enum07_func_code{
    ED07_CTL_BROADCAST = 0x10,
    ED07_CTL_READDATA    =  0x11,
    ED07_CTL_READDATA_FOLLOW   =  0X12,
    ED07_CTL_READCOMM_ADDR     = 0X13,
    ED07_CTL_WRITEDATA         = 0X14,
    ED07_CTL_WRITECOMM_DATA    =  0X15,
    ED07_CTL_WRITECOMM_DATA    =  0X15,
    ED07_CTL_WRITECOMM_DATA    =  0X15,
    ED07_CTL_WRITECOMM_DATA    =  0X15,
    ED07_CTL_WRITECOMM_DATA    =  0X15,
    ED07_CTL_WRITECOMM_DATA    =  0X15,
    ED07_CTL_WRITECOMM_DATA    =  0X15,
}enum07_func_code_t;


typedef struct st_control{
    int direction;          //0 from server; 1 from client
    int is_normal_response; //0 normal; 1 abnormal
    int is_data_follow;     //0 NO;  1 YES
    enum07_func_code_t func_code; 
}st_control_t;

typedef struct st_data_section{

}st_data_section_t;


typedef union st_data_extra{
    char *addr;
    char broadcost_time[6];
    char broadcost_time[4];
    char comm_rate[1];
    char *new_pwd;
    char *com_pwd;
    char *event_clean;


}st_data_extra_t;

typedef struct st_data{ 
    int err_code;
    st_data_extra_t extra_data;
    st_data_section_t *section;    //数据标识，可能好几组
}st_data_t;


typedef struct st_d07_frame{
    char *hexStt;
    char *addr;
    char *hexStt2;
    st_control_t control;
    int dataLen;
    /*     */
    int dataType;// 根据control和datalen直接确定,

    st_data_t data;

}










int main(int argc, char **argv){


    printf("%d",broadcast);


    return 1;

}