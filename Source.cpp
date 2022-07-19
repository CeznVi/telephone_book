#include <iostream>
#include <Windows.h>
#include "phonebook.h"

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	Phone_book pb;
	
	pb.menu();
	
	return 0;
}