#include<iostream>

using namespace std;

namespace Bai
{
	template<class T>
	class ListNode
	{
	public:
		ListNode(const T& value = T())
			:val (value)
			,_pnext(nullptr)
			,_prev(nullptr)
		{}
		T val;
		ListNode<T>* _pnext;
		ListNode<T>* _prev;
	};

	template<class T,class Ref,class Ptr>
	class ListIterator
	{
	public:
		typedef ListNode<T>* PNode;
		typedef ListIterator<T, Ref, Ptr>Self;
		PNode _node;

		ListIterator(PNode node)
			:_node(node)
		{}

		Ref operator*()
		{
			return _node->val;
		}

		Ptr operator->()
		{
			return &(_node->val);
		}

		Self& operator++()
		{
			_node = _node->_pnext;
			return *this;
		}

		Self operator++(int)
		{
			Self temp(*this);
			_node = _node->_pnext;
			return temp;
		}

		Self operator--()
		{
			_node = _node->_prev;
			return *this;
		}

		Self operator--(int)
		{
			Self temp(*this);
			_node = _node->_prev;
			return temp;
		}

		bool operator!=(const Self& x)
		{
			return _node != x._node;
		}

		bool operator==(const Self& x)
		{
			return _node == x._node;
		}

	};

	template<class T>
	class List
	{
	public:
		typedef ListNode<T> Node;
		typedef Node* PNode;
		typedef ListIterator<T, T&, T*> iterator;
		List()
		{
			_head = new Node;
			_head->_pnext = _head;
			_head->_prev = _head;
		}

		List(int n, const T& val = T())
		{
			_head = new Node;
			_head->_pnext = _head;
			_head->_prev = _head;

			for (int i = 0; i < n; ++i)
			{
				PushBack(val);
			}
		}
		template<class Iterator>
		List(Iterator first, Iterator last)
		{
			_head = new Node;
			_head->_pnext = _head;
			_head->_prev = _head;
			while (first != last)
			{
				PushBack(*first);
				first++;
			}
		}

		List(const List<T>& x)
		{
			_head = new Node;
			_head->_pnext = _head;
			_head->_prev = _head;

			List<T> temp(x.begin(), x.end());
			swap(_head, temp);
		}

		List<T>& operator=(List<T> x)
		{
			swap(_head, x._head);
			return *this;
		}

		~List()
		{
			if (_head)
			{
				PNode pcur = _head->_pnext;
				while (pcur != _head)
				{
					PNode next = pcur->_pnext;
					delete pcur;
					pcur = next;
				}
				delete _head;
				_head = nullptr;
			}
		}

		iterator begin()
		{
			return iterator(_head->_pnext);
		}

		iterator end()
		{
			return iterator(_head);
		}

		T& Front()
		{
			return _head->_pnext->val;
		}

		const T& Front()const
		{
			return _head->_pnext->val;
		}

		T& Back()
		{
			return _head->_prev->val;
		}

		void PushBack(const T& val)
		{
			PNode NewNode = new Node(val);
			PNode prev = _head->_prev;
			prev->_pnext = NewNode;
			NewNode->_prev = prev;
			NewNode->_pnext = _head;
			_head->_prev = NewNode;
		}

		void PopBack()
		{
			PNode del = _head->_prev;
			if (del != _head)
			{
				_head->_prev = del->_prev;
				del->_prev->_pnext = _head;
				delete del;
			}
		}

		void PushFront(const T& val)
		{
			PNode NewNode = new Node(val);
			NewNode->_prev = _head;
			NewNode->_pnext = _head->_pnext;
			_head->_pnext->_prev = NewNode;
			_head->_pnext = NewNode;
		}

		void PopFront()
		{
			PNode cur = _head->_pnext;
			if (cur != _head)
			{
				_head->_pnext = cur->_pnext;
				cur->_pnext->_prev = _head;
				delete cur;
			}	
		}
		//在pos位置前插入val
		iterator Insert(iterator pos, const T& val)
		{
			PNode NewNode = new Node(val);
			PNode pCur = pos._node;
			NewNode->_pnext = pCur;
			NewNode->_prev = pCur->_prev;
			NewNode->_prev->_pnext = NewNode;
			pCur->_prev = NewNode;
		}

		iterator Erase(iterator pos)
		{
			PNode pCur = pos._node;
			PNode prev = pCur->_prev;
			PNode next = pCur->_pnext;
			if (pCur != _head)
			{
				prev->_pnext = next;
				next->_prev = pre;
				delete pCur;
				pCur = nullptr;
				pos = iterator(next);
			}
			return next;
		}
		void Clear()
		{
			PNode cur = _head->_pnext;
			while (cur != _head)
			{
				PNode temp = cur->_pnext;
				delete cur;
				cur = temp;
			}
			_head->_pnext = _head;
			_head->_prev = _head;
		}

		size_t Size()
		{
			size_t size;
			PNode cur = _head->_pnext;
			while (cur != _head)
			{
				size++;
				cur = cur->_pnext;
			}
			return size;
		}

		bool Empty()const
		{
			return _head->_pnext == _head;
		}

		void Resize(size_t size, const T& val = T())
		{
			size_t Oldsize = Size();
			if (Oldsize <= size)
			{
				for (size_t i = Oldsize; i < size; ++i)
					PushBack(val);
			}
			else
			{
				for (size_t i = size; i > Oldsize; --i)
					PopBack();
			}
		}

		
	private:
		PNode _head;
	};
}

template<class T>
void PrintList(Bai::List<T>& x)
{
	auto it = x.begin();
	while (it != x.end())
	{
		cout << *it << " ";
		it++;
	}
}
int main()
{
	int array[] = { 1,2,3,4,5,6,7,8,9 };
	Bai::List<int> L(array, array + sizeof(array) / sizeof(array[0]));
	PrintList(L);
	system("pause");
	return 0;
}