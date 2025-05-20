#include "slide_scenes.h" 

// texture related variables 
GLuint texture_slide1; 
GLuint texture_slide2; 
GLuint texture_slide3; 
GLuint texture_slide4; 
GLuint texture_slide5; 
GLuint texture_slide6; 
GLuint texture_slide7; 
GLuint texture_slide8; 
GLuint texture_slide9; 

// file-io related variable declarations 
extern FILE* gpFile; 

// translation related variables 
extern float tx, ty, tz; 
extern float sx, sy, sz; 

extern float cameraX, cameraY, cameraZ; 
extern float cameraEyeX, cameraEyeY, cameraEyeZ; 
extern float cameraUpX, cameraUpY, cameraUpZ; 

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
    if (!loadGLPngTexture(&texture_slide6, "resources/Slide6-VisheshAabhar.png"))
	{
		fprintf(gpFile, "Slide6-VisheshAabhar.png Texture failed \n");
		return FALSE;

	}
    if (!loadGLPngTexture(&texture_slide7, "resources/Slide7-PrernaSthan.png"))
	{
		fprintf(gpFile, "Slide7-PrernaSthan.png Texture failed \n");
		return FALSE;

	}
    if (!loadGLPngTexture(&texture_slide8, "resources/Slide8-GuruCharniSamarpit.png"))
	{
		fprintf(gpFile, "Slide8-GuruCharniSamarpit.png Texture failed \n");
		return FALSE;

	}
    if (!loadGLPngTexture(&texture_slide9, "resources/Slide9-ThankYou.png"))
	{
		fprintf(gpFile, "Slide9-ThankYou.png Texture failed \n");
		return FALSE;

	}

    return (TRUE); 
} 

void uninitializeSlideScenes(void) 
{
    // code 
    if(texture_slide9) 
    {
        glDeleteTextures(1, &texture_slide9); 
        texture_slide9 = 0; 
    }
    if(texture_slide8) 
    {
        glDeleteTextures(1, &texture_slide8); 
        texture_slide8 = 0; 
    }
    if(texture_slide7) 
    {
        glDeleteTextures(1, &texture_slide7); 
        texture_slide7 = 0; 
    }
    if(texture_slide6) 
    {
        glDeleteTextures(1, &texture_slide6); 
        texture_slide6 = 0; 
    }
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

void initializeCameraForSlide(void)
{
    cameraX = 0.0f; 
    cameraY = 0.0f; 
    cameraZ = 5.0f; 
    cameraEyeX = 0.0f; 
    cameraEyeY = 0.0f; 
    cameraEyeZ = 0.0f; 
    cameraUpX = 0.0f; 
    cameraUpY = 1.0f; 
    cameraUpZ = 0.0f; 
}

void displaySlide1(void)
{
    // variable declarations 
    static int waitTimerMilisec = 2500; 
    static BOOL isThisFirstCall = TRUE;  
    // code 
    if(isThisFirstCall == TRUE) 
    {
        initializeCameraForSlide(); 
        isThisFirstCall = FALSE; 
    }
    textureOnQuad(0.0f, 0.0f, 0.0f, 3.68f, 2.08f, 1.00f, texture_slide1); 

    if(waitTimerMilisec > 0) 
        waitTimerMilisec = waitTimerMilisec - 1; 
    else 
        isFading = TRUE; 
} 

void displaySlide2(void) 
{
    // variable declarations 
    static int waitTimerMilisec = 2000; 
    static BOOL isThisFirstCall = TRUE;  
    
    if(isThisFirstCall == TRUE) 
    {
        initializeCameraForSlide(); 
        isThisFirstCall = FALSE; 
    }
    textureOnQuad(0.0f, 0.0f, 0.0f, 3.68f, 2.08f, 1.00f, texture_slide2); 

    if(waitTimerMilisec > 0) 
        waitTimerMilisec = waitTimerMilisec - 1; 
    else 
        isFading = TRUE; 
} 

void displaySlide3(void) 
{
    // variable declarations 
    static int waitTimerMilisec = 1300; 
    static BOOL isThisFirstCall = TRUE; 
    
    // code 
    if(isThisFirstCall == TRUE) 
    {
        initializeCameraForSlide(); 
        isThisFirstCall = FALSE; 
    }
    textureOnQuad(0.0f, 0.0f, 0.0f, 3.68f, 2.08f, 1.00f, texture_slide3); 

    if(waitTimerMilisec > 0) 
        waitTimerMilisec = waitTimerMilisec - 1; 
    else 
        isFading = TRUE;
} 

void displaySlide4(void) 
{
    // variable declarations 
    static int waitTimerMilisec = 1300; 
    static BOOL isThisFirstCall = TRUE; 
    
    // code 
    if(isThisFirstCall == TRUE) 
    {
        initializeCameraForSlide(); 
        isThisFirstCall = FALSE; 
    }
    textureOnQuad(0.0f, 0.0f, 0.0f, 3.68f, 2.08f, 1.00f, texture_slide4); 

    if(waitTimerMilisec > 0) 
        waitTimerMilisec = waitTimerMilisec - 1; 
    else 
        isFading = TRUE;
} 

void displaySlide5(void) 
{
    // variable declarations 
    static int waitTimerMilisec = 1300; 
    static BOOL isThisFirstCall = TRUE; 
    
    // code 
    if(isThisFirstCall == TRUE) 
    {
        initializeCameraForSlide(); 
        isThisFirstCall = FALSE; 
    }
    textureOnQuad(0.0f, 0.0f, 0.0f, 3.68f, 2.08f, 1.00f, texture_slide5); 

    if(waitTimerMilisec > 0) 
        waitTimerMilisec = waitTimerMilisec - 1; 
    else 
        isFading = TRUE;
} 

void displaySlide6(void) 
{
    // variable declarations 
    static int waitTimerMilisec = 1300; 
    static BOOL isThisFirstCall = TRUE; 
    
    // code 
    if(isThisFirstCall == TRUE) 
    {
        initializeCameraForSlide(); 
        isThisFirstCall = FALSE; 
    }
    textureOnQuad(0.0f, 0.0f, 0.0f, 3.68f, 2.08f, 1.00f, texture_slide6); 

    if(waitTimerMilisec > 0) 
        waitTimerMilisec = waitTimerMilisec - 1; 
    else 
        isFading = TRUE;
} 

void displaySlide7(void) 
{
    // variable declarations 
    static int waitTimerMilisec = 1300; 
    static BOOL isThisFirstCall = TRUE; 
    
    // code 
    if(isThisFirstCall == TRUE) 
    {
        initializeCameraForSlide(); 
        isThisFirstCall = FALSE; 
    }
    textureOnQuad(0.0f, 0.0f, 0.0f, 3.68f, 2.08f, 1.00f, texture_slide7); 

    if(waitTimerMilisec > 0) 
        waitTimerMilisec = waitTimerMilisec - 1; 
    else 
        isFading = TRUE;
} 

void displaySlide8(void) 
{
    // variable declarations 
    static int waitTimerMilisec = 1300; 
    static BOOL isThisFirstCall = TRUE; 
    
    // code 
    if(isThisFirstCall == TRUE) 
    {
        initializeCameraForSlide(); 
        isThisFirstCall = FALSE; 
    }
    textureOnQuad(0.0f, 0.0f, 0.0f, 3.68f, 2.08f, 1.00f, texture_slide8); 

    if(waitTimerMilisec > 0) 
        waitTimerMilisec = waitTimerMilisec - 1; 
    else 
        isFading = TRUE;
} 

void displaySlide9(void) 
{
    // variable declarations 
    static int waitTimerMilisec = 1650; 
    static BOOL isThisFirstCall = TRUE; 
    
    // code 
    if(isThisFirstCall == TRUE) 
    {
        initializeCameraForSlide(); 
        isThisFirstCall = FALSE; 
    }
    textureOnQuad(0.0f, 0.0f, 0.0f, 3.68f, 2.08f, 1.00f, texture_slide9); 

    if(waitTimerMilisec > 0) 
        waitTimerMilisec = waitTimerMilisec - 1; 
    else 
        isFading = TRUE;
} 
