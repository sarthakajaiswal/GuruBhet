#ifndef _SLIDE_SCENES_H 
#define _SLIDE_SCENES_H 

// standard headers 
#include <Windows.h> 

#define _USE_MATH_DEFINES 
#include <math.h> 

// OpenGL related variables 
#include <gl/glew.h> 
#include <gl/GL.h> 
#include <gl/glu.h> 

// custom headers 
#include "../../Common/Geometry/geometry.h" 
#include "../../Common/common.h" 

// function declarations 
extern BOOL initSlideScenes(void); 
extern void uninitializeSlideScenes(void);

extern void displaySlide1(void); 
extern void displaySlide2(void); 

#endif /* _SLIDE_SCENES_H */

