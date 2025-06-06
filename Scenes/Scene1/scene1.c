#include "scene1.h" 

// texture related variables 
GLuint texture_leaf; 
GLuint texture_tree; 
GLuint texture_temple_top; 
GLuint texture_temple_front_wall;
GLuint texture_temple_side_and_back_walls;  
GLuint texture_ground; 
GLuint texture_road; 
GLuint texture_tree1; 
GLuint texture_tree2; 
GLuint texture_tree3; 
GLuint texture_tree4; 
GLuint texture_god_image; 
GLuint texture_temple_floor; 

// camera related variables 
extern float cameraX, cameraY, cameraZ; 
extern float cameraEyeX, cameraEyeY, cameraEyeZ; 
extern float cameraUpX, cameraUpY, cameraUpZ; 

extern int shot_count; 

const char* cubamapFacesScene1And2[] = {
    "Resources/Cubemap/Scene1And2/right.png",
	"Resources/Cubemap/Scene1And2/left.png",
	"Resources/Cubemap/Scene1And2/top.png",
	"Resources/Cubemap/Scene1And2/bottom.png",
	"Resources/Cubemap/Scene1And2/front.png",
	"Resources/Cubemap/Scene1And2/back.png"
}; 
GLuint cubemapTextureScene1And2; 

// file-io related variables 
extern FILE* gpFile; 

// translation related variables 
extern float tx, ty, tz; 
extern float sx, sy, sz; 

// sphere related variables 
GLUquadric* scene1Quadric = NULL;

BOOL initScene1()
{
	if (!loadGLPngTexture(&texture_leaf, "resources/ganpati.png"))
	{
		fprintf(gpFile, "title.png Texture failed \n");
		return FALSE;
	}
	if (!loadGLPngTexture(&texture_tree, "resources/title.png"))
	{
		fprintf(gpFile, "title.png Texture failed \n");
		return FALSE;
	}
	if(!loadGLPngTexture(&texture_temple_front_wall, "resources/temple_front_wall.png")) 
	{
		fprintf(gpFile, "temple_front_wall.png Texture failed \n");
		return FALSE;
	}
	if(!loadGLPngTexture(&texture_temple_side_and_back_walls, "resources/temple_back_and_side_walls.png")) 
	{
		fprintf(gpFile, "temple_side_and_back_wall.png Texture failed \n");
		return FALSE;
	}
	if(!loadGLPngTexture(&texture_temple_top, "resources/temple_top.png")) 
	{
		fprintf(gpFile, "temple_top.png Texture failed \n");
		return FALSE;
	}
	if (!loadGLPngTexture(&texture_ground, "resources/ground.png"))
	{
		fprintf(gpFile, "ground.png Texture failed \n");
		return FALSE;
	}
	if (!loadGLPngTexture(&texture_road, "resources/road.png"))
	{
		fprintf(gpFile, "road.png Texture failed \n");
		return FALSE;
	}
	if (!loadGLPngTexture(&texture_tree1, "resources/tree1.png"))
	{
		fprintf(gpFile, "tree1.png Texture failed \n");
		return FALSE;
	}
	if (!loadGLPngTexture(&texture_tree2, "resources/tree2.png"))
	{
		fprintf(gpFile, "tree2.png Texture failed \n");
		return FALSE;
	}
	if (!loadGLPngTexture(&texture_tree3, "resources/tree3.png"))
	{
		fprintf(gpFile, "tree3.png Texture failed \n");
		return FALSE;
	}
	if (!loadGLPngTexture(&texture_tree4, "resources/tree4.png"))
	{
		fprintf(gpFile, "tree4.png Texture failed \n");
		return FALSE;
	}
	if (!loadGLPngTexture(&texture_god_image, "resources/vitthal.png"))
	{
		fprintf(gpFile, "vitthal.png Texture failed \n");
		return FALSE;
	}
	if (!loadGLPngTexture(&texture_temple_floor, "resources/temple_floor.png"))
	{
		fprintf(gpFile, "vitthal.png Texture failed \n");
		return FALSE;
	}

	cubemapTextureScene1And2 = loadCubeMap(cubamapFacesScene1And2);

	scene1Quadric = gluNewQuadric(); 

	return (TRUE);
}

void templeBase(
        float x, float y, float z, 
        float sx, float sy, float sz, 
        float r, float g, float b) 
{
    // code 
    glPushMatrix(); 
        glTranslatef(x, y, z);  
        glScalef(sx, sy, sz); 
        glColor3f(r, g, b); 

		// front face /* front-> 1 */ 
		glBindTexture(GL_TEXTURE_2D, texture_temple_front_wall); 
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
		
		glBindTexture(GL_TEXTURE_2D, texture_temple_side_and_back_walls);		
		// back face 
		glBegin(GL_QUADS); 
		glTexCoord2f(2.0f, 1.0f); 
		glVertex3f(-1.0f, 1.0f, -1.0f);	 // right top 
		glTexCoord2f(0.0f, 1.0f); 
		glVertex3f(1.0f, 1.0f, -1.0f);	 // left top 
		glTexCoord2f(0.0f, 0.0f); 
		glVertex3f(1.0, -1.0, -1.0f); 	 // left bottom 
		glTexCoord2f(2.0f, 0.0f); 
		glVertex3f(-1.0f, -1.0f, -1.0f); // right bottom  
		
		// right face 
		glTexCoord2f(1.0f, 1.0f); 
		glVertex3f(1.0f, 1.0f, -1.0f); 	// right top 
		glTexCoord2f(0.0f, 1.0f); 
		glVertex3f(1.0f, 1.0f, 1.0f);	// left top 
		glTexCoord2f(0.0f, 0.0f); 
		glVertex3f(1.0f, -1.0f, 1.0f);	// left bottom 
		glTexCoord2f(1.0f, 0.0f); 
		glVertex3f(1.0f, -1.0f, -1.0f); // right bottom  
		
		// left face 
		glTexCoord2f(1.0f, 1.0f); 
		glVertex3f(-1.0f, 1.0f, 1.0f);	// right top 
		glTexCoord2f(0.0f, 1.0f); 
		glVertex3f(-1.0f, 1.0f, -1.0f);// left top 
		glTexCoord2f(0.0f, 0.0f); 
		glVertex3f(-1.0f, -1.0f, -1.0f); // left bottom 
		glTexCoord2f(1.0f, 0.0f); 
		glVertex3f(-1.0f, -1.0f, 1.0f); // right bottom 

		// top face 
		glTexCoord2f(1.0f, 1.0f); 
		glVertex3f(1.0f, 1.0f, -1.0f); 	// right top 
		glTexCoord2f(0.0f, 1.0f); 
		glVertex3f(-1.0f, 1.0f, -1.0f);	// left top 
		glTexCoord2f(0.0f, 0.0f); 
		glVertex3f(-1.0f, 1.0f, 1.0f);	// left bottom 
		glTexCoord2f(1.0f, 0.0f); 
		glVertex3f(1.0f, 1.0f, 1.0f);   // right bottom 
		glEnd(); 
		glBindTexture(GL_TEXTURE_2D, 0); 
		
		glBindTexture(GL_TEXTURE_2D, texture_temple_floor); 
		// bottom face 
		glBegin(GL_QUADS); 
		glTexCoord2f(1.0f, 1.0f); 
		glVertex3f(1.0f, -1.0f, 1.0f);	// right top 
		glTexCoord2f(0.0f, 1.0f); 
		glVertex3f(-1.0f, -1.0f, 1.0f); // left top 
		glTexCoord2f(0.0f, 0.0f); 
		glVertex3f(-1.0f, -1.0f, -1.0f);	// left bottom 
		glTexCoord2f(1.0f, 0.0f); 
		glVertex3f(1.0f, -1.0f, -1.0f); 	// right bottom 
		glEnd(); 
		glBindTexture(GL_TEXTURE_2D, 0); 

		glBindTexture(GL_TEXTURE_2D, texture_god_image); 
		// drawing face near to back face for applying god's texture  
		glColor3f(1.0f, 1.0f, 1.0f); 
		glBegin(GL_QUADS); 
		glTexCoord2f(1.0f, 1.0f); 
		glVertex3f(-1.0f, 1.0f, -0.99f);	 // right top 
		glTexCoord2f(0.0f, 1.0f); 
		glVertex3f(1.0f, 1.0f, -0.99f);	 // left top 
		glTexCoord2f(0.0f, 0.0f); 
		glVertex3f(1.0, -1.0, -0.99f); 	 // left bottom 
		glTexCoord2f(1.0f, 0.0f); 
		glVertex3f(-1.0f, -1.0f, -0.99f); // right bottom 
		glEnd(); 
		glBindTexture(GL_TEXTURE_2D, 0);  
	glPopMatrix(); 
}

void displayScene1()
{
	// variable declarations 
	static BOOL isThisFirstCall = TRUE; 

	// array for trees 
	struct tree trees[] = {
		{3.70, 0.80, 0.10, 1.30, 1.30, texture_tree1}, 
		{-2.70, 1.30, 0.10, 2.40, 1.90, texture_tree3}, 
		{3.90, 0.70, 3.00, 1.60, 0.90, texture_tree1}, 
		{7.10, 0.65, 3.40, 2.04, 2.10, texture_tree2}, 
		{-3.90, 0.50, 6.30, 2.50f, 2.70f, texture_tree2}, 
		{-5.20, 0.20, 8.50, 0.60, 0.90, texture_tree3}, 
		{-0.80, 0.50, 10.70, 1.10, 1.50, texture_tree3}, 
		{-4.80, 0.50, 10.70, 1.10, 1.50, texture_tree1}, 
		{1.20, 0.80, 14.70, 1.4, 0.90, texture_tree1}, 
		{-5.20, 2.10, 16.30, 2.80, 3.30, texture_tree3}, 
		{2.00, 0.90, 17.60, 2.10, 1.50, texture_tree3}, 
		{2.10, 0.50, 20.20, 2.30, 2.70, texture_tree2}, 
		{-1.50, 1.10, 25.90, 1.72, 2.04, texture_tree4}  
	}; 
	
	// code 
	if(isThisFirstCall == TRUE) 
	{
		cameraX = -1.50f; 
		cameraY = 4.50f;
		cameraZ = 30.0f; 
		
		cameraEyeX = 0.0f; 
		cameraEyeY = -22.0f; 
		cameraEyeZ = -20.0f; 
		
		isThisFirstCall = FALSE; 
		return; 
	}
	
	displayCubemap(cubemapTextureScene1And2, 30.0f, 30.0f, 30.0f); 

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	
	// ground 
	glBindTexture(GL_TEXTURE_2D, texture_ground); 
	glColor3f(1.0f, 1.0f, 1.0f); 
    glBegin(GL_QUADS); 
    glTexCoord2f(40.0f, 50.0f); 
    glVertex3f(40.0f, -0.5f, -40.0f); 
    glTexCoord2f(0.0f, 40.0f); 
    glVertex3f(-40.0f, -0.5f, -40.0f); 
    glTexCoord2f(0.0f, 0.0f); 
    glVertex3f(-40.0f, -0.5f, 40.0f); 
    glTexCoord2f(40.0f, 0.0f); 
    glVertex3f(40.0f, -0.5f, 40.0f); 
    glEnd(); 
    glBindTexture(GL_TEXTURE_2D, 0); 
	
	// road upto temple 
	glBindTexture(GL_TEXTURE_2D, texture_road); 
	glColor3f(1.0f, 1.0f, 1.0f); 
	glBegin(GL_QUADS); 
	glTexCoord2f(1.0f, 10.0f); 
	glVertex3f(0.5f, -0.4f, -10.0f); 
	glTexCoord2f(0.0f, 10.0f); 
	glVertex3f(-0.5f, -0.4f, -10.0f); 
	glTexCoord2f(0.0f, 0.0f); 
	glVertex3f(-0.5f, -0.4f, 35.0f); 
	glTexCoord2f(1.0f, 0.0f); 
	glVertex3f(0.5f, -0.4f, 35.0f); 
	glEnd(); 
	glBindTexture(GL_TEXTURE_2D, 0); 
	
	// temple base  
	templeBase(
		0.0, 2.0f, -12.0f, 
		4.70f, 2.40f, 4.2, 
		1.0f, 1.0f, 1.0f
	); 
	
	// temple top
	billboard(
		0.0f, 7.10f, -12.5f, 
		2.10f, 2.60f, 1.0f,  
		texture_temple_top
	); 

	//-------

	// trees 
	for(int i = 0; i < sizeof(trees)/sizeof(trees[0]); ++i) 
	{
		billboard(
			trees[i].tx, trees[i].ty, trees[i].tz,
			trees[i].width, trees[i].height, 1.0f, 
			trees[i].texture 
		);
	}  
	
	glDisable(GL_BLEND);
}

/*
	initial position 
		-1.50 4.50 30.0
		0.0, -22.0, 0.0 

	Position 1 
		0.0, 0.0 28.0 
		0.0 0.04 -15.0 

	Position 2 
		0.0 0.2 -6.0 
		0.0 0.04 -15.0 

	Position 3 
		0.0 1.5 -9.0 
		0.0 2.11 -15.0 

	Position 4 
		0.00  1.50 -16.00
		0.000000 1.54 -34.94
*/

void updateScene1()
{
	// variable declarations 
	static BOOL isUpdate1 = TRUE; 
	static BOOL isUpdate2 = FALSE; 
	static BOOL isUpdate3 = FALSE; 
	static BOOL isUpdate4 = FALSE; 

	float inverse_constant_for_speed1 = 200.0f; // incresing this constant decreases camera speed 
	float inverse_constant_for_speed2 = 900.0; 
	float inverse_constant_for_speed3 = 250.0f; 
	float inverse_constant_for_speed4 = 80.0f; 

	// code 
	if(isUpdate1 == TRUE) 
	{
		glEnable(GL_FOG); 

		cameraX += 1.50/inverse_constant_for_speed1; 
		cameraY -= 4.50/inverse_constant_for_speed1; 
		cameraZ -= 2.0/inverse_constant_for_speed1; 

		cameraEyeY = 23.50/inverse_constant_for_speed1; 

		if(cameraY < 0.0f) 
		{
			isUpdate1 = FALSE; 
			isUpdate2 = TRUE; 
		} 
	}

	else if(isUpdate2 == TRUE) 
	{ 
		if(cameraY < 0.2f)
			cameraY = cameraY + 0.001; 
		cameraZ -= 34.0f/inverse_constant_for_speed2; 

		if(cameraZ <= -6.0f) 
		{
			isUpdate2 = FALSE;
			isUpdate3 = TRUE;  
		}
	}

	else if(isUpdate3 == TRUE)
	{
		if(cameraY < 1.5f) 
			cameraY = cameraY + 0.009f; 
		cameraZ = cameraZ - 4.0/inverse_constant_for_speed3; 
		if(cameraEyeY < 4.0) 
			cameraEyeY = cameraEyeY + 0.005f; 
		cameraEyeZ = cameraEyeZ - 0.05f;

		if(cameraZ <= -7.5f)  
			glDisable(GL_FOG); 

		if(cameraZ <= -9.0f) 
		{
			isUpdate3 = FALSE; 
			isUpdate4 = TRUE; 
		} 
	}

	else if(isUpdate4 == TRUE) 
	{
		cameraZ = cameraZ - 7.0/inverse_constant_for_speed4; 
		cameraEyeY = cameraEyeY - 0.57/inverse_constant_for_speed4; 
		cameraEyeZ = cameraEyeZ - 20.0/inverse_constant_for_speed4; 

		if(cameraZ <= -16.0)
		{
			isUpdate4 = FALSE; 
			shot_count = shot_count + 1; 
		} 
	}
}

void uninitializeScene1(void) 
{
	// code 
	if(texture_leaf) 
    {
		glDeleteTextures(1, &texture_leaf); 
		texture_leaf = 0; 
    }
	if(texture_temple_top) 
    {
		glDeleteTextures(1, &texture_temple_top); 
		texture_temple_top = 0; 
    }
	if(texture_temple_front_wall) 
    {
		glDeleteTextures(1, &texture_temple_front_wall); 
		texture_temple_front_wall = 0; 
    }
	if(texture_temple_side_and_back_walls) 
    {
		glDeleteTextures(1, &texture_temple_side_and_back_walls); 
		texture_temple_side_and_back_walls = 0; 
    }
	if(texture_ground) 
    {
		glDeleteTextures(1, &texture_ground); 
		texture_ground = 0; 
    }
	if(texture_road) 
    {
		glDeleteTextures(1, &texture_road); 
		texture_road = 0; 
    }
	if(texture_god_image) 
    {
		glDeleteTextures(1, &texture_god_image); 
		texture_god_image = 0; 
    }
	if(texture_temple_floor) 
    {
		glDeleteTextures(1, &texture_temple_floor); 
		texture_temple_floor = 0; 
    }
    if(texture_tree1) 
    {
		glDeleteTextures(1, &texture_tree1); 
		texture_tree1 = 0; 
    }
	if(texture_tree2) 
    {
		glDeleteTextures(1, &texture_tree2); 
		texture_tree2 = 0; 
    }
	if(texture_tree3) 
    {
		glDeleteTextures(1, &texture_tree3); 
		texture_tree3 = 0; 
    }
	if(texture_tree4) 
    {
		glDeleteTextures(1, &texture_tree4); 
		texture_tree4 = 0; 
    }
}
