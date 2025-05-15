#ifndef _SCENE5_H 
#define _SCENE5_H 

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
extern BOOL initScene5(void); 
extern void displayScene5(void); 
extern void updateScene5(void); 
extern void uninitializeScene5(void); 

// helper routines 
static void cubeFromFrontQuad(
    float v1x, float v1y, 
    float v2x, float v2y, 
    float v3x, float v3y, 
    float v4x, float v4y, 
    float depth
); 

#endif /* _SCENE5_H */
