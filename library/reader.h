#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "my_container.h"
#include "helputils.h"
#include "book.h"
using namespace std;

/* �������� (���������� �� ������ ���������) ����� �����������:
- ������ ����� �� ��������� �������� (����� ���� ��� ����� �����),
- ����� ����� �� ���� �� ������������ ���� (���� ����� �� �� �����),
- ������� ����� (���� ��� � ���� �� �����).*/


//��� ��������
class reader
{
public:
	char surname[40];		//������� ��������
	char name[40];		//��� ��������
	char r_number_of_ticket[40];  //����� ������������� ������ 
	//my_container<book> books;	//������ ���� ��������

	reader()
	{
		strcpy(surname, "0");
		strcpy(name, "0");
		strcpy(r_number_of_ticket, "0");
	}

	reader(char s[], char n[], char r_n[])
	{
		//���� �������� ������� ������� ��������
		if ((s == "") || (n == "") || (r_n == ""))
			throw 1;
		strcpy(surname, s);
		strcpy(name, n);
		strcpy(r_number_of_ticket, r_n);
	}

	void get_data()
	{
		do {
			cout << "������� ����� ������������� ������: ";
			cin >> r_number_of_ticket;
		} while (strcmp(r_number_of_ticket, "") == 0);
		do {
			cout << "������� ������� ��������: ";
			cin >> surname;
		} while (strcmp(surname, "") == 0);
		_tolower_ch_(surname);
		do {
			cout << "������� ��� ��������: ";
			cin >> name;
		} while (strcmp(name, "") == 0);
		_tolower_ch_(name);
	}

	void show_data()
	{
		cout << "��������: " << surname << " " << name << endl;
		cout << "����� ����������: " << r_number_of_ticket << endl;
	}

	//�������� ����
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
