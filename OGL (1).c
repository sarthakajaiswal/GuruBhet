// windows header files common header
#include<windows.h>    // win32 api
#include<stdio.h>       // file io             
#include<stdlib.h>       // for exit
#include "OGL.h"

// OpenGL header files
#include<gl/GL.h>   
#include<gl/glu.h>  

// macros
#define WIN_WIDTH 800
#define WIN_HEIGHT 600

// link with opengl library
#pragma comment(lib,"OpenGL32.lib")
#pragma comment(lib,"glu32.lib")


// global function declarations
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//global variable declarations

FILE* gpFILE = NULL;

HWND  ghwnd = NULL;
BOOL gbActive = FALSE;
DWORD dwStyle = 0;
WINDOWPLACEMENT wpPrev = { sizeof(WINDOWPLACEMENT) };
BOOL gbFullscreen = FALSE;

// OpenGL related global variables
HDC ghdc = NULL;
HGLRC ghrc = NULL;

// light variables
BOOL bLight = FALSE;
BOOL bSpotlight = TRUE;

GLfloat lightAmbiant[] = { 0.1,0.1,0.1,1.0f }; // grey light source disnt nahi 
GLfloat lightDiffuse[] = { 1.0,1.0,1.0,1.0f }; // white most imp  it is defination of light source dist ahe , color intensity is decided by gl_diffused
GLfloat lightSpecular[] = { 1.0,1.0,1.0,1.0}; // white 
GLfloat lightPosition[]= { 100.0,100.0,100.0,1.0f }; // baherun stage vr baght ahot w is imp becoz in light w is imp
GLfloat spotDirection[]={0.0,-1.0,0.0};
GLfloat materialAmbiant[] = {0.0,0.0,0.0,1.0}; //black
GLfloat materialDiffuse[] = {0.5,0.2,0.7,1.0}; 
GLfloat materialSpecualr[] = {0.7,0.7,0.7,1.0};
GLfloat materialShinyness[] = {128.0f}; // becoz why to use single member array

GLfloat spotLight=10.0f;
GLfloat posX=0.0;
GLfloat posY=5.0;
GLfloat posZ=0.0;

GLfloat spotExponent = 1.0f;


GLUquadric* quadric = NULL;


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	// function declaration
	int initialize(void);
	void uninitialize(void);
	void display(void);
	void update(void);

	// local variable declarations
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("TSAWindow");
	int screenWidth, screenHeight, windowWidth, windowHeight;
	float initialPositionOfY, initialPositionOfX;
	int iResult = 0;
	BOOL bDone = FALSE;


	gpFILE = fopen("log.txt", "w");
	if (gpFILE == NULL)
	{
		MessageBox(NULL, TEXT("log file can not be opened.."), TEXT("Error"), MB_OK | MB_ICONERROR);
		exit(0);
	}
	fprintf(gpFILE, "Program started successfuly\n");

	// code
	// WNDCLASSEX initialization
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpfnWndProc = WndProc;


	wndclass.hInstance = hInstance;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));

	// register WNDCLASSEX
	RegisterClassEx(&wndclass);

	// declaring window size
	windowWidth = 800;
	windowHeight = 600;

	// getting value of screen height and width
	screenWidth = GetSystemMetrics(SM_CXSCREEN);
	screenHeight = GetSystemMetrics(SM_CYSCREEN);

	// calculations for fetching x , y value for CreateWindow()
	initialPositionOfX = (screenWidth / 2) - (windowWidth / 2);
	initialPositionOfY = (screenHeight / 2) - (windowHeight / 2);

	//create window 
	hwnd = CreateWindowEx(WS_EX_APPWINDOW,
		szAppName,
		TEXT("Tejank_Sanjay_Ambrale"),
		WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE,
		initialPositionOfX,
		initialPositionOfY,
		WIN_WIDTH,
		WIN_HEIGHT,
		NULL,
		NULL,
		hInstance,
		NULL);

	ghwnd = hwnd;

	// initalization
	iResult = initialize();
	if (iResult != 0)
	{
		MessageBox(hwnd, TEXT("Initalized function failed.."), TEXT("Error"), MB_OK | MB_ICONERROR);
		DestroyWindow(hwnd);
	}

	// show the window
	ShowWindow(hwnd, iCmdShow);
	SetForegroundWindow(hwnd);
	SetFocus(hwnd);


	// game loop
	while (bDone == FALSE)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				bDone = TRUE;
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			if (gbActive == TRUE)
			{
				// render
				display();

				// update
				update();
			}
		}
	}

	// uninitalization
	uninitialize();

	return ((int)msg.wParam);
}

// callback function 
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	// local function declaration
	void ToggleFullscreen(void);
	void resize(int, int);

	// code
	switch (iMsg)
	{
	case WM_SETFOCUS:
		gbActive = TRUE;
		break;
	case WM_KILLFOCUS:
		gbActive = FALSE;
		break;
	case WM_SIZE:
		resize(LOWORD(lParam), HIWORD(lParam));
		break;
	case WM_ERASEBKGND:
		return(0);
	case WM_KEYDOWN:
		switch (LOWORD(wParam))
		{
		case VK_ESCAPE:
			DestroyWindow(hwnd);
			break;
		}
		break;
	case WM_CHAR:
		switch (LOWORD(wParam))
		{
		case 'f':
		case 'F':
			if (gbFullscreen == FALSE)
			{
				ToggleFullscreen();
				gbFullscreen = TRUE;
			}
			else {
				ToggleFullscreen();
				gbFullscreen = FALSE;
			}
			break;
		case 'L':
		case 'l':
			if (bLight==FALSE)
			{
				glEnable(GL_LIGHTING);
				bLight = TRUE;
			}
			else
			{
				glDisable(GL_LIGHTING);
				bLight = FALSE;
			}
			break;
        case 'W':
        case 'w':
            posZ-=0.1f;
            break;
        case 'S':
        case 's':
            posZ +=0.1f;
            break;
        case 'A':
        case 'a':
            posX-=0.1f;
            break;
        case 'D':
        case 'd':
            posX+=0.1f;
            break;
        case 'Q':
        case 'q':
            spotLight+=0.1f;
            break;
        case 'E':
        case 'e':
            spotLight-=0.1f;
            break;
        case 'Z':
        case 'z':
            spotExponent+=1.0f;
            if(spotExponent > 128.0f)
                spotExponent = 128.0f;
            break;
        case 'X':
        case 'x':
            spotExponent-=1.0f;
            if(spotExponent < 0.0f)
                spotExponent = 0.0f;
            break;
        // Toggle spotlight 
        case 'T':
        case 't':
            bSpotlight = !bSpotlight;
            break;
        //  spotlight Y position
        case 'Y':
        case 'y':
            posY += 0.1f;
            break;
        case 'H':
        case 'h':
            posY -= 0.1f;
            break;
		}
		break;
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		break;
	}
	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}

void ToggleFullscreen(void)
{
	// local variable declarations
	MONITORINFO mi = { sizeof(MONITORINFO) };

	// code
	if (gbFullscreen == FALSE)
	{
		dwStyle = GetWindowLong(ghwnd, GWL_STYLE);
		if (dwStyle & WS_OVERLAPPEDWINDOW)
		{
			if (GetWindowPlacement(ghwnd, &wpPrev) && GetMonitorInfo(MonitorFromWindow(ghwnd, MONITORINFOF_PRIMARY), &mi))
			{
				SetWindowLong(ghwnd, GWL_STYLE, dwStyle & ~WS_OVERLAPPEDWINDOW);
				SetWindowPos(ghwnd, HWND_TOP, mi.rcMonitor.left, mi.rcMonitor.top, mi.rcMonitor.right - mi.rcMonitor.left, mi.rcMonitor.bottom - mi.rcMonitor.top, SWP_NOZORDER | SWP_FRAMECHANGED);
			}
		}
		ShowCursor(FALSE);
	}
	else
	{
		SetWindowPlacement(ghwnd, &wpPrev);
		SetWindowLong(ghwnd, GWL_STYLE, dwStyle | WS_OVERLAPPEDWINDOW);
		SetWindowPos(ghwnd, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOZORDER | SWP_FRAMECHANGED);
		ShowCursor(TRUE);
	}
}

int initialize(void)
{
	void resize(int, int);
	// function declarations
	PIXELFORMATDESCRIPTOR pfd;
	int iPixelFormatIndex = 0;
	ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));

	// initalization of pixelformatdeciptor
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER; //imp
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;
	pfd.cRedBits = 8;
	pfd.cGreenBits = 8;
	pfd.cBlueBits = 8;
	pfd.cAlphaBits = 8;
	pfd.cDepthBits = 32; // Addition

	// inniatlize pixelfprmatdescriptor

	// get the dc
	ghdc = GetDC(ghwnd);

	if (ghdc == NULL)
	{
		fprintf(gpFILE, "GetDC() failed \n");
		return(-1);
	}


	iPixelFormatIndex = ChoosePixelFormat(ghdc, &pfd);
	if (iPixelFormatIndex == 0)
	{
		fprintf(gpFILE, "ChoosePixelFormat() failed \n");
		return(-2);
	}

	// iPixelFormatIndex milala mg to set kraycha , me os la dila demand la javal janal pixel format mg to set kraych
	// set obtain pixel format
	if (SetPixelFormat(ghdc, iPixelFormatIndex, &pfd) == FALSE)  // 1st kunal mde set kraych ahe , 2nd kontya index ch set kraych ahe , 3rd 
	{
		fprintf(gpFILE, "SetPixelFormat() failed \n");
		return(-3);
	}

	// lai bhari step 
	// indows graphics library = wgl
	// tell windows graphics wgl to give me opengl compatible dc by using ghdc and create dc like that avastanch structre
	// create opengl context from device context
	ghrc = wglCreateContext(ghdc);
	if (ghrc == NULL)
	{
		fprintf(gpFILE, "wglCreateContext() failed \n");
		return(-4);
	}

	// make rendering context current
	if (wglMakeCurrent(ghdc, ghrc) == FALSE) // 1st aata kon ahe , kunala current kraych ahe,
	{
		fprintf(gpFILE, "wglMakeCurrent() failed \n");
		return(-5);
	}

	// 3 c 2 o
	// enabling depth
	glShadeModel(GL_SMOOTH); // beatufication optional -> ajun tr lighing kela nhi but when we do that then do shading smooth

	glClearDepth(1.0); // compulsory -> framebuffer - color buffer - color clear krto , ts depth buffer chya sglya bits la 1 kr
	glEnable(GL_DEPTH_TEST); // compulsory ->
	glDepthFunc(GL_LEQUAL);  // compulsory -> depth sadhi kont func use kru , test enable jali but kunashi test kru compare kunashi kru >=
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // optional -> depth enable kelya vr corner circle astil tr tya ellipsi distat this is bad therefore when this happen depth and perpestive mule asa hoil tevha te nicest kr

	// set the clear color of window to blue
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // light related inialization
	glLightfv(GL_LIGHT0,GL_AMBIENT,lightAmbiant); // light la property denar he function , enabling first light, tyla ambiant property de , tyla array value de
	glLightfv(GL_LIGHT0,GL_DIFFUSE,lightDiffuse);
	glLightfv(GL_LIGHT0,GL_SPECULAR,lightSpecular);
	//glLightfv(GL_LIGHT0,GL_POSITION,lightPosition);
	glEnable(GL_LIGHT0);


	// material properties
	glMaterialfv(GL_FRONT,GL_AMBIENT,materialAmbiant);
	glMaterialfv(GL_FRONT,GL_DIFFUSE,materialDiffuse);
	glMaterialfv(GL_FRONT,GL_SPECULAR,materialSpecualr);
	glMaterialfv(GL_FRONT,GL_SHININESS,materialShinyness);


	// initalize quadric
	quadric = gluNewQuadric();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// code
	resize(WIN_WIDTH, WIN_HEIGHT);

	return(0);
}

void resize(int width, int height)
{
	// code
	if (height <= 0)
		height = 1;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// int x ,int y ,glsizei mde typecast kela 
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);  // viewprot -> hillstation la ahot ani boll to toger ahe tyachya vrti mandir bagh mg scope ne tech baghto zoom ne, aata maja focus hole indo vr ahe


	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);
}
void drawSphere()
{
    int i=0,j=0;

    glPushMatrix();
    {
        for(j=1;j<10;j++)
        {
            for(i=1;i<=10;i++)
            {
                glPushMatrix();
                {
                    glTranslatef(-2.35+(i*0.45),-1.45,0.0-(-0.65+j));
					glColor3f(1.0f, 0.0f, 0.0f); 
                    gluSphere(quadric, 0.2f, 50, 50);
                }
                glPopMatrix();
            }
        }
    }
    glPopMatrix();
}

void display(void)
{
    // Update light properties with the current values
    GLfloat lightPosition[]={posX, posY, posZ, 1.0};

    
    // code
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // glTranslatef(0.0f, 0.0f, -5.0f);

    // Update light properties
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    
    
    if (bSpotlight) {
        glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, spotLight);
        glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spotDirection);
        glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, spotExponent);
    } else {
        // Disable spotlight effect by setting cutoff to 180 degrees
        glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 180.0f);
    }

    drawSphere();

    SwapBuffers(ghdc);
}

void update(void)
{
    // code
}

void uninitialize(void)
{
    // function declarations 
    void ToggleFullscreen(void);

    // code 
    // if application is exiting in fullscreen
    if (gbFullscreen == TRUE)
    {
        ToggleFullscreen();
        gbFullscreen = FALSE;
    }

    // make the hdc as current dc
    if (wglGetCurrentContext() == ghrc)
    {
        wglMakeCurrent(NULL, NULL);
    }

    // destroy rendering context
    if (ghrc)
    {
        wglDeleteContext(ghrc);
        ghrc = NULL;
    }

    // release the hdc
    if (ghdc)
    {
        ReleaseDC(ghwnd, ghdc);
        ghdc = NULL;
    }

    // destroy window
    if (ghwnd)
    {
        DestroyWindow(ghwnd);
        ghwnd = NULL;
    }

    if (quadric)
    {
        gluDeleteQuadric(quadric);
        quadric = NULL;
    }

    // close the log file
    if (gpFILE)
    {
        fprintf(gpFILE, "program ended successfully\n");
        fclose(gpFILE);
        gpFILE = NULL;
    }
}