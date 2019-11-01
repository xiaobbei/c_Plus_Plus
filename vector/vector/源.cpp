#include<iostream>
#include<vector>
using namespace std;

/*
int main()
{

	/*vector<int> first(4, 10);
	vector<int> second(first);
	int m[] = { 1,2,3,4,5 };
	vector<int> third(m, m + sizeof(m) / sizeof(m[0]));
	for (auto it : first)
	{
		cout << it<<" ";
	}
	for (auto it : second)
	{
		cout << it << " ";
	}
	for (auto it : third)
	{
		cout << it << " ";
	}
	auto it = third.rbegin();
	while (it!=third.rend())
	{
		cout << *it;
		it++;
	}*/

	//find insert接口
	/*int a[] = { 1,2,3,4,5,6,7,8,9 };
	vector<int> v(a, a + sizeof(a) / sizeof(a[0]));
	
	auto pos = find(v.begin(), v.end(), 3);
	v.insert(pos, 10);
	auto it = v.begin();
	while (it != v.end())
	{
		cout << *it << " ";
		it++;
	}*/

	//operator 
	/*int a[] = { 1,2,3,4,5,6,7,8,9 };
	vector<int> v(a, a + sizeof(a) / sizeof(a[0]));
	v[0] = 10;
	for (auto e : v)
	{
		cout << e <<" ";
	}*/
	
	/*int a[] = { 1,2,3,4 };
	vector<int> v(a, a + sizeof(a) / sizeof(a[0]));
	auto pos = find(v.begin(),v.end(),3);
	cout << v.capacity() << endl;
	v.insert(pos, 5);
	v.insert(pos, 6);
	v.insert(pos, 7);
	for (auto e : v)
	{
		cout << e;
	}*/
	/*
	system("pause");
	return 0;
}*/

namespace bai
{
	template<class T>
	class vector
	{
	public:
		typedef T* iterator;
		typedef const T* const_iterator;
		iterator begin()
			return _first;
		iterator end()
			return _end;
		const_iterator cbegin()
			return _first;
		const_iterator cend()
			return _end;
		vector()
			:_first(nullptr)
			, _end(nullptr)
			, _endOfcapacity(nullptr)
		{}
		vector(int n, const T& val = T())
			:_first(nullptr)
			,_end(nullptr)
			,_endOfcapacity(nullptr)
		{
			reserve(n);
			while (n--)
			{
				push_back(val);
			}
		}
		template<class T>
		vector(InputIterator start, InputIterator finish)
		{
			reverse(finish - start);
			while (start != finish)
			{
				push_back(*start);
				++start;
			}
		}
		vector(const vector<T>& v)
			:_first(nullptr)
			,_end(nullptr)
			,_endOfcapacity(nullptr)
		{
			reverse(v.capacity());
			iterator it = begin();
			const_iterator vit = cbegin();
			while (vit != cend())
			{
				*it++ = *vit++;
			}
			_end = _first + v.size();
			_endOfcapacity = _first + v.capacity();
		}

		vector& operator(const vector& v)
		{
			Swap(v);
			return *this;
		}
		~vector()
		{
			delete[] _first;
			_first = _end = _endOfcapacity = nullptr;
		}
		void Swap(vector<T>& v)
		{
			swap(_first, v._first);
			swap(_end, v, _end);
			swap(_endOfcapacity, v._endOfcapacity);
		}
	private:
		iterator _first; //指向数据块开头
		iterator _end;	 //指向数据块结尾
		iterator _endOfcapacity;  //指向容量的尾部
	};
}