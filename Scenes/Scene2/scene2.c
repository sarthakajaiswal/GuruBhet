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

GLUquadric* quadric = NULL; 

// placeholder structure for calling cubemap() for getting trees 
struct tree 
{
	float tx, ty, tz; 
	float height, width; 
	GLuint texture; 
}; 

// structure storing texture_id, corrosponding texture image and texture info string 
struct ImageTexture 
{
	GLuint texture; 
	const char* file_path; 
	const char* info_string;  
};  

// structure to draw classroom cube | to call drawTexturedCube() 
struct Cube 
{
	float tx, ty, tz; 
	float sx, sy, sz;  
	float r, g, b; 
	FaceType faces_to_be_textured;
	GLuint textures[6];  
};  

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
	// if (!loadGLPngTexture(&texture_leaf, "resources/ganpati.png"))
	// {
	// 	fprintf(gpFile, "title.png Texture failed \n");
	// 	return FALSE;
	// }
	// if (!loadGLPngTexture(&texture_tree, "resources/title.png"))
	// {
	// 	fprintf(gpFile, "title.png Texture failed \n");
	// 	return FALSE;
	// }
	// if (!loadGLPngTexture(&texture_temple_front_wall, "resources/temple_front_wall.png")) 
	// {
	// 	fprintf(gpFile, "temple_front_wall.png Texture failed \n");
	// 	return FALSE;
	// }
	// if (!loadGLPngTexture(&texture_temple_side_and_back_walls, "resources/temple_back_and_side_walls.png")) 
	// {
	// 	fprintf(gpFile, "temple_side_and_back_wall.png Texture failed \n");
	// 	return FALSE;
	// }
	// if (!loadGLPngTexture(&texture_temple_top, "resources/temple_top.png")) 
	// {
	// 	fprintf(gpFile, "temple_top.png Texture failed \n");
	// 	return FALSE;
	// }
	// if (!loadGLPngTexture(&texture_ground, "resources/ground.png"))
	// {
	// 	fprintf(gpFile, "ground.png Texture failed \n");
	// 	return FALSE;
	// }
	// if (!loadGLPngTexture(&texture_road, "resources/road.png"))
	// {
	// 	fprintf(gpFile, "road.png Texture failed \n");
	// 	return FALSE;
	// }
	// if (!loadGLPngTexture(&texture_tree1, "resources/tree1.png"))
	// {
	// 	fprintf(gpFile, "tree1.png Texture failed \n");
	// 	return FALSE;
	// }
	// if (!loadGLPngTexture(&texture_tree2, "resources/tree2.png"))
	// {
	// 	fprintf(gpFile, "tree2.png Texture failed \n");
	// 	return FALSE;
	// }
	// if (!loadGLPngTexture(&texture_tree3, "resources/tree3.png"))
	// {
	// 	fprintf(gpFile, "tree3.png Texture failed \n");
	// 	return FALSE;
	// }
	// if (!loadGLPngTexture(&texture_tree4, "resources/tree4.png"))
	// {
	// 	fprintf(gpFile, "tree4.png Texture failed \n");
	// 	return FALSE;
	// }
	// if (!loadGLPngTexture(&texture_god_image, "resources/vitthal.png"))
	// {
	// 	fprintf(gpFile, "vitthal.png Texture failed \n");
	// 	return FALSE;
	// }
	// if (!loadGLPngTexture(&texture_temple_floor, "resources/temple_floor.png"))
	// {
	// 	fprintf(gpFile, "vitthal.png Texture failed \n");
	// 	return FALSE;
	// }
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

	// cubemapTexture = loadCubemap(faces);

	return (TRUE);
}

void displayScene2()
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
		{tx, ty, tz, sx, sy, texture_tree4}  
	}; 
	
	// array of cubes for drawing school 
	struct Cube CubesInSchool[] = {
		{0.00, -0.30, -3.20, 5.10, 0.10, 0.60, 1.0f, 1.0f, 1.0f, FACE_ALL, {texture_school_floor, texture_school_floor, texture_school_floor, texture_school_floor, texture_school_floor, 0}}, 	// bigger floor 
		{5.40, -0.30, -2.00, 1.00, 0.10, 1.80, 1.0f, 1.0f, 1.0f, FACE_ALL, {texture_school_floor, texture_school_floor, texture_school_floor, texture_school_floor, texture_school_floor, 0}}, 	// floor below lsp class 
		{0.20, 0.90, -3.40, 4.60, 0.10, 0.80, 1.0f, 1.0f, 1.0f, FACE_ALL, {texture_school_floor, texture_school_floor, texture_school_floor, texture_school_floor, texture_school_floor, texture_school_floor}}, 	// building top 
		{-3.35, 0.30, -3.70, 0.849, 0.50, 0.70, 1.0f, 1.0f, 1.0f, FACE_FRONT, {texture_class_front_mstc, 0, 0, 0, 0, 0}}, // classroom 1 
		{-1.65, 0.30, -3.70, 0.849, 0.50, 0.70, 1.0f, 1.0f, 1.0f, FACE_FRONT, texture_class_front_dsa, 0, 0, 0, 0, 0}, // classroom 2 
		{0.05, 0.30, -3.70, 0.849, 0.50, 0.70, 1.0f, 1.0f, 1.0f, FACE_FRONT, texture_head_cabin, 0, 0, 0, 0, 0}, 	// headmaster cabin  
		{1.75, 0.30, -3.70, 0.849, 0.50, 0.70, 1.0f, 1.0f, 1.0f, FACE_FRONT, texture_class_front_cpp, 0, 0, 0, 0, 0}, 	// classroom 3 
		{3.45, 0.30, -3.70, 0.849, 0.50, 0.70, 1.0f, 1.0f, 1.0f, FACE_FRONT, texture_class_front_python, 0, 0, 0, 0, 0}, 	// classroom 4 
		{5.10, 0.20, -1.50, 0.40, 0.40, 1.20, 1.0f, 1.0f, 1.0f, FACE_FRONT | FACE_RIGHT | FACE_LEFT, texture_lsp, texture_lsp, 0, texture_lsp, 0, 0}  // classroom 5 - lsp 
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
# l i n e   1   " D : \ \ D e m o F o r S i r \ \ C o d e \ \ R C a 0 3 4 7 2 "  
 # l i n e   1   " O G L . r c "  
 # l i n e   1   " O G L . r c "  
  
 # l i n e   1   " C : \ \ P r o g r a m   F i l e s   ( x 8 6 ) \ \ W i n d o w s   K i t s \ \ 1 0 \ \ \ \ i n c l u d e \ \ 1 0 . 0 . 2 2 6 2 1 . 0 \ \ \ \ u m \ \ W i n d o w s . h "  
 # l i n e   1   " C : \ \ P r o g r a m   F i l e s   ( x 8 6 ) \ \ W i n d o w s   K i t s \ \ 1 0 \ \ \ \ i n c l u d e \ \ 1 0 . 0 . 2 2 6 2 1 . 0 \ \ \ \ s h a r e d \ \ w i n a p i f a m i l y . h "  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
 # l i n e   2 5   " C : \ \ P r o g r a m   F i l e s   ( x 8 6 ) \ \ W i n d o w s   K i t s \ \ 1 0 \ \ \ \ i n c l u d e \ \ 1 0 . 0 . 2 2 6 2 1 . 0 \ \ \ \ s h a r e d \ \ w i n a p i f a m i l y . h "  
  
 # l i n e   1   " C : \ \ P r o g r a m   F i l e s   ( x 8 6 ) \ \ W i n d o w s   K i t s \ \ 1 0 \ \ \ \ i n c l u d e \ \ 1 0 . 0 . 2 2 6 2 1 . 0 \ \ \ \ s h a r e d \ \ w i n p a c k a g e f a m i l y . h "  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
 # l i n e   2 5   " C : \ \ P r o g r a m   F i l e s   ( x 8 6 ) \ \ W i n d o w s   K i t s \ \ 1 0 \ \ \ \ i n c l u d e \ \ 1 0 . 0 . 2 2 6 2 1 . 0 \ \ \ \ s h a r e d \ \ w i n p a c k a g e f a m i l y . h "  
  
  
  
 # l i n e   2 9   " C : \ \ P r o g r a m   F i l e s   ( x 8 6 ) \ \ W i n d o w s   K i t s \ \ 1 0 \ \ \ \ i n c l u d e \ \ 1 0 . 0 . 2 2 6 2 1 . 0 \ \ \ \ s h a r e d \ \ w i n p a c k a g e f a m i l y . h "  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
 # l i n e   9 0   " C : \ \ P r o g r a m   F i l e s   ( x 8 6 ) \ \ W i n d o w s   K i t s \ \ 1 0 \ \ \ \ i n c l u d e \ \ 1 0 . 0 . 2 2 6 2 1 . 0 \ \ \ \ s h a r e d \ \ w i n p a c k a g e f a m i l y . h "  
  
 # l i n e   9 2   " C : \ \ P r o g r a m   F i l e s   ( x 8 6 ) \ \ W i n d o w s   K i t s \ \ 1 0 \ \ \ \ i n c l u d e \ \ 1 0 . 0 . 2 2 6 2 1 . 0 \ \ \ \ s h a r e d \ \ w i n p a c k a g e f a m i l y . h "  
  
 # l i n e   2 7   " C : \ \ P r o g r a m   F i l e s   ( x 8 6 ) \ \ W i n d o w s   K i t s \ \ 1 0 \ \ \ \ i n c l u d e \ \ 1 0 . 0 . 2 2 6 2 1 . 0 \ \ \ \ s h a r e d \ \ w i n a p i f a m i l y . h "  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
 # l i n e   9 1   " C : \ \ P r o g r a m   F i l e s   ( x 8 6 ) \ \ W i n d o w s   K i t s \ \ 1 0 \ \ \ \ i n c l u d e \ \ 1 0 . 0 . 2 2 6 2 1 . 0 \ \ \ \ s h a r e d \ \ w i n a p i f a m i l y . h "  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
 # l i n e   1 4 8   " C : \ \ P r o g r a m   F i l e s   ( x 8 6 ) \ \ W i n d o w s   K i