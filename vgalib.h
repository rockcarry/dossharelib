#ifndef _VGALIB_H_
#define _VGALIB_H_

/* ����ͷ�ļ� */
#include "stdefine.h"

/* �������� */
#define VGA13H_MODE  0x0013
#define TEXT_MODE    0x0003

/* �ӿڶ��� */
typedef struct
{
    void far (*setmode )(int mode);
    void far (*putpixel)(int x, int y, int c);
    WORD libend;
} VGALIB;

#endif











