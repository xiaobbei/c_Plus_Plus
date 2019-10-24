#include<iostream>

using namespace std;

template<class T>
struct BSNode
{
	BSNode(const T&_data = T())
		:left(nullptr)
		,right(nullptr)
		,data(_data)
	{

	}
	BSNode<T>* left;
	BSNode<T>* right;
	T data;
};
template<class T>
class BSTree
{
	typedef BSNode<T> Node;
public:
	BSTree()
		:root(nullptr)
	{
	}
	~BSTree()
	{
		Destory(root);
	}
	BSTree(const BSTree<T>& t)
	{
		root = copy(t);
	}
	BSTree& operator = (const BSTree& t)
	{
		if (this != &t)
		{
			Destory(this->root);
			this->root = t->root;
		}
		return *this;
	}
	Node *copy(Node* t)
	{
		if (t.root == nullptr)
			return nullptr;
		Node *temp = new Node;
		temp->data = t->root;
		temp->left = copy(t->left);
		temp->right = copy(t->right);
		return temp;
	}
	bool Insert(const T&_data) //��һ��Ԫ�ز���
	{
		if (root == nullptr)
		{
			root = new Node(_data);
			return true;
		}
		Node* cur = root;
		Node* parent = nullptr;
		while (cur)
		{
			parent = cur;
			if (cur->data < _data)
				cur = cur->right;
			else if (cur->data > _data)
				cur = cur->left;
			else
				return false;
		}
		cur = new Node(_data);
		if (_data < parent->data)
			parent->left = cur;
		else
			parent->right = cur;
		return true;
	}

	Node* Find(const T& _data)
	{
		Node* cur = root;
		while (cur)
		{
			if (cur->data < _data)
				cur = cur->right;
			else if (cur->data > _data)
				cur = cur->left;
			else if (cur->data == _data)
				return cur;
		}
		cout << "û�и�Ԫ��" << endl;
		return nullptr;
	}

	bool Delete(const T& _data)
	{
		if (root == nullptr) //���Ϊ��
		{
			return false;
		}
		Node* cur = root;
		Node* parent = nullptr;
		while (cur)
		{
			if (_data == cur->data)
				break;
			else if (cur->data < _data)
			{
				parent = cur;
				cur = cur->right;
			}
			else
			{
				parent = cur;
				cur = cur->left;
			}
		}
		if (cur == nullptr) //δ�ҵ�
			return false;

		//1��ֻ������
		if (cur->right == nullptr)
		{
			if (cur == root)
				root = cur->left;
			else
			{
				if (cur == parent->left)
				{
					parent->left = cur->left;
				}
				else
				{
					parent->right = cur->left;
				}
			}
		}
		//ֻ��������
		else if(cur->left == nullptr)
		{
			if (cur == root)
				root = cur->right;
			else
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
		//��������������	
		/*��һ���滻�Ľ�㣺�������������ֵ���������������������ֵ�������滻
		*/
		else 
		{
			if (cur->left != nullptr || cur->right != nullptr)
			{
				//��������������Сֵ�����滻
				Node *replace = cur->right;
				parent = cur;
				while (replace->left)//��������������ߵĽ��ֵ��С
				{
					parent = replace;
					replace = replace->left;
				}
				cur->data = replace->data; //��Ҫɾ���Ľ��������������С����ֵ�����滻
				if (replace == parent->left)
				{
					parent->left = replace->right;
				}
				else
				{
					parent->right = replace->right;
				}
				delete replace;
				replace = nullptr;
			}
			return true;
		}
		return false;
	}
	void inorder() // �������
	{
		Inorder(root);
	}

private:
	void Inorder(Node * root) 
	{
		if (root)
		{
			Inorder(root->left);
			cout << root->data<<" ";
			Inorder(root->right);
		}
	}
	void Destory(Node*& root)
	{
		if (root)
		{
			Destory(root->left);
			Destory(root->right);
			root = nullptr;
		}
	}
	Node *root;
};

void TestBSTree()
{
	BSTree<int> BST1;
	BSNode<int> B;
	BST1.Insert(5);
	BST1.Insert(3);
	BST1.Insert(3);
	BST1.Insert(4);
	BST1.Insert(1);
	BST1.Insert(7);
	BST1.Insert(8);
	BST1.Insert(2);
	BST1.Insert(6);
	BST1.Insert(0);
	BST1.Insert(9);
	BST1.inorder();
	cout << endl;
	BST1.Find(11);
	BST1.Delete(3);
	BST1.inorder();
}
int main()
{
	TestBSTree();
	system("pause");
	return 0;
}