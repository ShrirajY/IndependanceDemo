cls
del *.obj
del OGL.exe

cl.exe /c /EHsc Program.cpp /I external\freeglut\include

cl.exe /c /EHsc core\Ankush\Engine\Programs\Ng_shapes.cpp /I external\freeglut\include /I core\Ankush\Engine\Headers

cl.exe /c /EHsc Monuments\Ankush\Programs\CSMT.cpp /I external\freeglut\include /I Monuments\Ankush\Headers

cl.exe /c /EHsc centralScene\Program\Scene.cpp /I external\freeglut\include /I centralScene\Header

link.exe Program.obj Ng_shapes.obj CSMT.obj Scene.obj /LIBPATH:external\freeglut\lib\x64 freeglut.lib opengl32.lib glu32.lib /SUBSYSTEM:CONSOLE 
    
Program.exe

