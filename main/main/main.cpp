
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#include <windows.h>
#include "login.h"
#include "file.h"
#include <string.h>
#include "child.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

HINSTANCE g_hInst;                                 
HWND hWndMain,hTop,hBottom,hLeft,hMiddle,hRight;
FILE *fp;    //����ó��
BOOL loginState;
LPCTSTR lpszClass = TEXT("ECONOVATION");
MEMBER **member;
MEMBER *current;
BOOK **book;
RECT crt;
int memberNum;
int bookNumber;
int awaitNum = 1; //����ڵ� ��

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = lpszClass;
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

	//���� ����ȸ�� ���� ������
	WndClass.hbrBackground = CreateSolidBrush(RGB(162,246,255));
	WndClass.lpfnWndProc = ChildTopProc;
	WndClass.lpszClassName = TEXT("ChildTop");
	RegisterClass(&WndClass);

	//ȸ�� �����ȸ ������
	WndClass.hbrBackground = CreateSolidBrush(RGB(72, 156, 255));
	WndClass.lpfnWndProc = ChildLeftProc;
	WndClass.lpszClassName = TEXT("ChildLeft");
	RegisterClass(&WndClass);

	//������� ������
	WndClass.hbrBackground = CreateSolidBrush(RGB(236, 173, 255));
	WndClass.lpfnWndProc = ChildMiddleProc;
	WndClass.lpszClassName = TEXT("ChildMiddle");
	RegisterClass(&WndClass);

	//�뿩��� ������
	WndClass.hbrBackground = CreateSolidBrush(RGB(255, 227, 255));
	WndClass.lpfnWndProc = ChildRightProc;
	WndClass.lpszClassName = TEXT("ChildRight");
	RegisterClass(&WndClass);

	//�޴���ư ������
	WndClass.hbrBackground = CreateSolidBrush(RGB(219,156, 255));
	WndClass.lpfnWndProc = ChildBottomProc;
	WndClass.lpszClassName = TEXT("ChildBottom");
	RegisterClass(&WndClass);


	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);

	while (GetMessage(&Message, NULL, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return (int)Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	TCHAR str[128];
	DWORD dwRead;
	

	switch (iMessage) {

	case WM_CREATE:
		
		loginState = FALSE;
		
		readclient(); //���Ϸκ��� ȸ�� �о����

		if(DialogBox(g_hInst, MAKEINTRESOURCE(IDD_LOGIN), hWnd, LoginProc) == IDOK) {
			loginState = TRUE;
    		//lstrcat(str, current.id);
			//SetWindowText(hAdmin, str);
			//�α��� �Ϸ��   	
		} 


		InitCommonControls();
		hWndMain = hWnd;
		GetClientRect(hWnd, &crt);

		hTop = CreateWindow(TEXT("ChildTop"), NULL, WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN, 0, 0, 0, 0, hWnd, (HMENU)0, g_hInst, NULL);
		hBottom = CreateWindow(TEXT("ChildBottom"), NULL, WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN, 0, 0, 0, 0, hWnd, (HMENU)0, g_hInst, NULL);
		hLeft= CreateWindow(TEXT("ChildLeft"), NULL, WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN, 0, 0, 0, 0, hWnd, (HMENU)0, g_hInst, NULL);
		hMiddle = CreateWindow(TEXT("ChildMiddle"), NULL, WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN, 0, 0, 0, 0, hWnd, (HMENU)0, g_hInst, NULL);
		hRight= CreateWindow(TEXT("ChildRight"), NULL, WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN, 0, 0, 0, 0, hWnd, (HMENU)0, g_hInst, NULL);
	
		return 0;
	case WM_SIZE:
		
		if (wParam != SIZE_MINIMIZED) { //ȭ�����
			GetClientRect(hWnd, &crt);
			MoveWindow(hTop, 0, 0,crt.right,crt.bottom*0.06 ,TRUE);
			MoveWindow(hLeft, 0, crt.bottom*0.06,crt.right*0.2,(crt.bottom- crt.bottom*0.06)*0.9, TRUE);
			MoveWindow(hRight,crt.right*0.2,crt.bottom*0.06, crt.right-crt.right*0.19, (crt.bottom - crt.bottom*0.06)*0.9*0.5 , TRUE);
			MoveWindow(hMiddle, crt.right*0.2, crt.bottom*0.06+ (crt.bottom - crt.bottom*0.06)*0.9*0.5 , crt.right - crt.right*0.19, (crt.bottom - crt.bottom*0.06)*0.9*0.5022, TRUE);
			MoveWindow(hBottom,0, crt.bottom*0.06 + (crt.bottom - crt.bottom*0.06)*0.9,crt.right ,crt.bottom-crt.bottom*0.06+(crt.bottom- crt.bottom*0.06)*0.9 , TRUE);

		}
		
		return 0;
	case WM_PAINT:
        
		hdc = BeginPaint(hWnd, &ps);
	

		EndPaint(hWnd, &ps);

		return 0;
	
	case WM_DESTROY:

		PostQuitMessage(0);

		return 0;
	}

	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}

