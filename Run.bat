del build\*.obj
del *obj
del *.exe

cl.exe /c /EHsc /I ./external/freeglut/include Program.cpp ./Monuments/Shriraj/Programs/RedFort.cpp ./Monuments/Lakshmi/Programs/Konark.cpp ./core/Shriraj/Engine/Programs/Ng_shapes.cpp ./core/Lakshmi/Engine/Programs/LP_shapes.cpp ^
    Monuments/Siddharth/Programs/Hampi.cpp core/Siddharth/Engine/Programs/E_SMB_2DShapes.cpp core/Siddharth/Engine/Programs/E_Math.cpp ^
    ./core/Mrunali/Engine/Programs/E_2Dshapes.cpp ./Monuments/Mrunali/Programs/Sarnath.cpp ^
    ./core/Ankush/Engine/Programs/Aa_shapes.cpp ./Monuments/Ankush/Programs/CSMT.cpp ^
    ./nameplate/Nameplate.cpp ./core/Shriraj/Engine/GlyphDS/Ng_glyph_DS.cpp ^
    ./core/Prashant/Program/E_PG_2DShapes.cpp ./Monuments/Prashant/Program/AgraFort.cpp ^
    /Fobuild\

link.exe build\Program.obj ^
    build\RedFort.obj ^
    build\Ng_shapes.obj ^
    build\Konark.obj ^
    build\LP_shapes.obj ^
    build\Hampi.obj ^
    build\E_SMB_2DShapes.obj ^
    build\E_Math.obj ^
    build\E_2Dshapes.obj ^
    build\Sarnath.obj ^
    build\Aa_shapes.obj ^
    build\CSMT.obj ^
    build\Nameplate.obj ^
    build\Ng_glyph_DS.obj ^
    build\AgraFort.obj ^
    build\E_PG_2DShapes.obj ^
    /LIBPATH:./external/freeglut/lib/x64 freeglut.lib /SUBSYSTEM:CONSOLE

Program.exe