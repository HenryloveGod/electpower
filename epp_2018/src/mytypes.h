//
//  mytypes.h
//  dltdog
//
//  Created by 雷邓 on 2018/7/30.
//  Copyright © 2018年 雷邓. All rights reserved.
//

#ifndef mytypes_h
#define mytypes_h

#if (defined(__unix__) || defined(unix)) && !defined(USG)
#include <sys/param.h>
#endif

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <inttypes.h>
#include <time.h>
#include <stdarg.h>
#include <errno.h>

/* NS types: */
    
#define    s08bits    char
#define    s16bits    int16_t
#define    s32bits    int32_t
#define    s64bits    int64_t
    
#define    u08bits    unsigned char
#define    u16bits    uint16_t
#define    u32bits    uint32_t
#define    u64bits    uint64_t
    
#define ns_bcopy(src,dst,sz) bcopy((src),(dst),(sz))
#define ns_bzero(ptr,sz) bzero((ptr),(sz))
#define ns_bcmp(ptr1,ptr2,sz) bcmp((ptr1),(ptr2),(sz))
    
#define nswap16(s) ntohs(s)
#define nswap32(ul) ntohl(ul)
#define nswap64(ull) ioa_ntoh64(ull)
        
#define ioa_ntoh64 _ioa_ntoh64
#define ioa_hton64 _ioa_ntoh64
    

#endif /* mytypes_h */
