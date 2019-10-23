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
	//拷贝构造函数
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
		//如果为空，则创建一个结点
		if (_root == nullptr)
		{
			_root = new Node(_data);
			return true;
		}
		//查找要插入的位置
		Node *  cur = _root;
		Node * parent = nullptr;
		while (cur)
		{
			parent = cur;
			if (_data < cur->data)
				cur = cur->left;
			else if (_data > cur->data)
				cur = cur->right;
			else //表示一个二叉排序树中已有该元素，则返回错误
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
		//表示二叉排序树中没有改元素，返回nullptr
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

		//没找到，则cur走到nullptr的位置
		if (cur == nullptr)
		{
			return false;
		}
		/*如果该树中有_data的元素，则需要分3中情况
		1、该_data的结点只有左孩子
		2、只有右孩子
		3、左右孩子都有
		*/
		if (cur->left == nullptr) //只有右孩子
		{
			if (cur == _root) //如果该结点为根结点
			{
				_root = cur->right;
			}
			else //不是根结点
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
		当前结点左右孩子都存在，直接删除不好删，可以在其子树中找一个替代结点，
		比如找其左子树中的最大结点，即左子树中最右侧的结点，或者找其右子树中最小的结点，
		即右子树中最小的结点。替换结点找到后，将替代结点中的值交给待删除结点，转换成删除替代结点。
		*/
		else
		{
			if (cur->left != nullptr || cur->right != nullptr)
			{
				//找右节点最小值
				Node *replace = cur->right; //从右边子树开始查找
				parent = cur;
				//右节点的最小值，在右子树的最左边，cur->left
				while (replace->left)
				{
					parent = replace;
					replace = replace->left;
				}
				//数值替换
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