@ECHO OFF
timeout 1
cd /d C:\Program Files\Microsoft Visual Studio\2022\Enterprise\VC\Auxiliary\Build
call vcvarsall.bat x86
cd /d D:\courseProject\SVA-2022\SVA-2022\Generated
ml /c /coff /Zi Generated.asm
link /OPT:NOREF /DEBUG /SUBSYSTEM:CONSOLE libucrt.lib Generated.obj 
call Generated.exe
timeout 5
\pause
exit