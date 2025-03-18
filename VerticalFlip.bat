@echo off
nasm -f win64 FlipVertical.asm
gcc -c VerticalFlip.c -o VerticalFlip.obj -m64
gcc VerticalFlip.obj FlipVertical.obj -o VerticalFlip.exe -m64
VerticalFlip.exe
pause