#include <Windows.h>

// Глобальные переменные:
HINSTANCE hInst;//текущий экземпляр
LPCWSTR szTitle = L"Программа";
LPCWSTR szWindowClass = L"Проект";
LPCWSTR szPopupClass = L"Окно";

ATOM InitClass(HINSTANCE hInstance, WNDPROC WndProc, LPCWSTR ClassName);
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow);
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK WndPopup(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	if (!InitClass(hInstance, WndProc, szWindowClass)) return FALSE;//регистрируем класс
	if (!InitClass(hInstance, WndPopup, szPopupClass)) return FALSE;//регистрируем класс
	
	if (!InitInstance(hInstance, nCmdShow))	return FALSE;//создаем главное окно

	MSG msg;
	// Цикл основного сообщения:
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
	wcx.style = CS_HREDRAW | CS_VREDRAW;//перерисовывать всё окно при изменении ширины и высоты соотв. 
	wcx.lpfnWndProc = WndProc;//обработчик
	wcx.cbClsExtra = 0;
	wcx.cbWndExtra = 0;
	wcx.hInstance = hInstance;//код приложения
	wcx.hIcon = LoadIcon(NULL, IDI_APPLICATION);//использовать одну из предопределенных пиктограмм Windows, второй аргумент не важен
	wcx.hCursor = LoadCursor(NULL, IDC_ARROW);//иконка курсора
	wcx.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcx.lpszMenuName = (LPCWSTR) NULL;//меню
	wcx.lpszClassName = ClassName;
	wcx.hIconSm = LoadIcon(NULL, IDI_APPLICATION);//иконка класса окна
	return RegisterClassExW(&wcx);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной
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