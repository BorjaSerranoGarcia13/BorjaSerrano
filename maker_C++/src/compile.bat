@ECHO OFF

REM Compile script 

del *.obj *.ilk *.pdb

REM Compile source files

cl /nologo /Zi /GR- /EHs /MD /W2 -I ..\include -I ..\deps\ESAT_rev218\include ^
/c ..\src\test_main.cc 

REM Link object files

cl /nologo /Zi /GR- /EHs /MD /W2 /Fe:..\bin\test_main.exe *.obj ..\deps\ESAT_rev218\bin\ESAT.lib opengl32.lib shell32.lib gdi32.lib user32.lib

REM Moving files

move *.pdb ..\build
move *.obj ..\build
move ..\bin\*.pdb ..\build
move ..\bin\*.ilk ..\build
move ..\bin\*.obj ..\build

