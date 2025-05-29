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

void billboard(float x, float y, float z, float width, float height, float depth, GLuint texture) 
{
    // code 
    glPushMatrix(); 
		glBindTexture(GL_TEXTURE_2D, texture); 
		glTranslatef(x, y, z); 
		glScalef(width, height, depth);  
		
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
		glScalef(width, height, depth);  
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

unsigned int loadCubeMap(const char* faces[])
{
	// variable declarations 
	unsigned int textureID;

	int width, height, nrChannels;

	// code 
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
	
	for (int i = 0; i < 6; i++) {
		unsigned char* data = stbi_load(faces[i], &width, &height, &nrChannels, STBI_rgb_alpha);
		if (data) {
			if (nrChannels == 3)
			{
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
				
			}
			else if (nrChannels == 4)
			{
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			}
			stbi_image_free(data);
		}
		else {
			printf("Cubemap texture failed to load at path: %s\n", faces[i]);
			stbi_image_free(data);
		}
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	return textureID;
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

BOOL loadGLTexture(GLuint* texture, TCHAR imageResourceID[]) 
{
	// variable declarations 
	HBITMAP hBitmap = NULL; 
	BITMAP bmp; 
	BOOL bResult = FALSE; 

	// code 
	// load the bitmap as image 	
	hBitmap = (HBITMAP)LoadImage(			/* value is typecasted accordingly this function can load various types of images, here we are loading bitmap so return */ 
					GetModuleHandle(NULL), 	/* hInstance, passing NULL to this function return handle to current instance */
					imageResourceID, 
					IMAGE_BITMAP, 			/* je image load krachi aahe tyacha type */
					0, 0,  					/* width and height pf image width and height is given ONLY when the image is of icon or cursor */
					LR_CREATEDIBSECTION 	/* LR -> load resource, DIB -> device independent bitmap | mazya image cha dib tayar krun load kr */
				); 

	if(hBitmap)
	{
		bResult = TRUE; 

		// get bitmap structure from the loaded bitmap image 
		GetObject(hBitmap, sizeof(BITMAP), &bmp); 

		// generate OpenGL texture object 
		glGenTextures(1, texture); 
			
		// bind to newly created empty texture object 
		glBindTexture(
			GL_TEXTURE_2D, 	/* bind kuth kru */
			*texture		/* bind kunala kru */
		); 

		glPixelStorei(GL_UNPACK_ALIGNMENT, 4); 	
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); 
		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, bmp.bmWidth, bmp.bmHeight, GL_BGR_EXT, GL_UNSIGNED_BYTE, bmp.bmBits); 
		
		glBindTexture(GL_TEXTURE_2D, 0); 
		DeleteObject(hBitmap); 
		hBitmap = NULL; 
	}

	// gen - bind - unbind triplet 

	return (bResult); 
}  

extern float sx; 

// cubemap related functions 
void displayCubemap(GLuint texture, float cubeScaleX, float cubeScaleY, float cubeScaleZ)
{
	// code  
	glPushMatrix();
	{
		// glScalef(1 + 3.100 , 1 + 2.770 , 1 + 3.600);
		// glScalef((1 + 3.100 + 11.650) * 2.5, (1 + 2.770) * 2.5, (1 + 3.600 + 9.7) * 2.5);
		// glScalef(1.0f, 1.0f, 1.0f); 
		glScalef(cubeScaleX, cubeScaleY, cubeScaleZ); 
		glColor3f(1.0f, 1.0f, 1.0f);

		glEnable(GL_TEXTURE_CUBE_MAP);
		glBindTexture(GL_TEXTURE_CUBE_MAP, texture);

		// Render Front face
		glBegin(GL_QUADS);
		glNormal3f(0.0, 0.0, -1.0);
		glTexCoord3f(-1.0f, -1.0f, 1.0f);
		glVertex3f(-1.0f, -1.0f, 1.0f);
		glTexCoord3f(1.0f, -1.0f, 1.0f);
		glVertex3f(1.0f, -1.0f, 1.0f);
		glTexCoord3f(1.0f, 1.0f, 1.0f);
		glVertex3f(1.0f, 1.0f, 1.0f);
		glTexCoord3f(-1.0f, 1.0f, 1.0f);
		glVertex3f(-1.0f, 1.0f, 1.0f);
		glEnd();

		// Render Back face
		glBegin(GL_QUADS);
		glNormal3f(0.0, 0.0, 1.0);
		glTexCoord3f(1.0f, -1.0f, -1.0f);
		glVertex3f(1.0f, -1.0f, -1.0f);
		glTexCoord3f(-1.0f, -1.0f, -1.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);
		glTexCoord3f(-1.0f, 1.0f, -1.0f);
		glVertex3f(-1.0f, 1.0f, -1.0f);
		glTexCoord3f(1.0f, 1.0f, -1.0f);
		glVertex3f(1.0f, 1.0f, -1.0f);
		glEnd();

		// Render Left face
		glBegin(GL_QUADS);
		glNormal3f(1.0, 0.0, 0.0);
		glTexCoord3f(-1.0f, -1.0f, -1.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);
		glTexCoord3f(-1.0f, -1.0f, 1.0f);
		glVertex3f(-1.0f, -1.0f, 1.0f);
		glTexCoord3f(-1.0f, 1.0f, 1.0f);
		glVertex3f(-1.0f, 1.0f, 1.0f);
		glTexCoord3f(-1.0f, 1.0f, -1.0f);
		glVertex3f(-1.0f, 1.0f, -1.0f);
		glEnd();

		// Render Right face
		glBegin(GL_QUADS);
		glNormal3f(-1.0, 0.0, 0.0);
		glTexCoord3f(1.0f, -1.0f, 1.0f);
		glVertex3f(1.0f, -1.0f, 1.0f);
		glTexCoord3f(1.0f, -1.0f, -1.0f);
		glVertex3f(1.0f, -1.0f, -1.0f);
		glTexCoord3f(1.0f, 1.0f, -1.0f);
		glVertex3f(1.0f, 1.0f, -1.0f);
		glTexCoord3f(1.0f, 1.0f, 1.0f);
		glVertex3f(1.0f, 1.0f, 1.0f);
		glEnd();

		//// Render Top face
		glNormal3f(0.0, -1.0, 0.0);
		glBegin(GL_QUADS);
		glTexCoord3f(-1.0f, 1.0f, 1.0f);
		glVertex3f(-1.0f, 1.0f, 1.0f);
		glTexCoord3f(1.0f, 1.0f, 1.0f);
		glVertex3f(1.0f, 1.0f, 1.0f);
		glTexCoord3f(1.0f, 1.0f, -1.0f);
		glVertex3f(1.0f, 1.0f, -1.0f);
		glTexCoord3f(-1.0f, 1.0f, -1.0f);
		glVertex3f(-1.0f, 1.0f, -1.0f);
		glEnd();

		//// Render Bottom face
		glBegin(GL_QUADS);
		glNormal3f(0.0, 1.0, 0.0);
		glTexCoord3f(-1.0f, -1.0f, -1.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);
		glTexCoord3f(1.0f, -1.0f, -1.0f);
		glVertex3f(1.0f, -1.0f, -1.0f);
		glTexCoord3f(1.0f, -1.0f, 1.0f);
		glVertex3f(1.0f, -1.0f, 1.0f);
		glTexCoord3f(-1.0f, -1.0f, 1.0f);
		glVertex3f(-1.0f, -1.0f, 1.0f);
		glEnd();

		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
		glDisable(GL_TEXTURE_CUBE_MAP);
	}
	glPopMatrix();
}

