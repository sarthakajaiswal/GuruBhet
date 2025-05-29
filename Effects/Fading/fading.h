#ifndef _FADE_H 
#define _FADE_H 

// standard headers 
#include <Windows.h> 
#include <stdio.h> 
#include <stdlib.h> 

// OpenGL related headers 
#include <gl/GL.h> 
#include <gl/glu.h> 

// function declarations 
extern BOOL initFade(void); 
extern void displayFade(void); 
extern void updateFade(float); 
extern void uninitializeFade(void);  

#endif /* _FADE_H */  
