#include <sstream>
#include <string>
#include <ctime>
#include <Windows.h>

// Глобальные переменные:
HINSTANCE hInst;//текущий экземпляр
LPCWSTR szTitle = L"Программа (вариант 1)";
LPCWSTR szWindowClass = L"WindowClass";
LPCWSTR szTextClass = L"TextClass";

UINT width = 800;
UINT height = 600;

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
	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX,
		CW_USEDEFAULT, CW_USEDEFAULT, width, height, nullptr, nullptr, hInstance, nullptr);
	if (!hWnd) return FALSE;
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_PAINT:
		{
			HANDLE hFile = CreateFileW(L"list.txt", GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
			if (hFile != INVALID_HANDLE_VALUE)
			{
				DWORD px = 0, py = 0, ox = 0, oy = 0;
				DWORD size = GetFileSize(hFile, NULL);
				WCHAR *buffer = new WCHAR[size / 2 + 1];
				ReadFile(hFile, buffer, size, nullptr, NULL);
				buffer[size / 2] = L'\0';
				std::wstring str = std::wstring(buffer);
				std::wstringstream ss(str);
				delete[] buffer;

				PAINTSTRUCT ps;
				HDC hdc = BeginPaint(hWnd, &ps);
				srand(time(NULL));
				while (!ss.eof())
				{
					ss >> px;
					if (ss.fail())
					{
						ss.clear();
						ss.ignore(1, '\n');
						continue;
					}
					ss >> py;
					if (ss.fail())
					{
						ss.clear();
						ss.ignore(1, '\n');
						continue;
					}
					if (!ox || !oy)
					{
						ox = px;
						oy = py;
						MoveToEx(hdc, ox, oy, NULL);
					}
					HPEN hpen = CreatePen(PS_SOLID, 2, RGB(rand() % 256, rand() % 256, rand() % 256)); \
						SelectObject(hdc, hpen);
					LineTo(hdc, px, py);
					DeleteObject(hpen);
				}
				HPEN hpen = CreatePen(PS_SOLID, 2, RGB(rand() % 256, rand() % 256, rand() % 256)); \
					SelectObject(hdc, hpen);
				LineTo(hdc, ox, oy);
				DeleteObject(hpen);
				EndPaint(hWnd, &ps);
				CloseHandle(hFile);
			}
			else
			{
				MessageBoxW(hWnd, L"Не удалось открыть файл list.txt!", szTitle, MB_OK);
				PostQuitMessage(0);
			}
			break;
		}
		case WM_DESTROY:
		{			
			PostQuitMessage(0);
			break;
		}
		default: return DefWindowProcW(hWnd, message, wParam, lParam);
	}
	return 0;
}