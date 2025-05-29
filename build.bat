cls 
del OGL.exe 
del *.obj 

cl.exe /c /EHsc /D UNICODE /I "C:\Program Files (x86)\Windows Kits\10\Include\10.0.22621.0\um\gl" OGL.c Effects\Fading\fading.c Effects\Fog\fog.c Common\common.c Scenes\Scene1\scene1.c Scenes\Scene2\scene2.c Scenes\Scene3\scene3.c Scenes\Scene4\scene4.c Scenes\Scene5\scene5.c Scenes\SlideScenes\slide_scenes.c Common\Geometry\geometry.c

rc.exe OGL.rc 
link.exe /OUT:OGL.exe *.obj OGL.res user32.lib gdi32.lib kernel32.lib Winmm.lib /LIBPATH:"C:\Program Files (x86)\Windows Kits\10\Lib\10.0.22621.0\um\x64" /LIBPATH:"C:\Program Files (x86)\OpenAL 1.1 SDK\libs\Win64" /SUBSYSTEM:WINDOWS 

del *.obj 
del *.res
OGL.exe 
