#include<iostream>
#include<string>
using namespace std;

//RAII
/*
template<class T>
class Smartptr
{
public:
	Smartptr(T *ptr = nullptr)
		:_ptr(ptr)
	{}
	~Smartptr()
	{
		if(_ptr)
			delete _ptr;
	}
private:
	T* _ptr;
};
*/

/*����* ��->�����
template<class T>

class Smartptr
{
public:
	Smartptr(T *ptr = nullptr)
		:_ptr(ptr)
	{}
	~Smartptr()
	{
		if (_ptr)
			delete _ptr;
	}
	T& operator*()
	{
		return *_ptr;
	}
	T* operator->()
	{
		return _ptr;
	}
private:
	T* _ptr;
};

struct Date
{
	int a;
	int b;
};
void testSmartptr()
{
	Smartptr<int> sp(new int);
	*sp = 10;
	cout << *sp << endl;
	Smartptr<Date> sp2(new Date);
	sp2->a = 1;
	sp2->b = 2;
	cout << sp2->a << sp2->b << endl;
}
*/

//autoPtr �⺯��
/*
namespace bai
{
	template<class T>
	class AutoPtr
	{
	public:
		AutoPtr(T* ptr)
			:_ptr(ptr)
		{}
		~Date()
		{
			if (_ptr)
				delete _ptr;
		}
		AutoPtr(AutoPtr<T>&sp) //�������캯��
			:_ptr(sp._ptr)
		{
			sp._ptr = nullptr;
		}
		AutoPtr<T>& operator=(AutoPtr<T>&sp)
		{
			if (*this != sp)
			{
				if (_ptr)
					delete _ptr;
				_ptr = sp._ptr;
				sp._ptr = nullptr;
			}			return *this;

		}
		AutoPtr* operator->()
		{
			return this;
		}
		AutoPtr& operator*()
		{
			return *this;
		}
	private:
		T* _ptr;
	};
}
struct Date
{
	int _year;
	int _month;
};
*/

//unique_ptr
/*
template<class T>
class  Uniqueptr
{
public:
	Uniqueptr(T* ptr = nullptr)
		:_ptr(ptr)
	{}
	~Uniqueptr()
	{
		if (_ptr)
			delete _ptr;[]
	}
	Uniqueptr* operator->()
	{
		return this;
	}
	Uniqueptr& operator*()
	{
		return *this;
	}
	Uniqueptr(Uniqueptr<T>const &) = delete;
	Uniqueptr<T>& operator = (Uniqueptr<T>const &) = delete;
private:
	
	T* _ptr;
};
*/
//#include<mutex> //�������򻥳��� 
//template<class T>
//class shared_ptr 
//{
//public:
//	shared_ptr(T *ptr)
//		:_ptr(ptr)
//		,_pcount(new int(1))
//		//,_pmutex(new mutex)
//	{
//	}
//	~shared_ptr()
//	{
//		Release();
//	}
//	shared_ptr(const shared_ptr<T> &sp)
//		:_ptr(sp._ptr)
//		,_pcount(sp._pcount)
//		//,_pmutex(sp._pmutex)
//	{
//		addcount();
//	}
//	shared_ptr<T>& operator=(const shared_ptr<T> &sp)
//	{
//		if (_ptr != sp._ptr)
//		{
//			Release(); //�ͷžɿռ�
//			_ptr = sp._ptr;
//			_pcount = sp._pcount;
//			addcount();			//����+1
//			//_pmutex = sp._pmutex;
//		}
//		return *this;
//	}
//
//	T& operator*()
//	{
//		return *this;
//	}
//	T* operator->()
//	{
//		return this;
//	}
//
//	void addcount()
//	{
//		//_pmutex->lock(); //����
//		++(*_pcount);			//����+1
//		//_pmutex->unlock();//����
//	}
//
//	void Release()
//	{
//		//bool deleteflag = false;
//		if (0 == --(*_pcount))
//		{
//			delete _ptr;
//			delete _pcount;
//		}
//		/*if (deleteflag == ture)
//		{
//			delete _pmutex;
//		}*/
//	}
//
//	int usecount()
//	{
//		return *_pcount;
//	}
//private:
//	T * _ptr;
//	int *_pcount;
//	//mutex* _pmutex; ���̼߳���
//};
#include <thread>
#include <mutex>
template <class T>
class SharedPtr
{
public:
	SharedPtr(T* ptr = nullptr)
		: _ptr(ptr)
		, _pRefCount(new int(1))
		, _pMutex(new mutex)
	{}
	~SharedPtr() { Release(); }
	SharedPtr(const SharedPtr<T>& sp)
		: _ptr(sp._ptr)
		, _pRefCount(sp._pRefCount)
		, _pMutex(sp._pMutex)
	{
		AddRefCount();
	}
	// sp1 = sp2
	SharedPtr<T>& operator=(const SharedPtr<T>& sp)
	{
		//if (this != &sp)
		if (_ptr != sp._ptr)
		{
			// �ͷŹ���ľ���Դ
			Release();
			// ��������¶������Դ�����������ü���
			_ptr = sp._ptr;
			_pRefCount = sp._pRefCount;
			_pMutex = sp._pMutex;
			AddRefCount();
		}
		return *this;
	}
	T& operator*() { return *_ptr; }
	T* operator->() { return _ptr; }
	int UseCount() { return *_pRefCount; }
	T* Get() { return _ptr; }
	void AddRefCount()
	{
		// ��������ʹ�ü�1��ԭ�Ӳ���
		_pMutex->lock();
		++(*_pRefCount);
		_pMutex->unlock();
	}
private:
	void Release()
	{
		bool deleteflag = false;
			//_pMutex.lock();
		if (--(*_pRefCount) == 0)
		{
			delete _ptr;
			delete _pRefCount;
			deleteflag = true;
		}
		//_pMutex.unlock();
		if (deleteflag == true)
			delete _pMutex;
	}
private:
	int* _pRefCount; // ���ü���
	T* _ptr; // ָ�������Դ��ָ��
	mutex* _pMutex; // ������
};
int main()
{
	SharedPtr<int> sp1(new int(10));
	SharedPtr<int> sp2(sp1);
	*sp2 = 20;
	cout << sp1.UseCount() << endl;
	cout << sp2.UseCount() << endl;
	SharedPtr<int> sp3(new int(10));
	sp2 = sp3;
	cout << sp1.UseCount() << endl;
	cout << sp2.UseCount() << endl;
	cout << sp3.UseCount() << endl;
	sp1 = sp3;
	cout << sp1.UseCount() << endl;
	cout << sp2.UseCount() << endl;
	cout << sp3.UseCount() << endl;
	system("pause");
	return 0;
}

