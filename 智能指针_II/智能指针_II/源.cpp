#include<iostream>
using namespace std;

struct A
{
	int a;
	int b;
};
template<class T>
class SmartPtr
{
public:
	SmartPtr(T *ptr = nullptr)
		:_ptr(ptr)
	{}
	~SmartPtr()
	{
		if (_ptr)
			delete _ptr;
	}
	T& operator*()//����ָ�����������
	{
		return *_ptr;
	}
	T* operator->()//���ص�ַ
	{
		return _ptr;
	}
protected:
	T* _ptr;
};

void TestFunc()
{
	SmartPtr<int> sp(new int);
	SmartPtr<A> sp2(new A); 
	sp2->a = 1;
	sp2->b = 2;
}


int main()
{
	system("pause");
	return 0;
}

