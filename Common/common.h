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

// placeholder structure for calling cubemap() for getting trees 
struct tree 
{
	float tx, ty, tz; 
	float height, width; 
	GLuint texture; 
}; 

// structure storing texture_id, corrosponding texture image and texture info string 
struct ImageTexture 
{
	GLuint texture; 
	const char* file_path; 
	const char* info_string;  
};  

// function declarations 
extern BOOL loadGLPngTexture(GLuint* texture, char* file); 

extern void billboard(
    float x, float y, float z, 
    float width, float height, 
    GLuint texture 
); 

extern unsigned int loadCubemap(const char* faces[]); 

extern void textureOnQuad(
	float tx, float ty, float tz, 
	float sx, float sy, float sz, 
	GLuint texture
);   

#endif /* _COMMON_H */

