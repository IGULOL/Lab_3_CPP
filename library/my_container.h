#pragma once
#include <vector>
#include <algorithm>

using namespace std;

template <class Type>
class my_container
{
protected:
	

public:
	vector<Type> c;

	//�������� �� �������
	bool is_empty()
	{
		return c.empty();
	}
	//���������� ���������
	int size()
	{
		return c.size();
	}

	//���������� � ���������
	bool push(Type el)
	{
		bool ok;
		for (int i = 0; i < c.size(); i++)
		{
			if (c[i] == el)
			{
				return false;
			}
		}
		c.push_back(el);
		return true;
	}

	//�������� �������� ����������
	bool remove(Type el)
	{
		if ((c.size() <= 0))
		{
			return false;
		}
		for (int i = 0; i < c.size(); i++)
		{
			if (c[i] == el)
			{
				c.erase(c.begin() + i);
				return true;
			}
		}
		return false;
	}

	//����� �������
	int search_ind(Type el)
	{
		if ((c.size() <= 0))
		{
			return -1;
		}
		for (int i = 0; i < c.size(); i++)
		{
			if (c[i] == el)
			{
				return i;
			}
		}
		return -1;
	}

	//�������� �������� ����������
	bool remove(int i)
	{
		if ((i >= c.size()) || (i < 0))
		{
			return false;
		}
		c.erase(c.begin() + i);
		return true;
	}

	//��������� ��������
	bool edit(int i, Type el)
	{
		if ((i >= c.size()) || (i < 0))
		{
			return false;
		}
		c[i] = el;
		return true;
	}
	

	//���� ���������� �� �����
	bool input_file(string name)
	{
		Type el;
		ifstream infile(name);
		string str; //��� �����������
		c.clear();
		bool ok;
		if (!infile)
		{
			ok = false;
		}
		else
		{
			ok = true;
			while ((infile >> el) && ok)
			{
				c.push_back(el);
				getline(infile, str); //��������� �����������
				ok = (str == "");
			}
			infile.close();
		}
		if (!ok)
		{
			c.clear();
		}
		return ok;
	}

	//���� ���������� �� �����
	bool input_file_bin(string name)
	{
		Type el;
		c.clear();
		ifstream infile(name, ios::binary);
		if (infile)
		{
			while (infile.read(reinterpret_cast<char*>(&el), sizeof(el)))
			{
				c.push_back(el);
			}
			infile.close();
			return true;
		}
		else
		{
			return false;
		}
	}

	//������ ���������� � ����
	bool output_file(string name)
	{
		Type el;
		ofstream outfile(name, ios::binary);
		if (outfile)
		{			
			for (vector<Type>::const_iterator iter = c.begin(); iter != c.end(); ++iter)
			{
				el = *iter;
				outfile.write(reinterpret_cast<char*>(&el), sizeof(el));
			}
			outfile.close();
			return true;
		}
		else
		{
			return false;
		}
	}

	/*�������� �����
	(������� ������������ �������� ��������, TSearch - ��� ��������)*/
	template <class TSearch>
	my_container<Type> search(int(*equal)(Type el, TSearch search), TSearch sear)
	{
		my_container<Type> find;
		for (vector<Type>::const_iterator iter = c.begin(); iter != c.end(); ++iter)
		{
			if ((*equal)(*iter, sear) == 0)
			{
				find.push(*iter);
			}
		}
		return find;
	}

	/*�������� �����
	(������� ������������ �������� ��������, TSearch - ��� ��������, ������� ��� ���������� �� ��������)*/
	template <class TSearch>
	my_container<Type> bin_search(int(*equal)(Type el, TSearch search), TSearch sear,
		bool(*compare)(Type el1, Type el2))
	{
		sort(c.begin(), c.end(), compare);

		int n;
		int left = 0;
		int right = c.size();
		int mid = 0;
		bool find = false;
		while ((left <= right) && !find)
		{
			mid = ((left + right) / 2);
			n = (*equal)(c[mid], sear);
			if (n == 1)        //(c[mid] > element � sear)
			{
				right = mid - 1;
			}
			else
			{
				if (n == -1)   //(element � sear < c[mid])
				{
					left = mid + 1;
				}
				else
				{
					find = true;
				}
			}
		}

		my_container<Type> res;
		if (find)
		{
			//���� ������
			for (int i = mid; (i < c.size()) && ((*equal)(c[i], sear) == 0); ++i)
			{
				res.push(c[i]);
			}
			mid--;
			//���� �����
			for (int i = mid; (i >= 0) && ((*equal)(c[mid], sear) == 0); --i)
			{
				res.push(c[i]);
			}
		}
		return res;
	}

	Type& operator[] (int index) 
	{
		if (index < size())
			return c[index];	// ���������� ������
	}
};
