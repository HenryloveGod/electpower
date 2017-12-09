//
//  PubFunctions.h
//  electpower
//
//  Created by 雷邓 on 17/2/27.
//  Copyright © 2017年 雷邓. All rights reserved.
//

#ifndef PubFunctions_h
#define PubFunctions_h

#include <stdio.h>
#include "main.h"

#endif /* PubFunctions_h */

#define bool int
#define false 0
#define true 1

#define _IsCellLegal(HexCell) IsCellLegal(HexCell)


bool _IsCellLegal(const char *HexCell);


char *GetStringFromCell(const char *cell, int start,  int end);

char *char2bins(char ch);
char *string2bins(char *str);
char *string_reverse(char *tmp_str);
int hex2int(char *hex);

char *string_minus33(char *str2s);
