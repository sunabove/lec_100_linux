@echo on
call "C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build\vcvarsall.bat" x64      
cl.exe shell.c sqlite3.c -Fesqlite.exe