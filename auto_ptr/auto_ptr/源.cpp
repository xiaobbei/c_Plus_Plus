#include<iostream>

using namespace std;
/*
namespace bai
{
	template<class T>
	class auto_ptr
	{
	public:
		auto_ptr(T* ptr = nullptr)
			:_ptr(ptr)
		{}

		auto_ptr(auto_ptr<T>& p) //��Դ��ת��
			:_ptr(p._ptr)
		{
			p._ptr = nullptr;
		}

		auto_ptr<T>& operator = (auto_ptr<T>& p)
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

		T& operator* ()
		{
			return *_ptr;
		}

		T* operator->()
		{
			return _ptr;
		}

		~auto_ptr()
		{
			if (_ptr)
				delete _ptr;
		}
	private:
		T* _ptr;
	};
}
*/

//auto_ptr�Ľ��棬ͨ��һ����������������Դ�ͷŵ�Ȩ��
namespace bai
{
	template<class T>
	class auto_ptr
	{
	public:
		auto_ptr(T* ptr = nullptr)
			:_ptr(ptr)
			, _owner(false)
		{	
			if (_ptr)
				_owner = true;
		}

		auto_ptr( auto_ptr<T>& p)
			:_ptr(p._ptr)
			,_owner(p._owner)
		{
			p._owner = false;
		}
		
		auto_ptr& operator*()
		{
			return *_ptr;
		}

		auto_ptr* operator->()
		{
			return _ptr;
		}

		auto_ptr<T>& operator = (auto_ptr& p)
		{
			if (this != &p)
			{
				if (_ptr && _owner)
					delete _ptr;
				_ptr = p._ptr;
				_owner = p._owner;
				p._owner = false;
			}
			return *this;
		}

		~auto_ptr()
		{
			if (_ptr && _owner)
				delete _ptr;
		}
	private: 
		T* _ptr;
		bool _owner;
	};
}
void Test_auto_ptr()
{
	//��Ϊauto_ptr���ײ���ǳ������������Ҫ�Ը�ֵ������Լ��������캯��������д������ʹ�ñ�����Ĭ�ϵġ�
	bai::auto_ptr<int> p1(new int);
	bai::auto_ptr<int> p2(p1);
	p1 = p2;
}
int main()
{
	Test_auto_ptr();
	system("pause");
	return 0;
}