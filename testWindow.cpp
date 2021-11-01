#include <windows.h>
#include <tchar.h>
#include <string.h>
#include <stdlib.h>
#include <string>

using namespace std;

//compile with: /D_UNICODE /DUNICODE /DWIN32 /D_WINDOWS /c

//the main window class name
static TCHAR szWindowClass[] = _T("testWindow");

//the string that appears int he applicaiton's title bar
static TCHAR szTitle[] = _T("USMC Digital Sead Timelines");

HINSTANCE hInst;

//forward dec of functions included in this code module:
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

HWND textbox, newWindow = nullptr;
LPWSTR buf = nullptr;

//Windows desktop application version of Main
int WINAPI WinMain
(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nCmdShow
)
{
	//window structure // function pointer to window-procedure
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(wcex.hInstance, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

	//register WNDCLASSEX with windows so it can pass msgs
	if (!RegisterClassEx(&wcex))
	{
		MessageBox
		(
			NULL,
			_T("Call to RegisterClassEx failed!"),
			_T("Sead Timelines"),
			NULL
		);
		return 1;
	}

	//store instance handle in our global var
	hInst = hInstance;

   //The parameters to CreateWindowEx explained:
   //WS_EX_OVERLAPPEDWINDOW : An optional extended window style.
   //szWindowClass: the name of the application
   //szTitle: the text that appears in the title bar
   //WS_OVERLAPPEDWINDOW: the type of window to create
   //CW_USEDEFAULT, CW_USEDEFAULT: initial position (x, y)
   //500, 100: initial size (width, length)
   //NULL: the parent of this window
   //NULL: this application dows not have a menu bar
   //hInstance: the first parameter from WinMain
   //NULL: not used in this application
	HWND hWnd = CreateWindowEx(

		WS_EX_OVERLAPPEDWINDOW,
		szWindowClass,
		szTitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		1000, 800,
		NULL,
		NULL,
		hInstance,
		NULL

	);

	//handle to a window (HWND) similar to a pointer
	//keeps track of open windows
	if (!hWnd)
	{
		MessageBox(NULL,
			_T("Call to CreateWindow failed!"),
			_T("Windows Desktop Guided Tour"),
			NULL);

		return 1;
	}

	//The parameters to ShowWindow explained:
    //hWnd: the value returned from CreateWindow
    //nCmdShow: the fourth parameter from WinMain
	//window has been created but we need to make it visable
	ShowWindow(
		hWnd,
		nCmdShow
	);
	UpdateWindow(hWnd);


	// Main message loop that will listen for messages
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}


//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//window-procedure function // needed by WinMain
//handles events // user input -> msg -> do something
LRESULT CALLBACK WndProc(
	_In_ HWND hWnd,
	_In_ UINT message,
	_In_ WPARAM wParam,
	_In_ LPARAM lParam
)
{
	//WM_PAINT message -> applicaiton needs updated
	//only windows knows and it will notify
	PAINTSTRUCT ps;
	//handle to a device context, used to draw in the windows area
	HDC hdc;
	TCHAR greeting[] = _T("Hello, Windows desktop AP test!");
#define IDC_BUTTON1 101


	switch (message)
	{

		//GetWindowText()
		//SetWindowText()
	case WM_CREATE :
	{
		textbox = CreateWindowEx(
			NULL,
			L"Edit",
			L"TOF",
			WS_VISIBLE | WS_CHILD | WS_BORDER,
			50,
			50,
			50,
			50,
			hWnd,
			NULL,
			hInst,
			NULL
		);
			
             CreateWindowA(
				"button",
				"run",
				WS_VISIBLE | WS_CHILD | WS_BORDER,
				100,
				100,
				100,
				100,
				hWnd,
				(HMENU) IDC_BUTTON1,
				NULL,
				NULL
			);

			 newWindow = CreateWindowA(
				 "Edit",
				 NULL,
				 WS_VISIBLE | WS_CHILD | WS_BORDER | ES_READONLY,
				 200,
				 200,
				 300,
				 200,
				 hWnd,
				 (HMENU) 3,
				 NULL,
				 NULL
			 );


			break;
	}

	case WM_COMMAND:
	{

		if (LOWORD(wParam) == IDC_BUTTON1)
		{
			//GetWindowText(GetDlgItem(hWnd, 101), test, 4);
			//Get the text from box 1.
			int len = GetWindowTextLength(textbox) + 1;
			char* text = new char[len];
			GetWindowText(textbox, (LPWSTR)&text[0], len);

			//string test(text);
			int min = 30;
			int sec = 45;
			string minS, secS = "";
			minS = to_string(min);
			secS = to_string(sec);
			char* standard = new char[16];
			//text[0] = test[0];
			

			//Append the text to box 2.
		    //SendMessage(newWindow, EM_SETSEL, -1, -1);
			//SendMessage(newWindow, EM_REPLACESEL, 0, (LPARAM)&text[0]);
			//SendMessage(newWindow, EM_REPLACESEL, 0, (LPARAM)&test[0]);

			//SetWindowText(newWindow, (LPCWSTR)&test[0]);
			//Delete the text from box 1.
			SetWindowText(textbox, L"TOF");
			//delete[] text;
			//MessageBoxA(hWnd, "test", "button1", MB_OK);

		}
		break;
	
	}
	case WM_PAINT:
	{

		//prepare paint
		hdc = BeginPaint(hWnd, &ps);

		//Here your application is laid out.
		//For this introduction, we just print out "Hello, Windows desktop!"
		//in the top left corner.
		TextOut(
			hdc,
			5, 5,
			greeting, _tcslen(greeting)
		);
		//End application-specific layout section.

		//finish paint
		EndPaint(hWnd, &ps);

		break;
	}
		//close window
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		break;
	}
	default:
	{
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}
	
	}

	return 0;

}