//#include <windows.h>
//
//// 用于注册的窗口类名
//const char g_szClassName[] = "myWindowClass";
//
////画一条线
//void Print(HWND hwnd) {
//	PAINTSTRUCT ps;
//	HDC hdc;//DC(可画图内存对象)的句柄
//	HPEN hpen;
//	hdc = BeginPaint(hwnd, &ps);//通过窗口句柄获取该窗口的DC
//	hpen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));//创建画笔
//	SelectObject(hdc, hpen);//DC选择画笔
//	MoveToEx(hdc, 50, 50, NULL);
//	LineTo(hdc, 150, 150);
//	EndPaint(hwnd, &ps);
//}
///*
//* 第四步,窗口过程
//*/
//LRESULT CALLBACK MyWindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
//{
//	switch (msg)
//	{
//		// 窗口绘制消息
//	case WM_PAINT:
//		Print(hwnd);
//		/*
//		* 在此调用 GDI 绘制函数
//		*/
//		break;
//		// 窗口关闭消息
//	case WM_CLOSE:
//		DestroyWindow(hwnd);
//		break;
//		// 窗口销毁消息
//	case WM_DESTROY:
//		PostQuitMessage(0); // 发送离开消息给系统
//		break;
//		// 其他消息
//	default:
//		//
//		return DefWindowProc(hwnd, msg, wParam, lParam);
//	}
//	return 0;
//}
//
///*
//* 第一步,注册窗口类
//*/
//void RegisterMyWindow(HINSTANCE hInstance)
//{
//	WNDCLASSEX wc;
//
//	// 1)配置窗口属性
//	wc.cbSize = sizeof(WNDCLASSEX);
//	wc.style = 0;
//	wc.lpfnWndProc = MyWindowProc; // 设置第四步的窗口过程回调函数
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
//	// 2)注册
//	if (!RegisterClassEx(&wc))
//	{
//		MessageBox(NULL, "窗口注册失败!", "错误", MB_ICONEXCLAMATION | MB_OK);
//		exit(0); // 进程退出
//	}
//}
//
//HWND CreateMyWindow(HINSTANCE hInstance, int nCmdShow)
//{
//	HWND hwnd;
//	hwnd = CreateWindowEx(
//		WS_EX_CLIENTEDGE,
//		g_szClassName,
//		"测试",
//		WS_OVERLAPPEDWINDOW,
//		CW_USEDEFAULT, CW_USEDEFAULT, 400, 300, // 出现坐标 
//		NULL, NULL, hInstance, NULL);
//
//	if (hwnd == NULL)
//	{
//		MessageBox(NULL, "窗口创建失败!", "错误", MB_ICONEXCLAMATION | MB_OK);
//		exit(0); // 进程退出
//	}
//
//	// 显示窗口
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
//	// 第一步,注册窗口类
//	RegisterMyWindow(hInstance);
//	// 第二步:创建窗口
//	hwnd = CreateMyWindow(hInstance, nCmdShow);
//	// 第三步:消息循环
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

HINSTANCE hInst; //当前实例句柄

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine,
	int nCmdShow)
{
	MSG msg;
	hInst = hInstance;

	if (!InitWindowClass(hInstance, nCmdShow)) //初始化窗口类
	{
		MessageBox(NULL, TEXT("创建窗口失败"), TEXT("创建窗口"), NULL);
		return 1;
	}

	while (GetMessage(&msg, NULL, 0, 0)) //消息循环
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
		hDC = GetDC(hWnd); //获取数据描述表
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
	TCHAR szWindowClass[] = TEXT("窗口示例");
	TCHAR szTitle[] = TEXT("位图显示");
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



