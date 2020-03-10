#include<iostream>

using namespace std;


class Date
{
public:
	Date() { cout << "Date()" << endl; }
	~Date(){ cout << "~Date()" << endl; }
	int _year;
	int _month;
	int _day;
};


template<class T>
class Auto_ptr
{
public:
	Auto_ptr(T* ptr = nullptr)
		:_ptr(ptr)
	{
		cout << "Auto_ptr()" << endl;
	}

	Auto_ptr(Auto_ptr<T>& p)
		:_ptr(p._ptr)
	{
		p._ptr = nullptr; // ×ÊÔ´×ªÒÆ
	}


	Auto_ptr& operator = (Auto_ptr<T>& p)
	{
		if (this != &p)
		{
			if (_ptr)
				delete _ptr;
			_ptr = p._ptr;
			p._ptr = nullptr;
		}
		return *this;
	}

	T& operator*()
	{
		return *_ptr;
	}

	T* operator->()
	{
		return _ptr;
	}

	~Auto_ptr()
	{
		if (_ptr)
			delete _ptr;
	}
	
private:
	T* _ptr;
};


int main()
{
	Auto_ptr<Date> d1 = new Date;

	Auto_ptr<Date> d2(d1);

	cout << d2->_year;


	system("pause");
	return 0;
}