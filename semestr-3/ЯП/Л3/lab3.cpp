#include <Windows.h>

// Глобальные переменные:
HINSTANCE hInst;//текущий экземпляр
LPCWSTR szTitle = L"Программа (вариант 1)";
LPCWSTR szWindowClass = L"WindowClass";
LPCWSTR szTextClass = L"TextClass";

UINT width = 400;
UINT height = 300;

ATOM InitClass(HINSTANCE hInstance, WNDPROC WndProc, LPCWSTR ClassName);
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow);
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	if (!InitClass(hInstance, WndProc, szWindowClass)) return FALSE;//регистрируем класс
	
	if (!InitInstance(hInstance, nCmdShow))	return FALSE;//создаем главное окно

	MSG msg;
	// Цикл основного сообщения:
	while (GetMessageW(&msg, nullptr, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
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
	wcx.hIcon = LoadIconW(NULL, IDI_APPLICATION);//использовать одну из предопределенных пиктограмм Windows, второй аргумент не важен
	wcx.hCursor = LoadCursorW(NULL, IDC_ARROW);//иконка курсора
	wcx.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcx.lpszMenuName = (LPCWSTR) NULL;//меню
	wcx.lpszClassName = ClassName;
	wcx.hIconSm = LoadIconW(NULL, IDI_APPLICATION);//иконка класса окна
	return RegisterClassExW(&wcx);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной
	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		CW_USEDEFAULT, CW_USEDEFAULT, width, height, nullptr, nullptr, hInstance, nullptr);
	if (!hWnd) return FALSE;
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HWND listbox, checkbox, edit, button;
	WCHAR text[30];
	switch (message)
	{
		case WM_CREATE:
		{
			RECT pos;
			GetClientRect(hWnd, &pos);
			listbox = CreateWindowW(L"listbox", NULL, 
				WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_BORDER | LBS_DISABLENOSCROLL | LBS_NOTIFY,
				10, 10, pos.right - 20, pos.bottom - 90, hWnd, nullptr, hInst, nullptr);
			checkbox = CreateWindowW(L"button", L"Преобразовывать в заглавные", 
				WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX | WS_BORDER,
				10, pos.bottom - 80, pos.right - 20, 30, hWnd, nullptr, hInst, nullptr);
			edit = CreateWindowW(L"edit", L"Текстовое поле", 
				WS_CHILD | WS_VISIBLE | WS_BORDER,
				10, pos.bottom - 40, pos.right / 3 * 2 - 20, 30, hWnd, nullptr, hInst, nullptr);
			button = CreateWindowW(L"button", L"Добавить", 
				WS_CHILD | WS_VISIBLE,
				pos.right / 3 * 2, pos.bottom - 40, pos.right / 3 - 10, 30, hWnd, nullptr, hInst, nullptr);
			break;
		}
		case WM_COMMAND:
		{
			if (lParam == (LPARAM)button)
			{
				GetWindowTextW(edit, text, 30);
				if ((WORD)SendMessageW(checkbox, BM_GETCHECK, 0, 0L)) CharUpperW(text);
				SetWindowTextW(edit, nullptr);
				SendMessageW(listbox, LB_ADDSTRING, 0, (LPARAM)text);
			}
			else if (lParam == (LPARAM)listbox && HIWORD(wParam) == LBN_DBLCLK)
			{
				WORD ind = (WORD)SendMessageW(listbox, LB_GETCURSEL, 0, 0L);
				SendMessageW(listbox, LB_DELETESTRING, ind, 0L);
			}
			break;
		}
		case WM_DESTROY:
		{
			HANDLE hFile = CreateFileW(L"result.txt", GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
			if (hFile != INVALID_HANDLE_VALUE)
			{
				unsigned short p = 0xFEFF;
				WriteFile(hFile, (LPCVOID)&p, 2, nullptr, NULL);
				for (int i = 0; i < SendMessageW(listbox, LB_GETCOUNT, 0, 0L); i++)
				{
					WCHAR buffer[30];
					WORD len = (WORD)SendMessageW(listbox, LB_GETTEXT, i, (LPARAM)buffer);
					WriteFile(hFile, buffer, sizeof(WCHAR) * len, nullptr, NULL);
					WriteFile(hFile, L"\r\n", 4, nullptr, NULL);
				}
				CloseHandle(hFile);
			}
			else MessageBoxW(hWnd, L"Не удалось создать файл!", szTitle, MB_OK);
			
			PostQuitMessage(0);
			break;
		}
		default: return DefWindowProcW(hWnd, message, wParam, lParam);
	}
	return 0;
}