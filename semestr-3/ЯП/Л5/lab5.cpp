#include <windows.h>
#include <commctrl.h>
#include <vector>
#include <algorithm>
#include "resource.h"

#pragma comment(lib,"Comctl32.lib")

#define MAX_LOADSTRING 100

struct Student
{
	WCHAR fullname[48];
	WCHAR group[11];
	INT recordbook;
	SYSTEMTIME date;
};

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна
BOOL is_saved = TRUE;

LPCWSTR header[] = { L"ФИО", L"Группа", L"№ зачетной книжки", L"Дата рождения" };
WCHAR check[85] = L"Once you do know what the question actually is, you'll know what the answer means...";

std::vector<Student> data;

// Отправить объявления функций, включенных в этот модуль кода:
ATOM InitClass(HINSTANCE hInstance, WNDPROC WndProc, LPCWSTR ClassName);
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK Process(HWND, UINT, WPARAM, LPARAM);

HWND CreateListView(HWND);
BOOL AddListViewItem(HWND);
BOOL UpdateListViewItem(HWND, unsigned);
BOOL EnableMenu(HWND, BOOL);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_LAB5, szWindowClass, MAX_LOADSTRING);

	if (!InitClass(hInstance, WndProc, szWindowClass)) return FALSE;//регистрируем класс
	if (!InitInstance(hInstance, nCmdShow))	return FALSE;//создаем главное окно

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB5));

    MSG msg;

    // Цикл основного сообщения:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}

ATOM InitClass(HINSTANCE hInstance, WNDPROC WndProc, LPCWSTR ClassName)
{
    WNDCLASSEXW wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB5));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_LAB5);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
	return RegisterClassExW(&wcex);
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

HWND CreateListView(HWND hParent)
{
	INITCOMMONCONTROLSEX icex;
	icex.dwICC = ICC_LISTVIEW_CLASSES;
	InitCommonControlsEx(&icex);

	RECT rcl;
	GetClientRect(hParent, &rcl);
	HWND hListView = CreateWindowW(WC_LISTVIEW,	L"", WS_CHILD | LVS_REPORT,
		0, 0, rcl.right - rcl.left, rcl.bottom - rcl.top, hParent, nullptr, hInst, NULL);
	if (!hListView) return hListView;

	//создаем сетку и выбор всей строки
	SendMessage(hListView, LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	INT idx = -1;
	LVCOLUMN lvc;
	lvc.mask = LVCF_TEXT | LVCF_WIDTH;
	lvc.cx = (rcl.right - rcl.left) / 4;
	lvc.cchTextMax = 48;
	for (INT i = 0; i < 4; i++)
	{
		lvc.pszText = (LPWSTR)header[i];
		idx = ListView_InsertColumn(hListView, i, &lvc);
		if (idx == -1) break;
	}
	return (hListView);
}

BOOL AddListViewItem(HWND hListView)
{
	int idx = data.size() - 1;
	LVITEM lvi;
	lvi.pszText = data[idx].fullname;
	lvi.mask = LVIF_TEXT;
	lvi.iItem = idx;
	lvi.iSubItem = 0;
	
	if (ListView_InsertItem(hListView, &lvi) == -1) return FALSE;

	WCHAR buff[64];
	ListView_SetItemText(hListView, idx, 1, data[idx].group);
	_itow_s(data[idx].recordbook, buff, 64, 10);
	ListView_SetItemText(hListView, idx, 2, buff);
	GetDateFormat(LOCALE_SYSTEM_DEFAULT, 0, &data[idx].date, L"dd.MM.yyyy", buff, 64);
	ListView_SetItemText(hListView, idx, 3, buff);
	return TRUE;
}

BOOL UpdateListViewItem(HWND hListView, unsigned i)
{
	LVITEM lvi;
	lvi.pszText = data[i].fullname;
	lvi.mask = LVIF_TEXT;
	lvi.iItem = i;
	lvi.iSubItem = 0;

	if (ListView_SetItem(hListView, &lvi) == -1) return FALSE;

	WCHAR buff[64];
	ListView_SetItemText(hListView, i, 1, data[i].group);
	_itow_s(data[i].recordbook, buff, 64, 10);
	ListView_SetItemText(hListView, i, 2, buff);
	GetDateFormat(LOCALE_SYSTEM_DEFAULT, 0, &data[i].date, L"dd.MM.yyyy", buff, 64);
	ListView_SetItemText(hListView, i, 3, buff);
	return TRUE;
}

BOOL EnableMenu(HWND hWnd, BOOL value)
{
	HMENU hMenu = GetMenu(hWnd);
	if (value == TRUE)
	{
		EnableMenuItem(hMenu, IDM_SAVE, MF_ENABLED);
		EnableMenuItem(hMenu, IDM_NAME_ASC, MF_ENABLED);
		EnableMenuItem(hMenu, IDM_NAME_DESC, MF_ENABLED);
		EnableMenuItem(hMenu, IDM_GROUP_ASC, MF_ENABLED);
		EnableMenuItem(hMenu, IDM_GROUP_DESC, MF_ENABLED);
		return TRUE;
	}
	else
	{
		EnableMenuItem(hMenu, IDM_SAVE, MF_DISABLED | MF_GRAYED);
		EnableMenuItem(hMenu, IDM_NAME_ASC, MF_DISABLED | MF_GRAYED);
		EnableMenuItem(hMenu, IDM_NAME_DESC, MF_DISABLED | MF_GRAYED);
		EnableMenuItem(hMenu, IDM_GROUP_ASC, MF_DISABLED | MF_GRAYED);
		EnableMenuItem(hMenu, IDM_GROUP_DESC, MF_DISABLED | MF_GRAYED);
		return TRUE;
	}
	return FALSE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HWND hListView;
    switch (message)
    {
		case WM_CREATE:
		{
			if (!(hListView = CreateListView(hWnd)))
				MessageBox(hWnd, L"Не удалось создать список для отображения!", L"Ошибка", MB_OK | MB_ICONERROR);
			ShowWindow(hListView, SW_SHOWDEFAULT);
			EnableMenu(hWnd, FALSE);
			break;
		}
		case WM_COMMAND:
		{
			int wmId = LOWORD(wParam);
			switch (wmId)
			{
				case IDM_ADD:
				{
					if (DialogBoxParam(hInst, MAKEINTRESOURCE(IDD_DATA), hWnd, Process, -1) == TRUE)
					{
						AddListViewItem(hListView);
						if (data.size() == 1) EnableMenu(hWnd, TRUE);
						is_saved = FALSE;
					}
					break;
				}
				case IDM_EDIT:
				{
					INT pos = ListView_GetNextItem(hListView, -1, LVNI_SELECTED);
					if (DialogBoxParam(hInst, MAKEINTRESOURCE(IDD_DATA), hWnd, Process, pos) == TRUE)
					{
						UpdateListViewItem(hListView, pos);
						is_saved = FALSE;
					}
					break;
				}
				case IDM_DELETE:
				{
					if (MessageBox(hWnd, L"Вы действительно хотите удалить выделенные строки?", L"Предупреждение",
						MB_YESNO | MB_ICONWARNING | MB_DEFBUTTON2) == IDYES)
					{
						INT pos = ListView_GetNextItem(hListView, -1, LVNI_SELECTED);
						while (pos != -1)
						{
							data.erase(data.begin() + pos);
							ListView_DeleteItem(hListView, pos);
							pos = ListView_GetNextItem(hListView, -1, LVNI_SELECTED);
						}
						if (data.size() == 0) EnableMenu(hWnd, FALSE);
						is_saved = FALSE;
					}
					break;
				}
				case IDM_OPEN:
				{
					HANDLE hFile = CreateFile(L"data.bin", GENERIC_READ, NULL, NULL, OPEN_EXISTING,
						FILE_ATTRIBUTE_NORMAL, 0);
					if (!hFile)
					{
						MessageBox(hWnd, L"Не удалось открыть файл с данных!", L"Ошибка", MB_OK | MB_ICONERROR);
						break;
					}
					WCHAR buff[85];
					ReadFile(hFile, (LPVOID)buff, sizeof(buff), nullptr, NULL);
					if (wcscmp(buff, check) != 0)
					{
						MessageBox(hWnd, L"Не удалось прочитать файл с данными!", L"Ошибка", MB_OK | MB_ICONERROR);
						CloseHandle(hFile);
						break;
					}

					data.erase(data.begin(), data.end());
					ListView_DeleteAllItems(hListView);

					unsigned size = 0;
					ReadFile(hFile, (LPVOID)&size, sizeof(size), nullptr, NULL);
					Student tmp;
					for (unsigned i = 0; i < size; i++)
					{
						ReadFile(hFile, (LPVOID)&tmp, sizeof(Student), nullptr, NULL);
						data.push_back(tmp);
						AddListViewItem(hListView);
					}
					if(data.size() > 0) EnableMenu(hWnd, TRUE);
					CloseHandle(hFile);
					is_saved = TRUE;
					break;
				}
				case IDM_SAVE:
				{
					HANDLE hFile = CreateFile(L"data.bin", GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS,
						FILE_ATTRIBUTE_NORMAL, 0);
					WriteFile(hFile, (LPVOID)check, sizeof(check), nullptr, NULL);
					unsigned size = data.size();
					WriteFile(hFile, (LPVOID)&size, sizeof(size), nullptr, NULL);
					for (unsigned i = 0; i < size; i++)
						WriteFile(hFile, (LPVOID)&data[i], sizeof(Student), nullptr, NULL);
					CloseHandle(hFile);
					MessageBox(hWnd, L"Данные сохранены!", L"Уведомление", MB_OK | MB_ICONINFORMATION);
					is_saved = TRUE;
					break;
				}
				case IDM_NAME_ASC:
				{
					std::sort(data.begin(), data.end(), 
						[](const Student &a, const Student &b) { return (wcscmp(a.fullname, b.fullname) < 0) ? 1 : 0; });
					for (unsigned i = 0; i < data.size(); i++) UpdateListViewItem(hListView, i);
					is_saved = FALSE;
					break;
				}
				case IDM_NAME_DESC:
				{
					std::sort(data.begin(), data.end(),
						[](const Student &a, const Student &b) { return (wcscmp(a.fullname, b.fullname) > 0) ? 1 : 0; });
					for (unsigned i = 0; i < data.size(); i++) UpdateListViewItem(hListView, i);
					is_saved = FALSE;
					break;
				}
				case IDM_GROUP_ASC:
				{
					std::sort(data.begin(), data.end(),
						[](const Student &a, const Student &b) { return (wcscmp(a.group, b.group) < 0) ? 1 : 0; });
					for (unsigned i = 0; i < data.size(); i++) UpdateListViewItem(hListView, i);
					is_saved = FALSE;
					break;
				}
				case IDM_GROUP_DESC:
				{
					std::sort(data.begin(), data.end(),
						[](const Student &a, const Student &b) { return (wcscmp(a.group, b.group) > 0) ? 1 : 0; });
					for (unsigned i = 0; i < data.size(); i++) UpdateListViewItem(hListView, i);
					is_saved = FALSE;
					break;
				}
				case IDM_EXIT:
				{
					DestroyWindow(hWnd);
					break;
				}
				default: return DefWindowProc(hWnd, message, wParam, lParam);
			}
			break;
		}
		case WM_NOTIFY:
		{
			LPNMHDR notify = (LPNMHDR)lParam;
			if (notify->code == NM_RCLICK)
			{
				INT idx = ListView_GetNextItem(hListView, -1, LVNI_SELECTED);
				HMENU hMenu = LoadMenu(NULL, MAKEINTRESOURCE(IDC_CONTEXT));

				if (idx == -1)//ничего не выбрано
				{
					EnableMenuItem(hMenu, IDM_EDIT, MF_DISABLED | MF_GRAYED);
					EnableMenuItem(hMenu, IDM_DELETE, MF_DISABLED | MF_GRAYED);
				}
				hMenu = GetSubMenu(hMenu, 0);

				POINT crs;
				GetCursorPos(&crs);
				TrackPopupMenu(hMenu, TPM_RIGHTBUTTON | TPM_TOPALIGN | TPM_LEFTALIGN, crs.x, crs.y, 0, hWnd, NULL);
				DestroyMenu(hMenu);
			}
			break;
		}
		case WM_SIZE:
		{
			RECT rcl;
			GetClientRect(hWnd, &rcl);
			SetWindowPos(hListView, 0, 0, 0, rcl.right, rcl.bottom, SWP_NOMOVE | SWP_NOZORDER);
			//не передвигает окно, не меняет очередность окон
			for (INT i = 0; i < 4; i++)
				ListView_SetColumnWidth(hListView, i, (rcl.right - rcl.left) / 4);
			break;
		}
		case WM_DESTROY:
		{
			if (is_saved == FALSE && MessageBox(hWnd, L"Данные не сохранены. Хотите сохранить?", L"Предупреждение",
				MB_YESNO | MB_ICONWARNING | MB_DEFBUTTON1) == IDYES)
				SendMessage(hWnd, WM_COMMAND, IDM_SAVE, NULL);
			else PostQuitMessage(0);
			break;
		}
		default: return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

INT_PTR CALLBACK Process(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	static INT pos;
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
		case WM_INITDIALOG:
		{
			pos = lParam;
			if (pos != -1)
			{
				WCHAR buff[64];
				unsigned len = wcslen(data[pos].fullname) + 1;
				for (unsigned i = 0, start = 0, count = 0; i < len; i++)
				{
					if (data[pos].fullname[i] == ' ' || i == len - 1)
					{
						wcsncpy_s(buff, &data[pos].fullname[start], i - start);
						SetDlgItemText(hDlg, (!count) ? IDC_LASTNAME : (count == 1) ? IDC_FIRSTNAME : IDC_MIDDLENAME, buff);
						start = i + 1;
						count++;
					}
				}
				SetDlgItemText(hDlg, IDC_GROUP, data[pos].group);
				_itow_s(data[pos].recordbook, buff, 64, 10);
				SetDlgItemText(hDlg, IDC_RECORDBOOK, buff);
				DateTime_SetSystemtime(GetDlgItem(hDlg, IDC_DATE), GDT_VALID, &data[pos].date);
				SetWindowText(hDlg, L"Изменение элемента");
			}
			return (INT_PTR)TRUE;
		}
		case WM_COMMAND:
		{
			if (LOWORD(wParam) == IDOK)
			{
				Student tmp;
				WCHAR buff[64], fullname[64];
				GetDlgItemText(hDlg, IDC_LASTNAME, buff, 64);
				if (!wcslen(buff) || wcslen(buff) > 15)
				{
					MessageBox(hDlg, L"Некорректно введено поле 'Фамилия'!", L"Ошибка", MB_OK | MB_ICONERROR);
					return (INT_PTR)FALSE;
				}
				wcscpy_s(fullname, buff);
				wcscat_s(fullname, L" ");
				GetDlgItemText(hDlg, IDC_FIRSTNAME, buff, 64);
				if (!wcslen(buff) || wcslen(buff) > 15)
				{
					MessageBox(hDlg, L"Некорректно введено поле 'Имя'!", L"Ошибка", MB_OK | MB_ICONERROR);
					return (INT_PTR)FALSE;
				}
				wcscat_s(fullname, buff);
				wcscat_s(fullname, L" ");
				GetDlgItemText(hDlg, IDC_MIDDLENAME, buff, 64);
				if (!wcslen(buff) || wcslen(buff) > 15)
				{
					MessageBox(hDlg, L"Некорректно введено поле 'Отчество'!", L"Ошибка", MB_OK | MB_ICONERROR);
					return (INT_PTR)FALSE;
				}
				wcscat_s(fullname, buff);
				wcscpy_s(tmp.fullname, fullname);
				GetDlgItemText(hDlg, IDC_GROUP, buff, 64);
				if (!wcslen(buff) || wcslen(buff) > 10)
				{
					MessageBox(hDlg, L"Некорректно введено поле 'Группа'!", L"Ошибка", MB_OK | MB_ICONERROR);
					return (INT_PTR)FALSE;
				}
				wcscpy_s(tmp.group, buff);
				GetDlgItemText(hDlg, IDC_RECORDBOOK, buff, 64);
				tmp.recordbook = _wtoi(buff);
				if (tmp.recordbook < 100000 || tmp.recordbook > 999999)
				{
					MessageBox(hDlg, L"Некорректно введено поле '№ зачетной книжки'!", L"Ошибка", MB_OK | MB_ICONERROR);
					return (INT_PTR)FALSE;
				}
				if (DateTime_GetSystemtime(GetDlgItem(hDlg, IDC_DATE), &tmp.date) != GDT_VALID)
				{
					MessageBox(hDlg, L"Некорректно введено поле 'Дата рождения'!", L"Ошибка", MB_OK | MB_ICONERROR);
					return (INT_PTR)FALSE;
				}
				if (pos != -1) data[pos] = tmp;
				else data.push_back(tmp);
				EndDialog(hDlg, LOWORD(wParam));
				return (INT_PTR)TRUE;
			}
			else if (LOWORD(wParam) == IDCANCEL)
			{
				EndDialog(hDlg, LOWORD(wParam));
				return (INT_PTR)FALSE;
			}
			break;
		}
	}
	return (INT_PTR)FALSE;
}
