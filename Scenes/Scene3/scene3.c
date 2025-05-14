#include "scene3.h" 

// texture related variables 
GLuint texture_gift_background; 
GLuint texture_giftbox; 
GLuint texture_giftbox_topface; 
GLuint texture_sunglass; 

// file-io related variables 
extern FILE* gpFile; 

// translation related variables 
extern float tx, ty, tz; 
extern float sx, sy, sz; 

float boxOpenAngle = 0.0f; 
float boxRotateAngle = 0.0f;

// camera related variables 
extern float cameraX, cameraY, cameraZ; 
extern float cameraEyeX, cameraEyeY, cameraEyeZ; 
extern float cameraUpX, cameraUpY, cameraUpZ; 

BOOL initScene3(void) 
{
    // code 
    if (!loadGLPngTexture(&texture_gift_background, "resources/boom.png"))
	{
		fprintf(gpFile, "boom.png Texture failed \n");
		return FALSE;
	}

    if (!loadGLPngTexture(&texture_giftbox, "resources/giftbox.png"))
	{
		fprintf(gpFile, "giftbox.png Texture failed \n");
		return FALSE;
	}

    if (!loadGLPngTexture(&texture_giftbox_topface, "resources/giftbox_topface.png"))
	{
		fprintf(gpFile, "giftbox_topface.png Texture failed \n");
		return FALSE;
	}

    if (!loadGLPngTexture(&texture_sunglass, "resources/sunglass.png"))
	{
		fprintf(gpFile, "sunglass.png Texture failed \n");
		return FALSE;
	}

    return (TRUE); 
}

void background(void) 
{
    glBindTexture(GL_TEXTURE_2D, texture_gift_background); 

    glColor3f(1.0f, 1.0f, 1.0f); 
    glBegin(GL_QUADS); 
    glTexCoord2f(1.0f, 1.0f); 
    glVertex3f(1.0f, 1.0f, 1.0f); // right top /* right->1, top->1 */ 
    glTexCoord2f(0.0f, 1.0f); 
    glVertex3f(-1.0f, 1.0f, 1.0f);	// left top /* left->-1, top->1 */ 
    glTexCoord2f(0.0f, 0.0f); 
    glVertex3f(-1.0f, -1.0f, 1.0f);  // left bottom /* left->-1, bottom->-1 */ 
    glTexCoord2f(1.0f, 0.0f); 
    glVertex3f(1.0f, -1.0f, 1.0f); // right bottom /* right->1, bottom->-1 */ 
    glEnd(); 
    glBindTexture(GL_TEXTURE_2D, 0); 
}

void drawGiftBox(
        float x, float y, float z, 
        float sizeX, float sizeY, float sizeZ 
) 
{
    // code 
    glPushMatrix(); 
    {
        glTranslatef(x, y, z);  
        glScalef(sizeX, sizeY, sizeZ); 
    
        glPushMatrix(); 
        {
            glTranslatef(0.0f, 1.0f, -1.0f);
            glRotatef(-boxOpenAngle, 1.0f, 0.0f, 0.0f); // rotation for opening box  
            
            glTranslatef(0.0f, -1.0f, 1.0f); 
            
            glBindTexture(GL_TEXTURE_2D, texture_giftbox_topface); 
            glBegin(GL_QUADS); 
            // top face 
            glTexCoord2f(1.0f, 1.0f); 
            glVertex3f(1.02f, 1.025f, -1.0f); 	// right top 
            glTexCoord2f(0.0f, 1.0f); 
            glVertex3f(-1.02f, 1.025f, -1.0f);	// left top 
            glTexCoord2f(0.0f, 0.0f); 
            glVertex3f(-1.02f, 1.025f, 1.0f);	// left bottom 
            glTexCoord2f(1.0f, 0.0f); 
            glVertex3f(1.02f, 1.025f, 1.0f);   // right bottom 
            glEnd(); 
            glBindTexture(GL_TEXTURE_2D, 0); 

            glBindTexture(GL_TEXTURE_2D, texture_giftbox);
            drawTexturedCube(
                0.00, 0.95, 0.00, 
                1.04, 0.04, 1.00, 
                1.0f, 1.0f, 1.0f, 
                FACE_ALL & ~FACE_TOP, 
                texture_giftbox,  
                texture_giftbox,  
                texture_giftbox,  
                0,  
                texture_giftbox,  
                texture_giftbox   
            );
            glBindTexture(GL_TEXTURE_2D, 0);
        } 
        glPopMatrix(); 

        drawTexturedCube(0.04, 0.12, 1.08, 1.00, 0.84, 0.04, 1.0f, 1.0f, 1.0f, FACE_ALL, texture_giftbox, texture_giftbox, texture_giftbox, texture_giftbox, texture_giftbox, texture_giftbox);   // front 
        drawTexturedCube(0.04, 0.12, -1.0, 1.00, 0.84, 0.04, 1.0f, 1.0f, 1.0f, FACE_ALL, texture_giftbox, texture_giftbox, texture_giftbox, texture_giftbox, texture_giftbox, texture_giftbox);   // back 
        drawTexturedCube(-1.00, 0.12, 0.04, 0.04, 0.84, 1.08, 1.0f, 1.0f, 1.0f, FACE_ALL, texture_giftbox, texture_giftbox, texture_giftbox, texture_giftbox, texture_giftbox, texture_giftbox);  // left 
        drawTexturedCube(1.00, 0.12, 0.04, 0.04, 0.84, 1.08, 1.0f, 1.0f, 1.0f, FACE_ALL, texture_giftbox, texture_giftbox, texture_giftbox, texture_giftbox, texture_giftbox, texture_giftbox);  // left 
        drawTexturedCube(0.00, -0.67, 0.00, 0.96, 0.042, 1.03, 1.0f, 1.0f, 1.0f, FACE_ALL, texture_giftbox, texture_giftbox, texture_giftbox, texture_giftbox, texture_giftbox, texture_giftbox);   // bottom 

        // sunglass 
        glPushMatrix(); 
        {
            glBindTexture(GL_TEXTURE_2D, texture_sunglass);
            glScalef(0.75, 4.50, 0.84); 

            glBegin(GL_QUADS); 
            glTexCoord2f(1.0f, 1.0f); 
            glVertex3f(1.0f, 0.0f, -1.0f); 	// right top 
            glTexCoord2f(0.0f, 1.0f); 
            glVertex3f(-1.0f, 0.0f, -1.0f);	// left top 
            glTexCoord2f(0.0f, 0.0f); 
            glVertex3f(-1.0f, 0.0f, 1.0f);	// left bottom 
            glTexCoord2f(1.0f, 0.0f); 
            glVertex3f(1.0f, 0.0f, 1.0f);   // right bottom 
            glEnd(); 
            glBindTexture(GL_TEXTURE_2D, 0);
        } 
        glPopMatrix(); 
    } 
    glPopMatrix(); 
}

void displayScene3(void) 
{
    // variable declarations 
    static BOOL isThisFirstCall = TRUE; 

    // code 
    if(isThisFirstCall) 
    {
        cameraX = -3.0; 
        cameraY = 15.0f; 
        cameraZ = 11.0f; 

        cameraEyeX = 0.0f; 
        cameraEyeY = 2.0f; 
        cameraEyeZ = 0.0f; 

        isThisFirstCall = FALSE;
    }

    // background 
    drawTexturedCube(
        0.0f, 0.0f, 0.0f, 
        20.0f, 20.0f, 20.0f, 
        1.0f, 1.0f, 1.0f, FACE_ALL, 
        texture_gift_background, 
        texture_gift_background, 
        texture_gift_background, 
        texture_gift_background, 
        texture_gift_background, 
        texture_gift_background
    ); 

    // giftbox with gift (sunglass texture) inside 
    glPushMatrix(); 
    {
        glRotatef(boxRotateAngle, 0.0f, 1.0f, 0.0f);  
        drawGiftBox(
            0.0f, 0.0f, 0.0f, 
            3.20f, 1.10f, 2.20f
        );
    }
    glPopMatrix();  
}

void updateScene3(void) 
{
    // variable declarations 
    static float inverse_constant_for_camera_speed = 1000; 
    static BOOL isCameraUpdating = TRUE; 

    // code 
    if(boxOpenAngle < 120.0f)
        boxOpenAngle += 1.0f; 
    
    if(boxRotateAngle <= 360.0f) 
    {
        boxRotateAngle = boxRotateAngle + 1.0f;  
    } 

    if(isCameraUpdating == TRUE) 
    {
        cameraX = cameraX + 6.0/inverse_constant_for_camera_speed; 
        cameraY = cameraY - 7.0/inverse_constant_for_camera_speed; 
        cameraZ = cameraZ - 8.0/inverse_constant_for_camera_speed; 

        cameraEyeX = cameraEyeX - 2.0/inverse_constant_for_camera_speed; 
        cameraEyeY = cameraEyeY - 5.0/inverse_constant_for_camera_speed; 
        cameraEyeZ = cameraEyeZ - 4.0/inverse_constant_for_camera_speed; 
    } 

    if(cameraX >= 3.0f) 
        isCameraUpdating = FALSE; 
}

void uninitializeScene3(void) 
{
    // code 
    if(texture_sunglass) 
    {
        glDeleteTextures(1, &texture_sunglass); 
        texture_sunglass = 0; 
    }
    if(texture_giftbox_topface) 
    {
        glDeleteTextures(1, &texture_giftbox_topface); 
        texture_giftbox_topface = 0; 
    }
    if(texture_giftbox) 
    {
        glDeleteTextures(1, &texture_giftbox); 
        texture_giftbox = 0; 
    }
    if(texture_gift_background) 
    {
        glDeleteTextures(1, &texture_gift_background); 
        texture_gift_background = 0; 
    }
} 
