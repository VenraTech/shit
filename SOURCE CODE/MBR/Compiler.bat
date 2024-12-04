@ECHO OFF
TITLE ASSEMBLY COMPILER

nasm -f bin bootloader.asm -o Soprano.bin

echo PRESS ANY KEY TO EXIT...
pause >nul
