/* ����ͷ�ļ� */
#include "vgalib.h"

/* �ڲ��������� */
static void far setmode (int mode);
static void far putpixel(int x, int y, int c);

/* ����ʵ�� */
/* �������ں��� */
int far vgalibmain(VGALIB far *lib)
{
    lib->setmode  = (void far*)setmode;
    lib->putpixel = (void far*)putpixel;
    lib->libend   = 0;
    return 0;
}

/* �ڲ�����ʵ�� */
static void far setmode(int mode)
{
    asm mov ax, mode;
    asm int 0x10;
}

static void far putpixel(int x, int y, int c)
{
    ((BYTE far *)0xa0000000l)[x + y * 320] = (BYTE)c;
}














