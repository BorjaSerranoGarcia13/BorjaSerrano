@ECHO OFF

REM Compile script 

del *.obj *.ilk *.pdb

REM Compile source files

cl /nologo /Zi /GR- /EHs /MD /W1 -I deps\ESAT_rev218\include ^
/c test_main.cc 

REM Link object files

cl /nologo /Zi /GR- /EHs /MD /W2 /Fe:demo.exe *.obj deps\ESAT_rev218\bin\ESAT.lib opengl32.lib shell32.lib gdi32.lib user32.lib


