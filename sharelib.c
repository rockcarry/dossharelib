/* 包含头文件 */
#include <stdlib.h>
#include <stdio.h>
#include <dos.h>
#include "sharelib.h"

/* 函数实现 */
void* loadlibrary(char *name, int size)
{
    int  far(*entry)(void far*);
    BYTE     *buf = 0;
    BYTE     *code= 0;
    FILE     *fp  = 0;
    int       len = 0;
    DWORD     addr_old;
    DWORD     addr_new;
    WORD      seg;
    WORD     *pwd;

    /* 申请缓冲区 */
    buf = malloc(len + size + 0x100);
    if (!buf) goto error_handler;

    /* 打开文件 */
    fp = fopen(name, "rb");
    if (!fp) goto error_handler;

    /* 计算文件长度 */
    fseek(fp, 0, SEEK_END);
    len = ftell(fp);

    /* 计算绝对地址 */
    code       = buf + size;
    addr_old   = FP_SEG(code);
    addr_old <<= 4;
    addr_old  += FP_OFF(code);

    /* 地址对齐 */
    addr_new  = addr_old;
    addr_new += 0xFF;
    addr_new &=~0xFF;

    /* 计算入口函数地址 */
    seg   = (addr_new - 0x100) >> 4;
    entry = MK_FP(seg, 0x100);

    /* 装载共享库到缓冲区 */
    fseek(fp, 0, SEEK_SET);
    fread(code + (addr_new - addr_old), len, 1, fp);

    /* 调用入口函数 */
    entry((void far*)buf);

    /* 重定位接口函数地址 */
    pwd = (WORD*)buf;
    while (*pwd) {
        *pwd += 0x100; pwd++;
        *pwd  = seg  ; pwd++;
    }

error_handler:
    if (fp) fclose(fp);
    return buf;
}

void freelibrary(void *lib)
{
    if (lib) free(lib);
}









