#ifndef _SCENE4_H 
#define _SCENE4_H 

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
extern BOOL initScene4(void); 
extern void displayScene4(void); 
extern void updateScene4(void); 
extern void uninitializeScene4(void); 

#endif /* _SCENE4_H */

