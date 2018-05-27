/* Общее требование: выход из программы не должен сбрасывать состояние.
Для этого необходимо предусмотреть хранение информации на жестком диске
(с загрузкой по мере необходимости). Обязательна внимательная обработка
ошибок — программа не должна падать!

4. Реализовать виртуальную библиотеку. Два режима работы
— читатель и библиотекарь (выбирается в меню).

1) Читатель (выбирается из списка доступных) имеет возможность:
- поиска книги по заданному критерию (любое поле или набор полей),
- взять книгу на руки на определенный срок (если книга не на руках),
- вернуть книгу (если она у него на руках).

2) Библиотекарь имеет возможность:
- редактирования списка читателей (регистрация, удаление, редактирование);
- редактирования списка книг;
- просмотра истории выдачи книг на руки;
- просмотра списка книг с текущим статусом.*/

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

//-----------------ПОИСК
template <class TSearch>
int(*sear)(book b1, TSearch b2);

//поиск по читательскому билету
int search_number(book b1, string number_of_ticket2)
{
	return strcmp(b1.number_of_ticket, number_of_ticket2.c_str());
}

//поиск по автору
int search_author(book b1, string author2)
{
	return strcmp(b1.author, author2.c_str());
}

//поиск по названию
int search_title(book b1, string title2)
{
	return strcmp(b1.title, title2.c_str());
}

//поиск по издательству
int search_office_publice(book b1, string office_publice2)
{
	return strcmp(b1.office_publice, office_publice2.c_str());
}

//поиск по дате возврата + просроченные
int search_date_end(book b1, date date_end2)
{
	if (b1.date_end > date_end2)
		return 1;
	return 0;
}

//поиск по дате выдачи + ранневыданные
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
//-----------КОНЕЦ ПОИСКА

//-----------ГЛАВНОЕ МЕНЮ
char main_menu()
{
	cout << "--------------------------------------------------------" << endl;
	cout << "                        Библиотека" << endl;
	cout << "--------------------------------------------------------" << endl;
	cout << "Войти как:" << endl;
	cout << "1 - Читатель" << endl;
	cout << "2 - Библиотекарь" << endl;
	cout << "c - Отмена" << endl;
	cout << "--------------------------------------------------------" << endl;

	return check_char_cin("cс12");
}
//--------КОНЕЦ ГЛАВНОГО МЕНЮ

//--------МЕНЮ ДЛЯ ЧИТАТЕЛЕЙ
//основное меню
int menu_readers()
{
	cout << "--------------------------------------------------------" << endl;
	cout << "                         Читатель" << endl;
	cout << "--------------------------------------------------------" << endl;
	cout << "Выберите номер:" << endl;
	output_screen<reader>(readers);
	cout << "c - Назад" << endl;
	cout << "--------------------------------------------------------" << endl;

	return check_interval(readers.size());
}

//меню читателя
char menu_reader(int i)
{
	cout << "--------------------------------------------------------" << endl;
	print(readers,i);
	cout << "--------------------------------------------------------" << endl;
	cout << "1 - Поиск книги" << endl;
	cout << "2 - Взять книгу" << endl;
	cout << "3 - Вернуть книгу" << endl;
	cout << "c - Назад" << endl;
	cout << "--------------------------------------------------------" << endl;

	return check_char_cin("cс123");
}
//---------КОНЕЦ МЕНЮ ДЛЯ ЧИТАТЕЛЕЙ

//---------МЕНЮ ПОИСКА
//главное меню
char main_search()
{
	cout << "--------------------------------------------------------" << endl;
	cout << "Выберите критерий поиска: " << endl;
	cout << "1 - Автор книги" << endl;
	cout << "2 - Название" << endl;
	cout << "3 - Издательство" << endl;
	cout << "c - Назад" << endl;
	cout << "--------------------------------------------------------" << endl;
	
	return check_char_cin("cс123");
}

//выполнение пунктов меню поиска
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
		str = check_string_cin("Введите автора книги: ");
		
		sear<string> = &search_author;
		res = boooks.search<string>(sear<string>, str);
	}
	break;
	case '2':
	{
		str = check_string_cin("Введите название книги: ");
		
		sear<string> = &search_title;
		res = boooks.search<string>(sear<string>, str);
	}
	break;
	case '3':
	{
		str = check_string_cin("Введите издательство: ");

		sear<string> = &search_office_publice;
		res = boooks.search<string>(sear<string>, str);
	}
	break;
	}
	return res;
}
//-------КОНЕЦ МЕНЮ ПОИСКА

//----ДОПОЛНИТЕЛЬНЫЕ ПРОЦЕДУРЫ И ФУНКЦИИ
//поиск книг конкретного читателя
my_container<book> get_book_reader(int i)
{
	sear<string> = &search_number;
	return boooks.search<string>(sear<string>, readers[i].r_number_of_ticket);
}
//---КОНЕЦ ДОПОЛНИТЕЛЬНЫХ ПРОЦЕДУР И ФУНКЦИЙ

//--ПРОЦЕДУРА ВЗЯТИЯ КНИГИ ЧИТАТЕЛЕМ
void take_book(int i)
{
	int m;

	string str;
	my_container<book> res;

	str = check_string_cin("Введите название книги: ");

	sear<string> = &search_title;
	res = boooks.search<string>(sear<string>, str);
	
	if (res.size() > 1)
	{
		str = check_string_cin("Уточните автора: ");

		sear<string> = &search_author;
		res = boooks.search<string>(sear<string>, str);
		if (res.size() > 1)
		{
			str = check_string_cin("Уточните издательство: ");

			sear<string> = &search_office_publice;
			res = boooks.search<string>(sear<string>, str);
		}
	}

	if (res.size() == 0)
	{
		cout << "Такой книги нет." << endl;
		return;
	}
	if (res.size() == 1)
	{
		m = boooks.search_ind(res[0]);
		if (boooks[m].set_reader(readers[i].r_number_of_ticket, readers[i].surname, 14))
		{
			cout << "Книга взята на срок 14 дней." << endl;
		}
		else
		{
			cout << "Книга занята." << endl;
			return;
		}
	}
}
//--КОНЕЦ ПРОЦЕДУРЫ ВЗЯТИЯ КНИГИ ЧИТАТЕЛЕМ

//--ПРОЦЕДУРА ВОЗВРАЩЕНИЯ КНИГИ ЧИТАТЕЛЕМ
void return_book(int i)
{
	my_container<book> res;
	int k,m;

	res = get_book_reader(i);
	if (res.size() == 0)
	{
		cout << "Задолжностей по книгам нет." << endl;
	}
	else
	{
		cout << "Ваши книги: " << endl;
		output_screen(res);

		cout << "Какую из книг вы хотите вернуть?" << endl;
		cout << "c - Отмена" << endl;
		m = check_interval(res.size());

		if (m != -1)
		{
			k = boooks.search_ind(res[m]);
			boooks[k].reset();
			cout << endl << "Книга возвращена." << endl;
		}
	}
}
//--КОНЕЦ ПРОЦЕДУРЫ ВОЗВРАЩЕНИЯ КНИГИ ЧИТАТЕЛЕМ


//----МЕНЮ БИБЛИОТЕКАРЯ
//основное меню
char main_librarian()
{
	cout << "--------------------------------------------------------" << endl;
	cout << "                   Администрирование" << endl;
	cout << "--------------------------------------------------------" << endl;
	cout << "1 - Редактирование читателей" << endl;
	cout << "2 - Редактирование книг" << endl;
	cout << "3 - Просмотр истории выдачи книг на руки" << endl;
	cout << "4 - Просмотр списка книг с текущим статусом" << endl;
	cout << "c - Назад" << endl;
	cout << "--------------------------------------------------------" << endl;

	return check_char_cin("cс1234");
}

//------------РЕДАКТИРОВАНИЕ
//меню редактирования
char menu_edit(string message)
{
	cout << "--------------------------------------------------------" << endl;
	cout << "                " << message << endl;
	cout << "--------------------------------------------------------" << endl;
	cout << "1 - Добавить" << endl;
	cout << "2 - Удалить" << endl;
	cout << "3 - Изменить" << endl;
	cout << "c - Отмена" << endl;
	cout << "--------------------------------------------------------" << endl;

	return check_char_cin("cс123");
}

//редактирование читателей
void menu_edit_readers()
{
	reader r;
	int m;
	char ch = menu_edit("Редактирование читателей");
	cout << endl;

	if ((ch != 'c') && (ch != 'с'))
	{
		if (ch == '1')
		{
			do
			{
				r.get_data();
				if (readers.push(r))
				{
					cout << "Читатель добавлен." << endl;
				}
				else
				{
					cout << "Такой читатель существует." << endl;
				}
				cout << "Добавить еще? (Y/N)" << endl;
				ch = check_char_cin("YyУуNnНн");
				cout << endl;
			} while ((ch == 'Y') || (ch == 'y') || (ch == 'У') || (ch == 'у'));
		}
		else
		{
			cout << "--------------------------------------------------------" << endl;
			cout << "Выберите читателя:" << endl;
			output_screen(readers);
			cout << "c - Отмена" << endl;
			cout << "--------------------------------------------------------" << endl;

			m = check_interval(readers.size());
			if (m != -1)
			{
				switch (ch)
				{
				case '2': 
					readers.remove(m);
					cout << "Читатель удален." << endl;
					break;
				case '3': 
					cout << "Введите новые данные: " << endl;
					r.get_data();
					readers.edit(m, r);
					cout << "Читатель изменен." << endl;
					break;
				default:
					break;
				}
			}
		}
	}
}

//редактирование книг
void menu_edit_books()
{
	book b;
	int m;
	char ch = menu_edit("Редактирование книг");
	cout << endl;

	if ((ch != 'c') && (ch != 'с'))
	{
		if (ch == '1')
		{
			do
			{
				b.get_data();
				if (boooks.push(b))
				{
					cout << "Книга добавлена." << endl;
				}
				else
				{
					cout << "Такая книга существует." << endl;
				}
				cout << "Добавить еще? (Y/N)" << endl;
				ch = check_char_cin("YyУуNnНн");
				cout << endl;
			} while ((ch == 'Y') || (ch == 'y') || (ch == 'У') || (ch == 'у'));
		}
		else
		{
			cout << "--------------------------------------------------------" << endl;
			cout << "Выберите книгу:" << endl;
			output_screen(boooks);
			cout << "c - Отмена" << endl;
			cout << "--------------------------------------------------------" << endl;

			m = check_interval(boooks.size());
			if (m != -1)
			{
				switch (ch)
				{
				case '2':
					boooks.remove(m);
					cout << "Книга удалена." << endl;
					break;
				case '3':
					cout << "Введите новые данные: " << endl;
					b.get_data();
					boooks.edit(m, b);
					cout << "Книга изменена." << endl;
					break;
				default:
					break;
				}
			}
		}
	}
}
//-------КОНЕЦ РЕДАКТИРОВАНИЯ

my_container<book> menu_history()
{
	time_t t = time(NULL);
	tm *tk;
	//преобразует время в структуру
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
	cout << "Выберите состояние книги:" << endl;
	cout << "1 - Занята" << endl;
	cout << "2 - Свободна" << endl;
	cout << "3 - Все" << endl;
	cout << "c - Отмена" << endl;
	cout << "--------------------------------------------------------" << endl;

	ch = check_char_cin("cс123");

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

	//загружаем читателей и книги
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
			cout << endl << "Вы вошли как читатель." << endl << endl;
			do 
			{
				//выбираем читателя
				i = menu_readers();
				cout << endl;
				//если выбран
				if (i != -1)
				{
					do
					{	
						//предоставляем меню читателю
						it = menu_reader(i);
						cout << endl;
						switch (it)
						{
						case '1':
						{
							res = menu_search();
							cout << "Результат поиска:" << endl;
							output_screen(res);
							if (res.size() > 0)
							{
								cout << "Хотите ли взять книгу на руки? (Y/N)" << endl;
								ch = check_char_cin("YyУуNnНн");
								if ((ch == 'Y') || (ch == 'y') || (ch == 'У') || (ch == 'у'))
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
					} while ((it != 'c') && (it != 'с'));
				}
			} while (i != -1);
		}
		break;
		case '2':
		{
			cout << endl << "Вы вошли как библиотекарь." << endl << endl;
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
			} while ((it != 'c') && (it != 'с'));
			break;
		}
		break;
		default:
		{
			//сохранение файлов
			SaveFiles();
			exit(0);
		}
		break;
		}
	} while ((item != 'c') && (item != 'с'));

	if (SetConsoleCtrlHandler)
	{
		SaveFiles();
	}

	return 0;
}