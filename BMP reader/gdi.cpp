#include <windows.h>

const char g_szClassNmae[] = "mywindowClasss";

//���ڹ���
LRESULT  CALLBACK MywindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) {
	case WM_PAINT://�˴�����GDI���ƺ���
		break;
	case WM_CLOSE://���ڹر�
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);//�����뿪��Ϣ��ϵͳ
	default://�������
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
}

//ע�ᴰ����

void RegisterMyWindow(HINSTANCE hInstance) {
	WNDCLASSEX wc;
	//���ô�������
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = 0;
	wc.lpfnWndProc = MywindowProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
}