#ifndef _COMMON_H 
#define _COMMON_H 

// standard headers 
#include <Windows.h> 
#include <stdio.h> 

// OpenGL related variables 
#include <gl\glew.h> 
#include <gl\GL.h> 
#include <gl\glu.h> 

// custom headers 
#include "../stb_image.h" 

// function declarations 
extern BOOL loadGLPngTexture(GLuint* texture, char* file); 

extern void billboard(
    float x, float y, float z, 
    float width, float height, 
    GLuint texture 
); 

extern unsigned int loadCubemap(const char* faces[]); 

#endif /* _COMMON_H */

