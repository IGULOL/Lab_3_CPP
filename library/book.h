#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "atlcomtime.h"
#include "helputils.h"
#include "time.h"
using namespace std;

/*�������������� ������ � �����, �������� �� ���� �������� ������������ ����� ���������:
- ����� ������������� ������,
- ������� ��������,
- ���� ������,
- ���� ��������,
- �����,
- ��������,
- ��� �������,
- ������������,
- ����.
����� �� ����� ����� ������������� ������, �����, ������������ � ���� �������� (������������).
*/

//��� ����
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

	//�������� ����
	void reset()
	{
		day = 1;
		month = 1;
		year = 1970;
	}

	void get_data()
	{
		do {
			cout << "����: ";
			cin >> day;
		} while ((day > 31) || (day < 1));
		do {
			cout << "����� ������: ";
			cin >> month;
		} while ((month > 12) || (month < 1));
		do {
			cout << "���: ";
			cin >> year;
		} while (year < 1970);
	}

	void show_data()
	{
		cout << day << "." << month << "." << year << endl;
	}

	//�������� ����
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
		//���� ���� �� �����
		if (!(year == d2.year))
		{
			return ((year > d2.year));
		}
		else
		{
			//���� ������ �� �����
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
		//���� ���� �� �����
		if (!(year == d2.year))
		{
			return ((year < d2.year));
		}
		else
		{
			//���� ������ �� �����
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

//��������� �����
class book
{
public:
	char number_of_ticket[40];    //����� ������������� ������ 
	char surname[40];			    //������� ��������
	date date_beg; 	//���� ������
	date date_end; 	//���� ��������
	char author[40];	//�����
	char title[40];	//��������
	int year_public; //��� �������
	char office_publice[40];      //������������
	int money;   //����

	
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
			cout << "������� ������: ";
			cin >> author;
		} while (strcmp(author, "") == 0);
		_tolower_ch_(surname);
		do {
			cout << "������� ��������: ";
			cin >> title;
		} while (strcmp(title, "") == 0);
		_tolower_ch_(surname);

		do {
			cout << "������� ��� �������: ";
			cin >> year_public;
		} while ((year_public < 1970) || (year_public > 2018));

		do {
			cout << "������� ������������: ";
			cin >> office_publice;
		} while (strcmp(office_publice, "") == 0);
		_tolower_ch_(surname);

		do {
			cout << "������� ����: ";
			cin >> money;
		} while (money <= 0);

	}

	void show_data()
	{
		cout << "�����: " << author << endl;
		cout << "��������: " << title << endl;
		cout << "��� �������: " << year_public << endl;
		cout << "������������: " << office_publice << endl;
	}

	void show_full_data()
	{
		cout << "����� ����������: " << number_of_ticket << endl;
		cout << "��������: " << surname << endl;
		cout << "���� ������: ";
		date_beg.show_data();
		cout << "���� ��������: ";
		date_end.show_data();
		cout << "�����: " << author << endl;
		cout << "��������: " << title << endl;
		cout << "��� �������: " << year_public << endl;
		cout << "������������: " << office_publice << endl;
		cout << "����: " << money << endl;
	}
					
	//�������� �� �����
	bool free()
	{
		return (strcmp(number_of_ticket,"0") == 0);
	}

	//�������� ��������
	void reset()
	{
		strcpy(number_of_ticket, "0");
		strcpy(surname, "0");
		date_beg = date(1, 1, 1970);
		date_end = date(1, 1, 1970);
	}

	//���������� �������� ����� �� ���� days
	bool set_reader(char r_num[], char surn[], int days)
	{
		if (free())
		{
			strcpy(number_of_ticket, r_num);
			strcpy(surname, surn);

			time_t t = time(NULL);
			tm *tk;
			//����������� ����� � ���������
			tk = localtime(&t);
			date_beg = date(tk->tm_mday, 1 + tk->tm_mon, 1900 + tk->tm_year);

			tk->tm_mday += days;
			//�������� �������������� ����
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
