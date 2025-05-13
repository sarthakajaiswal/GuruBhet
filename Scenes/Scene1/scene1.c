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

const char* faces[] = {
    "Resources/Cubemap/right.png",
	"Resources/Cubemap/left.png",
	"Resources/Cubemap/top.png",
	"Resources/Cubemap/bottom.png",
	"Resources/Cubemap/front.png",
	"Resources/Cubemap/back.png"
}; 
GLuint cubemapTexture; 

// file-io related variables 
extern FILE* gpFile; 

// translation related variables 
extern float tx, ty, tz; 
extern float sx, sy, sz; 

/* 
void displayCubemap(void)
{
	// code 
	glPushMatrix();
	{
		glScalef((1 + 3.100 + 11.650) * 2.5, (1 + 2.770) * 2.5, (1 + 3.600 + 9.7) * 2.5);
		glColor3f(1.0f, 1.0f, 1.0f);

		glEnable(GL_TEXTURE_CUBE_MAP);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);

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
*/ 

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

	// cubemapTexture = loadCubemap(faces);

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
	// array for trees 
	struct tree trees[] = {
		{3.70, 0.80, 0.10, 1.30, 1.30, texture_tree1}, 
		{-2.70, 1.30, 0.10, 2.40, 1.90, texture_tree3}, 
		{3.90, 0.70, 3.00, 1.60, 0.90, texture_tree1}, 
		{6.90, 0.35, 3.00, 1.60, 0.90, texture_tree2}, 
		{-3.90, 0.50, 6.30, 2.50f, 2.70f, texture_tree2}, 
		{-1.20, -0.30, 8.50, 0.60, 0.90, texture_tree2}, 
		{-5.20, 0.20, 8.50, 0.60, 0.90, texture_tree3}, 
		{-0.80, 0.50, 10.70, 1.10, 1.50, texture_tree3}, 
		{-4.80, 1.00, 10.70, 1.10, 1.50, texture_tree1}, 
		{1.20, 0.20, 14.70, 1.4, 0.90, texture_tree1}, 
		{-5.20, 2.10, 16.30, 2.80, 3.30, texture_tree3}, 
		{2.00, 0.90, 17.60, 1.10, 1.50, texture_tree3}, 
		{2.10, 0.50, 20.20, 2.30, 2.70, texture_tree2}, 
		{-1.50, 1.10, 25.90, 1.72, 2.04, texture_tree4}  
	}; 

	// code 
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	
	// displayCubemap(); 
	
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
		2.10f, 2.60f,  
		texture_temple_top
	); 

	//-------

	// trees 
	for(int i = 0; i < sizeof(trees)/sizeof(trees[0]); ++i) 
	{
		billboard(
			trees[i].tx, trees[i].ty, trees[i].tz,
			trees[i].width, trees[i].height, 
			trees[i].texture 
		);
	}  

	glDisable(GL_BLEND);
}

void updateScene1()
{
	// code 
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
