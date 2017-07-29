/* ����ͷ�ļ� */
#include <stdlib.h>
#include <stdio.h>
#include <dos.h>
#include "sharelib.h"

/* ����ʵ�� */
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

    /* ���뻺���� */
    buf = malloc(len + size + 0x100);
    if (!buf) goto error_handler;

    /* ���ļ� */
    fp = fopen(name, "rb");
    if (!fp) goto error_handler;

    /* �����ļ����� */
    fseek(fp, 0, SEEK_END);
    len = ftell(fp);

    /* ������Ե�ַ */
    code       = buf + size;
    addr_old   = FP_SEG(code);
    addr_old <<= 4;
    addr_old  += FP_OFF(code);

    /* ��ַ���� */
    addr_new  = addr_old;
    addr_new += 0xFF;
    addr_new &=~0xFF;

    /* ������ں�����ַ */
    seg   = (addr_new - 0x100) >> 4;
    entry = MK_FP(seg, 0x100);

    /* װ�ع���⵽������ */
    fseek(fp, 0, SEEK_SET);
    fread(code + (addr_new - addr_old), len, 1, fp);

    /* ������ں��� */
    entry((void far*)buf);

    /* �ض�λ�ӿں�����ַ */
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









