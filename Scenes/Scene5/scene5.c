#include "scene5.h" 

// variable declarations 
GLuint texture_sir; 

extern FILE* gpFile;  
extern BOOL isFading; 

BOOL initScene5(void) 
{
    if (!loadGLPngTexture(&texture_sir, "resources/ball.png"))
	{
		fprintf(gpFile, "ball.png Texture failed \n");
		return FALSE;
	}
    return (TRUE); 
} 

void displayScene5(void) 
{
    // cubeFromFrontQuad(1.0f, 1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, -1.0f, 1.0f); 

    drawTexturedCube(0.0f, 0.0f, 0.0f, 5.0, 5.0, 5.0, 1.0, 1.0, 1.0, FACE_ALL, texture_sir, texture_sir, texture_sir, texture_sir, texture_sir, texture_sir); 
} 

void updateScene5(void) 
{
    // variable declarations 
    int waitTimer = 500; 

    if(waitTimer > 0) 
        waitTimer = waitTimer - 1; 
    else 
        isFading = TRUE; 
} 

void uninitializeScene5(void) 
{
    // code 
    if(texture_sir) 
    {
        glDeleteTextures(1, &texture_sir); 
        texture_sir = 0; 
    }
} 








/*
static void cubeFromFrontQuad(
    float rightTopX, float rightTopY, float leftTopX, float leftTopY, 
    float leftBottomX, float leftBottomY, float rightBottomX, float rightBottomY, 
    float depth
)
{
    // variable declarations 
    float z = depth/2.0f; 

    // code 
    glBegin(GL_QUADS); 
    // front
    glVertex3f(rightTopX, rightTopY, z); 
    glVertex3f(leftTopX, leftTopY, z); 
    glVertex3f(leftBottomX, leftBottomY, z); 
    glVertex3f(rightBottomX, rightBottomY, z); 

    // right 
    glVertex3f(rightTopX, rightTopY, -z); 
    glVertex3f(rightTopX, rightTopY, z); 
    glVertex3f(rightBottomX, rightBottomY, z); 
    glVertex3f(rightBottomX, rightBottomY, -z); 
    
    // back 
    glVertex3f(leftTopX, leftTopY, -z); 
    glVertex3f(rightTopX, rightTopY, -z); 
    glVertex3f(rightBottomX, rightBottomY, -z); 
    glVertex3f(leftBottomX, leftBottomY, -z); 

    // left 
    glVertex3f(leftTopX, leftTopY, z); 
    glVertex3f(leftTopX, leftTopY, -z); 
    glVertex3f(leftBottomX, leftBottomY, -z); 
    glVertex3f(leftBottomX, leftBottomY, z);  

    // top 
    glVertex3f(rightTopX, rightTopY, -z); 
    glVertex3f(leftTopX, leftTopY, -z); 
    glVertex3f(leftTopX, leftTopY, z); 
    glVertex3f(rightTopX, rightTopY, z); 
    
    // bottom 
    glVertex3f(rightBottomX, rightBottomY, z); 
    glVertex3f(leftBottomX, leftBottomY, z); 
    glVertex3f(leftBottomX, leftBottomY, -z); 
    glVertex3f(rightBottomX, rightBottomY, -z); 

    glEnd(); 
} 

*/