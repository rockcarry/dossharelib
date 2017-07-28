del error.txt

tcc -mt -c vgalib.c >> error.txt
tlink vgalib.obj >> error.txt
exe2bin vgalib.exe vgalib.dll

tcc test.c sharelib.c >> error.txt