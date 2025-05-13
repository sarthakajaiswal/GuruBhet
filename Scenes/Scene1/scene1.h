#ifndef _SCENE1_H 
#define _SCENE1_H 

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
extern BOOL initScene1(void); 
extern void displayScene1(void); 
extern void updateScene1(void); 

#endif /* _SCENE1_H */

