#include "fading.h" 

BOOL isFading = FALSE; 

static float fadeDensity = 0.0f; 
static BOOL isFadingOut = TRUE; 

extern int shot_count; 
extern float cameraX, cameraY, cameraZ; 
extern FILE* gpFile; 

GLUquadric *fadeQuadric = NULL; 

BOOL initFade(void)
{
    fadeQuadric = gluNewQuadric(); 
    if(fadeQuadric == NULL) 
    {
        fprintf(gpFile, "gluNewQuadric() for fadeQuadric failed\n"); 
        return (FALSE); 
    }

    return (TRUE); 
}

void displayFade(void) 
{
    // code   
    if(isFading == TRUE)  
    { 
        glPushMatrix(); 
        {
            glEnable(GL_BLEND); 
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 

            glTranslatef(cameraX, cameraY, cameraZ); 
            glColor4f(0.0f, 0.0f, 0.0f, fadeDensity); 
            
            gluSphere(fadeQuadric, 0.5f, 4, 2); 

            glDisable(GL_BLEND); 
        } 
        glPopMatrix(); 
    }
}

void updateFade(float speed) 
{
    // code 
    if(isFading == TRUE) 
    {
        if(isFadingOut == TRUE) 
        {
            fadeDensity = fadeDensity + speed * 0.001; // increase darkness 

            if(fadeDensity >= 1.0f) 
            {
                fadeDensity = 1.0f; 
                isFadingOut = FALSE; 

                shot_count = shot_count + 1; 
            }
        }
        else // fading in 
        {
            fadeDensity = fadeDensity - speed * 0.001; // decrease darkness 

            if(fadeDensity <= 0.0f) 
            {
                fadeDensity = 0.0f; 
                isFadingOut = TRUE; 
                
                isFading = FALSE;   // stop fade effect when density restores to 0.0f; 
            }
        }
    }
} 

void uninitializeFade(void) 
{
    if(fadeQuadric) 
    {
        gluDeleteQuadric(fadeQuadric); 
        fadeQuadric = NULL; 
    }
}