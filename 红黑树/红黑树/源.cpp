#include<iostream>

using namespace std;

enum Color { RED, BLACK };
template<class T>
struct RBTreeNode
{
	RBTreeNode(const T& data = T(), Color color = RED)
		: _pLeft(nullptr)
		, _pRight(nullptr)
		, _pParent(nullptr)
		, _data(data)
		, _color(color)
	{}

	RBTreeNode<T>* _pLeft;
	RBTreeNode<T>* _pRight;
	RBTreeNode<T>* _pParent;
	T _data;
	Color _color;
};

template<class T>
class RBTree
{
	typedef RBTreeNode<T> Node;
public:
	RBTree()
	{
		_pHead = new Node;
		_pHead->_pLeft = _pHead;
		_pHead->_pRight = _pHead;
	}

	bool Insert(const T& data)
	{
		// ���ն��������������ʲ����½ڵ�
		Node* & pRoot = GetRoot();
		if (nullptr == pRoot)
		{
			pRoot = new Node(data, BLACK);
			pRoot->_pParent = _pHead;
			return true;
		}
		else
		{
			// �Ҵ�����ڵ��ڶ����������е�λ��
			// ��������˫�׽ڵ�
			Node* pCur = pRoot;
			Node* pParent = nullptr;
			while (pCur)
			{
				pParent = pCur;
				if (data < pCur->_data)
					pCur = pCur->_pLeft;
				else if (data > pCur->_data)
					pCur = pCur->_pRight;
				else
					return false;
			}

			// �����½ڵ�
			pCur = new Node(data);
			if (data < pParent->_data)
				pParent->_pLeft = pCur;
			else
				pParent->_pRight = pCur;

			pCur->_pParent = pParent;

			// pCur�½ڵ�Ĭ����ɫ����ɫ
			// ���pParent����ɫ�Ǻ�ɫ�ģ�������������
			// ���pParent����ɫ�Ǻ�ɫ�ģ�Υ����������--����������һ��ĺ�ɫ�ڵ�
			while (pParent != _pHead && pParent->_color == RED)
			{
				Node* grandFather = pParent->_pParent;
				if (pParent == grandFather->_pLeft)
				{
					Node* uncle = grandFather->_pRight;
					// ����ڵ������Ϊ��
					if (uncle && RED == uncle->_color)
					{
						// ���һ
						pParent->_color = BLACK;
						uncle->_color = BLACK;
						grandFather->_color = RED;
						pCur = grandFather;
						pParent = pCur->_pParent;
					}
					else
					{
						// ����ڵ㲻���� || ����ڵ���� && ��ɫ
						if (pCur == pParent->_pRight)
						{
							// �����
							RotateL(pParent);
							swap(pCur, pParent);
						}

						// �������
						pParent->_color = BLACK;
						grandFather->_color = RED;
						RotateR(grandFather);
					}
				}
				else
				{
					// һ�����ķ����
					Node* uncle = grandFather->_pLeft;
					if (uncle && RED == uncle->_color)
					{
						pParent->_color = BLACK;
						uncle->_color = BLACK;
						grandFather->_color = RED;
						pCur = grandFather;
						pParent = pCur->_pParent;
					}
					else
					{
						// ����ڵ㲻���� || ������Ϊ��
						if (pCur == pParent->_pLeft)
						{
							// ����������
							RotateR(pParent);
							swap(pCur, pParent);
						}

						// ������ķ����
						pParent->_color = BLACK;
						grandFather->_color = RED;
						RotateL(grandFather);
					}
				}
			}
		}

		pRoot->_color = BLACK;
		_pHead->_pLeft = LeftMost();
		_pHead->_pRight = RightMost();
		return true;
	}
	Node*& GetRoot()
	{
		return _pHead->_pParent;
	}
	Node* LeftMost()
	{
		Node* pRoot = GetRoot();
		if (pRoot == nullptr)
			return _pHead;
		Node* pCur = pRoot;
		while (pCur->_pLeft)
			pCur = pCur->_pLeft;
		return pCur;
	}
	Node* RightMost()
	{
		Node* pRoot = GetRoot();
		if (pRoot == nullptr)
			return _pHead;
		Node* pCur = pRoot;
		while (pCur->_pRight)
			pCur = pCur->_pRight;
		return pCur;
	}

	void InOrder()
	{
		_InOrder(GetRoot());
	}
private:
	void _InOrder(Node* pRoot)
	{
		if (pRoot)
		{
			_InOrder(pRoot->_pLeft);
			cout << pRoot->_data << " ";
			_InOrder(pRoot->_pRight);
		}
	}
	/*void RotateL(Node* pParent)
	{
	Node* pSubR = pParent->_pRight;
	Node* pSubRL = pSubR->_pLeft;

	pParent->_pRight = pSubRL;
	if (pSubRL)
	pSubRL->_pParent = pParent;
	pSubR->_pLeft = pParent;
	Node *temp = pParent->_pParent;
	pSubR->_pParent = temp;
	pParent->_pParent = pSubR;
	if (temp == _pHead)
	_pHead->_pParent = pSubR;
	else
	{
	if (pParent == temp->_pLeft)
	pSubR = temp->_pLeft;
	else
	pSubR = temp->_pRight;
	}
	}*/

	/*void RotateR(Node* pParent)
	{
	Node* pSubL = pParent->_pLeft;
	Node* pSubLR = pSubL->_pRight;

	pParent->_pLeft = pSubLR;
	if (pSubLR)
	pSubLR->_pParent = pParent;

	pSubL->_pRight = pParent;
	Node* temp = pParent->_pParent;
	pSubL->_pParent = temp;
	pParent->_pParent = pSubL;

	if (temp == _pHead)
	_pHead->_pParent = pSubL;
	else
	{
	if (pParent == temp->_pLeft)
	temp->_pLeft = pSubL;
	else
	temp->_pRight = pSubL;
	}
	}*/

	void RotateL(Node* pParent)
	{
		Node* pSubR = pParent->_pRight;
		Node* pSubRL = pSubR->_pLeft;

		pParent->_pRight = pSubRL;
		if (pSubRL)
			pSubRL->_pParent = pParent;

		pSubR->_pLeft = pParent;
		Node* pPParent = pParent->_pParent;
		pSubR->_pParent = pPParent;
		pParent->_pParent = pSubR;

		if (pPParent == _pHead)
			_pHead->_pParent = pSubR;
		else
		{
			if (pParent == pPParent->_pLeft)
				pPParent->_pLeft = pSubR;
			else
				pPParent->_pRight = pSubR;
		}
	}


	void RotateR(Node* pParent)
	{
		Node* pSubL = pParent->_pLeft;
		Node* pSubLR = pSubL->_pRight;

		pParent->_pLeft = pSubLR;
		if (pSubLR)
			pSubLR->_pParent = pParent;

		pSubL->_pRight = pParent;

		Node* pPParent = pParent->_pParent;
		pParent->_pParent = pSubL;
		pSubL->_pParent = pPParent;

		if (pPParent == _pHead)
			_pHead->_pParent = pSubL;
		else
		{
			if (pParent == pPParent->_pLeft)
				pPParent->_pLeft = pSubL;
			else
				pPParent->_pRight = pSubL;
		}
	}
	Node* _pHead;
};

void TestRBTree()
{
	int a[] = { 5, 3, 4, 1, 7, 8, 2, 6, 0, 9 };
	RBTree<int> t;
	for (auto e : a)
		t.Insert(e);
	t.InOrder();
}
int main()
{
	TestRBTree();
	system("pause");
	return 0;
}