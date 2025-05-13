#ifndef _SCENE2_H 
#define _SCENE2_H 

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
extern BOOL initScene2(void); 
extern void displayScene2(void); 
extern void updateScene2(void); 
extern void uninitializeScene2(void); 

#endif /* _SCENE2_H */

