#include <windows.h>

const char g_szClassNmae[] = "mywindowClasss";

//窗口过程
LRESULT  CALLBACK MywindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) {
	case WM_PAINT://此处调用GDI绘制函数
		break;
	case WM_CLOSE://窗口关闭
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);//发送离开消息给系统
	default://其他情况
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
}

//注册窗口类

void RegisterMyWindow(HINSTANCE hInstance) {
	WNDCLASSEX wc;
	//配置窗口属性
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = 0;
	wc.lpfnWndProc = MywindowProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
}