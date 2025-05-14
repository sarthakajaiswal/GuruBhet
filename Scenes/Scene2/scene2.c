#include "scene2.h" 

// texture related variables 
extern GLuint texture_leaf; 
extern GLuint texture_tree; 
extern GLuint texture_temple_top; 
extern GLuint texture_temple_front_wall;
extern GLuint texture_temple_side_and_back_walls;  
extern GLuint texture_ground; 
extern GLuint texture_road; 
extern GLuint texture_tree1; 
extern GLuint texture_tree2; 
extern GLuint texture_tree3; 
extern GLuint texture_tree4; 
extern GLuint texture_god_image; 
extern GLuint texture_temple_floor; 

GLuint texture_school_floor; 
GLuint texture_class_front_mstc; 
GLuint texture_class_front_dsa; 
GLuint texture_class_front_cpp; 
GLuint texture_class_front_python; 
GLuint texture_head_cabin; 
GLuint texture_logo; 
GLuint texture_lsp; 
GLuint texture_headmaster_front_wall; 
GLuint texture_headmaster_side_wall; 

GLUquadric* quadric = NULL; 

// camera related variables 
extern float cameraX, cameraY, cameraZ; 
extern float cameraEyeX, cameraEyeY, cameraEyeZ; 

/* 
const char* faces[] = {
    "Resources/Cubemap/right.png",
	"Resources/Cubemap/left.png",
	"Resources/Cubemap/top.png",
	"Resources/Cubemap/bottom.png",
	"Resources/Cubemap/front.png",
	"Resources/Cubemap/back.png"
}; 

GLuint cubemapTexture; 
*/ 

// file-io related variables 
extern FILE* gpFile; 

// translation related variables 
extern float tx, ty, tz; 
extern float sx, sy, sz; 

BOOL initScene2()
{
	if (!loadGLPngTexture(&texture_school_floor, "resources/temple_floor.png"))
	{
		fprintf(gpFile, "texture for school floor failed to load\n");
		return FALSE;
	}
	if (!loadGLPngTexture(&texture_class_front_mstc, "resources/classroom_front_mstc.png"))
	{
		fprintf(gpFile, "texture for mstc classroom failed to load\n");
		return FALSE;
	}
	if (!loadGLPngTexture(&texture_class_front_dsa, "resources/classroom_front_dsa.png"))
	{
		fprintf(gpFile, "texture for dsa classroom failed to load\n");
		return FALSE;
	}
	if (!loadGLPngTexture(&texture_class_front_cpp, "resources/classroom_front_cpp.png"))
	{
		fprintf(gpFile, "texture for cpp classroom failed to load\n");
		return FALSE;
	}
	if (!loadGLPngTexture(&texture_class_front_python, "resources/classroom_front_python.png"))
	{
		fprintf(gpFile, "texture for python classroom failed to load\n");
		return FALSE;
	}
	if (!loadGLPngTexture(&texture_head_cabin, "resources/headmaster_cabin.png"))
	{
		fprintf(gpFile, "texture for headmaster cabin failed to load\n");
		return FALSE;
	}
	if (!loadGLPngTexture(&texture_lsp, "resources/lsp.png"))
	{
		fprintf(gpFile, "texture for lsp class failed to load\n");
		return FALSE;
	}
	if (!loadGLPngTexture(&texture_logo, "resources/logo.png"))
	{
		fprintf(gpFile, "logo texture failed to load\n");
		return FALSE;
	}
	if (!loadGLPngTexture(&texture_headmaster_front_wall, "resources/headmaster_front_wall.png"))
	{
		fprintf(gpFile, "headmaster_front_wall texture failed to load\n");
		return FALSE;
	}
	if (!loadGLPngTexture(&texture_headmaster_side_wall, "resources/headmaster_side_wall.png"))
	{
		fprintf(gpFile, "headmaster_side_wall texture failed to load\n");
		return FALSE;
	}

	// cubemapTexture = loadCubemap(faces);

	return (TRUE);
}

void displayScene2()
{
	// variable declarations 
	static BOOL isThisFirstCall = TRUE; 
	
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
	
	// array of cubes for drawing school 
	struct Cube CubesInSchool[] = {
		{0.00, -0.30, -3.20, 5.10, 0.10, 0.60, 1.0f, 1.0f, 1.0f, FACE_ALL, {texture_school_floor, texture_school_floor, texture_school_floor, texture_school_floor, texture_school_floor, 0}}, 	// bigger floor 
		{5.40, -0.30, -2.00, 1.00, 0.10, 1.80, 1.0f, 1.0f, 1.0f, FACE_ALL, {texture_school_floor, texture_school_floor, texture_school_floor, texture_school_floor, texture_school_floor, 0}}, 	// floor below lsp class 
		{0.20, 0.90, -3.40, 4.60, 0.10, 0.80, 1.0f, 1.0f, 1.0f, FACE_ALL, {texture_school_floor, texture_school_floor, texture_school_floor, texture_school_floor, texture_school_floor, texture_school_floor}}, 	// building top 
		{-3.35, 0.30, -3.70, 0.849, 0.50, 0.70, 1.0f, 1.0f, 1.0f, FACE_FRONT, {texture_class_front_mstc, 0, 0, 0, 0, 0}}, // classroom 1 
		{-1.65, 0.30, -3.70, 0.849, 0.50, 0.70, 1.0f, 1.0f, 1.0f, FACE_FRONT, texture_class_front_dsa, 0, 0, 0, 0, 0}, // classroom 2 
		{0.05, 0.30, -3.70, 0.849, 0.50, 0.70, 1.0f, 1.0f, 1.0f, FACE_ALL, texture_head_cabin, texture_headmaster_side_wall, texture_headmaster_front_wall, texture_headmaster_side_wall, texture_school_floor, texture_school_floor}, 	// headmaster cabin  
		{1.75, 0.30, -3.70, 0.849, 0.50, 0.70, 1.0f, 1.0f, 1.0f, FACE_FRONT, texture_class_front_cpp, 0, 0, 0, 0, 0}, 	// classroom 3 
		{3.45, 0.30, -3.70, 0.849, 0.50, 0.70, 1.0f, 1.0f, 1.0f, FACE_FRONT, texture_class_front_python, 0, 0, 0, 0, 0}, 	// classroom 4 
		{5.10, 0.20, -1.50, 0.40, 0.40, 1.20, 1.0f, 1.0f, 1.0f, FACE_FRONT | FACE_RIGHT | FACE_LEFT, texture_lsp, texture_lsp, 0, texture_lsp, 0, 0}  // classroom 5 - lsp 
	}; 
	
	// code 
	if(isThisFirstCall == TRUE) 
	{
		cameraX = 0.20f; 
		cameraY = 0.20f;
		cameraZ = -4.20f; 

		cameraEyeX = 0.20f; 
		cameraEyeY = 3.30f; 
		cameraEyeZ = -26.40f; 

		isThisFirstCall = FALSE; 
	}

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

	// road upto class  
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

	//-------

	// school 
	for(int i = 0; i < sizeof(CubesInSchool)/sizeof(CubesInSchool[0]); ++i) 
	{
		drawTexturedCube(
				CubesInSchool[i].tx, CubesInSchool[i].ty, CubesInSchool[i].tz, 
				CubesInSchool[i].sx, CubesInSchool[i].sy, CubesInSchool[i].sz, 
				CubesInSchool[i].r, CubesInSchool[i].g, CubesInSchool[i].b, 
				CubesInSchool[i].faces_to_be_textured, 
				CubesInSchool[i].textures[0], 
				CubesInSchool[i].textures[1], 
				CubesInSchool[i].textures[2], 
				CubesInSchool[i].textures[3], 
				CubesInSchool[i].textures[4], 
				CubesInSchool[i].textures[5]  
		);
	}

	// logo at scool top 
	glBindTexture(GL_TEXTURE_2D, texture_school_floor);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); 
	glPushMatrix(); 
	{
		glTranslatef(0.0, 1.0, -2.60);  
		gluCylinder(quadric, 0.20, 0.20, 0.10, 24, 24); 
	}
	glPopMatrix(); 
	glBindTexture(GL_TEXTURE_2D, 0);

	glPushMatrix(); 
    {
        glTranslatef(0.00f, 1.00f, -3.50f); 
        glScalef(0.20f, 0.20f, 1.0f);
        
        glBindTexture(GL_TEXTURE_2D, texture_logo); 
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

	// trees 
	for(int i = 0; i < sizeof(trees)/sizeof(trees[0]); ++i) 
	{
		billboard(
			trees[i].tx, trees[i].ty, trees[i].tz,
			trees[i].width, trees[i].height, 
			trees[i].texture 
		);
	}  
} 

/*
	Initial 
		0.20  0.20 -4.24
		0.20 3.30 -26.40
	Position 1 
		-0.10  0.10 -3.00
		0.00 2.00 -20.00

	Position 3 
		-0.06  0.11 -1.99
		0.03 2.19 -20.96

	Position4
		-4.15  -0.09 -1.79
		3.43 5.89 -20.96
	Position5 
		3.15  0.01 -1.59
		16.43 1.79 -6.36

	Position 6 
		0.20  0.20 4.50
		0.20 3.30 -26.40
	final
		-0.06  0.91 -1.89
		1.43 3.49 -20.96
*/

static void loadCameraPosition4(void) 
{
	// code 
	cameraX = -4.15;
	cameraY = -0.09;
	cameraZ = -1.79;

	cameraEyeX = 3.43;
	cameraEyeY = 5.89;
	cameraEyeZ = -20.96;
} 

void updateScene2(void) 
{
	// variable declarations 
	static BOOL isUpdate1 = TRUE; 
	static BOOL isUpdate2 = FALSE; 
	static BOOL isUpdate3 = FALSE; 
	static BOOL isUpdate4 = FALSE; 
	static BOOL isUpdate5 = FALSE; 
	static BOOL isUpdate6 = FALSE; 

	static float inverse_constant_for_camera_speed1 = 100; 
	static float inverse_constant_for_camera_speed2 = 100; 
	static float inverse_constant_for_camera_speed3 = 100; 
	static float inverse_constant_for_camera_speed4 = 100; 
	static float inverse_constant_for_camera_speed5 = 100; 
	static float inverse_constant_for_camera_speed6 = 100; 

	static BOOL isCameraPosition4Loaded = FALSE; 

	// code 
	if(isUpdate1 == TRUE) 
	{
		cameraX = cameraX - 0.30/inverse_constant_for_camera_speed1; 
		cameraY = cameraY - 0.10/inverse_constant_for_camera_speed1; 
		cameraZ = cameraZ + 1.42/inverse_constant_for_camera_speed1; 

		cameraEyeX = cameraEyeX - 0.20/inverse_constant_for_camera_speed1; 
		cameraEyeY = cameraEyeY - 1.30/inverse_constant_for_camera_speed1; 
		cameraEyeZ = cameraEyeZ + 6.40/inverse_constant_for_camera_speed1; 

		if(cameraZ >= -3.0f) 
		{
			isUpdate1 = FALSE; 
			isUpdate2 = TRUE; 
		} 
	} 
	if(isUpdate2 == TRUE) 
	{
		cameraX = cameraX + 0.04/inverse_constant_for_camera_speed2; 
		cameraY = cameraY + 0.01/inverse_constant_for_camera_speed2; 
		cameraZ = cameraZ + 0.1/inverse_constant_for_camera_speed2; 

		cameraEyeX = cameraEyeX + 0.03/inverse_constant_for_camera_speed1; 
		cameraEyeY = cameraEyeY + 0.19/inverse_constant_for_camera_speed1; 
		cameraEyeZ = cameraEyeZ - 0.96/inverse_constant_for_camera_speed1; 

		if(cameraZ >= -2.0f) 
		{
			isUpdate2 = FALSE; 
			isUpdate3 = TRUE; 
		} 
	} 
	// if(isUpdate3 == TRUE) 
	// {
	// 	cameraX = cameraX + 0.04/inverse_constant_for_camera_speed2; 
	// 	cameraY = cameraY + 0.01/inverse_constant_for_camera_speed2; 
	// 	cameraZ = cameraZ + 0.2/inverse_constant_for_camera_speed2; 

	// 	cameraEyeX = cameraEyeX + 13.0/inverse_constant_for_camera_speed2; 
	// 	cameraEyeY = cameraEyeY - 4.10/inverse_constant_for_camera_speed2; 
	// 	cameraEyeZ = cameraEyeZ - 14.60/inverse_constant_for_camera_speed2; 

	// 	if(cameraZ <= -20.96f) 
	// 	{
	// 		isUpdate3 = FALSE; 
	// 		isUpdate4 = TRUE; 
	// 	} 
	// }
	if(isUpdate3 == TRUE) 
	{
		if(isCameraPosition4Loaded == FALSE) 
		{
			loadCameraPosition4(); 
			isCameraPosition4Loaded = TRUE; 
		} 

		cameraX = cameraX + 7.0/inverse_constant_for_camera_speed2; 
		cameraY = cameraY + 1.0/inverse_constant_for_camera_speed2; 
		cameraZ = cameraZ + 0.20/inverse_constant_for_camera_speed2; 

		cameraEyeX = cameraEyeX + 13.0/inverse_constant_for_camera_speed2; 
		cameraEyeY = cameraEyeY - 4.10/inverse_constant_for_camera_speed2; 
		cameraEyeZ = cameraEyeZ - 14.60/inverse_constant_for_camera_speed2;  

		if(cameraEyeZ >= -6.96f) 
		{
			isUpdate3 = FALSE; 
			isUpdate4 = TRUE; 
		} 
	}
}

void uninitializeScene2(void) 
{
	// code 
	if(texture_headmaster_side_wall)
	{
		glDeleteTextures(1, &texture_headmaster_side_wall); 
		texture_headmaster_side_wall = 0; 
	}
	if(texture_headmaster_front_wall)
	{
		glDeleteTextures(1, &texture_headmaster_front_wall); 
		texture_headmaster_front_wall = 0; 
	}
	if(texture_class_front_mstc)
	{
		glDeleteTextures(1, &texture_class_front_mstc); 
		texture_class_front_mstc = 0; 
	}
	if(texture_class_front_dsa)
	{
		glDeleteTextures(1, &texture_class_front_dsa); 
		texture_class_front_dsa = 0; 
	}
	if(texture_class_front_cpp)
	{
		glDeleteTextures(1, &texture_class_front_cpp); 
		texture_class_front_cpp = 0; 
	}
	if(texture_class_front_python)
	{
		glDeleteTextures(1, &texture_class_front_python); 
		texture_class_front_python = 0; 
	}
	if(texture_head_cabin)
	{
		glDeleteTextures(1, &texture_head_cabin); 
		texture_head_cabin = 0; 
	}
	if(texture_logo)
	{
		glDeleteTextures(1, &texture_logo); 
		texture_logo = 0; 
	}
	if(texture_lsp)
	{
		glDeleteTextures(1, &texture_lsp); 
		texture_lsp = 0; 
	}
	if(texture_school_floor)
	{
		glDeleteTextures(1, &texture_school_floor); 
		texture_school_floor = 0; 
	}
}

