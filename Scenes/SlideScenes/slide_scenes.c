#include "slide_scenes.h" 

// texture related variables 
GLuint texture_slide1; 
GLuint texture_slide2; 
GLuint texture_slide3; 
GLuint texture_slide4; 
GLuint texture_slide5; 

// file-io related variable declarations 
extern FILE* gpFile; 

// translation related variables 
extern float tx, ty, tz; 
extern float sx, sy, sz; 

extern BOOL isFading; 

BOOL initSlideScenes(void) 
{
    if (!loadGLPngTexture(&texture_slide1, "resources/slide1-SwarnDivas.png"))
	{
		fprintf(gpFile, "slide1-SwarnDivas.png Texture failed \n");
		return FALSE;
	}
    if (!loadGLPngTexture(&texture_slide2, "resources/slide2-GuruBhet.png"))
	{
		fprintf(gpFile, "slide2-GuruBhet.png Texture failed \n");
		return FALSE;
	}
    if (!loadGLPngTexture(&texture_slide3, "resources/Slide3-Tantragnyan.png"))
	{
		fprintf(gpFile, "Slide3-Tantragnyan Texture failed \n");
		return FALSE;
	}
    if (!loadGLPngTexture(&texture_slide4, "resources/Slide4-Sandarbha.png"))
	{
		fprintf(gpFile, "Slide4-Sandarbha.png Texture failed \n");
		return FALSE;
	}
    if (!loadGLPngTexture(&texture_slide5, "resources/Slide5-VisheshMadat.png"))
	{
		fprintf(gpFile, "Slide5-VisheshMadat.png Texture failed \n");
		return FALSE;
        
	}

    return (TRUE); 
} 

void uninitializeSlideScenes(void) 
{
    // code 
    if(texture_slide5) 
    {
        glDeleteTextures(1, &texture_slide5); 
        texture_slide5 = 0; 
    }
    if(texture_slide4) 
    {
        glDeleteTextures(1, &texture_slide4); 
        texture_slide4 = 0; 
    }
    if(texture_slide3) 
    {
        glDeleteTextures(1, &texture_slide3); 
        texture_slide3 = 0; 
    }
    if(texture_slide2) 
    {
        glDeleteTextures(1, &texture_slide2); 
        texture_slide2 = 0; 
    } 
    if(texture_slide1) 
    {
        glDeleteTextures(1, &texture_slide1); 
        texture_slide1 = 0; 
    } 
} 

void displaySlide1(void)
{
    // code 
    textureOnQuad(0.0f, 0.0f, 0.0f, 3.68f, 2.08f, 1.00f, texture_slide1); 
} 

void displaySlide2(void) 
{
    textureOnQuad(0.0f, 0.0f, 0.0f, 3.68f, 2.08f, 1.00f, texture_slide2); 
} 

void displaySlide3(void) 
{
    // variable declarations 
    static int waitTimer = 100; 

    // code 
    textureOnQuad(0.0f, 0.0f, 0.0f, 3.68f, 2.08f, 1.00f, texture_slide3); 

    waitTimer = waitTimer - 1; 
    if(waitTimer == 0) 
        isFading = TRUE; 
} 

void displaySlide4(void) 
{
    // variable declarations 
    static int waitTimer = 100; 

    // code 
    textureOnQuad(0.0f, 0.0f, 0.0f, 3.68f, 2.08f, 1.00f, texture_slide4); 

    waitTimer = waitTimer - 1; 
    if(waitTimer == 0) 
        isFading = TRUE; 
} 

void displaySlide5(void) 
{
    // variable declarations 
    static int waitTimer = 100; 

    // code 
    textureOnQuad(0.0f, 0.0f, 0.0f, 3.68f, 2.08f, 1.00f, texture_slide5); 

    waitTimer = waitTimer - 1; 
    if(waitTimer == 0) 
        isFading = TRUE; 
} 
