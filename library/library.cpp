/* ����� ����������: ����� �� ��������� �� ������ ���������� ���������.
��� ����� ���������� ������������� �������� ���������� �� ������� �����
(� ��������� �� ���� �������������). ����������� ������������ ���������
������ � ��������� �� ������ ������!

4. ����������� ����������� ����������. ��� ������ ������
� �������� � ������������ (���������� � ����).

1) �������� (���������� �� ������ ���������) ����� �����������:
- ������ ����� �� ��������� �������� (����� ���� ��� ����� �����),
- ����� ����� �� ���� �� ������������ ���� (���� ����� �� �� �����),
- ������� ����� (���� ��� � ���� �� �����).

2) ������������ ����� �����������:
- �������������� ������ ��������� (�����������, ��������, ��������������);
- �������������� ������ ����;
- ��������� ������� ������ ���� �� ����;
- ��������� ������ ���� � ������� ��������.*/

#include "my_container.h"
#include "book.h"
#include <windows.h>
#include <locale.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <iterator>
#include <cstdio>
#include <cstring>
#include "reader.h"
#include "helputils.h"
using namespace std;

my_container<book> boooks;
my_container<reader> readers;

char out_file_name_books[] = "Booksbin.dat";
char out_file_name_readers[] = "Readersbin.dat";

my_container<book> res;

//-----------------�����
template <class TSearch>
int(*sear)(book b1, TSearch b2);

//����� �� ������������� ������
int search_number(book b1, string number_of_ticket2)
{
	return strcmp(b1.number_of_ticket, number_of_ticket2.c_str());
}

//����� �� ������
int search_author(book b1, string author2)
{
	return strcmp(b1.author, author2.c_str());
}

//����� �� ��������
int search_title(book b1, string title2)
{
	return strcmp(b1.title, title2.c_str());
}

//����� �� ������������
int search_office_publice(book b1, string office_publice2)
{
	return strcmp(b1.office_publice, office_publice2.c_str());
}

//����� �� ���� �������� + ������������
int search_date_end(book b1, date date_end2)
{
	if (b1.date_end > date_end2)
		return 1;
	return 0;
}

//����� �� ���� ������ + �������������
int search_date_beg(book b1, date date_beg2)
{
	if (b1.date_beg > date_beg2)
		return 1;
	return 0;
}

//bool(*sortirovka)(book el1, book el2);

bool sort_date_beg(book b1, book b2)
{
	return (b1.date_beg < b2.date_beg);
}
//-----------����� ������

//-----------������� ����
char main_menu()
{
	cout << "--------------------------------------------------------" << endl;
	cout << "                        ����������" << endl;
	cout << "--------------------------------------------------------" << endl;
	cout << "����� ���:" << endl;
	cout << "1 - ��������" << endl;
	cout << "2 - ������������" << endl;
	cout << "c - ������" << endl;
	cout << "--------------------------------------------------------" << endl;

	return check_char_cin("c�12");
}
//--------����� �������� ����

//--------���� ��� ���������
//�������� ����
int menu_readers()
{
	cout << "--------------------------------------------------------" << endl;
	cout << "                         ��������" << endl;
	cout << "--------------------------------------------------------" << endl;
	cout << "�������� �����:" << endl;
	output_screen<reader>(readers);
	cout << "c - �����" << endl;
	cout << "--------------------------------------------------------" << endl;

	return check_interval(readers.size());
}

//���� ��������
char menu_reader(int i)
{
	cout << "--------------------------------------------------------" << endl;
	print(readers,i);
	cout << "--------------------------------------------------------" << endl;
	cout << "1 - ����� �����" << endl;
	cout << "2 - ����� �����" << endl;
	cout << "3 - ������� �����" << endl;
	cout << "c - �����" << endl;
	cout << "--------------------------------------------------------" << endl;

	return check_char_cin("c�123");
}
//---------����� ���� ��� ���������

//---------���� ������
//������� ����
char main_search()
{
	cout << "--------------------------------------------------------" << endl;
	cout << "�������� �������� ������: " << endl;
	cout << "1 - ����� �����" << endl;
	cout << "2 - ��������" << endl;
	cout << "3 - ������������" << endl;
	cout << "c - �����" << endl;
	cout << "--------------------------------------------------------" << endl;
	
	return check_char_cin("c�123");
}

//���������� ������� ���� ������
my_container<book> menu_search()
{
	char ch = main_search();
	cout << endl;

	string str;
	my_container<book> res;

	switch (ch)
	{
	case '1':
	{
		str = check_string_cin("������� ������ �����: ");
		
		sear<string> = &search_author;
		res = boooks.search<string>(sear<string>, str);
	}
	break;
	case '2':
	{
		str = check_string_cin("������� �������� �����: ");
		
		sear<string> = &search_title;
		res = boooks.search<string>(sear<string>, str);
	}
	break;
	case '3':
	{
		str = check_string_cin("������� ������������: ");

		sear<string> = &search_office_publice;
		res = boooks.search<string>(sear<string>, str);
	}
	break;
	}
	return res;
}
//-------����� ���� ������

//----�������������� ��������� � �������
//����� ���� ����������� ��������
my_container<book> get_book_reader(int i)
{
	sear<string> = &search_number;
	return boooks.search<string>(sear<string>, readers[i].r_number_of_ticket);
}
//---����� �������������� �������� � �������

//--��������� ������ ����� ���������
void take_book(int i)
{
	int m;

	string str;
	my_container<book> res;

	str = check_string_cin("������� �������� �����: ");

	sear<string> = &search_title;
	res = boooks.search<string>(sear<string>, str);
	
	if (res.size() > 1)
	{
		str = check_string_cin("�������� ������: ");

		sear<string> = &search_author;
		res = boooks.search<string>(sear<string>, str);
		if (res.size() > 1)
		{
			str = check_string_cin("�������� ������������: ");

			sear<string> = &search_office_publice;
			res = boooks.search<string>(sear<string>, str);
		}
	}

	if (res.size() == 0)
	{
		cout << "����� ����� ���." << endl;
		return;
	}
	if (res.size() == 1)
	{
		m = boooks.search_ind(res[0]);
		if (boooks[m].set_reader(readers[i].r_number_of_ticket, readers[i].surname, 14))
		{
			cout << "����� ����� �� ���� 14 ����." << endl;
		}
		else
		{
			cout << "����� ������." << endl;
			return;
		}
	}
}
//--����� ��������� ������ ����� ���������

//--��������� ����������� ����� ���������
void return_book(int i)
{
	my_container<book> res;
	int k,m;

	res = get_book_reader(i);
	if (res.size() == 0)
	{
		cout << "������������ �� ������ ���." << endl;
	}
	else
	{
		cout << "���� �����: " << endl;
		output_screen(res);

		cout << "����� �� ���� �� ������ �������?" << endl;
		cout << "c - ������" << endl;
		m = check_interval(res.size());

		if (m != -1)
		{
			k = boooks.search_ind(res[m]);
			boooks[k].reset();
			cout << endl << "����� ����������." << endl;
		}
	}
}
//--����� ��������� ����������� ����� ���������


//----���� ������������
//�������� ����
char main_librarian()
{
	cout << "--------------------------------------------------------" << endl;
	cout << "                   �����������������" << endl;
	cout << "--------------------------------------------------------" << endl;
	cout << "1 - �������������� ���������" << endl;
	cout << "2 - �������������� ����" << endl;
	cout << "3 - �������� ������� ������ ���� �� ����" << endl;
	cout << "4 - �������� ������ ���� � ������� ��������" << endl;
	cout << "c - �����" << endl;
	cout << "--------------------------------------------------------" << endl;

	return check_char_cin("c�1234");
}

//------------��������������
//���� ��������������
char menu_edit(string message)
{
	cout << "--------------------------------------------------------" << endl;
	cout << "                " << message << endl;
	cout << "--------------------------------------------------------" << endl;
	cout << "1 - ��������" << endl;
	cout << "2 - �������" << endl;
	cout << "3 - ��������" << endl;
	cout << "c - ������" << endl;
	cout << "--------------------------------------------------------" << endl;

	return check_char_cin("c�123");
}

//�������������� ���������
void menu_edit_readers()
{
	reader r;
	int m;
	char ch = menu_edit("�������������� ���������");
	cout << endl;

	if ((ch != 'c') && (ch != '�'))
	{
		if (ch == '1')
		{
			do
			{
				r.get_data();
				if (readers.push(r))
				{
					cout << "�������� ��������." << endl;
				}
				else
				{
					cout << "����� �������� ����������." << endl;
				}
				cout << "�������� ���? (Y/N)" << endl;
				ch = check_char_cin("Yy��Nn��");
				cout << endl;
			} while ((ch == 'Y') || (ch == 'y') || (ch == '�') || (ch == '�'));
		}
		else
		{
			cout << "--------------------------------------------------------" << endl;
			cout << "�������� ��������:" << endl;
			output_screen(readers);
			cout << "c - ������" << endl;
			cout << "--------------------------------------------------------" << endl;

			m = check_interval(readers.size());
			if (m != -1)
			{
				switch (ch)
				{
				case '2': 
					readers.remove(m);
					cout << "�������� ������." << endl;
					break;
				case '3': 
					cout << "������� ����� ������: " << endl;
					r.get_data();
					readers.edit(m, r);
					cout << "�������� �������." << endl;
					break;
				default:
					break;
				}
			}
		}
	}
}

//�������������� ����
void menu_edit_books()
{
	book b;
	int m;
	char ch = menu_edit("�������������� ����");
	cout << endl;

	if ((ch != 'c') && (ch != '�'))
	{
		if (ch == '1')
		{
			do
			{
				b.get_data();
				if (boooks.push(b))
				{
					cout << "����� ���������." << endl;
				}
				else
				{
					cout << "����� ����� ����������." << endl;
				}
				cout << "�������� ���? (Y/N)" << endl;
				ch = check_char_cin("Yy��Nn��");
				cout << endl;
			} while ((ch == 'Y') || (ch == 'y') || (ch == '�') || (ch == '�'));
		}
		else
		{
			cout << "--------------------------------------------------------" << endl;
			cout << "�������� �����:" << endl;
			output_screen(boooks);
			cout << "c - ������" << endl;
			cout << "--------------------------------------------------------" << endl;

			m = check_interval(boooks.size());
			if (m != -1)
			{
				switch (ch)
				{
				case '2':
					boooks.remove(m);
					cout << "����� �������." << endl;
					break;
				case '3':
					cout << "������� ����� ������: " << endl;
					b.get_data();
					boooks.edit(m, b);
					cout << "����� ��������." << endl;
					break;
				default:
					break;
				}
			}
		}
	}
}
//-------����� ��������������

my_container<book> menu_history()
{
	time_t t = time(NULL);
	tm *tk;
	//����������� ����� � ���������
	tk = localtime(&t);
	date dat = date(tk->tm_mday, 1 + tk->tm_mon, 1900 + tk->tm_year);

	sear<date> = &search_date_beg;
	res = boooks.search<date>(sear<date>, dat);

	sort(res.c.begin(), res.c.end(), &sort_date_beg);

	return res;
}

void menu_state_book()
{
	char ch;
	cout << "--------------------------------------------------------" << endl;
	cout << "�������� ��������� �����:" << endl;
	cout << "1 - ������" << endl;
	cout << "2 - ��������" << endl;
	cout << "3 - ���" << endl;
	cout << "c - ������" << endl;
	cout << "--------------------------------------------------------" << endl;

	ch = check_char_cin("c�123");

	cout << endl;

	res = menu_history();
	switch (ch)
	{
	case '1': 
		output_screen_busy(res);
		break;
	case '2': 
		output_screen_free(res);
	case '3':
		output_full_screen(res);
	default:
		break;
	}
}

void SaveFiles()
{
	boooks.output_file(out_file_name_books);
	readers.output_file(out_file_name_readers);
}

int main()
{
	SetConsoleCP(1251); 
	SetConsoleOutputCP(1251);
	char file_name_books[] = "Books.txt";
	char file_name_readers[] = "Readers.txt";

	//��������� ��������� � �����
	boooks.input_file_bin(out_file_name_books); readers.input_file_bin(out_file_name_readers);
	//boooks.input_file(file_name_books); readers.input_file(file_name_readers);
	
	int i;

	char item;
	char it;
	char ch;

	do
	{
		item = main_menu();
		switch (item)
		{
		case '1':
		{
			cout << endl << "�� ����� ��� ��������." << endl << endl;
			do 
			{
				//�������� ��������
				i = menu_readers();
				cout << endl;
				//���� ������
				if (i != -1)
				{
					do
					{	
						//������������� ���� ��������
						it = menu_reader(i);
						cout << endl;
						switch (it)
						{
						case '1':
						{
							res = menu_search();
							cout << "��������� ������:" << endl;
							output_screen(res);
							if (res.size() > 0)
							{
								cout << "������ �� ����� ����� �� ����? (Y/N)" << endl;
								ch = check_char_cin("Yy��Nn��");
								if ((ch == 'Y') || (ch == 'y') || (ch == '�') || (ch == '�'))
								{
									take_book(i);
									cout << endl;
								}
							}
						}
						break;
						case '2':
						{
							take_book(i);
							cout << endl;
						}
						break;
						case '3':
						{
							return_book(i);
							cout << endl;
						}
						break;
						default:
							break;
						}
						SaveFiles();
					} while ((it != 'c') && (it != '�'));
				}
			} while (i != -1);
		}
		break;
		case '2':
		{
			cout << endl << "�� ����� ��� ������������." << endl << endl;
			do
			{
				it = main_librarian();
				cout << endl;
				switch (it)
				{
				case '1': 
					menu_edit_readers();
					cout << endl;
					break;
				case '2': 
					menu_edit_books();
					cout << endl;
					break;
				case '3': 
				{
					res = menu_history();
					output_screen_busy(res);
					cout << endl;
				}
					break;
				case '4':
					menu_state_book();
					cout << endl;
					break;
				default:
					break;
				}
				SaveFiles();
			} while ((it != 'c') && (it != '�'));
			break;
		}
		break;
		default:
		{
			//���������� ������
			SaveFiles();
			exit(0);
		}
		break;
		}
	} while ((item != 'c') && (item != '�'));

	if (SetConsoleCtrlHandler)
	{
		SaveFiles();
	}

	return 0;
}