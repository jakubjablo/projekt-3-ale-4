#include <fstream>
#include <iostream>
#include <cmath>
#include <math.h>
#include <windows.h>
#include <objidl.h>
#include <gdiplus.h>
#include <queue>

constexpr auto ButtonDelete100 = 001;
constexpr auto ButtonDelete50 = 002;
constexpr auto ButtonStart = 003;
constexpr auto ButtonSlow = 004;
constexpr auto ButtonFast = 005;


using namespace Gdiplus;
#pragma comment (lib,"Gdiplus.lib")

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
using namespace std;


queue < float > YawQueue;
// Pobieranie danych z pliku outputCatapult01.log
void Data()
{
    ifstream input("outputCatapult01.log");
    string YawString;
    fstream plik("test.txt", std::ios::out);

    int i = 0;
    int yaw;
    while (input >> YawString)
    {
        float YawFloat = atof(YawString.c_str()); 
        if ((i % 12) == 2)
        {
            yaw = YawFloat;
            YawQueue.push(yaw);  
            cout << yaw << endl;
        }
        i++;
    }
    
}



// RYSOWANIE
VOID PaintCircle(HDC hdc)
{
    Graphics graphicsB(hdc);
    Pen penB(Color(255, 0, 0, 0));
    graphicsB.DrawEllipse(&penB, 100, 50, 300, 300);
    
}
VOID PaintCircleFill(HDC hdc)
{
    Graphics graphics(hdc);
    SolidBrush pen(Color(255, 255, 255, 255));
    graphics.FillEllipse(&pen, 100, 50, 300, 300);
    
}
VOID PaintLineBLUE(HDC hdc, int yawBlueX, int yawBlueY)
{
	Graphics graphics3(hdc);
	Pen      pen3(Color(255, 0, 0, 255));
	graphics3.DrawLine(&pen3, 250, 200, yawBlueX, yawBlueY);
}
VOID PaintLineRED(HDC hdc, int yawRedX, int yawRedY)
{
    Graphics graphics2(hdc);
    Pen      pen2(Color(255, 255, 0, 0));
    graphics2.DrawLine(&pen2, 250, 200, yawRedX, yawRedY);
   
}


//--------------------------------------------------



void Draw(HDC hdc)
{
    int yawBlueX, yawBlueY, yawRedX, yawRedY,;
     int size = YawQueue.size();
    float alfa;
    PaintCircle(hdc);
    while (size > 0)
    {    
        alfa = YawQueue.front();
        yawRedX = 150 * sin(alfa) + 250;
        yawRedY = 150 * cos(alfa) + 200;
        yawBlueX = 150 * sin(alfa+135) + 250;;
        yawBlueY = 150 * cos(alfa+135) + 200;
        PaintCircleFill(hdc);
        PaintLineRED(hdc, yawRedX, yawRedY);
        PaintLineBLUE(hdc, yawBlueX, yawBlueY);
        Sleep(10);
        YawQueue.pop();
        size--;
    }
}

void DrawSlow(HDC hdc)
{
    int yawBlueX, yawBlueY, yawRedX, yawRedY;
    int size = YawQueue.size();
    float alfa;
    PaintCircle(hdc);
    while (size > 0)
    {
        alfa = YawQueue.front();
        yawRedX = 150 * sin(alfa) + 250;
        yawRedY = 150 * cos(alfa) + 200;
        yawBlueX = 150 * sin(alfa + 135) + 250;;
        yawBlueY = 150 * cos(alfa + 135) + 200;
        PaintCircleFill(hdc);
        PaintLineRED(hdc, yawRedX, yawRedY);
        PaintLineBLUE(hdc, yawBlueX, yawBlueY);
        Sleep(50);
        YawQueue.pop();
        size--;
    }
}
void DrawFast(HDC hdc)
{
    int yawBlueX, yawBlueY, yawRedX, yawRedY;
    int size = YawQueue.size();
    float alfa;
    PaintCircle(hdc);
    while (size > 0)
    {
        alfa = YawQueue.front();
        yawRedX = 150 * sin(alfa) + 250;
        yawRedY = 150 * cos(alfa) + 200;
        yawBlueX = 150 * sin(alfa + 135) + 250;;
        yawBlueY = 150 * cos(alfa + 135) + 200;
        PaintCircleFill(hdc);
        PaintLineRED(hdc, yawRedX, yawRedY);
        PaintLineBLUE(hdc, yawBlueX, yawBlueY);
        Sleep(5);
        YawQueue.pop();
        size--;
    }
}

void deleteData()
{
    for (int i = 0; i < 100; i++)
    {
        YawQueue.pop();
    }
}
void deleteData2()
{
    for (int i = 0; i < 50; i++)
    {
        YawQueue.pop();
    }
}




INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pCmdLine, INT iCmdShow)
{
    int nr = 0;
   // Data();
    HWND                hWnd;
    MSG                 msg;
    WNDCLASS            wndClass = {};
    GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR           gdiplusToken;

    // Initialize GDI+.
    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
    
    wndClass.style = CS_HREDRAW | CS_VREDRAW;
    wndClass.lpfnWndProc = WndProc;
    wndClass.cbClsExtra = 0;
    wndClass.cbWndExtra = 0;
    wndClass.hInstance = hInstance;
    wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wndClass.lpszMenuName = NULL;
    wndClass.lpszClassName = TEXT("Techniki Prgramowania | Julia Strasser Weronika K³onowska");

    RegisterClass(&wndClass);

    hWnd = CreateWindow(
        TEXT("Techniki Prgramowania | Jakub Jablonski 184720 Jakub Pilarski 184815"),   // window class name
        TEXT("Techniki Prgramowania | Jakub Jablonski 184720 Jakub Pilarski 184815"),  // window caption
        WS_OVERLAPPEDWINDOW,      // window style
        CW_USEDEFAULT,            // initial x position
        CW_USEDEFAULT,            // initial y position
        CW_USEDEFAULT,            // initial x size
        CW_USEDEFAULT,            // initial y size
        NULL,                     // parent window handle
        NULL,                     // window menu handle
        hInstance,                // program instance handle
        NULL);                    // creation parameters
        
    HWND buttonDelete50 = CreateWindow(
        L"BUTTON",  // Predefined class; Unicode assumed 
        L"Odrzuc 50 poczatkowych probek danych ",      // Button text 
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
        450,         // x position 
        150,         // y position 
        400,        // Button width
        100,        // Button height
        hWnd,     // Parent window
        (HMENU) ButtonDelete50,       // No menu.
        hInstance,
        NULL);      // Pointer not needed.
        
    HWND buttonDelete100 = CreateWindow(
        L"BUTTON",  // Predefined class; Unicode assumed 
        L"Odrzuc 100 poczatkowych probek danych ",      // Button text 
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
        450,         // x position 
        0,         // y position 
        400,        // Button width
        100,        // Button height
        hWnd,     // Parent window
        (HMENU)ButtonDelete100,       // No menu.
        hInstance,
        NULL);      // Pointer not needed.
    
    HWND buttonStart = CreateWindow(
        L"BUTTON",  // Predefined class; Unicode assumed 
        L"Start",      // Button text 
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
        450,         // x position 
        300,         // y position 
        400,        // Button width
        100,        // Button height
        hWnd,     // Parent window
        (HMENU)ButtonStart,       // No menu.
        hInstance,
        NULL);      // Pointer not needed.
        
    HWND buttonFast = CreateWindow(
        L"BUTTON",  // Predefined class; Unicode assumed 
        L"Zwieksz predkosc igly",      // Button text 
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
        450,         // x position 
        600,         // y position 
        400,        // Button width
        100,        // Button height
        hWnd,     // Parent window
        (HMENU)ButtonFast,       // No menu.
        hInstance,
        NULL);      // Pointer not needed.
  
    HWND buttonSlow = CreateWindow(
        L"BUTTON",  // Predefined class; Unicode assumed 
        L"Zmniejsz predkosc igly",      // Button text 
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
        450,         // x position 
        450,         // y position 
        400,        // Button width
        100,        // Button height
        hWnd,     // Parent window
        (HMENU)ButtonSlow,       // No menu.
        hInstance,
        NULL);      // Pointer not needed.
        
    ShowWindow(hWnd, iCmdShow);
    UpdateWindow(hWnd);

    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    GdiplusShutdown(gdiplusToken);
    return msg.wParam;
}  // WinMain

LRESULT CALLBACK WndProc(HWND hWnd, UINT message,
    WPARAM wParam, LPARAM lParam)
{
    HDC          hdc;
    PAINTSTRUCT  ps;
    int size1 = 100;
    int size2 = 50;
    switch (message)
    {
    case WM_PAINT:
        break;
    case WM_COMMAND:

        switch (wParam)
        {
        	
        case ButtonDelete50:
            Data();
            deleteData2();
            hdc = BeginPaint(hWnd, &ps);
            Draw(hdc);
            EndPaint(hWnd, &ps);
            break;

        case ButtonDelete100:
            Data();
            deleteData();
            hdc = BeginPaint(hWnd, &ps);
            Draw(hdc);
            EndPaint(hWnd, &ps);
            break;

        case ButtonStart:
            Data();
            hdc = BeginPaint(hWnd, &ps);
            Draw(hdc);
           EndPaint(hWnd, &ps);
            break;
            
        case ButtonFast:
            Data();
            hdc = BeginPaint(hWnd, &ps);
            DrawFast(hdc);
            EndPaint(hWnd, &ps);
            break;
        }

        case ButtonSlow:
            Data();
            hdc = BeginPaint(hWnd, &ps);
            DrawSlow(hdc);
            EndPaint(hWnd, &ps);
            break;
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
}
