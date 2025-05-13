#ifndef _GEOMETRY_H 
#define _GEOMETRY_H 

// standard headers 
#include <Windows.h> 

// OpenGL related headers 
#include <GL/gl.h> 
#include <GL/glu.h> 

// enums 
typedef enum FaceType{
    FACE_NONE =     0x000000, 
    FACE_FRONT =    0x000001, 
    FACE_BACK =     0x000010, 
    FACE_LEFT =     0x000100, 
    FACE_RIGHT =    0x001000, 
    FACE_TOP =      0x010000, 
    FACE_BOTTOM =   0x100000, 
    FACE_ALL =      0x111111 
}FaceType;  

// structure to draw cube | to call drawTexturedCube() 
struct Cube 
{
	float tx, ty, tz; 
	float sx, sy, sz;  
	float r, g, b; 
	FaceType faces_to_be_textured;
	GLuint textures[6];  
};  


// function declarations 
extern void drawTexturedCube(
                float x, float y, float z, 
                float sx, float sy, float sz, 
                float r, float g, float b, 
                FaceType faces_to_be_textured, 
                GLuint texture_front, 
                GLuint texture_right, 
                GLuint texture_back, 
                GLuint texture_left, 
                GLuint texture_top, 
                GLuint texture_bottom
            ); 

extern void drawPyramid(
                float x, float y, float z, 
                float sx, float sy, float sz, 
                float r, float g, float b, float a
            ); 

extern void rectangle(
                float tx, float ty, float tz, 
                float sx, float sy, float sz, 
                float xAng, float yAng, float zAng
            ); 

#endif /* _GEOMETRY_H */

