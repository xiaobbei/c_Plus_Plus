#include<iostream>

using namespace std;


template<class T>
class Node
{
public:
	Node()
	{
		data = 0;
		next = nullptr;
	}
	T data;
	Node<T>* next;
};

template<class T>
class ListNode
{
public:
	ListNode()
	{
		phead = new Node<T>();
	};
	~ListNode()
	{
		delete phead;
	}
	ListNode<T>& Insert(int k, const T& x);
	int Find(const T& x);
	bool Delete(int k);
	int GetLength()const;
	void PrintList();
	void Erase();
private:
	Node<T>* phead;
};


template<class T>
ListNode<T>& ListNode<T>::Insert(int k, const T& x)
{
	if (k < 0)
		cout << "²åÈëÎ»ÖÃ´íÎó" << endl;
	Node<T>* p = phead;
	for (int index = 0; index < k &&p; index++)
	{
		p = p->next;
	}
	if (k > 0 && !p)
		cout << "²åÈëÎ»ÖÃ´íÎó" << endl;
	Node<T>* pcur = new Node<T>;
	pcur->data = x;
	pcur->next = p->next;
	p->next = pcur;
	return *this;
}

template<class T>
void ListNode<T>::PrintList()
{
	Node<T>* p = phead->next;
	while (p)
	{
		cout << p->data << "->";
		p = p->next;
	}
}

template<class T>
int ListNode<T>::Find(const T& x)
{
	int index = 1;
	Node<T>* p = phead->next;
	while (p)
	{
		if (p->data == x)
			return index;
		p = p->next;
		index++;
	}
	return -1;
}

template<class T>
int ListNode<T>::GetLength()const
{
	int length = 0;
	Node<T>* p = phead->next;
	while (p)
	{
		length++;
		p = p->next;
	}
	return length;
}

template<class T>
bool ListNode<T>::Delete(int k)
{
	Node<T>* p = phead->next;
	if (k<0 || k> GetLength())
		return false;
	for (int i = 1; i < k; ++i)
	{
		p = p->next;
	}
	p->next = p->next->next;
	return true;
}

template<class T>
void ListNode<T>::Erase()
{
	Node<T>* p = phead;
	Node<T>* pcur ;
	while (p)
	{
		pcur = p->next;
		delete p;
		p = pcur;
	}
}
int main()
{
	ListNode<int>* phead = new ListNode<int>();
	phead->Insert(0, 1);
	phead->Insert(1, 1);
	phead->Insert(2, 2);
	phead->Insert(3, 3);
	phead->Insert(4, 4);
	cout<< phead->GetLength();
	cout << endl;
	phead->PrintList();
	phead->Delete(2);
	cout<<endl;
	phead->PrintList();

	cout << endl;
	cout<< phead->Find(3);
	system("pause");
	return 0;
}