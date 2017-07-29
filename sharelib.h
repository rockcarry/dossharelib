#ifndef _SHARELIB_H_
#define _SHARELIB_H_

/* 包含头文件 */
#include "stdefine.h"

/* 函数声明 */
void* loadlibrary(char *name, int size);
void  freelibrary(void *lib);

#endif













