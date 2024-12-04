@ECHO OFF
TITLE ASSEMBLY COMPILER

nasm -f bin bootloader.asm -o Soprano.bin

echo PRESSIONE QUALQUER TECLA PARA SAIR...
pause >nul