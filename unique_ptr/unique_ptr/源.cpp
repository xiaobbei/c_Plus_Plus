#include<iostream>

using namespace std;

class Date
{
private:
	int _year;
	int _month;
	int _day;
};

template<class T>
class Unique_ptr
{
public:
	Unique_ptr(T* ptr = nullptr)
		:_ptr(ptr)
	{}

	Unique_ptr(Unique_ptr<T>& u) = delete;
	Unique_ptr& operator = (Unique_ptr<T>& u) = delete;

	T* operator->()
	{
		return _ptr;
	}

	T& operator*()
	{
		return *_ptr;
	}

	~Unique_ptr()
	{
		if (_ptr)
			delete _ptr;
	}
private:
	T* _ptr;
};
int main()
{

	Unique_ptr<Date> d = new Date;
	
	system("pause");
	return 0;
}