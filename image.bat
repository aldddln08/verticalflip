@echo off
nasm -f win64 FlipVertical.asm
gcc -c image.c -o image.obj -m64
gcc image.obj FlipVertical.obj -o image.exe -m64
image.exe
pause