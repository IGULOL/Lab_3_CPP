#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "atlcomtime.h"
#include "helputils.h"
#include "time.h"
using namespace std;

/*Информационная запись о книге, выданной на руки абоненту представляет собой структуру:
- номер читательского билета,
- фамилия абонента,
- дата выдачи,
- дата возврата,
- автор,
- название,
- год издания,
- издательство,
- цена.
Поиск по полям номер читательского билета, автор, издательство и дата возврата (просроченные).
*/

//тип дата
struct date
{
	int day;   //dd
	int month; //mm
	int year;  //yyyy

	date()
	{
		day = 1;
		month = 1;
		year = 1970;
	}

	date(unsigned short d, unsigned short m, unsigned short y)
	{
		day = d;
		month = m;
		year = y;
	}

	//сбросить дату
	void reset()
	{
		day = 1;
		month = 1;
		year = 1970;
	}

	void get_data()
	{
		do {
			cout << "день: ";
			cin >> day;
		} while ((day > 31) || (day < 1));
		do {
			cout << "номер месяца: ";
			cin >> month;
		} while ((month > 12) || (month < 1));
		do {
			cout << "год: ";
			cin >> year;
		} while (year < 1970);
	}

	void show_data()
	{
		cout << day << "." << month << "." << year << endl;
	}

	//файловый ввод
	friend ifstream& operator >> (ifstream& is, date& d)
	{
		string str;
		is >> str;
		int n, m;
		n = str.find('.');
		d.day = atoi((str.substr(0, n)).c_str());
		m = str.find('.', n + 1);
		d.month = atoi((str.substr(n + 1, m - n - 1)).c_str());
		d.year = atoi((str.substr(m + 1)).c_str());
		return is;
	}

	bool operator== (date d2) const
	{
		return ((day == d2.day) && (month == d2.month)
			&& (year == d2.year));
	}

	bool operator> (date d2) const
	{
		//если года не равны
		if (!(year == d2.year))
		{
			return ((year > d2.year));
		}
		else
		{
			//если месяцы не равны
			if (!(month == d2.month))
			{
				return ((month > d2.month));
			}
			else
			{
				return ((day > d2.day));
			}
		}
	}
	bool operator< (date d2) const
	{
		//если года не равны
		if (!(year == d2.year))
		{
			return ((year < d2.year));
		}
		else
		{
			//если месяцы не равны
			if (!(month == d2.month))
			{
				return ((month < d2.month));
			}
			else
			{
				return ((day < d2.day));
			}
		}
	}
};

//структура книга
class book
{
public:
	char number_of_ticket[40];    //номер читательского билета 
	char surname[40];			    //фамилия абонента
	date date_beg; 	//дата выдачи
	date date_end; 	//дата возврата
	char author[40];	//автор
	char title[40];	//название
	int year_public; //год издания
	char office_publice[40];      //издательство
	int money;   //цена

	
	book()
	{
		strcpy(number_of_ticket, "0");
		strcpy(surname, "0");
		date_beg = date(1,1,1970);
		date_end = date(1, 1, 1970);
		strcpy(author, "0");
		strcpy(title, "0");
		year_public = 1970;
		strcpy(office_publice, "0");
		money = 0;
	}

	void get_data()
	{
		do {
			cout << "Введите автора: ";
			cin >> author;
		} while (strcmp(author, "") == 0);
		_tolower_ch_(surname);
		do {
			cout << "Введите название: ";
			cin >> title;
		} while (strcmp(title, "") == 0);
		_tolower_ch_(surname);

		do {
			cout << "Введите год издания: ";
			cin >> year_public;
		} while ((year_public < 1970) || (year_public > 2018));

		do {
			cout << "Введите издательство: ";
			cin >> office_publice;
		} while (strcmp(office_publice, "") == 0);
		_tolower_ch_(surname);

		do {
			cout << "Введите цену: ";
			cin >> money;
		} while (money <= 0);

	}

	void show_data()
	{
		cout << "Автор: " << author << endl;
		cout << "Название: " << title << endl;
		cout << "Год издания: " << year_public << endl;
		cout << "Издательство: " << office_publice << endl;
	}

	void show_full_data()
	{
		cout << "Номер студбилета: " << number_of_ticket << endl;
		cout << "Читатель: " << surname << endl;
		cout << "Дата выдачи: ";
		date_beg.show_data();
		cout << "Дата Возврата: ";
		date_end.show_data();
		cout << "Автор: " << author << endl;
		cout << "Название: " << title << endl;
		cout << "Год издания: " << year_public << endl;
		cout << "Издательство: " << office_publice << endl;
		cout << "Цена: " << money << endl;
	}
					
	//свободна ли книга
	bool free()
	{
		return (strcmp(number_of_ticket,"0") == 0);
	}

	//сбросить читателя
	void reset()
	{
		strcpy(number_of_ticket, "0");
		strcpy(surname, "0");
		date_beg = date(1, 1, 1970);
		date_end = date(1, 1, 1970);
	}

	//установить читателя книги на срок days
	bool set_reader(char r_num[], char surn[], int days)
	{
		if (free())
		{
			strcpy(number_of_ticket, r_num);
			strcpy(surname, surn);

			time_t t = time(NULL);
			tm *tk;
			//преобразует время в структуру
			tk = localtime(&t);
			date_beg = date(tk->tm_mday, 1 + tk->tm_mon, 1900 + tk->tm_year);

			tk->tm_mday += days;
			//обратное преобразование даты
			time_t next = mktime(tk);
			tk = localtime(&next);
			date_end = date(tk->tm_mday, 1 + tk->tm_mon, 1900 + tk->tm_year);

			return true;
		}
		else
		{
			return false;
		}
	}

	bool operator== (book m2) const
	{
		return ((strcmp(number_of_ticket,m2.number_of_ticket) == 0) && (strcmp(surname,m2.surname) == 0)
			&& (date_beg == m2.date_beg) && (date_end == m2.date_end)
			&& (strcmp(author,m2.author) == 0) && (strcmp(title,m2.title) == 0)
			&& (year_public == m2.year_public) && (strcmp(office_publice,m2.office_publice) == 0)
			&& (money == m2.money));
	}
};
