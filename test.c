/* 包含头文件 */
#include <stdlib.h>
#include <conio.h>
#include "sharelib.h"
#include "vgalib.h"

void main(void)
{
    VGALIB *vgalib;
    int     i, j;

    vgalib = loadlibrary("vgalib.dll", sizeof(VGALIB));
    vgalib->setmode(VGA13H_MODE);

    for (i=0; i<200; i++)
        for (j=0; j<320; j++)
            vgalib->putpixel(j, i, j);

    getch();
    vgalib->setmode(TEXT_MODE);
    freelibrary(vgalib);
}









