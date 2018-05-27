#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "my_container.h"
#include "helputils.h"
#include "book.h"
using namespace std;

/* Читатель (выбирается из списка доступных) имеет возможность:
- поиска книги по заданному критерию (любое поле или набор полей),
- взять книгу на руки на определенный срок (если книга не на руках),
- вернуть книгу (если она у него на руках).*/


//тип читатель
class reader
{
public:
	char surname[40];		//фамилия читателя
	char name[40];		//имя читателя
	char r_number_of_ticket[40];  //номер читательского билета 
	//my_container<book> books;	//список книг читателя

	reader()
	{
		strcpy(surname, "0");
		strcpy(name, "0");
		strcpy(r_number_of_ticket, "0");
	}

	reader(char s[], char n[], char r_n[])
	{
		//если пытаемся создать пустого читателя
		if ((s == "") || (n == "") || (r_n == ""))
			throw 1;
		strcpy(surname, s);
		strcpy(name, n);
		strcpy(r_number_of_ticket, r_n);
	}

	void get_data()
	{
		do {
			cout << "Введите номер читательского билета: ";
			cin >> r_number_of_ticket;
		} while (strcmp(r_number_of_ticket, "") == 0);
		do {
			cout << "Введите фамилию абонента: ";
			cin >> surname;
		} while (strcmp(surname, "") == 0);
		_tolower_ch_(surname);
		do {
			cout << "Введите имя абонента: ";
			cin >> name;
		} while (strcmp(name, "") == 0);
		_tolower_ch_(name);
	}

	void show_data()
	{
		cout << "Читатель: " << surname << " " << name << endl;
		cout << "Номер студбилета: " << r_number_of_ticket << endl;
	}

	//файловый ввод
	friend ifstream& operator >> (ifstream& is, reader& r)
	{
		is >> r.r_number_of_ticket;
		is >> r.surname;
		is >> r.name;
		return is;
	}

	bool operator== (reader m2) const
	{
		return ((strcmp(r_number_of_ticket, m2.r_number_of_ticket) == 0) 
			&& (strcmp(surname, m2.surname) == 0)
			&& (strcmp(name, m2.name) == 0));
	}
};
