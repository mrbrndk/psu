//Исходные данные: программа должна реализовать игру «Линии» стандартного типа. 
//При начале новой игры игрок должен, по желанию, указать размер игрового поля.
//Количество цветов шаров не менее пяти. 
//В программе должны быть предусмотрены настройки: размер поля, звук, длина уничтожаемой линии (4 - 6).
//Реализовать подсчет очков и ведение таблицы рекордов на десять записей.

#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include <cmath>
#include <ctime>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
#include "resource.h"

#pragma comment(lib,"Comctl32.lib")
#pragma comment(lib, "D:/Programs/OpenGL/glut32.lib")
#include <D:/Programs/OpenGL/glut.h>

#define MAX_LOADSTRING 100
#define COLOR_SIZE 7
#define RECORD_AMOUNT 10

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

HGLRC hGLRC;
HDC hDC;

GLint fw = 40;//ширина поля
GLint fh = 40;//высота поля
GLint size = 9;//9x9 11x11 15x15
GLint radius = 15;//радиус шаров в поле
GLuint base; //база списка отображения для шрифта

GLint width = 200;//ширина окна
GLint height = 200;//высота окна + шапка для текста

int score = 0;//счет
int lineballs = 5;//минимальная длина строки которую надо собрать
int freefields = size * size;//изначально все свободны
int choice[2] = { -1, -1 };//для выбора перемещаемого шара
bool sound = true;//по умолчанию включен

int table[15][15];
int nextball[3];
int colors[COLOR_SIZE][3] = {	{255, 0, 0},//красный
								{255, 165, 0},//оранжевый
								{255, 255, 0},//желтый
								{0, 128, 0},//зеленый
								{66, 170, 255},//голубой
								{0, 0, 255},//синий
								{139, 0, 255} };//фиолетовый
LPCWSTR header[] = { L"Место", L"Имя", L"Очки" };
WCHAR check[85] = L"Once you do know what the question actually is, you'll know what the answer means...";

struct Record
{
	WCHAR name[32];
	INT result;
};
Record records[RECORD_AMOUNT];

// Отправить объявления функций, включенных в этот модуль кода:
ATOM InitClass(HINSTANCE hInstance, WNDPROC WndProc, LPCWSTR ClassName);
BOOL InitInstance(HINSTANCE, int);
BOOL ListView(HWND);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK NewGame(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK Records(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK RecordName(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK Settings(HWND, UINT, WPARAM, LPARAM);

int SetWindowPixelFormat();
void CreateGame();
void AddNextBall();
void CheckRecord(HWND hWnd);
void MoveBall(HWND hWnd, int x, int y);
bool IsLinedUp();
bool IsAvailable(int row1, int col1, int row2, int col2);
GLvoid SetFont();
GLvoid KillFont();
GLvoid Resize(HWND hWnd);
GLvoid Render();
GLvoid DrawBall(GLint color, GLint row, GLint column);
GLvoid DrawString(const WCHAR *fmt, ...);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// Инициализация глобальных строк
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_APP_CLASS, szWindowClass, MAX_LOADSTRING);

	if (!InitClass(hInstance, WndProc, szWindowClass)) return FALSE;//регистрируем класс
	if (!InitInstance(hInstance, nCmdShow))	return FALSE;//создаем главное окно

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_APP_CLASS));

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

	Render();// Нарисовать сцену
	SwapBuffers(hDC);// Переключить буфер экрана
	return (int)msg.wParam;
}

ATOM InitClass(HINSTANCE hInstance, WNDPROC WndProc, LPCWSTR ClassName)
{
	WNDCLASSEXW wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_APP_CLASS);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);
	return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, 
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		CW_USEDEFAULT, 0, width, height, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd) return FALSE;
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	return TRUE;
}

BOOL ListView(HWND hParent)
{
	INITCOMMONCONTROLSEX icex;
	icex.dwICC = ICC_LISTVIEW_CLASSES;
	InitCommonControlsEx(&icex);

	RECT rcl;
	GetClientRect(hParent, &rcl);
	HWND hListView = CreateWindowW(WC_LISTVIEW, L"", WS_CHILD | LVS_REPORT,
		0, 0, rcl.right - rcl.left, rcl.bottom - rcl.top, hParent, nullptr, hInst, NULL);
	if (!hListView) return FALSE;
	ShowWindow(hListView, SW_SHOWDEFAULT);
	//создаем сетку и выбор всей строки
	SendMessage(hListView, LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	//задаем шапку
	INT idx = -1;
	LVCOLUMN lvc;
	lvc.mask = LVCF_TEXT | LVCF_WIDTH;
	lvc.cx = (rcl.right - rcl.left) / 3;
	lvc.cchTextMax = 32;
	for (INT i = 0; i < 3; i++)
	{
		lvc.pszText = (LPWSTR)header[i];
		idx = ListView_InsertColumn(hListView, i, &lvc);
		if (idx == -1) break;
	}

	WCHAR buff[32];
	//задаем значения таблицы
	for (int i = 0; i < RECORD_AMOUNT; i++)
	{
		LVITEM lvi;
		_itow_s(i + 1, buff, 32, 10);
		lvi.pszText = buff;
		lvi.mask = LVIF_TEXT;
		lvi.iItem = i + 1;
		lvi.iSubItem = 0;
		if (ListView_InsertItem(hListView, &lvi) == -1) return FALSE;
		ListView_SetItemText(hListView, i, 1, records[i].name);
		_itow_s(records[i].result, buff, 32, 10);
		ListView_SetItemText(hListView, i, 2, buff);
	}
	return TRUE;
}

int SetWindowPixelFormat()
{
	int m_GLPixelIndex;
	PIXELFORMATDESCRIPTOR pfd;

	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL |	PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;
	pfd.cRedBits = 8;
	pfd.cRedShift = 16;
	pfd.cGreenBits = 8;
	pfd.cGreenShift = 8;
	pfd.cBlueBits = 8;
	pfd.cBlueShift = 0;
	pfd.cAlphaBits = 0;
	pfd.cAlphaShift = 0;
	pfd.cAccumBits = 64;
	pfd.cAccumRedBits = 16;
	pfd.cAccumGreenBits = 16;
	pfd.cAccumBlueBits = 16;
	pfd.cAccumAlphaBits = 0;
	pfd.cDepthBits = 32;
	pfd.cStencilBits = 8;
	pfd.cAuxBuffers = 0;
	pfd.iLayerType = PFD_MAIN_PLANE;
	pfd.bReserved = 0;
	pfd.dwLayerMask = 0;
	pfd.dwVisibleMask = 0;
	pfd.dwDamageMask = 0;

	m_GLPixelIndex = ChoosePixelFormat(hDC, &pfd);
	if (m_GLPixelIndex == 0)
	{
		m_GLPixelIndex = 1;
		if (DescribePixelFormat(hDC, m_GLPixelIndex, sizeof(PIXELFORMATDESCRIPTOR), &pfd) == 0)
			return 0;
	}
	if (SetPixelFormat(hDC, m_GLPixelIndex, &pfd) == FALSE)	return 0;
	return 1;
}

void CreateGame()
{
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++) table[i][j] = 0;
	srand(time(NULL));
	int count = 0;
	freefields = size * size;
	score = 0;
	choice[0] = -1;
	choice[1] = -1;
	while(count < 3)
	{
		int row = rand() % size;
		int col = rand() % size;
		if (table[row][col] == 0)
		{
			table[row][col] = rand() % COLOR_SIZE + 1;
			nextball[count] = rand() % COLOR_SIZE + 1;
			freefields--;
			count++;
		}
	}
}

void AddNextBall()
{
	srand(time(NULL));
	int count = 0;
	while (count < 3 && freefields > 0)
	{
		int row = rand() % size;
		int col = rand() % size;
		if (table[row][col] == 0)
		{
			table[row][col] = nextball[count];
			nextball[count] = rand() % COLOR_SIZE + 1;
			freefields--;
			count++;
		}
	}
}

void CheckRecord(HWND hWnd)
{
	if (score > records[RECORD_AMOUNT - 1].result)
	{//если счет больше хотя бы последнего рекорда
		for (int i = 0; i < RECORD_AMOUNT; i++)
		{
			if (score > records[i].result)
			{
				for (int j = RECORD_AMOUNT - 1; j >= i; j--)
				{//сдвигаем строки на одну вниз
					wcscpy_s(records[j + 1].name, 32, records[j].name);
					records[j + 1].result = records[j].result;
				}
				wcscpy_s(records[i].name, 32, L"Аноним");
				records[i].result = score;
				DialogBoxParam(hInst, MAKEINTRESOURCE(IDD_RECORDNAME), hWnd, RecordName, i);
				break;
			}
		}
	}
}

void MoveBall(HWND hWnd, int x, int y)
{
	if (!freefields) return;//если свободных полей нет - игра окончена
	int col = x / fw;//определяем по какому шару клик
	int row = (height - y) / fh;
	if (row >= 0 && row < size && col >= 0 && col < size)
	{//если такое поле существует
		if (choice[0] != -1 && choice[1] != -1 && //если выбран шар
			(row != choice[0] || col != choice[1]) &&//и новая позиция не равна выбранной
			table[row][col] == 0)//и новая позиция пуста
		{
			if (IsAvailable(choice[0], choice[1], row, col))//и к новой позиции есть путь
			{
				table[row][col] = table[choice[0]][choice[1]];
				table[choice[0]][choice[1]] = 0;
				choice[0] = -1;
				choice[1] = -1;
				if (!IsLinedUp())
				{
					AddNextBall();
					if (sound)
						PlaySound(MAKEINTRESOURCE(IDR_SOUND_MOVE), NULL, SND_ASYNC | SND_RESOURCE);
				}
				InvalidateRect(hWnd, NULL, TRUE);//перерисовываем
				if (!freefields)
				{
					MessageBox(hWnd, L"Игра окончена!", L"Уведомление", MB_OK | MB_ICONINFORMATION);
					CheckRecord(hWnd);
				}
			}
			else if (sound)
				PlaySound(MAKEINTRESOURCE(IDR_SOUND_CANTMOVE), NULL, SND_ASYNC | SND_RESOURCE);
		}
		else if (table[row][col] > 0)//если есть шар в этом поле
		{
			choice[0] = row;
			choice[1] = col;
			Render();
		}
	}
}

bool IsLinedUp()
{
	bool is_linedup = false;
	for (int r = 0; r < size; r++)//строка
	{
		for (int c = 0; c < size; c++)//столбец
		{
			if (table[r][c] == 0) continue;//если шара нет пропускаем
			int color = table[r][c];
			int chain[4] = { 1, 1, 1, 1 };//направления поиска: с, в, сз, св
			int totalchain[4] = { 0, 0, 0, 0 };
			int maxchain = 0;
			for (int k = 1; k < size + 1; k++)//комбо
			{// + 1 для доп. шаг выставляющего всем направлениям нули
				//если в следующей по направлению ячейчке тот же цвет увеличиваем размер цепочки
				//иначе если цепь достаточного размер записываем итог и сбрасываем счетчик чтобы не считало заново
				if (r + k < size && table[r + k][c] == color && chain[0] > 0) chain[0]++;//север
				else
				{
					if (chain[0] >= lineballs) totalchain[0] = chain[0];
					chain[0] = 0;
				}
				if (c + k < size && table[r][c + k] == color && chain[1] > 0) chain[1]++;//восток
				else
				{
					if (chain[1] >= lineballs) totalchain[1] = chain[1];
					chain[1] = 0;
				}
				if (r + k < size && c - k > 0 && table[r + k][c - k] == color && chain[2] > 0) chain[2]++;//северо-запад
				else
				{
					if (chain[2] >= lineballs) totalchain[2] = chain[2];
					chain[2] = 0;
				}
				if (r + k < size && c + k < size && table[r + k][c + k] == color && chain[3] > 0) chain[3]++;//северо-восток
				else
				{
					if (chain[3] >= lineballs) totalchain[3] = chain[3];
					chain[3] = 0;
				}
				if (chain[0] + chain[1] + chain[2] + chain[3] == 0) break;
				//если поиск по всем направлениям завершен цикл прерываем.
			}
			if (totalchain[0] + totalchain[1] + totalchain[2] + totalchain[3] > 0)
			{//если что-нибудь найдено
				for (int i = 0; i < 4; i++)
					if (totalchain[i] > maxchain) maxchain = i;
				int ro = 0, co = 0;
				//сдвиги по строкам и столбцам, определяют в каком направлении будут устанавливаться нули
				switch (maxchain)
				{
					case 0: ro = 1; co = 0; break;
					case 1: ro = 0; co = 1; break;
					case 2: ro = 1; co = -1; break;
					case 3: ro = 1; co = 1; break;
				}
				for (int i = 0; i < totalchain[maxchain]; i++)
					table[i * ro + r][i * co + c] = 0;
				score += totalchain[maxchain] * (totalchain[maxchain] - lineballs + 1);
				freefields += totalchain[maxchain];
				if (sound)
					PlaySound(MAKEINTRESOURCE(IDR_SOUND_DESTROY), NULL, SND_ASYNC | SND_RESOURCE);
				is_linedup = true;
			}
		}
	}
	return is_linedup;
}

bool IsAvailable(int row1, int col1, int row2, int col2)
{
	int path[225][2];//путь, худший случай 15x15=225, зависимость от size
	bool branch[225];//наличие разветвлений, худший случай 9x9=81, зависимость от size
	int a[15][15];//массив с возможностью ходов
	int count = 0;
	//далее начальная инициализация
	path[0][0] = row1;
	path[0][1] = col1;
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			a[i][j] = (table[i][j] > 0) ? 1 : 0;
	a[row1][col1] = 2;
	//далее поиск пути
	while (path[count][0] != row2 || path[count][1] != col2)
	{
		int row = path[count][0];
		int col = path[count][1];
		branch[count] = false;
		//далее определяем наличие путей и выбираем путь
		if (row - 1 >= 0 && a[row - 1][col] == 0)
		{//проверяем что этот ход не будет выходить из таблицы, существует и не заблокирован 
			path[count + 1][0] = row - 1;//вниз
			path[count + 1][1] = col;
			branch[count] = true;
		}
		else if (row + 1 < size && a[row + 1][col] == 0)
		{
			path[count + 1][0] = row + 1;//вверх
			path[count + 1][1] = col;
			branch[count] = true;
		}
		else if (col - 1 >= 0 && a[row][col - 1] == 0)
		{
			path[count + 1][0] = row;//влево
			path[count + 1][1] = col - 1;
			branch[count] = true;
		}
		else if (col + 1 < size && a[row][col + 1] == 0)
		{
			path[count + 1][0] = row;//вправо
			path[count + 1][1] = col + 1;
			branch[count] = true;
		}
		
		if (branch[count] == true)
		{//далее делаем ход
			branch[count] = false;
			count++;
			a[path[count][0]][path[count][1]] = 2;//блокируем новую ячейку
		}
		else
		{//если походить некуда
			if (count > 0)//если есть ходы назад
			{
				a[path[count][0]][path[count][1]] = 1;//отмечаем что пути нет
				path[count][0] = 0;
				path[count][1] = 0;
				count--;
			}
			else return false;
		}
	}
	return true;
}

GLvoid SetFont()
{
	HFONT font;  // Идентификатор шрифта
	base = glGenLists(0x0450);  // Выделим место для символов
	font = CreateFont(
		-16,          // Высота шрифта
		0,            // Ширина шрифта
		0,            // Угол отношения
		0,            // Угол наклона
		FW_BOLD,      // Ширина шрифта
		FALSE,        // Курсив
		FALSE,        // Подчеркивание
		FALSE,        // Перечеркивание
		DEFAULT_CHARSET,      // Идентификатор набора символов
		OUT_TT_PRECIS,      // Точность вывода
		CLIP_DEFAULT_PRECIS,    // Точность отсечения
		ANTIALIASED_QUALITY,    // Качество вывода
		FF_DONTCARE | DEFAULT_PITCH,  // Семейство и шаг
		L"Century Gothic"      // Имя шрифта
	);

	SelectObject(hDC, font);        // Выбрать шрифт, созданный нами
	wglUseFontBitmaps(hDC, 0x0, 0x0450, base); // Построить символы начиная с пробела
}

GLvoid KillFont()
{
	glDeleteLists(base, 0x0450);  // Удаление всех 96 списков отображения
}

GLvoid Resize(HWND hWnd = NULL)
{
	if (hWnd != NULL)
	{
		width = fw * size;
		height = fh * size + fh;
		SetWindowPos(hWnd, 0, 0, 0, width + 16, height + 59, SWP_NOMOVE | SWP_NOZORDER);
	}
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, width, 0, height);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

GLvoid Render()
{
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);// | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	//фон шапки
	glColor3ub(204, 204, 204);
	glBegin(GL_QUADS);
	glVertex2i(0, fh * size);
	glVertex2i(0, fh * size + fh);
	glVertex2i(fw * size, fh * size + fh);
	glVertex2i(fw * size, fh * size);
	glEnd();

	//рекорд и очки
	glColor3ub(0, 0, 0);
	int offset = (fh - (12 * 2)) / 3;
	glRasterPos2i(fw / 3, fh * size + (offset * 2 + 12));
	DrawString(L"РЕКОРД: %d", records[0].result);
	glRasterPos2i(fw / 3, fh * size + offset);
	DrawString(L"ОЧКИ: %d", score);

	//следующие шары
	DrawBall(nextball[0], size, size - 3);
	DrawBall(nextball[1], size, size - 2);
	DrawBall(nextball[2], size, size - 1);

	//выделяем выбранный шар, обязательно выше игровой сетки чтобы было под ней
	if (choice[0] != -1 && choice[1] != -1)
	{
		glColor3ub(170, 170, 170);
		glBegin(GL_QUADS);
		glVertex2i(choice[1] * fw, choice[0] * fh);
		glVertex2i(choice[1] * fw, choice[0] * fh + fh);
		glVertex2i(choice[1] * fw + fw, choice[0] * fh + fh);
		glVertex2i(choice[1] * fw + fw, choice[0] * fh);
		glEnd();
	}

	//сетка игрового поля
	glColor3ub(119, 119, 119);
	glBegin(GL_LINES);
	for (int i = 0; i < size; i++)
	{
		glVertex2i(i * fw, 0);//вертикальный линии
		glVertex2i(i * fw, fh * size);

		glVertex2i(0, i * fh);//горизонтальные
		glVertex2i(fw * size, i * fh);
	}
	glEnd();
	
	//шары на сетке
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			if(table[i][j] != 0) DrawBall(table[i][j], i, j);

	SwapBuffers(wglGetCurrentDC());
	glFlush(); //Очистить все очереди команд и буферы OpenGL
}

GLvoid DrawBall(GLint color, GLint row, GLint column)
{
	float x = fw * column + (fw / 2);
	float y = fh * row + (fh / 2);
	glColor3ub(colors[color - 1][0], colors[color - 1][1], colors[color - 1][2]);
	glBegin(GL_POLYGON);
	for (int i = 0; i < 50; i++)
	{
		float angle = 2.0 * 3.1415926 * float(i) / float(50);
		float dx = radius * cosf(angle);
		float dy = radius * sinf(angle);
		glVertex2f(x + dx, y + dy);
	}
	glEnd();
}

GLvoid DrawString(const WCHAR *fmt, ...)
{
	WCHAR text[256];      // Место для нашей строки
	va_list ap;          // Указатель на список аргументов
	if (fmt == NULL) return;
	va_start(ap, fmt);           // Разбор строки переменных
	wvsprintf(text, fmt, ap); // И конвертирование символов в реальные коды
	va_end(ap);                  // Результат помещается в строку
	glPushAttrib(GL_LIST_BIT);      // Протолкнуть биты списка отображения
	glListBase(base);          // Задать базу символа в 0
	glCallLists(wcslen(text), GL_UNSIGNED_SHORT, text);  // Текст списками отображения
	glPopAttrib(); // Возврат битов списка отображения
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	switch (message)
	{
		case WM_CREATE:
		{
			hDC = GetDC(hWnd);       // получаем контекст устройства нашего окна
			SetWindowPixelFormat();  // устанавливаем параметры контекста воспроизведения OpenGL
			hGLRC = wglCreateContext(hDC);// создаем контекст воспроизведения OpenGL
			wglMakeCurrent(hDC, hGLRC);   // делаем его текущим
			SetFont();//задаем шрифт
			//загружаем из файла рекорды
			HANDLE hFile = CreateFile(L"data.bin", GENERIC_READ, NULL, NULL, OPEN_EXISTING,
				FILE_ATTRIBUTE_NORMAL, 0);
			if (hFile)
			{
				WCHAR buff[85];
				ReadFile(hFile, (LPVOID)buff, sizeof(buff), nullptr, NULL);
				if (wcscmp(buff, check) == 0)
				{
					Record tmp;
					for (unsigned i = 0; i < RECORD_AMOUNT; i++)
					{
						ReadFile(hFile, (LPVOID)&tmp, sizeof(Record), nullptr, NULL);
						records[i] = tmp;
					}
				}
				CloseHandle(hFile);
			}
			CreateGame();
			break;
		}
		case WM_COMMAND:
		{
			int wmId = LOWORD(wParam);
			switch (wmId)
			{
				case IDM_NEWGAME:
				{
					DialogBox(hInst, MAKEINTRESOURCE(IDD_NEWGAME), hWnd, NewGame);
					InvalidateRect(hWnd, NULL, TRUE);
					break;
				}
				case IDM_RECORDS:
				{
					DialogBox(hInst, MAKEINTRESOURCE(IDD_RECORDS), hWnd, Records);
					break;
				}
				case IDM_SETTINGS:
				{
					DialogBox(hInst, MAKEINTRESOURCE(IDD_SETTINGS), hWnd, Settings);
					break;
				}
				default: return DefWindowProc(hWnd, message, wParam, lParam);
			}
			break;
		}
		case WM_LBUTTONDOWN:
		{
			MoveBall(hWnd, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
			break;
		}
		case WM_PAINT:
		{
			Resize(hWnd);
			hDC = BeginPaint(hWnd, &ps);
			Render();
			EndPaint(hWnd, &ps);
			break;
		}
		case WM_DESTROY:
		{
			if (hGLRC)
			{
				wglMakeCurrent(NULL, NULL);
				wglDeleteContext(hGLRC);
			}// освобождаем контекст устройства нашего окна
			KillFont();
			//сохраняем рекорды
			HANDLE hFile = CreateFile(L"data.bin", GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS,
				FILE_ATTRIBUTE_NORMAL, 0);
			if (hFile)
			{
				WriteFile(hFile, (LPVOID)check, sizeof(check), nullptr, NULL);
				for (unsigned i = 0; i < RECORD_AMOUNT; i++)
					WriteFile(hFile, (LPVOID)&records[i], sizeof(Record), nullptr, NULL);
				CloseHandle(hFile);
			}
			PostQuitMessage(0);
			break;
		}
		default: return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

INT_PTR CALLBACK NewGame(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
		case WM_INITDIALOG:
		{
			Button_SetCheck(GetDlgItem(hDlg, IDC_RADIO9), BST_CHECKED);
			return (INT_PTR)TRUE;
		}
		case WM_COMMAND:
		{
			if (LOWORD(wParam) == IDOK)
			{
				if (Button_GetCheck(GetDlgItem(hDlg, IDC_RADIO9))) size = 9;
				if (Button_GetCheck(GetDlgItem(hDlg, IDC_RADIO11))) size = 11;
				if (Button_GetCheck(GetDlgItem(hDlg, IDC_RADIO15))) size = 15;
				Resize(GetParent(hDlg));
				CreateGame();
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

INT_PTR CALLBACK Records(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
		case WM_INITDIALOG:
		{
			if (!ListView(hDlg))
				MessageBox(hDlg, L"Не удалось создать список для отображения!", L"Ошибка", MB_OK | MB_ICONERROR);
			return (INT_PTR)TRUE;
		}
		case WM_CLOSE:
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK RecordName(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	static INT place;
	switch (message)
	{
		case WM_INITDIALOG:
		{
			place = lParam;
			return (INT_PTR)TRUE;
		}
		case WM_COMMAND:
		{
			if (LOWORD(wParam) == IDOK)
			{
				WCHAR buff[32];
				GetDlgItemText(hDlg, IDC_NAME, buff, 32);
				if (!wcslen(buff) || wcslen(buff) > 32)
				{
					MessageBox(hDlg, L"Некорректно введено поле 'Имя'!", L"Ошибка", MB_OK | MB_ICONERROR);
					return (INT_PTR)FALSE;
				}
				wcscpy_s(records[place].name, 32, buff);
				EndDialog(hDlg, LOWORD(wParam));
				return (INT_PTR)TRUE;
			}
			break;
		}
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK Settings(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	static INT pos;
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
		case WM_INITDIALOG:
		{
			if(sound) Button_SetCheck(GetDlgItem(hDlg, IDC_SOUND), BST_CHECKED);

			int choice = 0;
			if (size == 9) choice = IDC_RADIO9;
			else if (size == 11) choice = IDC_RADIO11;
			else if (size == 15) choice = IDC_RADIO15;
			if (choice > 0) Button_SetCheck(GetDlgItem(hDlg, choice), BST_CHECKED);

			choice = 0;
			if (lineballs == 4) choice = IDC_RADIO4;
			else if (lineballs == 5) choice = IDC_RADIO5;
			else if (lineballs == 6) choice = IDC_RADIO6;
			if (choice > 0) Button_SetCheck(GetDlgItem(hDlg, choice), BST_CHECKED);
			return (INT_PTR)TRUE;
		}
		case WM_COMMAND:
		{
			if (LOWORD(wParam) == IDOK)
			{
				if (Button_GetCheck(GetDlgItem(hDlg, IDC_SOUND))) sound = true;
				else sound = false;

				if (Button_GetCheck(GetDlgItem(hDlg, IDC_RADIO9))) size = 9;
				else if (Button_GetCheck(GetDlgItem(hDlg, IDC_RADIO11))) size = 11;
				else if (Button_GetCheck(GetDlgItem(hDlg, IDC_RADIO15))) size = 15;
				Resize(GetParent(hDlg));

				if (Button_GetCheck(GetDlgItem(hDlg, IDC_RADIO4))) lineballs = 4;
				else if (Button_GetCheck(GetDlgItem(hDlg, IDC_RADIO5))) lineballs = 5;
				else if (Button_GetCheck(GetDlgItem(hDlg, IDC_RADIO6))) lineballs = 6;
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
