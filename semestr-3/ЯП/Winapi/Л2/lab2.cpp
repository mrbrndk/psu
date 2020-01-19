#include <Windows.h>

// ���������� ����������:
HINSTANCE hInst;//������� ���������
LPCWSTR szTitle = L"���������";
LPCWSTR szWindowClass = L"������";
LPCWSTR szPopupClass = L"����";

ATOM InitClass(HINSTANCE hInstance, WNDPROC WndProc, LPCWSTR ClassName);
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow);
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK WndPopup(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	if (!InitClass(hInstance, WndProc, szWindowClass)) return FALSE;//������������ �����
	if (!InitClass(hInstance, WndPopup, szPopupClass)) return FALSE;//������������ �����
	
	if (!InitInstance(hInstance, nCmdShow))	return FALSE;//������� ������� ����

	MSG msg;
	// ���� ��������� ���������:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (int)msg.wParam;
}

ATOM InitClass(HINSTANCE hInstance, WNDPROC WndProc, LPCWSTR ClassName)
{
	WNDCLASSEXW wcx;
	wcx.cbSize = sizeof(WNDCLASSEX);
	wcx.style = CS_HREDRAW | CS_VREDRAW;//�������������� �� ���� ��� ��������� ������ � ������ �����. 
	wcx.lpfnWndProc = WndProc;//����������
	wcx.cbClsExtra = 0;
	wcx.cbWndExtra = 0;
	wcx.hInstance = hInstance;//��� ����������
	wcx.hIcon = LoadIcon(NULL, IDI_APPLICATION);//������������ ���� �� ���������������� ���������� Windows, ������ �������� �� �����
	wcx.hCursor = LoadCursor(NULL, IDC_ARROW);//������ �������
	wcx.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcx.lpszMenuName = (LPCWSTR) NULL;//����
	wcx.lpszClassName = ClassName;
	wcx.hIconSm = LoadIcon(NULL, IDI_APPLICATION);//������ ������ ����
	return RegisterClassExW(&wcx);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // ��������� ������ ���������� � ���������� ����������
	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);
	if (!hWnd) return FALSE;
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HWND hWndP;
	switch (message)
	{
		case WM_LBUTTONDOWN:
		{
			RECT pos;
			GetWindowRect(hWnd, &pos);
			hWndP = CreateWindowW(szPopupClass, szTitle, WS_OVERLAPPEDWINDOW,
				pos.left, pos.top, (pos.right - pos.left) / 2, (pos.bottom - pos.top) / 2,
				hWnd, nullptr, hInst, nullptr);
			if (!hWndP) return FALSE;
			ShowWindow(hWndP, SW_SHOW);
			UpdateWindow(hWndP);
			SetCapture(hWnd);
			break;
		}
		case WM_LBUTTONUP:
		{
			SendMessage(hWndP, WM_CLOSE, 0, 0);
			ReleaseCapture();
			break;
		}
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			break;
		}
		default: return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

LRESULT CALLBACK WndPopup(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, message, wParam, lParam);
}