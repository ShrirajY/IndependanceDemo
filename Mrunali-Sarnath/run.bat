del *.obj
del *.exe

cl.exe /c /EHsc /I external\freeglut\include core/E_2Dshapes.cpp
cl.exe /c /EHsc /I external\freeglut\include core/E_utils.cpp
cl.exe /c /EHsc /I external\freeglut\include demo\Objects\01_sarnath.cpp
cl.exe /c /EHsc /I external\freeglut\include demo\Scenes\00_Scene.cpp

link.exe 00_Scene.obj 01_sarnath.obj E_2Dshapes.obj E_utils.obj   /LIBPATH:external\freeglut\lib\x64 freeglut.lib /SUBSYSTEM:CONSOLE

00_Scene.exe


