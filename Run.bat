@echo off
del *.obj
del scene.exe

cl.exe /c /EHsc Monuments\Lakshmi\Programs\Konark.cpp /I external\freeglut\include
cl.exe /c /EHsc centralScene\Program\Scene.cpp /I external\freeglut\include
cl.exe /c /EHsc core\Lakshmi\Engine\Programs\Ng_shapes.cpp /I external\freeglut\include
cl.exe /c /EHsc outro\Programs\musicnotes.cpp /I external\freeglut\include

link.exe /OUT:scene.exe Konark.obj Scene.obj Ng_shapes.obj musicnotes.obj /LIBPATH:external\freeglut\lib\x64 freeglut.lib /SUBSYSTEM:CONSOLE

scene.exe
