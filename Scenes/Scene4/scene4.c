#include "scene4.h" 

// texture related variables 
GLuint texture_room1; 
GLuint texture_room2; 
GLuint texture_room_floor; 
GLuint texture_hometheater; 
GLuint texture_ball; 
GLuint texture_tv; 
GLuint texture_sofa_back; 
GLuint texture_clock; 
GLuint texture_certificate; 

// file-io related variables 
extern FILE* gpFile; 
extern GLUquadric* quadric; 

// translation related variables 
extern float tx, ty, tz; 
extern float sx, sy, sz; 

BOOL initScene4(void) 
{
    // code 

    if (!loadGLPngTexture(&texture_room1, "resources/room1.png"))
	{
		fprintf(gpFile, "room1.png Texture failed \n");
		return FALSE;
	}
    if (!loadGLPngTexture(&texture_room2, "resources/room2.png"))
	{
		fprintf(gpFile, "room2.png Texture failed \n");
		return FALSE;
	}
    if (!loadGLPngTexture(&texture_room_floor, "resources/room_floor.png"))
	{
		fprintf(gpFile, "room_floor.png Texture failed \n");
		return FALSE;
	}
    if (!loadGLPngTexture(&texture_hometheater, "resources/hometheater.png"))
	{
		fprintf(gpFile, "hometheater.png Texture failed \n");
		return FALSE;
	}
    if (!loadGLPngTexture(&texture_ball, "resources/ball.png"))
	{
		fprintf(gpFile, "ball.png Texture failed \n");
		return FALSE;
	}
    if (!loadGLPngTexture(&texture_tv, "resources/tv.png"))
	{
		fprintf(gpFile, "tv.png Texture failed \n");
		return FALSE;
	}
    if (!loadGLPngTexture(&texture_sofa_back, "resources/sofa_back.png"))
	{
		fprintf(gpFile, "sofa_back.png Texture failed \n");
		return FALSE;
	}
    if (!loadGLPngTexture(&texture_clock, "resources/clock.png"))
	{
		fprintf(gpFile, "clock.png Texture failed \n");
		return FALSE;
	}
    if (!loadGLPngTexture(&texture_certificate, "Resources/certificate.png"))
	{
		fprintf(gpFile, "certificate.png Texture failed \n");
		return FALSE;
	}
    
    if(!quadric) 
        quadric = gluNewQuadric(); 

    return (TRUE); 
} 

void displayScene4(void) 
{
    // code 
    // room 
    drawTexturedCube(0.0f, 40.0f, 0.0f, 60.2f, 40.2f, 60.2f, 1.0f, 1.0f, 1.0f, FACE_ALL, texture_room2, texture_room2, texture_room1, texture_room2, texture_room2, texture_room_floor); 

    // hometheater 
    drawTexturedCube(
        -40.0, 6.50, -51.0, 
        2.52, 6.84, 2.32,
        1.0f, 1.0f, 1.0f, 
        FACE_ALL, 
        texture_hometheater, 
        texture_room1, 
        texture_room1, 
        texture_room1, 
        texture_room1, 
        texture_room1 
    );

    billboard(-36.0f, 2.2f, -55.0f, 4.0, 4.0, texture_ball); 

    // tv 
    glPushMatrix(); 
    {
        glTranslatef(-3.0f, 25.0f, -62.0f); 
        glScalef(17.36f, 8.24f, 2.08f);
        
        glColor3f(1.0f, 1.0f, 1.0f); 
        glBindTexture(GL_TEXTURE_2D, texture_tv); 
        glBegin(GL_QUADS); 
        glTexCoord2f(1.0f, 1.0f); 
        glVertex3f(1.0f, 1.0f, 1.0f); 
        glTexCoord2f(0.0f, 1.0f); 
        glVertex3f(-1.0f, 1.0f, 1.0f);	 
        glTexCoord2f(0.0f, 0.0f); 
        glVertex3f(-1.0f, -1.0f, 1.0f);  
        glTexCoord2f(1.0f, 0.0f); 
        glVertex3f(1.0f, -1.0f, 1.0f); 
        glEnd(); 
        glBindTexture(GL_TEXTURE_2D, 0); 
    } 
    glPopMatrix(); 

    // clock 
    glPushMatrix(); 
    {
        glTranslatef(63.50, 52.50, 0.0); 
        glScalef(4.92, 5.28, 5.52);
        
        glBindTexture(GL_TEXTURE_2D, texture_clock); 
        glBegin(GL_QUADS); 
        glTexCoord2f(1.0f, 1.0f); 
        glVertex3f(-1.0f, 1.0f, 1.0f);	// right to
        glTexCoord2f(0.0f, 1.0f); 
        glVertex3f(-1.0f, 1.0f, -1.0f);// left top 
        glTexCoord2f(0.0f, 0.0f); 
        glVertex3f(-1.0f, -1.0f, -1.0f); // left bottom 
        glTexCoord2f(1.0f, 0.0f); 
        glVertex3f(-1.0f, -1.0f, 1.0f); // right bottom 
        glEnd(); 
        glBindTexture(GL_TEXTURE_2D, 0); 
    } 
    glPopMatrix(); 

    // certificate  
    glPushMatrix(); 
    {
        glTranslatef(-60.50, 45.0, 8.50); 
        glScalef(2.32, 3.64, 5.44);
        
        glBindTexture(GL_TEXTURE_2D, texture_certificate); 
        glBegin(GL_QUADS); 
        glTexCoord2f(1.0f, 1.0f); 
        glVertex3f(1.0f, 1.0f, -1.0f); 	// right top 
        glTexCoord2f(0.0f, 1.0f); 
        glVertex3f(1.0f, 1.0f, 1.0f);	// left top 
        glTexCoord2f(0.0f, 0.0f); 
        glVertex3f(1.0f, -1.0f, 1.0f);	// left bottom 
        glTexCoord2f(1.0f, 0.0f); 
        glVertex3f(1.0f, -1.0f, -1.0f); // right bottom  
        glEnd(); 
        glBindTexture(GL_TEXTURE_2D, 0); 
    } 
    glPopMatrix(); 

    // sofa
    drawTexturedCube(
        0.0, 3.00, 38.50, 
        17.28, 3.0, 6.96, 
        1.0f, 1.0f, 1.0f, 
        FACE_ALL, 
        texture_sofa_back, 
        texture_sofa_back, 
        texture_sofa_back, 
        texture_sofa_back, 
        texture_sofa_back, 
        texture_sofa_back 
    );

    drawTexturedCube(
        16.50, 8.4, 38.50, 
        0.80, 2.8, 6.96, 
        1.0f, 1.0f, 1.0f, 
        FACE_ALL, 
        texture_sofa_back, 
        texture_sofa_back, 
        texture_sofa_back, 
        texture_sofa_back, 
        texture_sofa_back, 
        texture_sofa_back 
    );

    drawTexturedCube(
        -16.50, 8.4, 38.50, 
        0.80, 2.8, 6.96, 
        1.0f, 1.0f, 1.0f, 
        FACE_ALL, 
        texture_sofa_back, 
        texture_sofa_back, 
        texture_sofa_back, 
        texture_sofa_back, 
        texture_sofa_back, 
        texture_sofa_back 
    );

    glPushMatrix(); 
    {
        glRotatef(20.0f, 1.0f, 0.0f, 0.0f); 
        drawTexturedCube(
            0.00, 24.0, 39.50, 
            17.36, 3.76, 0.84, 
            1.0f, 1.0f, 1.0f, 
            FACE_ALL, 
            texture_sofa_back, 
            texture_sofa_back, 
            texture_sofa_back, 
            texture_sofa_back, 
            texture_sofa_back, 
            texture_sofa_back 
        );
    }  
    glPopMatrix(); 

    drawTexturedCube(
        55.30, 0.00, -33.30, 4.72, 6.40, 4.20,
        1.0f, 0.0f, 0.0f, 
        FACE_NONE, 
        0, 0, 0, 0, 0, 0
    );

    drawPyramid(55.60, 4.20, -0.90, 3.92, 4.88, 5.88, 1.0f, 1.0f, 0.3f, 1.0f); 

    glColor3f(1.0f, 0.0f, 1.0f); 
    glPushMatrix(); 
    glTranslatef(53.60, 3.80, -17.70); 
    gluSphere(quadric, 5.0, 16, 16); 
    glPopMatrix(); 

} 

void updateScene4(void) 
{
    // code 
}  

void uninitializeScene4(void) 
{
    // code 
    if(quadric) 
    {
        gluDeleteQuadric(quadric); 
        quadric = NULL; 
    }

    if(texture_certificate) 
    {
        glDeleteTextures(1, &texture_certificate); 
        texture_certificate = 0; 
    } 
    if(texture_clock) 
    {
        glDeleteTextures(1, &texture_clock); 
        texture_clock = 0; 
    }
    if(texture_sofa_back) 
    {
        glDeleteTextures(1, &texture_sofa_back); 
        texture_sofa_back = 0; 
    }
    if(texture_tv) 
    {
        glDeleteTextures(1, &texture_tv); 
        texture_tv = 0; 
    }
    if(texture_ball) 
    {
        glDeleteTextures(1, &texture_ball); 
        texture_ball = 0; 
    }
    if(texture_hometheater) 
    {
        glDeleteTextures(1, &texture_hometheater); 
        texture_hometheater = 0; 
    }
    if(texture_room_floor) 
    {
        glDeleteTextures(1, &texture_room_floor); 
        texture_room_floor = 0; 
    }
    if(texture_room1) 
    {
        glDeleteTextures(1, &texture_room1); 
        texture_room1 = 0; 
    }
    if(texture_room2) 
    {
        glDeleteTextures(1, &texture_room2); 
        texture_room2 = 0; 
    }
} 