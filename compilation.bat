@ECHO OFF
call  C:/Program Files (x86)/Microsoft Visual Studio/2019/Community/VC/Tools/MSVC/14.26.28801/bin/Hostx64/x86/ml.exe
ml.exe /c /coff /Zi "C:\Users\cenia\Desktop\Backup\Course_project2\ASM\ASM.asm"
link /OPT:NOREF /DEBUG "C:\Users\cenia\Desktop\Backup\Course_project2\ASM\Debug\ASM.obj" "C:\Users\cenia\Desktop\Backup\Course_project2\Debug\kernel32.lib" "C:\Users\cenia\Desktop\Backup\Course_project2\Debug\userlib.lib" /SUBSYSTEM:CONSOLE
call D:\Desktop\Labs\SIA-2020\DEBUG\SIA_ASM.exe