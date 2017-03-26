//#include <windows.h>
//
//// ����ע��Ĵ�������
//const char g_szClassName[] = "myWindowClass";
//
////��һ����
//void Print(HWND hwnd) {
//	PAINTSTRUCT ps;
//	HDC hdc;//DC(�ɻ�ͼ�ڴ����)�ľ��
//	HPEN hpen;
//	hdc = BeginPaint(hwnd, &ps);//ͨ�����ھ����ȡ�ô��ڵ�DC
//	hpen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));//��������
//	SelectObject(hdc, hpen);//DCѡ�񻭱�
//	MoveToEx(hdc, 50, 50, NULL);
//	LineTo(hdc, 150, 150);
//	EndPaint(hwnd, &ps);
//}
///*
//* ���Ĳ�,���ڹ���
//*/
//LRESULT CALLBACK MyWindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
//{
//	switch (msg)
//	{
//		// ���ڻ�����Ϣ
//	case WM_PAINT:
//		Print(hwnd);
//		/*
//		* �ڴ˵��� GDI ���ƺ���
//		*/
//		break;
//		// ���ڹر���Ϣ
//	case WM_CLOSE:
//		DestroyWindow(hwnd);
//		break;
//		// ����������Ϣ
//	case WM_DESTROY:
//		PostQuitMessage(0); // �����뿪��Ϣ��ϵͳ
//		break;
//		// ������Ϣ
//	default:
//		//
//		return DefWindowProc(hwnd, msg, wParam, lParam);
//	}
//	return 0;
//}
//
///*
//* ��һ��,ע�ᴰ����
//*/
//void RegisterMyWindow(HINSTANCE hInstance)
//{
//	WNDCLASSEX wc;
//
//	// 1)���ô�������
//	wc.cbSize = sizeof(WNDCLASSEX);
//	wc.style = 0;
//	wc.lpfnWndProc = MyWindowProc; // ���õ��Ĳ��Ĵ��ڹ��̻ص�����
//	wc.cbClsExtra = 0;
//	wc.cbWndExtra = 0;
//	wc.hInstance = hInstance;
//	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
//	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
//	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
//	wc.lpszMenuName = NULL;
//	wc.lpszClassName = g_szClassName;
//	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
//
//	// 2)ע��
//	if (!RegisterClassEx(&wc))
//	{
//		MessageBox(NULL, "����ע��ʧ��!", "����", MB_ICONEXCLAMATION | MB_OK);
//		exit(0); // �����˳�
//	}
//}
//
//HWND CreateMyWindow(HINSTANCE hInstance, int nCmdShow)
//{
//	HWND hwnd;
//	hwnd = CreateWindowEx(
//		WS_EX_CLIENTEDGE,
//		g_szClassName,
//		"����",
//		WS_OVERLAPPEDWINDOW,
//		CW_USEDEFAULT, CW_USEDEFAULT, 400, 300, // �������� 
//		NULL, NULL, hInstance, NULL);
//
//	if (hwnd == NULL)
//	{
//		MessageBox(NULL, "���ڴ���ʧ��!", "����", MB_ICONEXCLAMATION | MB_OK);
//		exit(0); // �����˳�
//	}
//
//	// ��ʾ����
//	ShowWindow(hwnd, nCmdShow);
//	UpdateWindow(hwnd);
//
//	return hwnd;
//}
//
//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
//	LPSTR lpCmdLine, int nCmdShow)
//{
//	HWND hwnd;
//	MSG Msg;
//
//	// ��һ��,ע�ᴰ����
//	RegisterMyWindow(hInstance);
//	// �ڶ���:��������
//	hwnd = CreateMyWindow(hInstance, nCmdShow);
//	// ������:��Ϣѭ��
//	while (GetMessage(&Msg, NULL, 0, 0) > 0)
//	{
//		TranslateMessage(&Msg);
//		DispatchMessage(&Msg);
//	}
//	return Msg.wParam;
//}


//#include <Windows.h>
//#include <tchar.h>

#include <windows.h>
#include <tchar.h>
#include "resource.h"

BOOLEAN InitWindowClass(HINSTANCE hInstance, int nCmdShow);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

HINSTANCE hInst; //��ǰʵ�����

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine,
	int nCmdShow)
{
	MSG msg;
	hInst = hInstance;

	if (!InitWindowClass(hInstance, nCmdShow)) //��ʼ��������
	{
		MessageBox(NULL, TEXT("��������ʧ��"), TEXT("��������"), NULL);
		return 1;
	}

	while (GetMessage(&msg, NULL, 0, 0)) //��Ϣѭ��
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hDC;
	PAINTSTRUCT ps;
	static HDC hMemDC;
	static HBITMAP hBitmap;
	static BITMAP bitmap;
	static bool fullClient = false;
	RECT clientRect;

	switch (message)
	{
	case WM_CREATE:
		hDC = GetDC(hWnd); //��ȡ����������
		hMemDC = CreateCompatibleDC(hDC);
		hBitmap = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP1));
		SelectObject(hMemDC, hBitmap);
		GetObject(hBitmap, sizeof(BITMAP), &bitmap);
		ReleaseDC(hWnd, hDC);
		break;
	case WM_LBUTTONDOWN:
		fullClient = !fullClient;
		InvalidateRect(hWnd, NULL, true);
		break;
	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);
		if (fullClient)
		{
			GetClientRect(hWnd, &clientRect);
			StretchBlt(hDC, 0, 0, clientRect.right - clientRect.left,
				clientRect.bottom - clientRect.top, hMemDC, 0, 0,
				bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);
		}
		else
			BitBlt(hDC, 0, 0, bitmap.bmWidth, bitmap.bmHeight, hMemDC, 0,
				0, SRCCOPY);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		DeleteObject(hBitmap);
		ReleaseDC(hWnd, hMemDC);
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}

	return 0;
}

BOOLEAN InitWindowClass(HINSTANCE hInstance, int nCmdShow)
{
	WNDCLASSEX wcex;
	HWND hWnd;
	TCHAR szWindowClass[] = TEXT("����ʾ��");
	TCHAR szTitle[] = TEXT("λͼ��ʾ");
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = 0;
	wcex.lpfnWndProc = &WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

	if (!RegisterClassEx(&wcex))
		return FALSE;

	hWnd = CreateWindow(
		szWindowClass,
		szTitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	if (!hWnd)
		return FALSE;
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	return TRUE;
}



