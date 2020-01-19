/*
Программа будет представлять из себя консольную однофайловую базу данных, 
вывод должен быть оформлен с помощью псевдографики, тему выбираете самостоятельно, 
тематика может быть любая, главное чтобы у сущности, которая будет храниться в базе данных было минимум 6 полей.
Например, если вы выберите тему "Автомобили", то там возможны такие поля как марка, 
модель, год выпуска, страна производитель и т.д., всего 6 таких полей.
Необходимо мне написать какую тематику вы выберите и написать мне эти 6 полей, которые вы придумаете.

Создать запись
Изменить запись
Удалить запись
Сортировать таблицу
Сохранить
Открыть
Выйти
*/

#include <iostream>//ввод/вывод
#include <fstream>//файлы
#include <iomanip>//setw
#include <algorithm>//sort
#include <limits>//лимиты
#include <string>//строки
#include <vector>//вектора
#include <Windows.h>//SetConsole

using namespace std;

unsigned max_barcode_lenght;
unsigned max_name_lenght;
unsigned max_unit_lenght;
unsigned max_file_lenght;

#if defined(max)
#undef max
#endif

typedef struct
{
	string barcode;
	string name;
	int size;
	string unit;
	double price;
	int amount;
} Product;

bool main_menu();
void add_item();
void edit_item();
void delete_item();
void search_item(bool filter);
void sort_items();
void open_items();
void save_items();
int get_int(int min, int max);
float get_float(float min, float max);
void get_str(string &str, unsigned &max);
void get_item(unsigned i);
void get_list();
void get_max_lenght();
void read_string(ifstream &fin, string &str);
void write_string(ofstream &fout, string &str);

const Product init[] = {	{ "4870122202445",	"Молоко",			1,		"л", 		5.51, 	93 },
							{ "8240422764568",	"Мука",				2,		"кг", 		14.68, 	69 },
							{ "2986903806663",	"Манная крупа",		500,	"г", 		7.32, 	61 },
							{ "2633404577266",	"Мороженное",		75,		"г", 		25.53, 	274 },
							{ "6096624107005",	"Курица замор.",	1,		"кг", 		61.69, 	202 },
							{ "1141178974888",	"Макароны",			700,	"г", 		3.02, 	176 },
							{ "2919461108729",	"Яйцо",				1,		"десят", 	1.89, 	305 },
							{ "5035873944676",	"Петрушка",			1,		"упак", 	5.78, 	367 },
							{ "2363176215419",	"Лимон",			1,		"шт", 		0.63, 	63 },
							{ "7328150843187",	"Питьевая вода",	1,		"л", 		2.86, 	410 },

							{ "4009139757181",	"Йогурт",			300,	"мл", 		29.53, 	211 },
							{ "1810999265890",	"Киви",				1,		"кг", 		30.88, 	302 },
							{ "7687700644569",	"Рис",				950,	"г", 		10.77, 	395 },
							{ "9832921357754",	"Сахар",			2,		"кг", 		11.26, 	100 },
							{ "3344465781497",	"Шампиньоны",		350,	"г", 		7.10, 	391 },
							{ "5329344167614",	"Кефир",			1,		"л", 		20.58, 	48 },
							{ "6027615604754",	"Груша",			1,		"кг",		6.93, 	79 },
							{ "3921249202148",	"Картофель",		1,		"кг",		6.68, 	149 },
							{ "7485348331276",	"Виноград",			1,		"упак", 	18.59, 	230 },
							{ "5390031486003",	"Фарш мясной",		1,		"кг", 		25.32, 	251 },

							{ "3436237256395",	"Лук репчатый",		1,		"шт", 		1.07, 	352 },
							{ "3166426705904",	"Апельсин",			1,		"кг", 		10.73, 	441 },
							{ "5900207908672",	"Мандарин",			1,		"упак", 	4.43, 	463 },
							{ "9004439994522",	"Лаваш",			3,		"шт", 		4.07, 	229 },
							{ "4544893424998",	"Сметана",			250,	"г", 		10.18, 	156 },
							{ "4409398103397",	"Творог",			1,		"упак", 	15.20, 	148 },
							{ "6075690024954",	"Филе курицы",		1,		"кг",		13.25, 	470 },
							{ "3161310934779",	"Хлеб",				1,		"упак", 	13.57, 	78 },
							{ "1009209204494",	"Шоколад",			2,		"шт", 		1.42, 	298 },
							{ "6571130483521",	"Сыр",				400,	"г",		13.05, 	276 } };
vector<Product> prod(init, init+30);//убрать get_max_lenght()
//vector<Product> prod;

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	get_max_lenght();//при начальной инициализации
	while(!main_menu());
	return 0;
}

bool main_menu()
{
	cout << "ОСНОВНОЕ МЕНЮ" << endl;
	cout << "1. Создать запись" << endl;
	cout << "2. Изменить запись" << endl;
	cout << "3. Удалить запись" << endl;
	cout << "4. Поиск записей" << endl;
	cout << "5. Отфильтровать записи" << endl;
	cout << "6. Сортировать таблицу" << endl;
	cout << "7. Открыть" << endl;
	cout << "8. Сохранить" << endl;
	cout << "9. Выйти" << endl << endl;
	cout << "Выберите пункт меню: ";
	switch (get_int(1, 9))
	{
		case 1:	{ add_item(); break; }
		case 2: { edit_item(); break; }
		case 3: { delete_item(); break; }
		case 4: { search_item(false); break; }
		case 5: { search_item(true); break; }
		case 6: { sort_items(); break; }
		case 7: { open_items(); break; }
		case 8: { save_items(); break; }
		case 9: { return true; }
	}
	return false;
}

void add_item()
{
	system("cls");
	cout << "СОЗДАНИЕ ЗАПИСИ" << endl;
	Product input;
	cout << "Введите штрихкод: ";
	get_str(input.barcode, max_barcode_lenght);
	cout << "Введите наименование: ";
	get_str(input.name, max_name_lenght);
	cout << "Введите массу/объём: ";
	input.size = get_int(0, 0);
	cout << "Введите единицу измерения: ";
	get_str(input.unit, max_unit_lenght);
	cout << "Введите цену: ";
	input.price = get_float(0, 0);
	cout << "Введите количество: ";
	input.amount = get_int(0, 0);
	prod.push_back(input);
	get_max_lenght();
	system("cls");
	cout << "Запись добавлена!" << endl << endl;
}

void edit_item()
{
	system("cls");
	if (prod.empty())
	{
		cout << "Список пуст!" << endl << endl;
		return;
	}
	cout << "РЕДАКТИРОВАНИЕ ЗАПИСИ" << endl;
	get_list();
	cout << "Введите номер редактируемой записи (1-" << prod.size() << ", 0 - отмена): ";
	int item = get_int(0, prod.size());
	system("cls");
	if (item > 0)
	{
		Product input;
		cout << "Введите штрихкод: ";
		get_str(input.barcode, max_barcode_lenght);
		cout << "Введите наименование: ";
		get_str(input.name, max_name_lenght);
		cout << "Введите массу/объём: ";
		input.size = get_int(0, 0);
		cout << "Введите единицу измерения: ";
		get_str(input.unit, max_unit_lenght);
		cout << "Введите цену: ";
		input.price = get_float(0, 0);
		cout << "Введите количество: ";
		input.amount = get_int(0, 0);
		prod[item - 1] = input;
		get_max_lenght();
		system("cls");
		cout << "Запись отредактирована!" << endl << endl;
	}
}

void delete_item()
{
	system("cls");
	if (prod.empty())
	{
		cout << "Список пуст!" << endl << endl;
		return;
	}
	cout << "УДАЛЕНИЕ ЗАПИСИ" << endl;
	get_list();
	cout << "Введите номер удаляемой записи (1-" << prod.size() << ", 0 - отмена): ";
	int item = get_int(0, prod.size());
	system("cls");
	if (item > 0)
	{
		prod.erase(prod.begin() + item - 1);
		get_max_lenght();
		cout << "Запись удалена!" << endl << endl;
	}
}

void search_item(bool filter)
{
	system("cls");
	if (prod.empty())
	{
		cout << "Список пуст!" << endl << endl;
		return;
	}
	cout << (filter ? "ФИЛЬТРАЦИЯ ЗАПИСЕЙ" : "ПОИСК ЗАПИСЕЙ") << endl;
	cout << "1. Штрихкод" << endl;
	cout << "2. Наименование" << endl;
	cout << "3. Масса/объём" << endl;
	cout << "4. Единица измерения" << endl;
	cout << "5. Цена" << endl;
	cout << "6. Количество" << endl;
	cout << "0. Вернуться назад" << endl << endl;
	cout << "Выберите столбец: ";
	int column = get_int(0, 6);
	cout << "Введите значение: ";
	switch (column)
	{
		case 1:
		{
			string input;
			get_str(input, max_barcode_lenght);
			system("cls");
			cout << "Результат:" << endl;
			for (unsigned i = 0; i < prod.size(); i++) 
				if (filter ? prod[i].barcode.find(input) == string::npos : prod[i].barcode.find(input) != string::npos) 
					get_item(i);
			break;
		}
		case 2:
		{
			string input;
			get_str(input, max_name_lenght);
			system("cls");
			cout << "Результат:" << endl;
			for (unsigned i = 0; i < prod.size(); i++)
				if (filter ? prod[i].name.find(input) == string::npos : prod[i].name.find(input) != string::npos)
					get_item(i);
			break;
		}
		case 3:
		{
			int input = get_int(0, 0);
			system("cls");
			cout << "Результат:" << endl;
			for (unsigned i = 0; i < prod.size(); i++)
				if (filter ? prod[i].size != input : prod[i].size == input)
					get_item(i);
			break;
		}
		case 4: 
		{
			string input;
			get_str(input, max_unit_lenght);
			system("cls");
			cout << "Результат:" << endl;
			for (unsigned i = 0; i < prod.size(); i++)
				if (filter ? prod[i].unit.find(input) == string::npos : prod[i].unit.find(input) != string::npos)
					get_item(i);
			break;
		}
		case 5:
		{
			double input = get_float(0, 0);
			system("cls");
			cout << "Результат:" << endl;
			for (unsigned i = 0; i < prod.size(); i++)
				if (filter ? fabs(prod[i].price - input) > 0.001 : fabs(prod[i].price - input) <= 0.001)
					get_item(i);
			break;
		}
		case 6:
		{
			int input = get_int(0, 0);
			system("cls");
			cout << "Результат:" << endl;
			for (unsigned i = 0; i < prod.size(); i++)
				if (filter ? prod[i].amount != input : prod[i].amount == input)
					get_item(i);
			break;
		}
		case 0:
		{
			system("cls");
			return;
		}
	}
	cout << endl;
}

void sort_items()
{
	system("cls");
	if (prod.empty())
	{
		cout << "Список пуст!" << endl << endl;
		return;
	}
	cout << "СОРТИРОВКА ЗАПИСЕЙ" << endl;
	cout << "1. Штрихкод" << endl;
	cout << "2. Наименование" << endl;
	cout << "3. Масса/объём" << endl;
	cout << "4. Единица измерения" << endl;
	cout << "5. Цена" << endl;
	cout << "6. Количество" << endl;
	cout << "0. Вернуться назад" << endl << endl;
	cout << "Выберите столбец для сортировки: ";
	int input = get_int(0, 6);
	if (!input)
	{
		system("cls");
		return;
	}
	cout << "Выберите направление для сортировки (1 - прямое, 0 - обратное): ";
	int dir = get_int(0, 1);
	switch (input)
	{
		case 1: { sort(prod.begin(), prod.end(), 
						[dir](Product a, Product b) { return (dir) ? a.barcode < b.barcode : a.barcode > b.barcode; }); break; }
		case 2: { sort(prod.begin(), prod.end(), 
						[dir](Product a, Product b) { return (dir) ? a.name < b.name : a.name > b.name; }); break; }
		case 3: { sort(prod.begin(), prod.end(), 
						[dir](Product a, Product b) { return (dir) ? a.size < b.size : a.size > b.size; }); break; }
		case 4: { sort(prod.begin(), prod.end(), 
						[dir](Product a, Product b) { return (dir) ? a.unit < b.unit : a.unit > b.unit; }); break; }
		case 5: { sort(prod.begin(), prod.end(), 
						[dir](Product a, Product b) { return (dir) ? a.price < b.price : a.price > b.price; }); break; }
		case 6: { sort(prod.begin(), prod.end(), 
						[dir](Product a, Product b) { return (dir) ? a.amount < b.amount : a.amount > b.amount; }); break; }
	}
	system("cls");
	cout << "Список отсортирован!" << endl << endl;
	get_list();
}

void open_items()
{
	system("cls");
	cout << "ОТКРЫТИЕ ФАЙЛА" << endl;
	string input;
	cout << "Введите имя файла: ";
	get_str(input, max_file_lenght);
	system("cls");
	ifstream fin(input + ".bin", ios::in | ios::binary);
	if (!fin.is_open())
	{
		cout << "Произошла ошибка при открытии файла!" << endl << endl;
		return;
	}
	char check[10];
	fin.read((char *)&check, 10);
	if (strcmp(check, "prod_list") != 0)
	{
		cout << "Файл не является поддерживаемой базой данных!" << endl << endl;
		fin.close();
		return;
	}
	prod.erase(prod.begin(), prod.end());
	while (!fin.eof())
	{
		Product *tmp = new Product;
		read_string(fin, tmp->barcode);
		read_string(fin, tmp->name);
		fin.read((char *)&tmp->size, sizeof(int));
		read_string(fin, tmp->unit);
		fin.read((char *)&tmp->price, sizeof(double));
		fin.read((char *)&tmp->amount, sizeof(int));
		if(fin.good()) prod.push_back(*tmp);
		delete tmp;
	}
	fin.close();
	cout << "Файл открыт!" << endl << endl;
	get_max_lenght();
	get_list();
}

void save_items()
{
	system("cls");
	if (prod.empty())
	{
		cout << "Нет данных для сохранения!" << endl << endl;
		return;
	}
	cout << "СОХРАНЕНИЕ ФАЙЛА" << endl;
	string input;
	cout << "Введите имя файла: ";
	get_str(input, max_file_lenght);
	system("cls");
	ofstream fout(input + ".bin", ios::out | ios::binary);
	if (fout.is_open())
	{
		char check[10] = "prod_list";
		fout.write((char *)&check, 10);//запись проверочной строки
		for (unsigned i = 0; i < prod.size(); i++)
		{
			write_string(fout, prod[i].barcode);
			write_string(fout, prod[i].name);
			fout.write((char *)&prod[i].size, sizeof(int));
			write_string(fout, prod[i].unit);
			fout.write((char *)&prod[i].price, sizeof(double));
			fout.write((char *)&prod[i].amount, sizeof(int));
		}
		fout.close();
		cout << "Файл сохранён!" << endl << endl;
	}
	else cout << "Произошла ошибка при сохранении файла!" << endl << endl;
}

int get_int(int min, int max)
{
	int input;
	cin >> input;
	while (cin.fail() || (input < min && min != max) || (input > max && max > min))
	{//если min и max не нужны указать их равными, если не нужен только max указать его меньше чем min.
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Некорректный ввод! Попробуйте снова: ";
		cin >> input;
	}
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	return input;
}

float get_float(float min, float max)
{
	float input;
	cin >> input;
	while (cin.fail() || (input < min && min != max) || (input > max && max > min))
	{//если min и max не нужны указать их равными, если не нужен только max указать его меньше чем min.
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Некорректный ввод! Попробуйте снова: ";
		cin >> input;
	}
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	return input;
}

void get_str(string &str, unsigned &max)
{
	cin >> str;
	while (cin.fail())
	{//если max не нужен указать равным нулю.
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Некорректный ввод! Попробуйте снова: ";
		cin >> str;
	}
	if (str.size() > max && max >= 0) max = str.size();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void get_item(unsigned i)
{
	cout << setw(4) << i + 1 << " | " <<
		setw(max_barcode_lenght) << prod[i].barcode << " | " <<
		setw(max_name_lenght) << prod[i].name << " | " <<
		setw(10) << prod[i].size << " | " <<
		setw(max_unit_lenght) << prod[i].unit << " | " <<
		setw(10) << prod[i].price << " | " <<
		setw(10) << prod[i].amount << endl;
}

void get_list()
{
	for (unsigned i = 0; i < prod.size(); i++)
	{
		cout << setw(4) << i + 1 << " | " <<
			setw(max_barcode_lenght) << prod[i].barcode << " | " <<
			setw(max_name_lenght) << prod[i].name << " | " <<
			setw(10) << prod[i].size << " | " <<
			setw(max_unit_lenght) << prod[i].unit << " | " <<
			setw(10) << prod[i].price << " | " <<
			setw(10) << prod[i].amount << endl;
	}
	cout << endl;
}

void get_max_lenght()
{
	for (unsigned i = 0; i < prod.size(); i++)
	{
		if (prod[i].barcode.size() > max_barcode_lenght) max_barcode_lenght = prod[i].barcode.size();
		if (prod[i].name.size() > max_name_lenght) max_name_lenght = prod[i].name.size();
		if (prod[i].unit.size() > max_unit_lenght) max_unit_lenght = prod[i].unit.size();
	}
}

void read_string(ifstream &fin, string &str)
{
	unsigned size;
	fin.read((char *)&size, sizeof(size));//читаем размер строки
	if (!fin.good()) return;
	char *buffer = new char[size];//создаем буфер для char > string
	fin.read((char *)buffer, size);//читаем файл
	if (fin.good()) str = buffer;//переписываем char > string
	delete[] buffer;//удаляем буфер
}

void write_string(ofstream &fout, string &str)
{
	unsigned size = str.size() + 1;//определяем размер строки
	fout.write((char *)&size, sizeof(size));//записываем размер строки
	fout.write((char *)str.data(), size);//переводим в char и записываем
}