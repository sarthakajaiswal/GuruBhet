// header files 
#include "fog.h" 

extern GLfloat fogColor[4]; 
extern GLfloat fogDensity; 
extern GLint fogMode; 
extern GLfloat fogStart; 
extern GLfloat fogEnd; 
extern BOOL gbFogEnabled; 

// initialize fog 
void initFog(void) 
{
    glFogfv(GL_FOG_COLOR, fogColor); 

    // fog mode (GL_EXP, GL_EXP2, or GL_LINEAR)
    glFogi(GL_FOG_MODE, fogMode); 
    glFogf(GL_FOG_DENSITY, fogDensity); 

    glFogf(GL_FOG_START, fogStart); 
    glFogf(GL_FOG_END, fogEnd); 

    glHint(GL_FOG_HINT, GL_NICEST); 
}

// updating fog 
void updateFog(void) 
{
    if(gbFogEnabled) 
    {
        glEnable(GL_FOG); 
        glFogfv(GL_FOG_COLOR, fogColor); 
        glFogi(GL_FOG_MODE, fogMode); 
        glFogf(GL_FOG_DENSITY, fogDensity); 
        glFogf(GL_FOG_START, fogStart); 
        glFogf(GL_FOG_END, fogEnd); 
    }
    else 
    {
        glDisable(GL_FOG); 
    }
}
