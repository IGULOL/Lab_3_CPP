#pragma once
#include "my_container.h"
#include "book.h"

//----�������������� ��������� � �������

//�������� ������ ��� Xxxxx
void _tolower_str_(string * s)
{
	setlocale(LC_ALL, "");
	transform(s->begin(), s->end(), s->begin(), tolower);
	transform(s->begin(), s->begin() + 1, s->begin(), toupper);
}

void _tolower_ch_(char s[40])
{
	setlocale(LC_ALL, "");
	strcpy(s, strlwr(s));
	s[0] = toupper(s[0]);
}

//������ �� ����� ����������
template <class T>
void output_screen(my_container<T> c)
{
	for (int i = 0; i < c.size(); i++)
	{
		cout << "������ " << i << endl;
		c[i].show_data();
		cout << endl;
	}
}

template <class T>
void output_full_screen(my_container<T> c)
{
	for (int i = 0; i < c.size(); i++)
	{
		cout << "������ " << i << endl;
		c[i].show_full_data();
		cout << endl;
	}
}

//���������
template <class T>
void output_screen_free(my_container<T> c)
{
	int n = 0;
	for (int i = 0; i < c.size(); i++)
	{
		if (c[i].free())
		{
			cout << "������ " << n << endl;
			c[i].show_full_data();
			cout << endl;
			n++;
		}
	}
}

//�������
template <class T>
void output_screen_busy(my_container<T> c)
{
	int n = 0;
	for (int i = 0; i < c.size(); i++)
	{
		if (!c[i].free())
		{
			cout << "������ " << n << endl;
			c[i].show_full_data();
			cout << endl;
			n++;
		}
	}
}

//������ ������ �������� ����������
template <class T>
bool print(my_container<T> c, int i)
{
	if ((i >= 0) && (i < c.size()))
	{
		c[i].show_data();
		return true;
	}
	return false;
}

//�������� �����
char check_char_cin(char new_correct[])
{
	bool ok = false;

	char ch;

	char correct[11] = "0123456789";
	strcpy(correct, new_correct);

	do
	{
		cout << ">> ";
		cin >> ch;
		if (cin.good())
		{
			//�������� �� ������ ������ � ������ �������
			ok = (strchr(correct, ch) != NULL);
			cin.ignore(10, '\n');
			if (ok)
			{
				return ch;
			}
		}
		cout << "������������ ����." << endl;
		cin.clear();

	} while (!ok);
}

//�������� �����
string check_string_cin(string message)
{
	string str;
	bool ok = false;
	
	do
	{
		cout << message;
		cin >> str;
		if (cin.good())
		{
			ok = (str != "");
			cin.ignore(10, '\n');
		}
		if (!ok)
		{
			cout << "������������ ����." << endl;
			cin.clear();
		}
	} while (!ok);
	_tolower_str_(&str);

	return str;
}

//�������� ��������� ��������� < max
int check_interval(int max)
{
	string num;
	bool ok = false;

	do
	{
		cout << ">> ";
		cin >> num;
		if (cin.good())
		{
			cin.ignore(10, '\n');
			ok = (num >= "0") && (num < to_string(max));
			if (ok)
			{
				return stoi(num);
			}
			if ((num == "c") || (num == "�"))
			{
				return -1;
			}
		}
		cout << "������������ ����." << endl;
		cin.clear();

	} while (!ok);
}

