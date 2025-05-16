#include "scene5.h" 

// variable declarations 
GLuint texture_sir1; 
GLuint texture_sir2; 
GLuint texture_sir3; 
GLuint texture_sir4; 

// translation related variables 
float scene5RotateAngle = 0.0; 

extern GLuint texture_temple_floor; 
extern FILE* gpFile;  
extern BOOL isFading; 

// camera related variables 
extern float cameraX, cameraY, cameraZ; 
extern float cameraEyeX, cameraEyeY, cameraEyeZ; 

BOOL initScene5(void) 
{
    if (!loadGLPngTexture(&texture_sir1, "resources/Sir1.png"))
	{
		fprintf(gpFile, "Sir1.png Texture failed \n");
		return FALSE;
	}
    if (!loadGLPngTexture(&texture_sir2, "resources/Sir2.png"))
	{
		fprintf(gpFile, "Sir2.png Texture failed \n");
		return FALSE;
	}
    if (!loadGLPngTexture(&texture_sir3, "resources/Sir3.png"))
	{
		fprintf(gpFile, "Sir3.png Texture failed \n");
		return FALSE;
	}
    if (!loadGLPngTexture(&texture_sir4, "resources/Sir4.png"))
	{
		fprintf(gpFile, "Sir4.png Texture failed \n");
		return FALSE;
	}
    return (TRUE); 
} 

void displayScene5(void) 
{
    // variable declarations 
    static BOOL isCameraInitialized = FALSE; 

    // code 
    if(isCameraInitialized == FALSE) 
    {
        cameraX = 0.0f; 
        cameraY = 0.0f; 
        cameraZ = 25.0f;
        cameraEyeX = 0.0f; 
        cameraEyeY = 0.0f; 
        cameraEyeZ = 0.0f; 

        isCameraInitialized = TRUE; 
    }
    glPushMatrix(); 
    glRotatef(scene5RotateAngle, 0.0f, 1.0f, 0.0f); 
    drawTexturedCube(0.0f, 0.0f, 0.0f, 5.0, 5.0, 5.0, 1.0, 1.0, 1.0, FACE_ALL, texture_sir1, texture_sir2, texture_sir3, texture_sir4, texture_temple_floor, texture_temple_floor); 
    glPopMatrix(); 
} 

void updateScene5(void) 
{
    // variable declarations 
    scene5RotateAngle = scene5RotateAngle + 0.1f;
    if(scene5RotateAngle > 400) 
        isFading = TRUE;  
} 

void uninitializeScene5(void) 
{
    // code 
    if(texture_sir4) 
    {
        glDeleteTextures(1, &texture_sir4); 
        texture_sir4 = 0; 
    }
    if(texture_sir3) 
    {
        glDeleteTextures(1, &texture_sir3); 
        texture_sir3 = 0; 
    }
    if(texture_sir2) 
    {
        glDeleteTextures(1, &texture_sir2); 
        texture_sir2 = 0; 
    }
    if(texture_sir1) 
    {
        glDeleteTextures(1, &texture_sir1); 
        texture_sir1 = 0; 
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