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
			if (_ptr) // 如果资源不为nullptr
				++(*_pcount);
		}

		//p1 == p2
		//p1:未管理资源------直接p2共享
		//p1：单独管理资源----在于p2共享之前先释放自己的资源
		//p1:与其他对象共享资源---p1计数--，p2计数++
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

//shared_ptr改进

template<class T>
class DFDel //默认new出来的空间
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
class Free //malloc申请的空间
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
	template<class T,class DF = DFDel<T>>  //DF为删除类型，DF默认为new出来的空间
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
			if (_ptr) // 如果资源不为nullptr
				++(*_pcount);
		}

		//p1 == p2
		//p1:未管理资源------直接p2共享
		//p1：单独管理资源----在于p2共享之前先释放自己的资源
		//p1:与其他对象共享资源---p1计数--，p2计数++
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
			if (_ptr && --(*_pcount) == 0) //由于资源的申请方式不同，
			{							//所以需要根据资源的类型，定制释放的方式
				//delete _ptr;
				DF()(_ptr);				//DF相当于一种类型，DF()相当于创建一个无名的对象，DF()(_ptr)，相当于DF对象调用
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
