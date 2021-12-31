#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>

using namespace std;

struct Initials {
	string surname;
	string name;
	string patronymic;
};


class Data {
private:
	Initials initials;
public:
	Data();
	Data(Initials initials);
	~Data();

	void Print();
	void DataEntry(Initials initials);
	Initials GetInitials(){return initials;};
	Data& operator = (Data d_o);

};


Data::Data()
{
	initials.surname = "";
	initials.name = "";
	initials.patronymic = "";
}


Data::Data(Initials initials_)
{
	initials.surname = initials_.surname;
	initials.name = initials_.name;
	initials.patronymic = initials_.patronymic;
}


Data::~Data()
{
}


void Data::Print()
{
	cout << "ФИО" << initials.surname << " " << initials.name <<  " " << initials.patronymic << endl;
 }


void Data::DataEntry(Initials initials_) {
	initials.surname = initials_.surname;
	initials.name = initials_.name;
	initials.patronymic = initials_.patronymic;
}


Data& Data::operator=(Data d_o) {
	this->initials.surname = d_o.initials.surname;
	this->initials.name = d_o.initials.name;
	this->initials.patronymic = d_o.initials.patronymic;
	return *this;
}






void DataEntry(Data* (&d), int& n) {
	Initials initials;
	cout << "Введите размер массива: ";
	cin >> n;
	d = new Data[n];
	for (int i = 0; i < n; i++) {
		cout << "";
		cin >> initials.surname >> initials.name >> initials.patronymic;
		d[i].DataEntry(initials);
		cout << "_______________________________________________";
	}
}

void DataReading(Data* (&d), int& n, string filename) {
	ifstream reading(filename);
	if (reading) {
		Initials initials;
		reading >> n;
		d = new Data[n];
		for (int i = 0; i < n; i++) {
			reading >> initials.surname >> initials.name >> initials.patronymic;
			d[i].DataEntry(initials);
		}
		cout << "Данные считаны!" << endl;
	}
	else
		cout << "Ошибка при открытии файла!" << endl;

	reading.close();
}

void Print(Data* d, int n) {
	for (int i = 0; i < n; i++) {
		cout << "Данные №" << i + 1 << endl;
		d[i].Print();
		cout << "_____________________________________________";
	}
}

void DataChange(Data* d, int n) {
	Initials initials;
	int _n;
	cout << "Введите номер нужного элемента (от 1 до " << n << "):";
	cin >> _n;
	_n--;
	if (_n >= 0 && _n < n) {
		cout << "Введите новую ФИО: ";
		cin >> initials.surname >> initials.name >> initials.patronymic;
		d[_n].DataEntry(initials);
	}
	else
		cout << "Номер введён неверно!" << endl;

}

void Copy(Data* d_n, Data* d_o, int n) {
	for (int i = 0; i < n; i++)
		d_n[i] = d_o[i];
}

void AddData(Data* (&d), int& n) {
	Initials initials;
	Data* buf = new Data[n];
	int size = n, new_size = ++n;
	Copy(buf, d, size);
	d = new Data[new_size];
	Copy(d, buf, size);
	cout << "Введите новую ФИО: ";
	cin >> initials.surname >> initials.name >> initials.patronymic;
	d[size].DataEntry(initials);
	cout << "Данные добавлены!" << endl;
	delete[] buf;
}

void DeleteData(Data* (&d), int& n) {
	int _n;
	Data* buf = new Data[n];
	cout << "Введите номер нужного элемента (от 1 до " << n << "):";
	cin >> _n;
	_n--;
	if (_n >= 0 && _n < n) {
		Copy(buf, d, n);
		int q = 0;
		n--;
		d = new Data[n];
		for (int i = 0; i <= n; i++) {
			if (i != _n) {
				d[q] = buf[i];
				q++;
			}
		}
		cout << "Данные удалены!" << endl;
	}
	else
		cout << "Номер введён неверно!" << endl;
	delete[] buf;
}

void SortingData(Data* d, int n) {
	Data buf;
	int numofSorted = 0;

	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			if (d[i].GetInitials().surname > d[j].GetInitials().surname) {
				buf = d[i];
				d[i] = d[j];
				d[j] = buf;
				numofSorted++;
			}
		}
	}
	cout << "Данные отсортированы!\nКоличество сортировок:" << numofSorted << endl;
}

void SaveData(Data* d, int n, string filename) {
	ofstream record(filename);
	if (record) {
		record << n << endl;
		for (int i = 0; i < n; i++) {
			record << d[i].GetInitials().surname << " " << d[i].GetInitials().name << d[i].GetInitials().patronymic << endl;
			if (i < n - 1)
				record << endl;
		}
	}
	else
		cout << "Ошибка при открытии файла!" << endl;
	cout << "Данные сохранены в файл:" << filename << endl;
	record.close();
}




int _stateMenu;
void Menu() {
	cout << "Выберите действие: " << endl
		<< "(0) Выход из программы" << endl
		<< "(1) Ввод данных" << endl
		<< "(2) Вывод данных" << endl
		<< "(3) Изменение данных" << endl
		<< "(4) Добавление данных" << endl
		<< "(5) Удаление данных" << endl
		<< "(6) Сортировка данных" << endl
		<< "(7) Сохранение данных" << endl
		<< "Ваш выбор:  ";
	cin >> _stateMenu;

}


void main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	Menu();
	int _actions;
	int _size = 0;
	Data* d = new Data[_size];
	while (_stateMenu != 0)
	{
		switch (_stateMenu)
		{
		case 1:
			system("cls");
			DataReading(d, _size, "Input.txt");
			system("pause");
			system("cls");
			Menu();
			break;
		case 2:
			system("cls");
			if (_size != 0)
				Print(d, _size);
			else
				cout << "Данные пусты!" << endl;
			system("pause");
			system("cls");
			Menu();
			break;
		case 3:
			system("cls");
			if (_size != 0)
				DataChange(d, _size);
			else cout << "Данные пусты!" << endl;
			system("pause");
			system("cls");
			Menu();
			break;
		case 4:
			system("cls");
			if (_size != 0)
				AddData(d, _size);
			else
				cout << "Данные пусты!" << endl;
			system("pause");
			system("cls");
			Menu();
			break;
		case 5:
			system("cls");
			if (_size != 0)
				DeleteData(d, _size);
			else
				cout << "Данные пусты!" << endl;
			system("pause");
			system("cls");
			Menu();
			break;
		case 6:
			system("cls");
			if (_size != 0)
				SortingData(d, _size);
			else
				cout << "Данные пусты!" << endl;
			system("pause");
			system("cls");
			Menu();
			break;
		case 7:
			system("cls");
			if (_size != 0)
				SaveData(d, _size, "Out.txt");
			else
				cout << "Данные пусты!" << endl;
			system("pause");
			system("cls");
			Menu();
			break;
		default:
			cout << "Пункт меню введён неверно!" << endl;
			system("cls");
			Menu();
			break;
		}
	}
	system("cls");
	cout << "Работа завершена!" << endl;
	system("pause");
}



