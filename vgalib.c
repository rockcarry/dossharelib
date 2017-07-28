/* 包含头文件 */
#include "vgalib.h"

/* 内部函数声明 */
static void far setmode (int mode);
static void far putpixel(int x, int y, int c);

/* 函数实现 */
/* 共享库入口函数 */
int far vgalibmain(VGALIB far *lib)
{
    lib->setmode  = (void far*)setmode;
    lib->putpixel = (void far*)putpixel;
    lib->libend   = 0;
    return 0;
}

/* 内部函数实现 */
static void far setmode(int mode)
{
    asm mov ax, mode;
    asm int 0x10;
}

static void far putpixel(int x, int y, int c)
{
    ((BYTE far *)0xa0000000l)[x + y * 320] = (BYTE)c;
}














