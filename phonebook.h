#pragma once

#include <iostream>
#include <conio.h> 
//��� ���������� ��������� ��������
#include <fstream> 
// ��� ���������� �� ������������ �����

class Subscriber
{
private:
	//ϲ�
	char* name = nullptr;
	//��������� �����
	char* pNumb = nullptr;
	//��������� ���������� ��� �������
	char* info = nullptr;
	bool isNum(const char* n);
	friend void saveInFile(Subscriber* Subscribers, int& count);

public:
	//������������
	Subscriber();
	Subscriber(const char* name, const char* pNumb, const char* info);
	//����������� ���������
	Subscriber(const Subscriber& obj);
	Subscriber& operator=(const Subscriber& obj);
	//����������
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
	//������� �������� � ��������� ����
	int count = 0;
	//�������� �������� ���'�� �� ��������
	Subscriber* Subscribers = nullptr;
	//������ ����� ���������
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

////�����������, �� �� ������ ���������
Subscriber::Subscriber()
{
	name = nullptr;
	pNumb = nullptr;
	info = nullptr;
}

////�����������
Subscriber::Subscriber(const char* name, const char* pNumb, const char* info)
{
	if(name != nullptr)
		setName(name);

	if (pNumb != nullptr)
		setpNumb(pNumb);

	if (info != nullptr)
		setInfo(info);
}

////����������� ���������
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

////����������
Subscriber::~Subscriber()
{
	delete name;
	name = nullptr;
	delete pNumb;
	pNumb = nullptr;
	delete info;
	info = nullptr;
}

////////������������ �������
void Subscriber::print()
{
	std::cout << '\n';
	if(name == nullptr && pNumb == nullptr)
		std::cout << "������� �� ���� " << '\n';
	else
	{
		std::cout << "ϲ�: " << name << '\n';
		
		if(pNumb == nullptr)
			std::cout << "����� ��������: �� ������" << '\n';
		else
			std::cout << "����� ��������: +" << pNumb << '\n';
		if(info != nullptr)
			std::cout << "���������� ��� �������: " << info << '\n';
	}
}

////����� ϲ� ��������
void Subscriber::setName(const char* n)
{
	delete name;
	name = new char[strlen(n) + 1];
	strcpy_s(name, strlen(n) + 1, n);
}

////��������� ������ ��� �� ����� ������ ��������
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

////����� ������ ��������
void Subscriber::setpNumb(const char* n)
{
	delete pNumb;
	pNumb = new char[strlen(n) + 1];
	strcpy_s(pNumb, strlen(n) + 1, n);
}

////����� ��������� ���������� ��� ��������
void Subscriber::setInfo(const char* n)
{
	delete info;
	info = new char[strlen(n) + 1];
	strcpy_s(info, strlen(n) + 1, n);
}

////����� ������ �� ����������� ��'�
void Subscriber::getName()
{
	//// ����������� ������� ���� ϲ�
	int const lenght = 40;
	std::cout << "���� ����� ������ ϲ� �������� \n";
	char n[lenght]{};
	std::cin.getline(n, lenght);
	this->setName(n);
}

////����� ������ �� ����������� ���������� �����
void Subscriber::getNumber()
{
	//// ����������� ������� ���� ϲ�
	int const lenght = 13;
	char n[lenght]{};

	std::cout << "���� ����� ������ ����� �������� �������� (��� �����+)\n";
	while (!isNum(n))
	{
		std::cin.getline(n, lenght);
		
		if (std::cin.fail())
		{
			std::cin.clear(); // ������� �� �������
			std::cin.ignore(32767, '\n'); // ��������� �����
			std::cout << "������� �����. ����� ������� ������ ���� ����� �� ���� ������� 12 ����\n";
		}
		else if ((!isNum(n)))
			std::cout << "������� �����. ����� ������� ������ ���� ����� �� ���� ������� 12 ����\n";
		
	}
		
	this->setpNumb(n);
}

////����� ������ �� ����������� ��������� ����������
void Subscriber::getInfo()
{
	//// ����������� ������� ���� ϲ�
	int const lenght = 50;
	std::cout << "���� ����� ������ ��������� ���������� ��� �������� \n";
	char n[lenght]{};
	std::cin.getline(n, lenght);
	this->setInfo(n);
}

////������� ���
char* Subscriber::returnName()
{
	return name;
}

////������� �����
char* Subscriber::returnNumb()
{
	return pNumb;
}

////������� ���������� ��� �������
char* Subscriber::returnInfo()
{
	return info;
}

////������������ �� �������� 
void Phone_book::print() const
{
	if (Subscribers == nullptr)
		std::cout << "�������� � ��� �� ��������\n";
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

////�������� ��������� �����
void Phone_book::copySubscribers(Subscriber* to, Subscriber* base)
{
	for (int i{}; i < count; ++i)
	{
		to[i].setName((base[i].returnName()));
		to[i].setpNumb((base[i].returnNumb()));
		to[i].setInfo((base[i].returnInfo()));
	}
}

////����������� � ����� ��������� �����
void Phone_book::loadFromFile()
{
	FILE* file;
	fopen_s(&file, "pb.txt", "r");
	if (!file)
	{
		std::cerr << "������� �������� �����(�������)...\n";
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
		//����� ��'� �����������
		tempChar = new char[nameCount[i]];
		fread(tempChar, sizeof(char), nameCount[i], file);
		Subscribers[i].setName(tempChar);
		delete[] tempChar;

		//����� ������ �������� �����������
		tempChar = new char[numberCount[i]];
		fread(tempChar, sizeof(char), numberCount[i], file);
		Subscribers[i].setpNumb(tempChar);
		delete[] tempChar;
		//����� ��� ��� �����������
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

////�������� � ���� �������� �����
void saveInFile(Subscriber* Subscribers, int& count)
{
	FILE* file;
	fopen_s(&file, "pb.txt", "w");
	if (!file)
		{
			std::cerr << "������� ���������� �����...";
			exit(1);
		}
	
	//˳������� ������� ������� � ������� ������� ����,����� ��������,
	size_t* nameCount = new size_t[count];
	size_t* numberCount = new size_t[count];
	size_t* infoCount = new size_t[count];
	
	//����� ������� ������� � ������� �������
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

////������ ������� � ��������� �����
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
	//// ����������� ������� ���� ϲ�
	int const lenght = 40;
	std::cout << "���� ����� ������ ϲ� �������� ����� ������� ��������\n";
	char n[lenght]{};
	std::cin.getline(n, lenght);
	
	int dellId{};
	std::cout << "���������� ��������:  \n";

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
		std::cout << "��� ������ �������� ������� �� ����� ����������� ���������� �����\n";
		std::cout << "1 - ����� �� ϲ�\n";
		std::cout << "2 - ����� �� ������� ��������\n";
		std::cout << "ESC - ����� � ������� ����\n\n";
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
	//// ����������� ������� ���� ϲ�
	int const lenght = 40;
	std::cout << "���� ����� ������ ϲ� �������� \n";
	char n[lenght]{};
	std::cin.getline(n, lenght);

	std::cout << "���������� ������:  \n";
	
	for (int i{}; i < count; i++)
	{
		if (strcmp(n, Subscribers[i].returnName()) == 0)
			Subscribers[i].print();
	}
	system("pause");
	
}

void Phone_book::searchByPhone()
{
	//// ����������� ������� ���� ϲ�
	int const lenght = 13;
	std::cout << "���� ����� ������ ����� �������� \n";
	char n[lenght]{};
	std::cin.getline(n, lenght);

	std::cout << "���������� ������:  \n";

	for (int i{}; i < count; i++)
	{
		if (strcmp(n, Subscribers[i].returnNumb()) == 0)
			Subscribers[i].print();
	}
	system("pause");


}

////���� �������� �����
void Phone_book::menu()
{
	loadFromFile();
	bool isExit = false;
	int doId{};

	while (!isExit)
	{
		std::cout << "���� ��������� �����: \n";
		std::cout << "\tTAB - �������� ��� ��������\n";
		std::cout << "\tSPACE - ������ ��������\n";
		std::cout << "\t = - ������ ��������\n";
		std::cout << "\tDelete - �������� ��������\n";
		std::cout << "\tESC - ����� � ��������\n";
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