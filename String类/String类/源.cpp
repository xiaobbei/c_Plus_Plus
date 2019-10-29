#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<assert.h>
#include<string.h>
#include<string>
using namespace std;

/*½â¾öÇ³¿½±´(Ò»)
class String
{
public:
	String(const char* str = "")
	{
		if (str == nullptr)
		{
			assert(str);
			return;
		}
		_str = new char[strlen(str) + 1];
		strcpy(_str, str);
	}
	String(String& s)
		:_str(new char[strlen(s._str)+1])
	{
		strcpy(_str, s._str);
	}
	String operator = (String& s)
	{
		if (this != &s)
		{
			delete _str;
			_str = new char[strlen(s._str) + 1];
			strcpy(_str, s._str);
		}
		return *this;
	}
	~String()
	{
		if (_str)
		{
			delete[] _str;
			_str = nullptr;
		}
	}
private:
	char *_str;
};
*/
class String
{
public:
	typedef char* iterator;
	String(const char* s = "")
		:_size(0)
		,_capacity(0)
		,_str(new char[strlen(s) + 1])
	{
		
		_size = strlen(s);
		_capacity = 15;
		strcpy(_str, s);
	}
	String(const String& s)
	{
		String temp(s._str);
		this->Swap(temp);
	}
	String operator = (const String& s)
	{
		if (this != &s)
		{
			String temp(s._str);
			this->Swap(temp);
		}
		return *this;
	}
	void Swap(String& s)
	{
		swap(_str, s._str);
		swap(_size, s._size);
		swap(_capacity, s._capacity);
	}
	~String()
	{
		if (_str)
		{
			delete[] _str;
			_str = nullptr;
		}
	}
	iterator begin()
	{
		return _str;
	}
	iterator end()
	{
		return _str + _size;
	}
	String& operator += (char c)
	{
		pushBack(c);
		return *this;
	}
	void Append(char c)
	{
		pushBack(c);
	}
	void Clear()
	{
		_size = 0;
		_str[_size] = '\0';
	}
	const char* C_str()const
	{
		return _str;
	}
	size_t size()
	{
		return _size;
	}
	size_t capacity()
	{
		return _capacity;
	}
	bool Empty()const
	{
		if (_size > 0)
			return false;
		else
			return true;
	}

	const char& operator[](size_t index)const
	{
		assert(index < _size);
		return _str[index];
	}
	bool operator == (const String& s)
	{
		if (strcmp(_str, s._str) == 0)
			return true;
		return false;
	}
	bool operator !=(const String& s)
	{
		return !operator==(s);
	}
	bool operator > (const String& s)
	{
		if (strcmp(_str, s._str) > 0)
			return true;
		return false;
	}
	bool operator >= (const String& s)
	{
		if (strcmp(_str, s._str) >= 0)
			return true;
		return false;
	}
	bool operator < (const String& s)
	{
		if (strcmp(_str, s._str) < 0)
			return true;
		return false;
	}
	bool operator <= (const String& s)
	{
		if (strcmp(_str, s._str) <= 0)
			return true;
		return false;
	}
	void pushBack(char c)
	{
		if (_size == _capacity)
			Reverse(2 * _capacity);
		_str[_size++] = c;
		_str[_size] = '\0';
	}
	void Resize(size_t Newsize,char c = '\0')
	{
		if (Newsize > _size)
		{
			if (Newsize > _capacity)
			{
				Reverse(Newsize);
			}
			memset(_str + _size, c, Newsize);
		}
		_size = Newsize;
		_str[_size] = '\0';
	}
	void Reverse(size_t Newcapacity)
	{
		if (Newcapacity > _capacity)
		{
			char* str = new char[Newcapacity + 1];
			strcpy(str, _str);
			delete[] _str;
			_str = str;
			_capacity = Newcapacity;
		}
	}
	

private:
	friend ostream& operator<<(ostream& _cout,  String& s);
	friend istream& operator >> (istream& _cin, String& s);
	char *_str;
	int _size;
	int _capacity;
};

ostream & operator<<(ostream & _cout,  String & s)
{
	_cout << s._str;
	return _cout;
}
istream& operator >> (istream& _cin, String& s)
{
	s._str = new char[256];
	_cin >> s._str;
	return _cin;
}
void test()
{
	String s1("hello");
	cout << s1.size();
	String s2(s1);
	String s3 = s1;
	s1 += 't';
	cout<<s1.size();
	cout << s1;
	cout << endl;
	auto it = s1.begin();
	while (it != s1.end())
	{
		cout << *it;
		it++;
	}
	s1.pushBack('!');
	cout << s1;
}
int main()
{
	test();
	system("pause");
	return 0;
}

