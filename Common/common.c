#include "common.h" 

extern FILE* gpFile; 

extern GLfloat tx; 

BOOL loadGLPngTexture(GLuint* texture, char* file) 
{
    // variable declarations 
    int w, h, comp; 
    unsigned char* image = stbi_load(file, &w, &h, &comp, 4); // force RGBA 

    // code 
    if(image == NULL) 
    {
        fprintf(gpFile, "Failed to load image : %s\n", file); 
        return (FALSE); 
    }

    glGenTextures(1, texture); 
    glBindTexture(GL_TEXTURE_2D, *texture); 
    glPixelStorei(GL_UNPACK_ALIGNMENT, 4); 

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image); 
    
    glBindTexture(GL_TEXTURE_2D, 0); 
    stbi_image_free(image); 

    fprintf(gpFile, "Image loaded successfully: %s (%dX%d)\n", file, w, h); 
    return (TRUE); 
}

void billboard(float x, float y, float z, float width, float height, GLuint texture) 
{
    // code 
    glPushMatrix(); 
		glBindTexture(GL_TEXTURE_2D, texture); 
		glTranslatef(x, y, z); 
		glScalef(width, height, 1.0f);  
		
		glColor3f(1.0f, 1.0f, 1.0f); 
		glBegin(GL_QUADS);
		glTexCoord2f(1.0f, 1.0f); 
		glVertex3f(1.0f, 1.0f, 0.0f);  // right-top 
		glTexCoord2f(0.0f, 1.0f); 
		glVertex3f(-1.0f, 1.0f, 0.0f); // left-top 
		glTexCoord2f(0.0f, 0.0f); 
		glVertex3f(-1.0f, -1.0f, 0.0f);	// left-bottom 
		glTexCoord2f(1.0f, 0.0f); 
		glVertex3f(1.0f, -1.0f, 0.0f);	// right-bottom 
		glEnd(); 
		glBindTexture(GL_TEXTURE_2D, 0); 
	glPopMatrix(); 
	
	glPushMatrix(); 
		glBindTexture(GL_TEXTURE_2D, texture); 
		glTranslatef(x, y, z); 
		glScalef(width, height, 1.0f);  
		glRotatef(90.0f, 0.0f, 1.0f, 0.0f); 
		glColor3f(1.0f, 1.0f, 1.0f); 
		
		glBegin(GL_QUADS);
		glTexCoord2f(1.0f, 1.0f); 
		glVertex3f(1.0f, 1.0f, 0.0f);  // right-top 
		glTexCoord2f(0.0f, 1.0f); 
		glVertex3f(-1.0f, 1.0f, 0.0f); // left-top 
		glTexCoord2f(0.0f, 0.0f); 
		glVertex3f(-1.0f, -1.0f, 0.0f);	// left-bottom 
		glTexCoord2f(1.0f, 0.0f); 
		glVertex3f(1.0f, -1.0f, 0.0f);	// right-bottom 
		glEnd(); 
		glBindTexture(GL_TEXTURE_2D, 0); 
	glPopMatrix(); 
}

unsigned int loadCubemap(const char* faces[]) 
{
    // variable declarations 
    unsigned int textureID; 
    int width, height, nrChannels; 

    // code 
    glGenTextures(1, &textureID); 
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID); 

    for(int i = 0; i < 6; ++i) 
    {
        unsigned char* data = stbi_load(faces[i], &width, &height, &nrChannels, STBI_rgb_alpha); 

        if(data) 
        {
            if(nrChannels == 3) 
            {
                glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data); 
            }
            else if(nrChannels == 4) 
            {
                glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data); 
            } 
            stbi_image_free(data); 
        }
        else 
        {
            printf("Cubemap texture failed to load at path : %s\n", faces[i]); 
            stbi_image_free(data); 
        }
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); 
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); 
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE); 

    return (textureID); 
}

void textureOnQuad(float tx, float ty, float tz, float sx, float sy, float sz, GLuint texture)  
{
    glPushMatrix(); 
        glTranslatef(tx, ty, tz); 
        glScalef(sx, sy, sz);  
        
        glBindTexture(GL_TEXTURE_2D, texture); 
        glColor3f(1.0f, 1.0f, 1.0f); 
		glBegin(GL_QUADS);
		glTexCoord2f(1.0f, 1.0f); 
		glVertex3f(1.0f, 1.0f, 0.0f);  // right-top 
		glTexCoord2f(0.0f, 1.0f); 
		glVertex3f(-1.0f, 1.0f, 0.0f); // left-top 
		glTexCoord2f(0.0f, 0.0f); 
		glVertex3f(-1.0f, -1.0f, 0.0f);	// left-bottom 
		glTexCoord2f(1.0f, 0.0f); 
		glVertex3f(1.0f, -1.0f, 0.0f);	// right-bottom 
		glEnd(); 
		glBindTexture(GL_TEXTURE_2D, 0); 
	glPopMatrix(); 
}  