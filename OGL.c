#include "OGL.h" 

enum SceneNumber
{
    SLIDE1, SLIDE2, SCENE_ZERO, SCENE_ONE, SCENE_TWO, SCENE_THREE, SCENE_FOUR
}; 

enum SceneNumber currentSceneNumber = SCENE_THREE; 

// global variable declarations 
// variables related with full-screen  
BOOL gbFullScreen = FALSE; 
HWND ghWnd = NULL; 
DWORD dwStyle; 
WINDOWPLACEMENT wpPrev; 
GLUquadric* quadric; 

// variables related with file I/O 
char gszLogFileName[] = "Log.txt"; 
FILE* gpFile = NULL; 

// active window related variable 
BOOL gbActiveWindow = FALSE; 

// exit key pressed related 
BOOL gbEscapeKeyIsPressed = FALSE; 

// openGL related global variables 
HDC ghdc = NULL; 
HGLRC ghrc = NULL; 

// global variables for FOG configuration 
GLfloat fogColor[4] = {0.8f, 0.8f, 0.8f, 1.0f}; 
GLfloat fogDensity = 0.07f; 
GLfloat fogMode = GL_EXP2; 
GLfloat fogStart = 0.0f; 
GLfloat fogEnd = 2000.0f; 
BOOL gbFogEnabled = FALSE; 

// fade related variables 
extern BOOL isFading; 

// camera variables 
float cameraX = 0.0f,       cameraY = 0.0f,     cameraZ = 5.0f; 
float cameraEyeX = 0.0f,    cameraEyeY = 0.0f,  cameraEyeZ = 0.0f; 
float cameraUpX = 0.0f,     cameraUpY = 1.0f,   cameraUpZ = 0.0f; 
float cameraAngle = 0.0f; 

BOOL toggleCamera = FALSE; 

// translation try-out variables 
float sx = 1.0f, sy = 1.0f, sz = 1.0f; 
float tx, ty, tz; 

// timer related variables 
FILETIME ft;  
SYSTEMTIME stCurrentTime;
SYSTEMTIME stStartTime;  
unsigned long long start_time_stamp_microsec; 
unsigned long long current_time_stamp_microsec; 
unsigned long long main_timer_microsec;      

// entry-point function 
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow) 
{
    // function declarations 
    int initialize(void); 
    void uninitialize(void); 
    void display(void); 
    void update(void); 

    // local variable declarations 
    WNDCLASSEX wndclass; 
    HWND hwnd; 
    MSG msg; 
    TCHAR szAppName[] = TEXT("GuruBhet"); 

    int screenWidth, screenHeight, windowWidth, windowHeight; 
    float initialPositionOfY, initialPositionOfX; 
    int iResult = 0; 
    BOOL bDone = FALSE; 

    gpFile = fopen("log.txt", "w"); 
    if(gpFile == NULL) 
    {
        MessageBox(NULL, TEXT("Log file cannot be opened.."), TEXT("Error"), MB_OK | MB_ICONERROR); 
        exit(0); 
    }
    fprintf(gpFile, "Program started successfully\n"); 

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
    wndclass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON)); 
    wndclass.lpfnWndProc = WndProc; 
    wndclass.lpszClassName = szAppName; 
    wndclass.lpszMenuName = NULL; 

    // register WNDCLASS 
    RegisterClassEx(&wndclass); 

    // declaring window size 
    windowWidth = 800; 
    windowHeight = 600; 

    // getting value of screen height and width 
    screenWidth = GetSystemMetrics(SM_CXSCREEN); 
    screenHeight = GetSystemMetrics(SM_CYSCREEN); 

    // calculations for fetching x, y value for createWindow() 
    initialPositionOfX = (screenWidth / 2) - (windowWidth / 2); 
    initialPositionOfY = (screenHeight / 2) - (windowHeight / 2); 

    // create window 
    hwnd = CreateWindowEx(
        WS_EX_APPWINDOW, 
        szAppName, 
        TEXT("GuruBhet"),  
        WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE, 
        initialPositionOfX, 
        initialPositionOfY, 
        WIN_WIDTH, 
        WIN_HEIGHT, 
        NULL, 
        NULL, 
        hInstance, 
        NULL 
    ); 

    ghWnd = hwnd; 

    // initialization 
    iResult = initialize(); 
    if(iResult != 0) 
    {
        MessageBox(hwnd, TEXT("initialize() failed.."), TEXT("Error"), MB_OK | MB_ICONERROR); 
        DestroyWindow(ghWnd); 
    }

    // show the window 
    ShowWindow(hwnd, iCmdShow); 
    SetForegroundWindow(hwnd); 
    SetFocus(hwnd); 

    // game loop 
    while(bDone == FALSE) 
    {
        if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) 
        {
            if(msg.message == WM_QUIT) 
                bDone = TRUE; 

            else 
            {
                TranslateMessage(&msg); 
                DispatchMessage(&msg); 
            }
        }
        else 
        {
            if(gbActiveWindow == TRUE) 
            {
                // render 
                display(); 

                // update 
                update(); 
            }
        }
    }

    // uninitialize 
    uninitialize(); 

    return ((int)msg.wParam); 
}

// callback function 
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) 
{
    // local function declarations 
    void toggleFullScreen(void); 
    void resize(int, int); 

    // code 
    switch(iMsg) 
    {
        case WM_SETFOCUS: 
            gbActiveWindow = TRUE; 
            break; 
        
        case WM_KILLFOCUS: 
            gbActiveWindow = FALSE; 
            break; 

        case WM_SIZE: 
            resize(LOWORD(lParam), HIWORD(lParam)); 
            break; 

        case WM_ERASEBKGND: 
            return (0); 

        case WM_KEYDOWN: 
            switch(LOWORD(wParam)) 
            {
                case VK_ESCAPE: 
                    DestroyWindow(ghWnd); 
                    break; 

                // camera movement with arrow keys 
                case VK_UP: 
                    cameraZ -= 1.0f; 
                    break; 

                case VK_DOWN: 
                    cameraZ += 1.0f; 
                    break; 

                case VK_LEFT: 
                    cameraAngle -= 1.0f; 
                    break; 

                case VK_RIGHT: 
                    cameraAngle += 1.0f; 
                    break; 

                default: 
                    break; 
            }
            break; 

        case WM_CHAR: 
            switch(LOWORD(wParam)) 
            {
                case 'f': 
                case 'F': 
                    if(gbFullScreen == FALSE) 
                    {
                        toggleFullScreen(); 
                        gbFullScreen = TRUE; 
                    }
                    else 
                    {
                        toggleFullScreen(); 
                        gbFullScreen = FALSE; 
                    }
                    break; 

                // camera position controls 
                case 'w': 
                case 'W': 
                    cameraY += 1.0f; 
                    break; 

                case 's': 
                case 'S': 
                    cameraY -= 0.5f; 
                    break; 

                case 'a': 
                case 'A': 
                    cameraX -= 0.5f; 
                    break; 

                case 'd': 
                case 'D': 
                    cameraX += 0.5f; 
                    break; 

                case '6': 
                    cameraEyeX += 0.5f; 
                    break; 

                case '4': 
                    cameraEyeX -= 0.5f; 
                    break; 

                case '8': 
                    cameraEyeY += 0.5f; 
                    break; 

                case '2': 
                    cameraEyeY -= 0.5f; 
                    break; 

                case '7': 
                    cameraEyeZ -= 0.5f; 
                    break; 

                case '9': 
                    cameraEyeZ += 0.5f; 
                    break;  

                // -------- size -------- 

                case 'z': 
                    sx += 0.04f; 
                    break; 

                case 'Z': 
                    sx -= 0.04f; 
                    break; 
                
                case 'x': 
                    sy += 0.04f; 
                    break; 

                case 'X': 
                    sy -= 0.04f; 
                    break; 

                case 'c': 
                    sz += 0.04f; 
                    break; 

                case 'C': 
                    sz -= 0.04f; 
                    break; 

                //----- translate ----- 
                case 'v': 
                    tx += 0.1f; 
                    break; 

                case 'V': 
                    tx -= 0.1f; 
                    break; 

                case 'b': 
                    ty += 0.1f; 
                    break; 

                case 'B': 
                    ty -= 0.1f; 
                    break; 

                case 'n': 
                    tz += 0.1f; 
                    break; 

                case 'N': 
                    tz -= 0.1f; 
                    break; 

                // // ------- Print the values ------ 
                case 'm': 
                    fprintf(gpFile, "\n\n%.2f, %.2f, %.2f, %.2f, %.2f, %.2f\n\n", tx, ty, tz, sx, sy, sz); 
                    fclose(gpFile); 
                    gpFile = fopen("log.txt", "a"); 
                    break; 

                case 'p': 
                case 'P': 
                    fprintf(gpFile, "\n\n%f  %f %f\n%f %f %f\n%f %f %f\n\n", 
                            cameraX, cameraY, cameraZ, 
                            cameraEyeX, cameraEyeY, cameraEyeZ, 
                            cameraUpX, cameraUpY, cameraUpZ 
                    ); 
                    fclose(gpFile); 
                    gpFile = fopen("log.txt", "a"); 
                    break; 

                case '1': 
                    toggleCamera = !toggleCamera; 
                    break; 

                default: 
                    break; 
            }
            break; 

        case WM_CLOSE: 
            DestroyWindow(ghWnd); 
            break; 

        case WM_DESTROY: 
            PostQuitMessage(0); 
            break; 
        
        default: 
            break; 
    }
    return (DefWindowProc(hwnd, iMsg, wParam, lParam)); 
}

void toggleFullScreen(void) 
{
    // variable declarations 
    MONITORINFO mi; 

    // code 
    if(gbFullScreen == FALSE) 
    {
        dwStyle = GetWindowLong(ghWnd, GWL_STYLE); 
        if(dwStyle & WS_OVERLAPPEDWINDOW) 
        {
            ZeroMemory((void*)&mi, sizeof(MONITORINFO)); 
            mi.cbSize = sizeof(MONITORINFO); 
            if (GetWindowPlacement(ghWnd, &wpPrev) && GetMonitorInfo(MonitorFromWindow(ghWnd, MONITORINFOF_PRIMARY), &mi)) 
            {
                SetWindowLong(ghWnd, GWL_STYLE, dwStyle & ~WS_OVERLAPPEDWINDOW); 
                SetWindowPos(ghWnd, HWND_TOP, 
                            mi.rcMonitor.left, 
                            mi.rcMonitor.top, 
                            mi.rcMonitor.right-mi.rcMonitor.left, 
                            mi.rcMonitor.bottom-mi.rcMonitor.top, 
                            SWP_NOZORDER | SWP_FRAMECHANGED
                        ); 
            }
        }
        ShowCursor(FALSE); 
    }
    else 
    {
        SetWindowPlacement(ghWnd, &wpPrev); 
        SetWindowLong(ghWnd, GWL_STYLE, dwStyle | WS_OVERLAPPEDWINDOW); 
        SetWindowPos(ghWnd, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOZORDER | SWP_FRAMECHANGED); 
        ShowCursor(TRUE); 
    }
}

int initialize(void) 
{
    // function declarations 
    void resize(int, int); 

    quadric = gluNewQuadric(); 
	if(quadric == NULL) 
		return (FALSE); 

    // variable declarations 
    PIXELFORMATDESCRIPTOR pfd; 
    int iPixelFormatIndex = 0; 

    // code 
    // pixel formal descriptor initialization 
    ZeroMemory((void*)&pfd, sizeof(PIXELFORMATDESCRIPTOR)); 
    
    pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR); 
    pfd.nVersion = 1; 
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER; 
    pfd.iPixelType = PFD_TYPE_RGBA; 
    pfd.cColorBits = 32; 
    pfd.cRedBits = 8; 
    pfd.cGreenBits = 8; 
    pfd.cBlueBits = 8; 
    pfd.cAlphaBits = 8; 
    pfd.cDepthBits = 32; 

    // get dc 
    ghdc = GetDC(ghWnd); 
    if(ghdc == NULL) 
    {
        fprintf(gpFile, "GetDC() failed.\n"); 
        return (-1); 
    }

    // get matching pixel format index using hdc and pfd 
    iPixelFormatIndex = ChoosePixelFormat(ghdc, &pfd); 
    if(iPixelFormatIndex == 0) 
    {
        fprintf(gpFile, "ChoosePixrlFormat() failed\n"); 
        return (-2); 
    }
    
    // selext the pixel format og gound index 
    if(SetPixelFormat(ghdc, iPixelFormatIndex, &pfd) == FALSE) 
    {
        fprintf(gpFile, "SetPixelFormat() failed\n"); 
        return (-3); 
    } 

    // create rendering context using hdc, pfd and chosen pixel format index 
    ghrc = wglCreateContext(ghdc); 
    if(ghrc == NULL) 
    {
        fprintf(gpFile, "wglCreateContext() failed\n"); 
        return (-4); 
    }
    
    // make this rendering context as current context 
    if(wglMakeCurrent(ghdc, ghrc) == FALSE) 
    {
        fprintf(gpFile, "wglMakeCurrent() failed\n"); 
        return (-5); 
    }

    // ***** FROM HERE ONWARDS OPENGL CODE STARTS ***** 
    // tell openGL to choose the color to clear the screen 
    glClearColor(0.0f, 0.0f, 0.0f, 1.0); 

    // enabling depth 
    glShadeModel(GL_SMOOTH); 
    glClearDepth(1.0f); 
    glEnable(GL_DEPTH_TEST); 
    glDepthFunc(GL_LEQUAL); 
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); 

    glEnable(GL_TEXTURE_2D); 

    // initFog(); 

    switch(currentSceneNumber) 
    {
        case SCENE_TWO: 
            if(!initScene2()) 
            {
                fprintf(gpFile, "initScene2() failed\n"); 
                return (FALSE); 
            }
        case SCENE_ONE: 
            if(!initScene1()) 
            {
                fprintf(gpFile, "initScene1() failed\n"); 
                return (FALSE); 
            }
            break; 
            
        case SCENE_THREE: 
            if(!initScene3()) 
            {
                fprintf(gpFile, "initScene3() failed\n"); 
                return (FALSE); 
            }
            break; 
        
        case SCENE_FOUR: 
            if(!initScene4()) 
            {
                fprintf(gpFile, "initScene4() failed\n"); 
                return (FALSE); 
            }
            break; 

        default: 
            break; 
    }
    initSlideScenes(); 

    // warmup resize 
    resize(WIN_WIDTH, WIN_HEIGHT); 

    GetSystemTimePreciseAsFileTime(&ft); 
    FileTimeToSystemTime(&ft, &stStartTime); 
    GetSystemTimePreciseAsFileTime(&ft); 
    FileTimeToSystemTime(&ft, &stCurrentTime); 

    PlayBackgroundMusic(); 

    start_time_stamp_microsec = (stStartTime.wMinute * 60000) + (stStartTime.wSecond * 1000) + stStartTime.wMilliseconds; 
    current_time_stamp_microsec = (stCurrentTime.wMinute * 60000) + (stCurrentTime.wSecond * 1000) + stCurrentTime.wMilliseconds; 
    main_timer_microsec = current_time_stamp_microsec - start_time_stamp_microsec;  

    return (0); 
}

void resize(int width, int height) 
{
    // code 
    // if height accidently is <= 0.0, make height 1
    if(height <= 0) 
    {
        height = 1; 
    }

    glMatrixMode(GL_PROJECTION); 
    glLoadIdentity(); 

    // set the viewport 
    glViewport(0, 0, (GLsizei)width, (GLsizei)height);     

    gluPerspective(45.0f, (GLfloat)width/(GLfloat)height, 0.1f, 200.0f); 
}

void display(void) 
{
    // code 
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

    char str[128]; 
    sprintf(str, "%llu", main_timer_microsec); 
    SetWindowText(ghWnd, str); 

    current_time_stamp_microsec = (stCurrentTime.wMinute * 60000) + (stCurrentTime.wSecond * 1000) + stCurrentTime.wMilliseconds; 
    main_timer_microsec = current_time_stamp_microsec - start_time_stamp_microsec;  

    glMatrixMode(GL_MODELVIEW); 
    glLoadIdentity(); 

    // Position the camera 
    gluLookAt(
        cameraX, cameraY, cameraZ, 
        cameraEyeX, cameraEyeY, cameraEyeZ, 
        cameraUpX, cameraUpY, cameraUpZ
    ); 

    // apply camera rotation 
    // glRotatef(cameraAngle, 0.0f, 1.0f, 0.0f); 

    switch(currentSceneNumber) 
    {
        case SCENE_TWO: 
            displayScene2(); 
        case SCENE_ONE: 
            displayScene1(); 
            break; 
        case SCENE_THREE: 
            displayScene3(); 
            break; 
        case SCENE_FOUR: 
            displayScene4(); 
            break; 
        default: 
            break; 
    }

    
    // if(main_timer_microsec < 500) 
    //     isFading = TRUE; 
    
    // if(main_timer_microsec > 2000 && main_timer_microsec <= 9426) 
    //     displaySlide1();    

    // if(main_timer_microsec > 5500 && main_timer_microsec < 5520) 
    //     isFading = TRUE; 

    // if(main_timer_microsec > 8500 && main_timer_microsec <= 12000) 
    //     displaySlide2(); 

    // if(main_timer_microsec > 11000 && main_timer_microsec < 11010) 
    //     isFading = TRUE; 

    // if(main_timer_microsec > 12000 && main_timer_microsec <= 18000) 
    //     displayScene1(); 

    displayFade(); 
    
    // swap the buffers 
    SwapBuffers(ghdc); 
}

void PlayBackgroundMusic(void)
{
    char buffer[MAX_PATH] = {0};
    GetModuleFileName(NULL, buffer, MAX_PATH);
    char *LastSlash = strrchr(buffer, '\\');
    if (LastSlash == NULL)
        LastSlash = strrchr(buffer, '/');
    buffer[LastSlash - buffer] = 0;
    strcat(buffer, "\\Resources\\audio.wav");
    PlaySound(buffer, NULL, SND_ASYNC | SND_LOOP);
}

void update(void) 
{
    // code 
    GetSystemTimePreciseAsFileTime(&ft); 
    FileTimeToSystemTime(&ft, &stCurrentTime); 

    switch(currentSceneNumber) 
    {
        case SCENE_ONE: 
            updateScene1(); 
            break; 
        case SCENE_TWO: 
            updateScene2(); 
            break; 
        case SCENE_THREE: 
            updateScene3(); 
            break; 
        case SCENE_FOUR: 
            updateScene4(); 
            break; 
        default: 
            break; 
    }
    updateFade(); 
}

void uninitialize(void) 
{
    // function declarations 
    void toggleFullScreen(void); 

    // code 
    uninitializeScene4(); 
    uninitializeScene3(); 
    uninitializeScene2(); 
    uninitializeScene1(); 

    // if user is exitting in fullscreen, restore fullscreen to nornal  
    if(gbFullScreen) 
    {
        toggleFullScreen(); 
        gbFullScreen = FALSE; 
    }

    // make hdc as cuurent context by releasing rendering context as current context 
    if(wglGetCurrentContext() == ghrc) 
    {
        wglMakeCurrent(NULL, NULL); 
    }

    // delete the rendering context 
    if(ghrc) 
    {
        wglDeleteContext(ghrc); 
        ghrc = NULL; 
    }

    // release the dc 
    if(ghdc) 
    {
        ReleaseDC(ghWnd, ghdc); 
        ghdc = NULL; 
    }

    if(ghWnd) 
    {
        DestroyWindow(ghWnd); 
        ghWnd = NULL; 
    }

    // close the file 
    if(gpFile) 
    {
        fprintf(gpFile, "Program terminated successfully"); 
        fclose(gpFile); 
        gpFile = NULL; 
    } 
}
