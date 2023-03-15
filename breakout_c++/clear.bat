@ECHO OFF


REM Delete Exe, .obj, .pdb
del /s /q build\*.exe  
del /s /q bin\*.ilk
del /s /q bin\*.pdb
del /s /q bin\*.obj
del /s /q data\*.db