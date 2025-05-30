#include "scene4.h" 

// texture related variables 
GLuint texture_room1; 
GLuint texture_room2; 
GLuint texture_room_floor; 
GLuint texture_hometheater; 
GLuint texture_tv; 
GLuint texture_sofa_back; 
GLuint texture_clock; 
GLuint texture_certificate; 
GLuint texture_c_book; 
GLuint texture_stool_wood; 
GLuint texture_stool_foam; 
GLuint texture_struct_tv; 
GLuint texture_struct_sofa; 
GLuint texture_struct_hometheater; 
GLuint texture_struct_hometheater; 
GLuint texture_struct_photoframe; 
GLuint texture_struct_clock; 
GLuint texture_struct_pyramid; 
GLuint texture_struct_cube; 
GLuint texture_struct_sphere; 
GLuint texture_struct_book; 
GLuint texture_initializing; 
GLuint texture_initialized; 

// file-io related variables 
extern FILE* gpFile; 

// translation related variables 
extern float tx, ty, tz; 
extern float sx, sy, sz; 

// camera related variables 
extern float cameraX, cameraY, cameraZ; 
extern float cameraEyeX, cameraEyeY, cameraEyeZ; 
extern float cameraUpX, cameraUpY, cameraUpZ; 

float specAngleY; 

extern int shot_count; 
extern BOOL isFading; 

// initial waiting time 
int initialWaitTimerScene4 = 400; 

// structure info texture related toggle variables 
BOOL displayStructPhotoframe = FALSE; 
BOOL displayStructTV = FALSE; 
BOOL displayStructHometheater = FALSE;
BOOL displayStructClock = FALSE; 
BOOL displayStructCube = FALSE; 
BOOL displayStructPyramid = FALSE; 
BOOL displayStructSphere = FALSE; 
BOOL displayStructSofa = FALSE; 
BOOL displayStructBook = FALSE; 
BOOL displayInitializingTexture = FALSE; 
BOOL displayInitializedTexture = FALSE; 

// GLU shapes related variables 
GLUquadric *quadricScene4 = NULL; 

BOOL initScene4(void) 
{
    // code 
    if (!loadGLPngTexture(&texture_room1, "resources/room1.png"))
	{
		fprintf(gpFile, "room1.png Texture failed \n");
		return (FALSE);
	}
    if (!loadGLPngTexture(&texture_room2, "resources/room2.png"))
	{
		fprintf(gpFile, "room2.png Texture failed \n");
		return (FALSE);
	}
    if (!loadGLPngTexture(&texture_room_floor, "resources/room_floor.png"))
	{
		fprintf(gpFile, "room_floor.png Texture failed \n");
		return (FALSE);
	}
    if (!loadGLPngTexture(&texture_hometheater, "resources/hometheater.png"))
	{
		fprintf(gpFile, "hometheater.png Texture failed \n");
		return (FALSE);
	}
    if (!loadGLPngTexture(&texture_tv, "resources/tv.png"))
	{
		fprintf(gpFile, "tv.png Texture failed \n");
		return (FALSE);
	}
    if (!loadGLPngTexture(&texture_sofa_back, "resources/sofa_back.png"))
	{
		fprintf(gpFile, "sofa_back.png Texture failed \n");
		return (FALSE);
	}
    if (!loadGLPngTexture(&texture_clock, "resources/clock.png"))
	{
		fprintf(gpFile, "clock.png Texture failed \n");
		return (FALSE);
	}
    if (!loadGLPngTexture(&texture_certificate, "Resources/certificate.png"))
	{
		fprintf(gpFile, "certificate.png Texture failed \n");
		return (FALSE);
	}
    if (!loadGLPngTexture(&texture_c_book, "Resources/c_book.png"))
	{
		fprintf(gpFile, "c_book.png Texture failed \n");
		return (FALSE);
	}
    if (!loadGLPngTexture(&texture_stool_wood, "Resources/stool_wood.png"))
	{
		fprintf(gpFile, "stool_wood.png Texture failed \n");
		return (FALSE);
	}
    if (!loadGLPngTexture(&texture_stool_foam, "Resources/stool_foam.png"))
	{
		fprintf(gpFile, "stool_foam.png Texture failed \n");
		return (FALSE);
	}
    if (!loadGLPngTexture(&texture_struct_tv, "Resources/struct_tv.png"))
	{
		fprintf(gpFile, "struct_tv.png Texture failed \n");
		return (FALSE);
	}
    if (!loadGLPngTexture(&texture_struct_photoframe, "Resources/struct_photoframe.png"))
	{
		fprintf(gpFile, "struct_photoframe.png Texture failed \n");
		return (FALSE);
	}
    if (!loadGLPngTexture(&texture_struct_hometheater, "Resources/struct_hometheater.png"))
	{
		fprintf(gpFile, "struct_hometheater.png Texture failed \n");
		return (FALSE);
	}
    if (!loadGLPngTexture(&texture_struct_sphere, "Resources/struct_sphere.png"))
	{
		fprintf(gpFile, "struct_sphere.png Texture failed \n");
		return (FALSE);
	}
    if (!loadGLPngTexture(&texture_struct_cube, "Resources/struct_cube.png"))
	{
		fprintf(gpFile, "struct_cube.png Texture failed \n");
		return (FALSE);
	}
    if (!loadGLPngTexture(&texture_struct_pyramid, "Resources/struct_pyramid.png"))
	{
		fprintf(gpFile, "struct_pyramid.png Texture failed \n");
		return (FALSE);
	}
    if (!loadGLPngTexture(&texture_struct_clock, "Resources/struct_clock.png"))
	{
		fprintf(gpFile, "struct_clock.png Texture failed \n");
		return (FALSE);
	}
    if (!loadGLPngTexture(&texture_struct_book, "Resources/struct_book.png"))
	{
		fprintf(gpFile, "struct_book.png Texture failed \n");
		return (FALSE);
	}
    if (!loadGLPngTexture(&texture_struct_sofa, "Resources/struct_sofa.png"))
	{
		fprintf(gpFile, "struct_sofa.png Texture failed \n");
		return (FALSE);
	}
    if (!loadGLPngTexture(&texture_initializing, "Resources/initializing.png"))
	{
		fprintf(gpFile, "initializing.png Texture failed \n");
		return (FALSE);
	}
    if (!loadGLPngTexture(&texture_initialized, "Resources/initialized.png"))
	{
		fprintf(gpFile, "initialized.png Texture failed \n");
		return (FALSE);
	}

    quadricScene4 = (GLUquadric*)gluNewQuadric(); 
    if(quadricScene4 == NULL) 
    {
        fprintf(gpFile, "gluNewQuadric() failed\n"); 
        return (FALSE); 
    }

    return (TRUE); 
} 

void displayScene4(void) 
{
    // variable declarations 
    static BOOL isThisFirstCall = TRUE; 

    // cubes for sofa 
    struct Cube sofaCubes[] = {
        {0.0, 3.00, 38.50, 17.28, 3.0, 6.96, 1.0f, 1.0f, 1.0f, FACE_ALL, texture_sofa_back, texture_sofa_back, texture_sofa_back, texture_sofa_back, texture_sofa_back, texture_sofa_back}, // base 
        {16.50, 8.4, 38.50, 0.80, 2.8, 6.96, 1.0f, 1.0f, 1.0f, FACE_ALL, texture_sofa_back, texture_sofa_back, texture_sofa_back, texture_sofa_back, texture_sofa_back, texture_sofa_back}, // hand 
        {-16.50, 8.4, 38.50, 0.80, 2.8, 6.96, 1.0f, 1.0f, 1.0f, FACE_ALL, texture_sofa_back, texture_sofa_back, texture_sofa_back, texture_sofa_back, texture_sofa_back, texture_sofa_back}, // hand 
        {0.00, 24.0, 39.50, 17.36, 3.76, 0.84, 1.0f, 1.0f, 1.0f, FACE_ALL, texture_sofa_back, texture_sofa_back, texture_sofa_back, texture_sofa_back, texture_sofa_back, texture_sofa_back}  // back 
    }; 

    // code
    if(isThisFirstCall) 
    {
        cameraX = -47.0f; 
        cameraY = 51.0f; 
        cameraZ = 9.0f; 

        cameraEyeX = -181.0f; 
        // cameraEyeX = 0.0f; 
        cameraEyeY = 41.0f; 
        cameraEyeZ = 0.0f; 

        // cameraX = 0.0f; 
        // cameraY = 2.0f; 
        // cameraZ = 0.0f; 
        // cameraEyeX = 0.0f; 
        // cameraEyeY = 5.0f; 
        // cameraEyeZ = -30.0f; 
        
        isThisFirstCall = FALSE; 
    }
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); 

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

    glEnable(GL_BLEND); 
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 

    // tv 
    glPushMatrix(); 
    {
        glTranslatef(-3.0f, 25.0f, -62.0f); 
        glScalef(17.36f, 8.24f, 2.08f);
        
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

    glDisable(GL_BLEND); 
    
    // certificate  
    glPushMatrix(); 
    {
        glTranslatef(-60.50, 50.0, 8.50); 
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

    // table 
    drawTexturedCube(
        56.0, 0.40, 48.70, 3.80, 12.16, 4.96, 
        1.0f, 1.0f, 1.0f, 
        FACE_ALL, 
        texture_stool_wood, texture_stool_wood, texture_stool_wood,
        texture_stool_wood, texture_stool_wood, texture_stool_wood
    );

    // book on table 
    drawTexturedCube(
        55.40, 13.0, 48.10, 2.86, 0.32, 3.96, 
        1.0f, 1.0f, 1.0f, 
        FACE_TOP, 
        0, 0, 0, 0, texture_c_book, 0
    );

    drawTexturedCube(
        55.90, 11.70, 48.50, 3.80, 0.92, 5.12, 
        1.0f, 1.0f, 1.0f, 
        FACE_ALL, 
        texture_stool_foam, texture_stool_foam, texture_stool_foam, 
        texture_stool_foam, texture_stool_foam, texture_stool_foam
    );

    drawTexturedCube(
        55.30, 0.00, -33.30, 4.72, 6.40, 4.20,
        1.0f, 1.0f, 0.0f, 
        FACE_NONE, 
        0, 0, 0, 0, 0, 0
    );

    drawPyramid(55.60, 4.20, -0.90, 3.92, 4.88, 5.88, 0.0f, 1.0f, 0.0f, 1.0f); 
    glPushMatrix(); 
    glColor3f(0.0f, 0.0f, 1.0f); 
    glTranslatef(53.60, 3.80, -17.70); 
    gluSphere(quadricScene4, 5.0, 16, 16); 
    glPopMatrix(); 

    //=========================================== 
    // structure definition textures 
    if(displayStructTV)
        billboard(1.10, 37.60, -59.50, 8.60, 6.30, 0, texture_struct_tv); 
    if(displayStructSofa)
        billboard(0.0, 10.60, 42.50, 6.04, 5.40, 0.0f, texture_struct_sofa); 
    if(displayStructHometheater)
        billboard(-44.10, 17.30, -50.60, 7.0, 7.0, 0.0f, texture_struct_hometheater); 
    if(displayStructPhotoframe)
        billboard(-58.0, 49.90, 16.50, 0.0f, 3.0, 3.16, texture_struct_photoframe); 
    if(displayStructCube)
        billboard(56.40, 13.20, -34.20, 0.0, 5.04, 6.72, texture_struct_cube); 
    if(displayStructSphere)
        billboard(56.70, 13.80, -15.60, 0.0, 7.12, 7.40, texture_struct_sphere); 
    if(displayStructPyramid)
        billboard(58.40, 12.20, 4.20, 0.0, 8.12, 7.40, texture_struct_pyramid); 
    if(displayStructClock)
        billboard(57.60, 38.0, 8.60, 0.0, 8.52, 9.32, texture_struct_clock); 
    if(displayStructBook)
        billboard(51.60, 21.20, 49.30, 5.48, 5.50, 0.0, texture_struct_book); 

    glEnable(GL_BLEND); 
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
    // initialized-uninitialized texture 
    if(displayInitializedTexture || displayInitializingTexture) 
    {
        glPushMatrix(); 
        {
            glTranslatef(-41.10, 50.0, 7.90);
            glScalef(17.0, 4.84, 8.28f);  

            if(displayInitializedTexture) 
                glBindTexture(GL_TEXTURE_2D, texture_initialized); 
            else 
                glBindTexture(GL_TEXTURE_2D, texture_initializing); 

            glBegin(GL_QUADS); 
            glTexCoord2f(1.0f, 1.0f); 
            glVertex3f(-1.0f, 1.0f, 1.0f);	// right top 
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
    }  

    // goggle 
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 

    glColor4f(0.0f, 0.0f, 1.0f, 0.3f); 
    glPushMatrix(); 
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); 
    glTranslatef(cameraX, cameraY, cameraZ); 
    gluSphere(quadricScene4, 1.0f, 4, 2);  
    glPopMatrix(); 

    glDisable(GL_BLEND); 
} 

/*
    Initial 
       -47.000000  51.000000 9.000000
        -181.500000 41.000000 0.000

    Postion 1 
        expected 
        -14.500000  50.000000 54.000000
        -11.500000 50.500000 0.0
        ---------
        // after loop 
        -14.56  50.00 53.91
        -11.34 50.48 0.00
        0.00 1.00 0.00

    Psition 2 
        // expected
        -1.500000  26.500000 39.00000
        -11.500000 27.000000 0.000
         ---------
        // after loop 
        -1.29  26.01 38.59
        -11.34 27.00 0.00

    Position 3 
        // expected
        -20.500000  35.000000 9.000000
        -0.500000 28.500000 0.0000
         ---------
        // after loop 
        -20.03  34.39 9.01
        -0.50 28.48 0.00
        
    Position 4 
        // expected 
        -30.50  32.96 -18.90
        -26.00 26.50 0.00
        0.000000 1.000000 0.000000
         ---------
        // after loop 
        -30.51  32.25 -20.22
        -26.70 26.38 0.00

    Position 5 
        // expected 
         -3.21  31.75 2.28
        15.90 34.28 0.00
         ---------
        // after loop 
        -3.21  31.75 1.98
        14.50 34.28 0.00

    final 
        // expected 
        35.79  26.65 35.68
        40.30 23.18 37.50
         ---------
        // after loop
        35.79  26.65 35.46
        38.90 25.18 37.50 
*/

 
void updateScene4(void) 
{
    // variable declarations 
    static BOOL isUpdate1 = FALSE; 
    static BOOL isUpdate2 = FALSE; 
    static BOOL isUpdate3 = FALSE; 
    static BOOL isUpdate4 = FALSE; 
    static BOOL isUpdate5 = FALSE; 
    static BOOL isUpdate6 = FALSE; 

    static float inverse_constant_for_camera_speed1 = 950; 
    static float inverse_constant_for_camera_speed2 = 950; 
    static float inverse_constant_for_camera_speed3 = 950; 
    static float inverse_constant_for_camera_speed = 1000; 

 
    // code
    if(initialWaitTimerScene4 > 0) 
    {
        if(initialWaitTimerScene4 == 1) 
        {
            isUpdate1 = TRUE; 
        }  
        if(initialWaitTimerScene4 > 200) 
        {
            displayInitializingTexture = TRUE; 
        }
        if(initialWaitTimerScene4 < 200 && initialWaitTimerScene4 > 100) 
        {
            displayInitializingTexture = FALSE; 
            displayInitializedTexture = TRUE; 
        } 
        if(initialWaitTimerScene4 < 100) 
        {
            displayInitializingTexture = FALSE; 
            displayInitializedTexture = FALSE; 
        }

        initialWaitTimerScene4 = initialWaitTimerScene4 - 1;
    }

    // initial -> position1
    if(isUpdate1 == TRUE) 
    {
        cameraX = cameraX + 32.50/inverse_constant_for_camera_speed1; 
        cameraY = cameraY - 1.0/inverse_constant_for_camera_speed1; 
        cameraZ = cameraZ + 45.0/inverse_constant_for_camera_speed1; 

        cameraEyeX = cameraEyeX + 170.0/inverse_constant_for_camera_speed1; 
        cameraEyeY = cameraEyeY + 9.5/inverse_constant_for_camera_speed1; 

        displayStructPhotoframe = TRUE; // display photoframe struct from start itself of update1 

        if(cameraEyeX >= -11.50) 
        {
            isUpdate1 = FALSE; 
            isUpdate2 = TRUE; 
        }
    }

    // position1->position2
    if(isUpdate2 == TRUE) 
    {
        cameraX = cameraX + (float)13.00/inverse_constant_for_camera_speed3; 
        cameraY = cameraY - (float)23.50/inverse_constant_for_camera_speed3; 
        cameraZ = cameraZ - (float)15.00/inverse_constant_for_camera_speed3; 

        cameraEyeY = cameraEyeY - 23.0/inverse_constant_for_camera_speed3; 

        // remove previous structures 
        displayStructPhotoframe = FALSE; 

        // display New Textures 
        if(cameraY < 51.0f) 
            displayStructTV = TRUE; 
        if(cameraY < 48.0f) 
            displayStructHometheater = TRUE; 

        if(cameraEyeY <= 27.0) 
        {
            isUpdate2 = FALSE; 
            isUpdate3 = TRUE; 
        }
    }
    
    // position2->position3
    if(isUpdate3 == TRUE) 
    {
        cameraX = cameraX - (float)19.0/inverse_constant_for_camera_speed3; 
        cameraY = cameraY + (float)8.50/inverse_constant_for_camera_speed3; 
        cameraZ = cameraZ - (float)30.0/inverse_constant_for_camera_speed3; 

        cameraEyeX = cameraEyeX + (float)11.0/inverse_constant_for_camera_speed3; 
        cameraEyeY = cameraEyeY + (float)1.5/inverse_constant_for_camera_speed3; 

        // remove previous structures 
        displayStructTV = FALSE; 
        displayStructHometheater = FALSE; 

        // display new structures 
        if(cameraZ < 17.0f) 
            displayStructCube = TRUE; 
        if(cameraZ < 14.0f) 
            displayStructSphere = TRUE; 
        if(cameraZ < 11.0f) 
            displayStructPyramid = TRUE;  

        if(cameraEyeX >= -0.50) 
        {
            isUpdate3 = FALSE; 
            isUpdate4 = TRUE; 
        }
    }

    // Position3 -> position4 
    if(isUpdate4 == TRUE) 
    {
        cameraX = cameraX - 10.0/inverse_constant_for_camera_speed; 
        cameraY = cameraY - 2.04/inverse_constant_for_camera_speed; 
        cameraZ = cameraZ - 27.90/inverse_constant_for_camera_speed; 

        cameraEyeX = cameraEyeX - 25.0f/inverse_constant_for_camera_speed; 
        cameraEyeY = cameraEyeY - 2.0/inverse_constant_for_camera_speed; 

        // remove previous structures 
        displayStructCube = FALSE; 
        displayStructSphere = FALSE; 
        displayStructPyramid = FALSE; 

        // display new structures 
        if(cameraX < -28.f) 
            displayStructSofa = TRUE; 

        if(cameraX <= -30.50) 
        {
            isUpdate4 = FALSE; 
            isUpdate5 = TRUE; 
        }
    }

    // position4 -> position5 
    if(isUpdate5 == TRUE) 
    {
        cameraX = cameraX + 27.30/inverse_constant_for_camera_speed2; 
        cameraY = cameraY - 0.50/inverse_constant_for_camera_speed2; 
        cameraZ = cameraZ + 22.20/inverse_constant_for_camera_speed2; 

        cameraEyeX = cameraEyeX + 41.20/inverse_constant_for_camera_speed2; 
        cameraEyeY = cameraEyeY + 7.90/inverse_constant_for_camera_speed2; 

        // remove previous structures 
        displayStructSofa = FALSE; 

        // display new structures 
        if(cameraZ > -6.0) 
            displayStructClock = TRUE; 

        if(cameraX >= -3.21) 
        {
            isUpdate5 = FALSE; 
            isUpdate6 = TRUE; 
        }
    }
    
    // Position5 -> final 
    if(isUpdate6 == TRUE) 
    {
        cameraX = cameraX + 39.00/inverse_constant_for_camera_speed3; 
        cameraY = cameraY - 5.10/inverse_constant_for_camera_speed3; 
        cameraZ = cameraZ + 33.48/inverse_constant_for_camera_speed3; 

        cameraEyeX = cameraEyeX + 24.40/inverse_constant_for_camera_speed3; 
        cameraEyeY = cameraEyeY - 9.10/inverse_constant_for_camera_speed3; 
        cameraEyeZ = cameraEyeZ + 37.50/inverse_constant_for_camera_speed3; 

        // remove previous structures 
        displayStructClock = FALSE; 
        
        // display new structure 
        if(cameraZ > 34.0f)
            displayStructBook = TRUE; 

        if(cameraEyeZ >= 37.50) 
        {
            isUpdate6 = FALSE; 
            isFading = TRUE;
        }
    }
}  

void uninitializeScene4(void) 
{
    // code 
    if(quadricScene4) 
    {
        gluDeleteQuadric(quadricScene4); 
        quadricScene4 = NULL; 
    }

    if(texture_initialized) 
    {
        glDeleteTextures(1, &texture_initialized); 
        texture_initialized = 0; 
    }
    if(texture_initializing) 
    {
        glDeleteTextures(1, &texture_initializing); 
        texture_initializing = 0; 
    }
    if(texture_struct_book) 
    {
        glDeleteTextures(1, &texture_struct_book); 
        texture_struct_book = 0; 
    }
    if(texture_struct_clock) 
    {
        glDeleteTextures(1, &texture_struct_clock); 
        texture_struct_clock = 0; 
    }
    if(texture_struct_sphere) 
    {
        glDeleteTextures(1, &texture_struct_sphere); 
        texture_struct_sphere = 0; 
    }
    if(texture_struct_cube) 
    {
        glDeleteTextures(1, &texture_struct_cube); 
        texture_struct_cube = 0; 
    }
    if(texture_struct_pyramid) 
    {
        glDeleteTextures(1, &texture_struct_pyramid); 
        texture_struct_pyramid = 0; 
    }
    if(texture_struct_hometheater) 
    {
        glDeleteTextures(1, &texture_struct_hometheater); 
        texture_struct_hometheater = 0; 
    }
    if(texture_struct_sofa) 
    {
        glDeleteTextures(1, &texture_struct_sofa); 
        texture_struct_sofa = 0; 
    }
    if(texture_struct_sofa) 
    {
        glDeleteTextures(1, &texture_struct_sofa); 
        texture_struct_sofa = 0; 
    }
    if(texture_struct_tv) 
    {
        glDeleteTextures(1, &texture_struct_tv); 
        texture_struct_tv = 0; 
    }
    if(texture_stool_wood) 
    {
        glDeleteTextures(1, &texture_stool_wood); 
        texture_stool_wood = 0; 
    } if(texture_stool_foam) 
    {
        glDeleteTextures(1, &texture_stool_foam); 
        texture_stool_foam = 0; 
    } if(texture_c_book) 
    {
        glDeleteTextures(1, &texture_c_book); 
        texture_c_book = 0; 
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