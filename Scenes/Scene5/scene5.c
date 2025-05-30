#include "scene5.h" 

// variable declarations 
GLuint texture_sir1; 
GLuint texture_sir2; 
GLuint texture_sir3; 
GLuint texture_sir4; 
GLuint texture_sea; 

// translation related variables 
float scene5RotateAngle = 0.0; 

extern GLuint texture_temple_floor; 
extern FILE* gpFile;  
extern BOOL isFading; 

// camera related variables 
extern float cameraX, cameraY, cameraZ; 
extern float cameraEyeX, cameraEyeY, cameraEyeZ; 

extern float sx, sy, sz, tx, ty, tz; 

// cubemap related variables 
const char* cubemapFacesScene5[] = {
    "Resources/Cubemap/Scene5/right.png",
	"Resources/Cubemap/Scene5/left.png",
	"Resources/Cubemap/Scene5/top.png",
	"Resources/Cubemap/Scene5/bottom.png",
	"Resources/Cubemap/Scene5/front.png",
	"Resources/Cubemap/Scene5/back.png"
}; 
GLuint scene5CubemapTexture; 

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
    if (!loadGLPngTexture(&texture_sea, "resources/water.png"))
	{
		fprintf(gpFile, "water Texture failed \n");
		return FALSE;
	}
    
    scene5CubemapTexture = loadCubeMap(cubemapFacesScene5); 
    return (TRUE); 
} 

void drawScene5CubeOriginal(void) 
{
    glPushMatrix(); 
    glRotatef(-scene5RotateAngle, 0.0f, 1.0f, 0.0f); 
    drawTexturedCube(0.0f, 12.0, 0.0f, 10.0, 10.0, 10.0, 1.0, 1.0, 1.0, FACE_ALL, texture_sir1, texture_sir2, texture_sir3, texture_sir4, texture_temple_floor, texture_temple_floor); 
    glPopMatrix(); 
}

void drawScene5CubeReflection(void) 
{
    glPushMatrix(); 
    glRotatef(-scene5RotateAngle, 0.0f, 11.0f, 0.0f); 
    drawTexturedCube(0.0f, 12.0, 0.0f, 10.0, 10.0, 10.0, 1.0, 1.0, 1.0, FACE_ALL, texture_sir1, texture_sir2, texture_sir3, texture_sir4, texture_temple_floor, texture_temple_floor); 
    glPopMatrix(); 
}

void drawFloor(void) 
{
    glPushMatrix(); 

	glScalef(90.0f, 50.30f, 53.10); 
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f); 

	glBindTexture(GL_TEXTURE_2D, texture_sea); 

	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 1.0f); 
	glVertex3f(1.0f, 1.0f, 0.0f);  // right-top 
	glTexCoord2f(0.0f, 1.0f); 
	glVertex3f(-1.0f, 1.0f, 0.0f); // left-top 
	glTexCoord2f(0.0f, 0.0f); 
	glVertex3f(-1.0f, -1.0f, 0.0f);	// left-bottom 
	glTexCoord2f(1.0f, 0.0f); 
	glVertex3f(1.0f, -1.0f, 0.0f);	// right-bottom 
	glEnd();
	
	glBindTexture(GL_TEXTURE_2D, 0); 

	glPopMatrix(); 
}

void displayScene5(void) 
{
    // variable declarations 
    static BOOL isCameraInitialized = FALSE; 

    // code 
    if(isCameraInitialized == FALSE) 
    {
        cameraX = 38.50f; 
        cameraY = 10.0f; 
        cameraZ = 46.50f;
        cameraEyeX = 0.0f; 
        cameraEyeY = 12.0f; 
        cameraEyeZ = 0.0f; 

        isCameraInitialized = TRUE; 
    }

    displayCubemap(scene5CubemapTexture, 97.0f, 56.0f, 56.0f); 

    drawScene5CubeOriginal(); 

    glDisable(GL_DEPTH_TEST); 

	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE); 
	glEnable(GL_STENCIL_TEST); 
	glStencilFunc(GL_ALWAYS, 1, 1); 
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);  
	drawFloor(); 
	glEnable(GL_DEPTH_TEST); 

	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE); 
	glStencilFunc(GL_EQUAL, 1, 1);  
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP); 

    glPushMatrix(); 
    {
        glScalef(1.0f, -1.0f, 1.0f);
        drawScene5CubeReflection();  
    }
    glPopMatrix(); 

    glDisable(GL_STENCIL_TEST); 
	glEnable(GL_BLEND); 
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  
	glColor4f(1.0f, 1.0f, 1.0f, 0.7f); 
	drawFloor(); 
	glDisable(GL_BLEND); 
} 

void updateScene5(void) 
{
    // variable declarations 
    scene5RotateAngle = scene5RotateAngle + 0.7f;
    if(scene5RotateAngle > 500) 
        isFading = TRUE;  
} 

void uninitializeScene5(void) 
{
    // code 
    if(scene5CubemapTexture) 
    {
        glDeleteTextures(1, &scene5CubemapTexture); 
        scene5CubemapTexture = 0; 
    }
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

