#include<iostream>

using namespace std;

template<class T>
struct BSTNode
{
	BSTNode(const T&_data = T())
		:left(nullptr)
		,right(nullptr)
		,data(_data)
	{
	}
	BSTNode<T> *left;
	BSTNode<T> *right;
	T data;
};

template<class T>
class BSTree
{
	typedef BSTNode<T> Node;
public:
	BSTree()
		:_root(nullptr)
	{
	}
	~BSTree()
	{
		Destory(_root);
	}
	BSTree(const BSTree<T> & t)
	{
		_root = copy(t);
	}
	//�������캯��
	Node* copy(Node *root)
	{
		if (root == nullptr)
			return nullptr;
		Node *temp = new Node;
		temp->data = root->data;
		temp->left = copy(root->left);
		temp->right = copy(root->right);
		return temp;
	}
	BSTree& operator = (const BSTree& t)
	{
		if (this != &t)
		{
			Destory(this->_root);
			this->_root = copy(t._root);
		}
		return *this;
	}

	bool Insert(const T& _data)
	{
		//���Ϊ�գ��򴴽�һ�����
		if (_root == nullptr)
		{
			_root = new Node(_data);
			return true;
		}
		//����Ҫ�����λ��
		Node *  cur = _root;
		Node * parent = nullptr;
		while (cur)
		{
			parent = cur;
			if (_data < cur->data)
				cur = cur->left;
			else if (_data > cur->data)
				cur = cur->right;
			else //��ʾһ�����������������и�Ԫ�أ��򷵻ش���
				return false;
		}
	}

	Node *Find(const T&_data)
	{
		Node* cur = _root;
		while (cur)
		{
			if (cur->data == _data)
				return cur;
			else if (cur->data > _data)
				cur = cur->left;
			else
				cur = cur->right;
		}
		//��ʾ������������û�и�Ԫ�أ�����nullptr
		return nullptr;
	}

	bool Erase(const T& _data)
	{
		if (_root == nullptr)
			return false;
		Node *cur = _root;
		Node *parent = nullptr;
		while (cur)
		{
			if (_data == cur->data)
			{
				break;
			}
			else if (_data < cur->data)
			{
				parent = cur;
				cur = cur->left;
			}
			else
			{
				parent = cur;
				cur = cur->right;
			}
		}

		//û�ҵ�����cur�ߵ�nullptr��λ��
		if (cur == nullptr)
		{
			return false;
		}
		/*�����������_data��Ԫ�أ�����Ҫ��3�����
		1����_data�Ľ��ֻ������
		2��ֻ���Һ���
		3�����Һ��Ӷ���
		*/
		if (cur->left == nullptr) //ֻ���Һ���
		{
			if (cur == _root) //����ý��Ϊ�����
			{
				_root = cur->right;
			}
			else //���Ǹ����
			{
				if (cur == parent->left)
				{
					parent->left = cur->right;
				}
				else
				{
					parent->right = cur->right;
				}
			}
		}
		else if (cur->right == nullptr)
		{
			if (cur == _root)
			{
				_root = cur->left;
			}
			else
			{
				if (cur == parent->right)
				{		
					parent->right = cur->left;
				}
				else
				{
					parent->left = cur->left;
				}
			}
		}
		/*
		��ǰ������Һ��Ӷ����ڣ�ֱ��ɾ������ɾ������������������һ�������㣬
		���������������е�����㣬�������������Ҳ�Ľ�㣬������������������С�Ľ�㣬
		������������С�Ľ�㡣�滻����ҵ��󣬽��������е�ֵ������ɾ����㣬ת����ɾ�������㡣
		*/
		else
		{
			if (cur->left != nullptr || cur->right != nullptr)
			{
				//���ҽڵ���Сֵ
				Node *replace = cur->right; //���ұ�������ʼ����
				parent = cur;
				//�ҽڵ����Сֵ����������������ߣ�cur->left
				while (replace->left)
				{
					parent = replace;
					replace = replace->left;
				}
				//��ֵ�滻
				cur->data = replace->data;
				if (replace == parent->left)
					parent->left = replace->left;
				else
					parent->right = replace->right;
				delete replace;
				replace = nullptr;
			}
			return true;
		}
		return false;
	}
private:
	void Destory(Node*& _root)
	{
		if (root)
		{
			Destory(_root->left);
			Destory(_root->right);
			_root = nullptr;
		}
	}
	Node *_root;
};
int main()
{
	system("pause");
	return 0;
}