@echo off
rem
rem link DYNAMIC against ucrt.lib
rem 
set out=.\build\
cl /nologo /std:c++17 /Fo%OUT% /EHsc /O2 .\euler57.cpp ^
/link /out:%OUT%euler57_cpp.exe /nodefaultlib ^
kernel32.lib ucrt.lib libvcruntime.lib libcmt.lib libcpmt.lib Advapi32.lib user32.lib