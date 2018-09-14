//
//  main.c
//  dltdog
//
//  Created by 雷邓 on 2018/7/30.
//  Copyright © 2018年 雷邓. All rights reserved.
//

#include <stdio.h>
#include "dlt645_07.h"


int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    
    u08bits msg[]={0,0x68,0,0};
  
    config_init();
    config_test();
    
    d07_msg_depart_main(msg);
    
    
    return 0;
}
