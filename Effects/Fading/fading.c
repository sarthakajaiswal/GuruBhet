#include "fading.h" 

BOOL isFading = FALSE; 

static float fadeDensity = 0.0f; 
static BOOL isFadingOut = TRUE; 

void displayFade(void) 
{
    // code     
    glPushMatrix(); 
    {
        glEnable(GL_BLEND); 
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 

        glScalef(11.20f, 6.30f, 0.0f); 
        glColor4f(0.0f, 0.0f, 0.0f, fadeDensity); 
        glBegin(GL_QUADS); 
        glVertex3f(1.0f, 1.0f, 1.0f); 
        glVertex3f(-1.0f, 1.0f, 1.0f);	
        glVertex3f(-1.0f, -1.0f, 1.0f); 
        glVertex3f(1.0f, -1.0f, 1.0f); 
        glEnd(); 
        
        glDisable(GL_BLEND); 
    } 
    glPopMatrix(); 
    
}

extern FILE* gpFile; 
extern double main_timer; 

void updateFade(void) 
{
    // code 
    if(isFading == TRUE) 
    {
        if(isFadingOut == TRUE) 
        {
            fadeDensity = fadeDensity + 0.001f; // increase darkness 

            if(fadeDensity >= 1.0f) 
                isFadingOut = FALSE; 
        }
        else // fading in 
        {
            fadeDensity = fadeDensity - 0.001f; // decrease darkness 

            if(fadeDensity <= 0.0f) 
            {
                isFadingOut = TRUE; 
                isFading = FALSE;   // stop fade effect when density restores to 0.0f; 
            }
        }
    }
} 