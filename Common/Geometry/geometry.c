// header files 
#include "geometry.h"

// function definitions 

// function to draw cube at specified location 
void drawTexturedCube(
        float x, float y, float z, 
        float sx, float sy, float sz, 
        float r, float g, float b, 
        FaceType faces_to_be_textured, 
        GLuint texture_front, 
        GLuint texture_right, 
        GLuint texture_back, 
        GLuint texture_left, 
        GLuint texture_top, 
        GLuint texture_bottom
    ) 
{
    // code 
    glPushMatrix(); 
    {
        glTranslatef(x, y, z);  
        glScalef(sx, sy, sz); 
        glColor3f(r, g, b); 

        // front face  
        glNormal3f(0.0f, 0.0f, 1.0f); 
        glBindTexture(GL_TEXTURE_2D, texture_front); 
        glBegin(GL_QUADS); 
        if(faces_to_be_textured & FACE_FRONT)
            glTexCoord2f(1.0f, 1.0f); 
        glVertex3f(1.0f, 1.0f, 1.0f); 

        if(faces_to_be_textured & FACE_FRONT) 
            glTexCoord2f(0.0f, 1.0f); 
        glVertex3f(-1.0f, 1.0f, 1.0f);	 
        
        if(faces_to_be_textured & FACE_FRONT)
            glTexCoord2f(0.0f, 0.0f); 
        glVertex3f(-1.0f, -1.0f, 1.0f);  
        
        if(faces_to_be_textured & FACE_FRONT)
            glTexCoord2f(1.0f, 0.0f); 
        glVertex3f(1.0f, -1.0f, 1.0f); 
        glEnd(); 
        glBindTexture(GL_TEXTURE_2D, 0); 
        
        // right face 
        glNormal3f(1.0f, 0.0f, 0.0f); 
        glBindTexture(GL_TEXTURE_2D, texture_right); 
        glBegin(GL_QUADS); 
        if(faces_to_be_textured & FACE_RIGHT) 
            glTexCoord2f(1.0f, 1.0f); 
        glVertex3f(1.0f, 1.0f, -1.0f); 	// right top 

        if(faces_to_be_textured & FACE_RIGHT)
            glTexCoord2f(0.0f, 1.0f); 
        glVertex3f(1.0f, 1.0f, 1.0f);	// left top 

        if(faces_to_be_textured & FACE_RIGHT)
            glTexCoord2f(0.0f, 0.0f); 
        glVertex3f(1.0f, -1.0f, 1.0f);	// left bottom 

        if(faces_to_be_textured & FACE_RIGHT)
            glTexCoord2f(1.0f, 0.0f); 
        glVertex3f(1.0f, -1.0f, -1.0f); // right bottom  
        glEnd(); 
        glBindTexture(GL_TEXTURE_2D, 0); 
        
        // back face 
        glNormal3f(0.0f, 0.0f, -1.0f);
        glBindTexture(GL_TEXTURE_2D, texture_back); 
        glBegin(GL_QUADS); 
        if(faces_to_be_textured & FACE_BACK)
            glTexCoord2f(1.0f, 1.0f); 
        glVertex3f(-1.0f, 1.0f, -1.0f);	 // right top 

        if(faces_to_be_textured & FACE_BACK)
            glTexCoord2f(0.0f, 1.0f); 
        glVertex3f(1.0f, 1.0f, -1.0f);	 // left top 

        if(faces_to_be_textured & FACE_BACK)
            glTexCoord2f(0.0f, 0.0f); 
        glVertex3f(1.0, -1.0, -1.0f); 	 // left bottom 

        if(faces_to_be_textured & FACE_BACK)
            glTexCoord2f(1.0f, 0.0f); 
        glVertex3f(-1.0f, -1.0f, -1.0f); // right bottom  
        glEnd(); 
        glBindTexture(GL_TEXTURE_2D, 0); 
        
        // left face 
        glNormal3f(-1.0f, 0.0f, 0.0f);
        glBindTexture(GL_TEXTURE_2D, texture_left); 
        glBegin(GL_QUADS); 
        if(faces_to_be_textured & FACE_LEFT)
            glTexCoord2f(1.0f, 1.0f); 
        glVertex3f(-1.0f, 1.0f, 1.0f);	// right top 

        if(faces_to_be_textured & FACE_LEFT)
            glTexCoord2f(0.0f, 1.0f); 
        glVertex3f(-1.0f, 1.0f, -1.0f);// left top 

        if(faces_to_be_textured & FACE_LEFT)
            glTexCoord2f(0.0f, 0.0f); 
        glVertex3f(-1.0f, -1.0f, -1.0f); // left bottom 

        if(faces_to_be_textured & FACE_LEFT)
            glTexCoord2f(1.0f, 0.0f); 
        glVertex3f(-1.0f, -1.0f, 1.0f); // right bottom 
        glEnd(); 
        glBindTexture(GL_TEXTURE_2D, 0); 

        // top face 
        glNormal3f(0.0f, 1.0f, 0.0f); 
        glBindTexture(GL_TEXTURE_2D, texture_top); 
        glBegin(GL_QUADS); 
        if(faces_to_be_textured & FACE_TOP)
            glTexCoord2f(1.0f, 1.0f); 
        glVertex3f(1.0f, 1.0f, -1.0f); 	// right top 

        if(faces_to_be_textured & FACE_TOP)
            glTexCoord2f(0.0f, 1.0f); 
        glVertex3f(-1.0f, 1.0f, -1.0f);	// left top 

        if(faces_to_be_textured & FACE_TOP)
            glTexCoord2f(0.0f, 0.0f); 
        glVertex3f(-1.0f, 1.0f, 1.0f);	// left bottom 

        if(faces_to_be_textured & FACE_TOP)
            glTexCoord2f(1.0f, 0.0f); 
        glVertex3f(1.0f, 1.0f, 1.0f);   // right bottom 
        glEnd(); 
        glBindTexture(GL_TEXTURE_2D, 0); 
        
        // bottom face 
        glNormal3f(0.0f, -1.0f, 0.0f);
        glBindTexture(GL_TEXTURE_2D, texture_bottom); 
        glBegin(GL_QUADS); 
        if(faces_to_be_textured & FACE_BOTTOM)
            glTexCoord2f(1.0f, 1.0f); 
        glVertex3f(1.0f, -1.0f, 1.0f);	// right top 

        if(faces_to_be_textured & FACE_BOTTOM)
            glTexCoord2f(0.0f, 1.0f); 
        glVertex3f(-1.0f, -1.0f, 1.0f); // left top 

        if(faces_to_be_textured & FACE_BOTTOM)
            glTexCoord2f(0.0f, 0.0f); 
        glVertex3f(-1.0f, -1.0f, -1.0f);	// left bottom 

        if(faces_to_be_textured & FACE_BOTTOM)
            glTexCoord2f(1.0f, 0.0f); 
        glVertex3f(1.0f, -1.0f, -1.0f); 	// right bottom 
        glEnd(); 
        glBindTexture(GL_TEXTURE_2D, 0); 
    } 
    glPopMatrix(); 
}

void drawPyramid(
    float x, float y, float z, 
    float sx, float sy, float sz, 
    float r, float g, float b, float a 
) 
{
    glPushMatrix(); 
        glTranslatef(x, y, z);  
        glScalef(sx, sy, sz); 
        glColor4f(r, g, b, a); 

        glBegin(GL_TRIANGLES);
        // front face 
        glNormal3f(0.0f, 0.447214f, 0.894428f); 
        glTexCoord2f(0.5f, 1.0f); 
        glVertex3f(0.0f, 1.0f, 0.0f);
        glTexCoord2f(0.0f, 0.0f); 
        glVertex3f(-1.0f, -1.0f, 1.0f);	
        glTexCoord2f(1.0f, 0.0f); 
        glVertex3f(1.0f, -1.0f, 1.0f); 
        
        // right face 
        glNormal3f(0.894428f, 0.447214f, 0.0f); 
        glTexCoord2f(0.5f, 1.0f); 
        glVertex3f(0.0f, 1.0f, 0.0f); 
        glTexCoord2f(0.0f, 0.0f); 
        glVertex3f(1.0f, -1.0f, 1.0f); 
        glTexCoord2f(1.0f, 0.0f); 
        glVertex3f(1.0f, -1.0f, -1.0f); 
        
        // back face 
        glNormal3f(0.0f, 0.447214f, -0.894428f); 
        glTexCoord2f(0.5f, 1.0f); 
        glVertex3f(0.0f, 1.0f, 0.0f); 
        glTexCoord2f(1.0f, 0.0f); 
        glVertex3f(1.0f, -1.0f, -1.0f); 
        glTexCoord2f(0.0f, 0.0f); 
        glVertex3f(-1.0f, -1.0f, -1.0f); 
        
        // left face 
        glNormal3f(-0.894428, 0.447214f, 0.0f);
        glTexCoord2f(0.5f, 1.0f); 
        glVertex3f(0.0f, 1.0f, 0.0f); 
        glTexCoord2f(0.0f, 0.0f); 
        glVertex3f(-1.0f, -1.0f, -1.0f);  
        glTexCoord2f(1.0f, 0.0f); 
        glVertex3f(-1.0f, -1.0f, 1.0f); 
        glEnd();
    glPopMatrix(); 
}

void rectangle(
    float tx, float ty, float tz, 
    float sx, float sy, float sz, 
    float xAng, float yAng, float zAng
) 
{
    // code 
    glPushMatrix(); 
        glTranslatef(tx, ty, tz);  
        glScalef(1+sx, 1+sy, 1+sz); 
        glRotatef(xAng, 1, 0, 0);
        glRotatef(yAng, 0, 1, 0);  
        glRotatef(zAng, 0, 0, 1);  

        glBegin(GL_QUADS); 

        glTexCoord2f(1.0f, 1.0f); 
        glVertex3f(1.0f, 1.0f, 0.0f); 

        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(-1.0f, -1.0f, 0.0f);  

        glTexCoord2f(1.0f, 0.0f); 
        glVertex3f(1.0f, -1.0f, 0.0f); 

        glEnd(); 
    glPopMatrix(); 
}

