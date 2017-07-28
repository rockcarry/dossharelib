#ifndef _VGALIB_H_
#define _VGALIB_H_

/* 包含头文件 */
#include "stdefine.h"

/* 常量定义 */
#define VGA13H_MODE  0x0013
#define TEXT_MODE    0x0003

/* 接口定义 */
typedef struct
{
    void far (*setmode )(int mode);
    void far (*putpixel)(int x, int y, int c);
    WORD libend;
} VGALIB;

#endif











