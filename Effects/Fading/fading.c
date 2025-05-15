#include "fading.h" 

BOOL isFading = FALSE; 

static float fadeDensity = 0.0f; 
static BOOL isFadingOut = TRUE; 

extern unsigned long long main_timer_microsec; 
extern int shot_count; 
extern float cameraX, cameraY, cameraZ; 

void displayFade(void) 
{
    // code   
    if(isFading == TRUE)  
    { 
        glPushMatrix(); 
        {
            glEnable(GL_BLEND); 
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 

            glTranslatef(cameraX, cameraY, cameraZ - 0.5f); 
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
}

extern FILE* gpFile; 
extern double main_timer; 

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

                // fprintf(gpFile, "\n\n%d) timer = %lld\n", times_called, main_timer_microsec); 
                // fclose(gpFile); 
                // gpFile = fopen("log.txt", "a"); 
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