#ifndef _SHARELIB_H_
#define _SHARELIB_H_

/* ����ͷ�ļ� */
#include "stdefine.h"

/* �������� */
void* loadlibrary(char *name, int size);
void  freelibrary(void *lib);

#endif













