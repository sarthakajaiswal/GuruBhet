#include "slide_scenes.h" 

// texture related variables 
GLuint texture_slide1; 
GLuint texture_slide2; 

// file-io related variable declarations 
extern FILE* gpFile; 

// translation related variables 
extern float tx, ty, tz; 
extern float sx, sy, sz; 

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

    return (TRUE); 
} 

void uninitializeSlideScenes(void) 
{
    // code 
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