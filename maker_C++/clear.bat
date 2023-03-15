@ECHO OFF


REM Delete Exe, .obj, .pdb
del /s /q bin\*.exe  
del /s /q build\*.ilk
del /s /q build\*.pdb
del /s /q build\*.obj