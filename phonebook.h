#pragma once

#include <iostream>
#include <conio.h> 
//для підключення керування клавішами
#include <fstream> 
// для збереження та завантаження файлів

class Subscriber
{
private:
	//ПІБ
	char* name = nullptr;
	//Мобиільний номер
	char* pNumb = nullptr;
	//Додаткова інформація про контакт
	char* info = nullptr;
	bool isNum(const char* n);
	friend void saveInFile(Subscriber* Subscribers, int& count);

public:
	//конструктори
	Subscriber();
	Subscriber(const char* name, const char* pNumb, const char* info);
	//конструктор копіювання
	Subscriber(const Subscriber& obj);
	Subscriber& operator=(const Subscriber& obj);
	//деструктор
	~Subscriber();
	
	void print();
	void setName(const char* n);
	void setpNumb(const char* n);
	void setInfo(const char* n);
	void getName();
	void getNumber();
	void getInfo();
	char* returnName();
	char* returnNumb();
	char* returnInfo();
};

class Phone_book
{
private:
	//кількість абонентів в телефонній книзі
	int count = 0;
	//Динамічне виділення пам'яті під абонентів
	Subscriber* Subscribers = nullptr;
	//перелік клавіш керування
	enum action {
		Up = 72,
		Down = 80,
		Left = 75,
		Rigth = 77,
		Space = 32,
		Esc = 27,
		Tab = 9,
		Delete = 83,
		Equals = 61,
		One = 49,
		Two = 50,
		Three = 51,
	};
	void copySubscribers(Subscriber* to, Subscriber* base);
	void loadFromFile();
	friend void saveInFile(Subscriber* Subscribers, int& count);
	void deleteById(int id);

public:
	
	void menu();
	void print() const;
	void add();
	void dell();
	void search_menu();
	void searchByName();
	void searchByPhone();
};

////Конструктор, що не приймає аргументів
Subscriber::Subscriber()
{
	name = nullptr;
	pNumb = nullptr;
	info = nullptr;
}

////Конструктор
Subscriber::Subscriber(const char* name, const char* pNumb, const char* info)
{
	if(name != nullptr)
		setName(name);

	if (pNumb != nullptr)
		setpNumb(pNumb);

	if (info != nullptr)
		setInfo(info);
}

////Конструктор копіювання
Subscriber::Subscriber(const Subscriber& obj)
{
	this->setName(obj.name);
	this->setpNumb(obj.pNumb);
	this->setInfo(obj.info);
}

Subscriber& Subscriber::operator=(const Subscriber& obj)
{
	if (this == &obj)
		return *this;

	this->~Subscriber();
	this->setName(obj.name);
	this->setpNumb(obj.pNumb);
	this->setInfo(obj.info);

	return *this;

}

////Деструктор
Subscriber::~Subscriber()
{
	delete name;
	name = nullptr;
	delete pNumb;
	pNumb = nullptr;
	delete info;
	info = nullptr;
}

////////Роздрукувати контакт
void Subscriber::print()
{
	std::cout << '\n';
	if(name == nullptr && pNumb == nullptr)
		std::cout << "Контакт не існує " << '\n';
	else
	{
		std::cout << "ПІБ: " << name << '\n';
		
		if(pNumb == nullptr)
			std::cout << "Номер телефону: не додано" << '\n';
		else
			std::cout << "Номер телефону: +" << pNumb << '\n';
		if(info != nullptr)
			std::cout << "Інформація про контакт: " << info << '\n';
	}
}

////Сетер ПІБ абонента
void Subscriber::setName(const char* n)
{
	delete name;
	name = new char[strlen(n) + 1];
	strcpy_s(name, strlen(n) + 1, n);
}

////Інспектор масиву чар на числа номера телефону
bool Subscriber::isNum(const char* n)
{
	int count = 0;

	for(int i{}; i < strlen(n); ++i)
	{
		if (n[i] >= 48 && n[i] <= 57)
			count++;

	}
	if (count == strlen(n) && strlen(n) == 12)
		return true;
	else
		return false;
}

////Сетер номера телефону
void Subscriber::setpNumb(const char* n)
{
	delete pNumb;
	pNumb = new char[strlen(n) + 1];
	strcpy_s(pNumb, strlen(n) + 1, n);
}

////Сетер додаткової інформації про абонента
void Subscriber::setInfo(const char* n)
{
	delete info;
	info = new char[strlen(n) + 1];
	strcpy_s(info, strlen(n) + 1, n);
}

////Гетер отримує від користувача ім'я
void Subscriber::getName()
{
	//// максимальни довжина поля ПІБ
	int const lenght = 40;
	std::cout << "Будь ласка введіть ПІБ абонента \n";
	char n[lenght]{};
	std::cin.getline(n, lenght);
	this->setName(n);
}

////Гетер отримує від користувача телефонний номер
void Subscriber::getNumber()
{
	//// максимальни довжина поля ПІБ
	int const lenght = 13;
	char n[lenght]{};

	std::cout << "Будь ласка введіть номер телефона абонента (без знаку+)\n";
	while (!isNum(n))
	{
		std::cin.getline(n, lenght);
		
		if (std::cin.fail())
		{
			std::cin.clear(); // скинути всі помилки
			std::cin.ignore(32767, '\n'); // почистити буфер
			std::cout << "Невірний номер. Номер повинен містити лише цифри та бути розміром 12 цифр\n";
		}
		else if ((!isNum(n)))
			std::cout << "Невірний номер. Номер повинен містити лише цифри та бути розміром 12 цифр\n";
		
	}
		
	this->setpNumb(n);
}

////Гетер отримує від користувача додаткову інформацію
void Subscriber::getInfo()
{
	//// максимальни довжина поля ПІБ
	int const lenght = 50;
	std::cout << "Будь ласка введіть додаткову інформацію про абонента \n";
	char n[lenght]{};
	std::cin.getline(n, lenght);
	this->setInfo(n);
}

////Повертає імя
char* Subscriber::returnName()
{
	return name;
}

////Повертає Номер
char* Subscriber::returnNumb()
{
	return pNumb;
}

////Повертає інформацію про контакт
char* Subscriber::returnInfo()
{
	return info;
}

////Роздрукувати всі контакти 
void Phone_book::print() const
{
	if (Subscribers == nullptr)
		std::cout << "Контактів в базі не знайдено\n";
	else
	{
		for (int i{}; i < count; ++i)
		{
			Subscribers[i].print();
		}
	}
	system("pause");
	system("cls");
}

////Копіювати телефонну книгу
void Phone_book::copySubscribers(Subscriber* to, Subscriber* base)
{
	for (int i{}; i < count; ++i)
	{
		to[i].setName((base[i].returnName()));
		to[i].setpNumb((base[i].returnNumb()));
		to[i].setInfo((base[i].returnInfo()));
	}
}

////Завантажити з файлу телефонну книгу
void Phone_book::loadFromFile()
{
	FILE* file;
	fopen_s(&file, "pb.txt", "r");
	if (!file)
	{
		std::cerr << "Помилка відкриття файлу(читання)...\n";
		system("pause");
		system("cls");
		return;
		///exit(1);
	}

	fread(&count, sizeof(int), 1, file);
	


	size_t* nameCount = new size_t[count];
	size_t* numberCount = new size_t[count];
	size_t* infoCount = new size_t[count];

	delete[] Subscribers;
	Subscribers = new Subscriber[count];

	const int countNew = count;
	fread(nameCount, sizeof(size_t), countNew, file);
	fread(numberCount, sizeof(size_t), countNew, file);
	fread(infoCount, sizeof(size_t), countNew, file);

	char* tempChar = nullptr;
	
	for (int i{}; i < count; i++)
	{
		//запис ім'я користувача
		tempChar = new char[nameCount[i]];
		fread(tempChar, sizeof(char), nameCount[i], file);
		Subscribers[i].setName(tempChar);
		delete[] tempChar;

		//запис номеру телефону користувача
		tempChar = new char[numberCount[i]];
		fread(tempChar, sizeof(char), numberCount[i], file);
		Subscribers[i].setpNumb(tempChar);
		delete[] tempChar;
		//запис дод інф користувача
		tempChar = new char[infoCount[i]];
		fread(tempChar, sizeof(char), infoCount[i], file);
		Subscribers[i].setInfo(tempChar);
		delete[] tempChar;
	}

	delete[] nameCount;
	delete[] numberCount;
	delete[] infoCount;
	
	fclose(file);
}

void Phone_book::deleteById(int id)
{
	Subscriber* temp = new Subscriber[count];
	
	for (int i{}; i < count; ++i)
	{
		if (i != id)
		{
			temp[i].setName((Subscribers[i].returnName()));
			temp[i].setpNumb((Subscribers[i].returnNumb()));
			temp[i].setInfo((Subscribers[i].returnInfo()));
		}
	}
	
	--count;
	delete[] Subscribers;
	Subscribers = new Subscriber[count];
	copySubscribers(Subscribers, temp);

	delete[] temp;
}

////Зберегти в файл телефону книгу
void saveInFile(Subscriber* Subscribers, int& count)
{
	FILE* file;
	fopen_s(&file, "pb.txt", "w");
	if (!file)
		{
			std::cerr << "Помилка збереження файлу...";
			exit(1);
		}
	
	//Лічильник кількості символів в чарових масивах імен,номер телефону,
	size_t* nameCount = new size_t[count];
	size_t* numberCount = new size_t[count];
	size_t* infoCount = new size_t[count];
	
	//Запис кількості символів в чарових масивах
	for (int i{}; i < count; i++)
	{
		nameCount[i] = strlen(Subscribers[i].name) + 1;
		numberCount[i] = strlen(Subscribers[i].pNumb) + 1;
 		infoCount[i] = strlen(Subscribers[i].info) + 1;
	}
	
	fwrite(&count, sizeof(int), 1, file);
	fwrite(nameCount, sizeof(size_t), count, file);
	fwrite(numberCount, sizeof(size_t), count, file);
	fwrite(infoCount, sizeof(size_t), count, file);
	
	
	for (int i{}; i < count; i++)
	{
		fwrite(Subscribers[i].name, sizeof(char), nameCount[i], file);
		fwrite(Subscribers[i].pNumb, sizeof(char), numberCount[i], file);
		fwrite(Subscribers[i].info, sizeof(char), infoCount[i], file);
	}
	
	delete[] nameCount;
	delete[] numberCount;
	delete[] infoCount;
	
	fclose(file);
}

////Додати контакт в телефонну книгу
void Phone_book::add()
{
	if (Subscribers == nullptr)
	{
		count++;
		Subscribers = new Subscriber[count];
		Subscribers[count - 1].getName();
		Subscribers[count - 1].getNumber();
		Subscribers[count - 1].getInfo();
	}
	else
	{
		Subscriber* temp = new Subscriber[count];
		copySubscribers(temp, Subscribers);
		delete[] Subscribers;
		Subscribers = new Subscriber[count + 1];
		copySubscribers(Subscribers, temp);
		count++;
		delete[] temp;
		Subscribers[count - 1].getName();
		Subscribers[count - 1].getNumber();
		Subscribers[count - 1].getInfo();
	}

	system("pause");
	system("cls");
}

void Phone_book::dell()
{
	//// максимальни довжина поля ПІБ
	int const lenght = 40;
	std::cout << "Будь ласка введіть ПІБ абонента якого потрібно видалити\n";
	char n[lenght]{};
	std::cin.getline(n, lenght);
	
	int dellId{};
	std::cout << "Результати видалень:  \n";

	for (int i{}; i < count; i++)
	{
		if (strcmp(n, Subscribers[i].returnName()) == 0)
		{
			Subscribers[i].print();
			deleteById(i);
		}
	}
	system("pause");

}

void Phone_book::search_menu()
{
	system("cls");
	bool isExit = false;
	int doId{};

	while (!isExit)
	{
		std::cout << "Для пошуку абонента виберіть за якими параметрами здійснювати пошук\n";
		std::cout << "1 - Пошук за ПІБ\n";
		std::cout << "2 - Пошук за номером телефону\n";
		std::cout << "ESC - Вихід в головне меню\n\n";
		doId = _getch();

		if (doId == action::Esc)
			isExit = true;
		else if (doId == action::One)
			searchByName();
		else if (doId == action::Two)
			searchByPhone();
	}

}

void Phone_book::searchByName()
{
	//// максимальни довжина поля ПІБ
	int const lenght = 40;
	std::cout << "Будь ласка введіть ПІБ абонента \n";
	char n[lenght]{};
	std::cin.getline(n, lenght);

	std::cout << "Результати пошуку:  \n";
	
	for (int i{}; i < count; i++)
	{
		if (strcmp(n, Subscribers[i].returnName()) == 0)
			Subscribers[i].print();
	}
	system("pause");
	
}

void Phone_book::searchByPhone()
{
	//// максимальни довжина поля ПІБ
	int const lenght = 13;
	std::cout << "Будь ласка введіть номер абонента \n";
	char n[lenght]{};
	std::cin.getline(n, lenght);

	std::cout << "Результати пошуку:  \n";

	for (int i{}; i < count; i++)
	{
		if (strcmp(n, Subscribers[i].returnNumb()) == 0)
			Subscribers[i].print();
	}
	system("pause");


}

////меню телефоної книги
void Phone_book::menu()
{
	loadFromFile();
	bool isExit = false;
	int doId{};

	while (!isExit)
	{
		std::cout << "Меню телефонної книги: \n";
		std::cout << "\tTAB - показати всіх абонентів\n";
		std::cout << "\tSPACE - додати абонента\n";
		std::cout << "\t = - знайти абонента\n";
		std::cout << "\tDelete - видалити абонента\n";
		std::cout << "\tESC - вийти з програми\n";
		doId = _getch();
		
		if (doId == action::Esc)
			isExit = true;
		else if (doId == action::Tab)
			this->print();
		else if (doId == action::Space)
			this->add();
		else if (doId == action::Delete)
			this->dell();
		else if (doId == action::Equals)
			this->search_menu();
		system("cls");
	}

	saveInFile(Subscribers, count);
}