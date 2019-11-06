#include<iostream>

using namespace std;
template<class T>
class LinearList
{
public:
	LinearList(int MaxListSize = 10);
	LinearList()
	{
		delete[]element;
	}
	bool Empty()const
	{
		return length == 0;
	}
	int Length()const
	{
		return length;
	}
	int capacity()const
	{
		return MaxSize;
	}
	bool Find(int k, T& x)const; //将第k个元素，放入x中
	int Search(const T& x)const;
	LinearList<T>& Delete(int k, T& x);//删除第K个元素，并保存到x中
	LinearList<T>& Insert(int k, T& x);//在第k个元素后面插入x
	void OutPut(ostream& out)const;
private:
	int length;
	int MaxSize;
	T* element;
};

template<class T>
LinearList<T>::LinearList(int MaxListSize)
{
	MaxSize = MaxListSize;
	element = new T[MaxSize];
	length = 0;
}
template<class T>
bool LinearList<T>::Find(int k, T& x)const
{
	if (k<0 || k>length)
		return false;
	x = element[k - 1];
	return true;
}

template<class T>
int LinearList<T>::Search(const T& x)const
{
	for (int i = 0; i < length; ++i)
	{
		if (element[i] == x)
			return i;
	}
	return 0;
}

template<class T>
LinearList<T>& LinearList<T>::Delete(int k, T& x)
{
	x = element[k];
	for (int i = k + 1; i < length; ++i)
	{
		element[i - 1] = element[i];
	}
	length--;
	return x;
}

template<class  T>
LinearList<T>& LinearList<T>::Insert(int k, T& x)
{
	if (k<0 || k>length)
		throw OutOfBounds();
	if (length == MaxSize)
	{
		T* newElement = new T[2 * MaxSize];
		for (int i = 0; i < length; ++i)
		{
			newElement[i] = element[i];
		}
		delete[] element;
		element = newElement;
	}
	for (int i = length - 1; i >= k; i--)
	{
		element[i+1] = element[i];
	}
	element[k] = x;
	length++;
	return *this;
}


int main()
{
	LinearList<int> r(5);
	cout << "Length =" << r.Length() << endl;
	cout << "MaxSize=" << r.capacity() << endl;
	system("pause");
	return 0;
}