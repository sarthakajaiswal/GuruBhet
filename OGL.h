#ifndef _OGL_H 
#define _OGL_H  

#define MYICON 101 
#define IDBITMAP_MARBLE 102 
#define ID_MUSIC 103 

// windows header files 
#include <Windows.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <mmsystem.h> 

// audio related header files 
#include "C:\Program Files (x86)\OpenAL 1.1 SDK\include\al.h" 
#include "C:\Program Files (x86)\OpenAL 1.1 SDK\include\alc.h"

#define _CRT_NO_TIME_T
#include <time.h> 

// OpenGL related files 
#include <GL\glew.h> 
#include <gl\GL.h> 
#include <GL\glu.h> 

#define STB_IMAGE_IMPLEMENTATION 
#include "stb_image.h" 

// custom header files 
#include "Common\common.h"
#include "Effects\Fog\fog.h" 
#include "Effects\Fading\fading.h" 
#include "Common\Geometry\geometry.h" 

// scene header files 
#include "Scenes\scene1\scene1.h" 
#include "Scenes\scene2\scene2.h" 
#include "Scenes\scene3\scene3.h" 
#include "Scenes\scene4\scene4.h" 
#include "Scenes\scene5\scene5.h" 

// effects header files 
#include "Effects\Fog\fog.h"

// macros 
#define WIN_WIDTH   800 
#define WIN_HEIGHT  600 

// openGL libraries 
#pragma comment(lib, "OpenGL32.lib")
#pragma comment(lib, "glu32.lib") 
#pragma comment(lib, "kernel32.lib") 

// audio library 
#pragma comment(lib, "OpenAL32.lib") 

// global function declarations 
extern LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM); 
extern void PlayBackgroundMusic(void); 

extern BOOL initializeAudio(void); 
extern void uninitializeAudio(void); 

#endif 

