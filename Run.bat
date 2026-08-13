del *.obj
del main.exe

cl.exe /c /EHsc main.cpp											/I external\freeglut\include /I include /I core\Rugved

cl.exe /c /EHsc Utils.cpp /I external\freeglut\include				/I D:\IndependanceDemo
				

cl.exe /c /EHsc core/Rugved/RSD_BINE/Programs/shapes.cpp			/I external\freeglut\include /I include /I core\Rugved\RSD_BINE\Programs /I.


cl.exe /c /EHsc Monuments/Rugved/Programs/cholaTemple.cpp			/I external\freeglut\include /I include /I Monuments\Rugved\Programs /I.


link.exe main.obj Utils.obj shapes.obj cholaTemple.obj  /LIBPATH:external\freeglut\lib\x64 freeglut.lib /SUBSYSTEM:CONSOLE
main.exe