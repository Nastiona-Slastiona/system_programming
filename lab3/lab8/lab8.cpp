#include "framework.h"
#include "lab8.h"
#define MAX_LOADSTRING 100
#define BUTTON_DRAW_ID 1
#define BUTTON_CLEAR_ID 2

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];           
bool pictureVisible = false;
HWND buttonAdd, buttonClear;

ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_LAB8, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB8));

	MSG msg;


	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB8));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(CreateSolidBrush(RGB(250, 230, 200)));
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_LAB8);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // Store instance handle in our global variable

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		0, 0, 890, 500, nullptr, nullptr, hInstance, nullptr);

	buttonAdd = CreateWindow(L"BUTTON", NULL, WS_VISIBLE | WS_CHILD | BS_OWNERDRAW | BS_PUSHBUTTON,
		20, 20, 60, 60, hWnd, (HMENU)BUTTON_DRAW_ID, NULL, NULL);
	buttonClear = CreateWindow(L"BUTTON", NULL, WS_VISIBLE | WS_CHILD | BS_OWNERDRAW | BS_PUSHBUTTON,
		800, 20, 60, 60, hWnd, (HMENU)BUTTON_CLEAR_ID, NULL, NULL);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;

	switch (message)
	{
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
	
		switch (wmId)
		{
		case BUTTON_DRAW_ID:
			pictureVisible = true;
			InvalidateRect(hWnd, NULL, true);
			break;
		case BUTTON_CLEAR_ID:
			pictureVisible = false;
			InvalidateRect(hWnd, NULL, true);
			break;
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_DRAWITEM:
	{
		DRAWITEMSTRUCT* draw = (DRAWITEMSTRUCT*)lParam;
		HBRUSH brush;
		HPEN pen;

		switch (draw->CtlID)
		{
		case BUTTON_DRAW_ID:
		{
			HDC hdc = draw->hDC;

			if (draw->itemAction == ODA_SELECT) {
				brush = CreateSolidBrush(RGB(114, 158, 161));
			}
			else {
				brush = CreateSolidBrush(RGB(131, 179, 77));
			}


			pen = CreatePen(BS_SOLID, 2, RGB(0, 0, 0));

			SelectObject(hdc, brush);
			SelectObject(hdc, pen);

			Rectangle(hdc, 0, 0, 60, 60);
			MoveToEx(hdc, 10, 30, NULL);
			LineTo(hdc, 50, 30);
			MoveToEx(hdc, 30, 10, NULL);
			LineTo(hdc, 30, 50);
		}
		break;
		case BUTTON_CLEAR_ID:
		{
			HDC hdc = draw->hDC;

			if (draw->itemAction == ODA_SELECT) {
				brush = CreateSolidBrush(RGB(114, 158, 161));
			}
			else {
				brush = CreateSolidBrush(RGB(212, 15, 28));
			}
			pen = CreatePen(BS_SOLID, 2, RGB(0, 0, 0));

			SelectObject(hdc, brush);
			SelectObject(hdc, pen);

			Rectangle(hdc, 0, 0, 60, 60);
			MoveToEx(hdc, 10, 10, NULL);
			LineTo(hdc, 50, 50);
			MoveToEx(hdc, 50, 10, NULL);
			LineTo(hdc, 10, 50);
			
		}
		break;
		default:
			break;
		}

	}
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);

		HBRUSH brush;
		HPEN pen;
		if (pictureVisible)
		{
			brush = CreateSolidBrush(RGB(50, 50, 50));
			SelectObject(hdc, brush);


			brush = CreateSolidBrush(RGB(140, 62, 14));
			SelectObject(hdc, brush);
			pen = CreatePen(BS_SOLID, 2, RGB(0, 0, 0));
			SelectObject(hdc, pen);

			POINT p[16] = { 150, 70, 150, 350, 550, 350,
							550, 340, 500, 340, 500, 330, 
							450, 330, 450, 70
							
			};
			Polygon(hdc, p, 8);

			pen = CreatePen(BS_SOLID, 1, RGB(0, 0, 0));
			SelectObject(hdc, pen);
			brush = CreateSolidBrush(RGB(149, 184, 242));
			SelectObject(hdc, brush);

			Rectangle(hdc, 200, 150, 250, 250);
			Rectangle(hdc, 250, 150, 300, 250);

			brush = CreateSolidBrush(RGB(255, 209, 5));
			SelectObject(hdc, brush);
			Ellipse(hdc, 600, 10, 660, 70);

			brush = CreateSolidBrush(RGB(133, 19, 7));
			SelectObject(hdc, brush);
			POINT p2[3] = { 70, 100, 530, 100, 300, 10 }; //roof
			Polygon(hdc, p2, 3);

			pen = CreatePen(BS_SOLID, 5, RGB(175, 209, 117));
			SelectObject(hdc, pen);

			MoveToEx(hdc, 0, 350, NULL);
			LineTo(hdc, 820, 350);

			pen = CreatePen(BS_SOLID, 7, RGB(255, 209, 5));
			SelectObject(hdc, pen);
										
			Arc(hdc, 550, 10, 650, 110, 590, 10, 630, 160);
										
		}
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}