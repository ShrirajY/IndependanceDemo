del *.obj
del *.exe

cl.exe /c /EHsc /I ./external/freeglut/include Program.cpp ./Monuments/Shriraj/Programs/RedFort.cpp ./Monuments/Lakshmi/Programs/Konark.cpp ./core/Shriraj/Engine/Programs/Ng_shapes.cpp ./core/Lakshmi/Engine/Programs/LP_shapes.cpp

link.exe Program.obj RedFort.obj Ng_shapes.obj Konark.obj LP_shapes.obj /LIBPATH:./external/freeglut/lib/x64 freeglut.lib /SUBSYSTEM:CONSOLE

Program.exe
