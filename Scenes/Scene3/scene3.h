#ifndef _SCENE3_H 
#define _SCENE3_H 

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
extern BOOL initScene3(void); 
extern void displayScene3(void); 
extern void updateScene3(void); 
extern void uninitializeScene3(void); 

#endif /* _SCENE3_H */

