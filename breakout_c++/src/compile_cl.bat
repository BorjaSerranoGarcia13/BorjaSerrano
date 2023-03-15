@echo off


del ..\bin\*.pdb 
del ..\bin\*.ilk 
del ..\bin\*.obj

REM Compile script 

del *.obj *.ilk *.pdb

REM Compile source files
 
cl /nologo /Zi /MDd /EHs /W4 /DSFML_STATIC /c -I ../include -I ../deps/sfml/x86/include ../src/main.cc -I .
cl /nologo /Zi /MDd /EHs /W4 /DSFML_STATIC /c -I ../include -I ../deps/sfml/x86/include ../src/bs_ball.cc -I .
cl /nologo /Zi /MDd /EHs /W4 /DSFML_STATIC /c -I ../include -I ../deps/sfml/x86/include ../src/bs_character.cc -I .
cl /nologo /Zi /MDd /EHs /W4 /DSFML_STATIC /c -I ../include -I ../deps/sfml/x86/include ../src/bs_enemy.cc -I .
cl /nologo /Zi /MDd /EHs /W4 /DSFML_STATIC /c -I ../include -I ../deps/sfml/x86/include ../src/bs_entity.cc -I .
cl /nologo /Zi /MDd /EHs /W4 /DSFML_STATIC /c -I ../include -I ../deps/sfml/x86/include ../src/bs_input.cc -I .
cl /nologo /Zi /MDd /EHs /W4 /DSFML_STATIC /c -I ../include -I ../deps/sfml/x86/include ../src/bs_label.cc -I .
cl /nologo /Zi /MDd /EHs /W4 /DSFML_STATIC /c -I ../include -I ../deps/sfml/x86/include ../src/bs_player.cc -I .
cl /nologo /Zi /MDd /EHs /W4 /DSFML_STATIC /c -I ../include -I ../deps/sfml/x86/include ../src/bs_rect.cc -I .
cl /nologo /Zi /MDd /EHs /W4 /DSFML_STATIC /c -I ../include -I ../deps/sfml/x86/include ../src/bs_scene.cc -I .
cl /nologo /Zi /MDd /EHs /W4 /DSFML_STATIC /c -I ../include -I ../deps/sfml/x86/include ../src/bs_scene_board.cc -I .
cl /nologo /Zi /MDd /EHs /W4 /DSFML_STATIC /c -I ../include -I ../deps/sfml/x86/include ../src/bs_scene_game_over.cc -I .
cl /nologo /Zi /MDd /EHs /W4 /DSFML_STATIC /c -I ../include -I ../deps/sfml/x86/include ../src/bs_scene_start.cc -I .
cl /nologo /Zi /MDd /EHs /W4 /DSFML_STATIC /c -I ../include -I ../deps/sfml/x86/include ../src/bs_scene_login_sign.cc -I .
cl /nologo /Zi /MDd /EHs /W4 /DSFML_STATIC /c -I ../include -I ../deps/sfml/x86/include ../src/bs_window.cc -I .
cl /nologo /Zi /MDd /EHs /W4 /DSFML_STATIC /c -I ../include -I ../deps/sfml/x86/include ../src/bs_game.cc -I .
cl /nologo /Zi /MDd /EHs /W4 /DSFML_STATIC /c -I ../include -I ../deps/sfml/x86/include ../src/bs_imgui.cc -I .
cl /nologo /Zi /MDd /EHs /W4 /DSFML_STATIC /c -I ../include -I ../deps/sfml/x86/include ../src/bs_database.cc -I .
cl /nologo /Zi /MDd /EHs /W4 /DSFML_STATIC /c -I ../include -I ../deps/sfml/x86/include ../src/sqlite3.c -I .
cl /nologo /Zi /MDd /EHs /W4 /DSFML_STATIC /c -I ../include -I ../deps/sfml/x86/include ../deps/imgui-sfml-master/imgui-SFML.cpp -I .
cl /nologo /Zi /MDd /EHs /W4 /DSFML_STATIC /c -I ../include -I ../deps/sfml/x86/include ../deps/imgui-sfml-master/imgui.cpp -I .
cl /nologo /Zi /MDd /EHs /W4 /DSFML_STATIC /c -I ../include -I ../deps/sfml/x86/include ../deps/imgui-sfml-master/imgui_draw.cpp -I .
cl /nologo /Zi /MDd /EHs /W4 /DSFML_STATIC /c -I ../include -I ../deps/sfml/x86/include ../deps/imgui-sfml-master/imgui_tables.cpp -I .
cl /nologo /Zi /MDd /EHs /W4 /DSFML_STATIC /c -I ../include -I ../deps/sfml/x86/include ../deps/imgui-sfml-master/imgui_widgets.cpp -I .



cl /nologo /Zi /MDd /EHs /W4 /Fe:test.exe main.obj sqlite3.obj bs_database.obj imgui-SFML.obj imgui.obj imgui_draw.obj imgui_tables.obj imgui_widgets.obj bs_ball.obj bs_imgui.obj bs_character.obj bs_enemy.obj bs_entity.obj bs_game.obj bs_input.obj bs_label.obj bs_player.obj bs_rect.obj bs_scene.obj bs_scene_board.obj bs_scene_game_over.obj bs_scene_login_sign.obj bs_scene_start.obj bs_window.obj ../deps/sfml/x86/lib/sfml-system-s-d.lib ../deps/sfml/x86/lib/sfml-window-s-d.lib ../deps/sfml/x86/lib/sfml-graphics-s-d.lib ../deps/sfml/x86/lib/freetype.lib winmm.lib opengl32.lib shell32.lib gdi32.lib user32.lib advapi32.lib

move *.exe ..\build
move *.pdb ..\bin
move *.ilk ..\bin
move *.obj ..\bin
