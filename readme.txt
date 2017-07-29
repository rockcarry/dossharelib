DOS 下共享库的实现

（代码请使用 tc201 编译器编译）

DOS 下也可以实现简单的动态链接库或者叫共享库，其实技术很简单，我的方法如下。
一个共享库就是一个 COM 文件，也就是 DOS 下的 COM 可执行文件
COM 文件有如下的特点：
1. 是完全的纯代码
2. 不包含任何头和重定位项
3. 加载到一个段里面可以直接执行

基于以上特点，就可以实现共享库了。
一个 .c 文件里面不能使用全局变量
第一个函数为共享库入口函数，形式如下
/* 共享库入口函数 */
int far vgalibmain(VGALIB far *lib)
{
    lib->setmode  = setmode;
    lib->putpixel = putpixel;
    lib->libend   = 0;
    return 0;
}

定义一个结构体，用于导出共享库的接口函数
/* 接口定义 */
typedef struct
{
    void far (*setmode )(int mode);
    void far (*putpixel)(int x, int y, int c);
    WORD libend;
} VGALIB;

在入口函数中会填充这个接口体

接下来就是如何加载了，申请内存，直接加载到 xxxx:0100 地址上就可以了，而 xxxx:0100 这个地址就是共享库的入口地址了。调用这个地址，入口函数就会填充那个接口体。当然返回后，还需要对结构体里面的函数指针进行重定位。然后就 ok 了。直接通过这个结构体就可以调用共享库中的函数了，真是很简单。

这个代码可以工作在 TC 编译器的所有内存模式。如果要分析代码，请注意代码中那几个 far 的作用。

还要注意共享库的一些限制，不能使用全局变量，不能调用外部的函数，特别是 TC 的库函数。在编译共享库是需要用 tcc -c 编译成 .obj, 然后再 tlink xxx.obj 生成 xxx.exe，然后再 exe2bin xxx.exe xxx.dll. 就这样了。














