#define _CRT_SECURE_NO_WARNINGS
#include<iostream>

using namespace std;

/*
namespace bai
{
	template<class T>
	class shared_ptr
	{
	public:
		shared_ptr(T* ptr = nullptr)
			:_ptr(ptr)
		{
			if (_ptr)
				_pcount = new int(1);
		}
		shared_ptr(const shared_ptr<T>& p)
			:_ptr(p._ptr)
			, _pcount(p._pcount)
		{
			if (_ptr) // �����Դ��Ϊnullptr
				++(*_pcount);
		}

		//p1 == p2
		//p1:δ������Դ------ֱ��p2����
		//p1������������Դ----����p2����֮ǰ���ͷ��Լ�����Դ
		//p1:��������������Դ---p1����--��p2����++
		shared_ptr<T> operator = (const shared_ptr<T>& p)
		{
			if (this != &p)
			{
				if (_ptr && 0 == --(*_pcount))
				{
					delete _ptr;
					delete _pcount;
				}

				_ptr = p._ptr;
				_pcount = p._pcount;
				if (_ptr)
					++(*_pcount);
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


		~shared_ptr()
		{
			if (_ptr && --(*_pcount) == 0)
			{
				delete _ptr;
				delete _pcount;
			}
		}

		int usecount()
		{
			return *_pcount;
		}
	private:
		T* _ptr;
		int* _pcount;
	};
}

void TestFunc()
{
	bai::shared_ptr<int> p1(new int);
	bai::shared_ptr<int> p2(p1);
	bai::shared_ptr<int> p3(new int);
	bai::shared_ptr<int> p4(p3);
	bai::shared_ptr<int> p5;
	p5 = p1;
}*/

//shared_ptr�Ľ�

template<class T>
class DFDel //Ĭ��new�����Ŀռ�
{
public:
	void operator()(T*& p)
	{
		if (p)
		{
			delete p;
			p = nullptr;
		}
	}
};

template<class T>
class Free //malloc����Ŀռ�
{
public:
	void operator()(T*& p)
	{
		if (p)
		{
			free(p);
			p = nullptr;
		}
	}
};



class Fclose
{
public:
	void operator()(FILE* p)
	{
		if (p)
		{
			fclose(p);
			p = nullptr;
		}
	}
};

namespace bai
{
	template<class T,class DF = DFDel<T>>  //DFΪɾ�����ͣ�DFĬ��Ϊnew�����Ŀռ�
	class shared_ptr
	{
	public:
		shared_ptr(T* ptr = nullptr)
			:_ptr(ptr)
		{
			if (_ptr)
				_pcount = new int(1);
		}
		shared_ptr(const shared_ptr<T>& p)
			:_ptr(p._ptr)
			, _pcount(p._pcount)
		{
			if (_ptr) // �����Դ��Ϊnullptr
				++(*_pcount);
		}

		//p1 == p2
		//p1:δ������Դ------ֱ��p2����
		//p1������������Դ----����p2����֮ǰ���ͷ��Լ�����Դ
		//p1:��������������Դ---p1����--��p2����++
		shared_ptr<T> operator = (const shared_ptr<T>& p)
		{
			if (this != &p)
			{
				if (_ptr && 0 == --(*_pcount))
				{
					delete _ptr;
					delete _pcount;
				}

				_ptr = p._ptr;
				_pcount = p._pcount;
				if (_ptr)
					++(*_pcount);
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


		~shared_ptr()
		{
			if (_ptr && --(*_pcount) == 0) //������Դ�����뷽ʽ��ͬ��
			{							//������Ҫ������Դ�����ͣ������ͷŵķ�ʽ
				//delete _ptr;
				DF()(_ptr);				//DF�൱��һ�����ͣ�DF()�൱�ڴ���һ�������Ķ���DF()(_ptr)���൱��DF�������
				delete _pcount;
			}
		}

		int usecount()
		{
			return *_pcount;
		}
	private:
		T* _ptr;
		int* _pcount;
	};
}
void TestFunc()
{
	bai::shared_ptr<int,DFDel<int>> p1(new int);
	bai::shared_ptr<int,DFDel<int>> p2(p1);
	bai::shared_ptr<FILE, Fclose> p3(fopen("666.text" ,"rb")); 
}
int main()
{
	TestFunc();
	system("pause");
	return 0;
}
