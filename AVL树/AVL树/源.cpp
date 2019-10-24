#include<iostream>

using namespace std;
template<class T> 
struct AVLTreeNode
{
	AVLTreeNode(const T& _data = T())
		:left(nullptr)
		,right(nullptr)
		,pParent(nullptr)
		,data(_data)
		,bf(0)
	{}
	AVLTreeNode<T> *left;
	AVLTreeNode<T> *right;
	AVLTreeNode<T> *pParent;
	T data;
	int bf;
};

template<class T>
class AVLTree
{
	typedef AVLTreeNode<T> Node;
public:
	AVLTree()
		:root(nullptr)
	{
	}
	~AVLTree()
	{
		Destory();
	}

	//先按照二叉树进行插入
	bool Insert(const T&_data)
	{
		if (root == nullptr)
		{
			root = new Node(_data);
			return true;
		}
		Node *cur = root;
		Node *parent = nullptr;
		while (cur)
		{
			parent = cur;
			if (cur->data < _data)
			{
				cur = cur->right;
				cur->pParent = parent;
			}
			else if (cur->data > _data)
			{
				cur = cur->left;
				cur->pParent = parent;
			}
			else
				return false;
		}
		cur = new Node(_data);
		if (_data < parent->data)
		{
			parent->left = cur;
			cur->pParent = parent;
		}
		else
		{
			parent->right = cur;
			cur->pParent = parent;
		}
		while (parent)
		{
			if (cur = parent->left)
				parent->bf--;
			else
				parent->bf++;
			if (parent->bf == 0)
				break;
			else if (1 == parent->bf || parent->bf == -1)
				//插入前双亲的平衡因子为0；说明以该结点为根的平衡二叉树的高度增加1，需要向上调整
			{
				cur = parent;
				parent = cur->pParent;
			}
			else
			{
				if (parent->bf == 2) //右边子树的高度高，需要进行左旋
				{
					_RotateL(parent);
				}
				else
				{
					_RotateR(parent);
				}
			}
		}
		return true;
	}

	void _RotateR(Node * parent)//左单旋
	{
		Node *SubR = parent->right;
		Node *SubRL = SubR->left;
		parent->right = SubRL;
		if (SubRL)
		{
			SubRL->pParent = parent;
		}	
		SubR->right = parent;
		Node* temp = parent->pParent;
		SubR->pParent == temp;
		parent->pParent = SubR;
		if (temp == nullptr)
		{
			root = SubR;
			SubR->pParent = nullptr;
		}
		else
		{
			if (temp->left == parent)
			{
				temp->left = SubR;
			}
			else
			{
				temp->right = SubR;
			}
		}
		parent->bf = SubR->bf = 0;
	}

	void _RotateL(Node *parent) //右单旋
	{
		Node *SubL = parent->left;
		Node *SubLR = SubL->right;
		parent->left = SubLR;
		if(SubLR)
			SubLR->pParent = parent;
		Node *temp = parent->pParent;
		SubL->pParent = temp;
		parent->pParent = SubL;
		if (temp == nullptr)
		{
			root = SubL;
			SubL->pParent = nullptr;
		}
		else
		{
			if (temp->left == parent)
			{
				temp->left = SubL;
			}
			else
			{
				temp->right = SubL;
			}	
		}
		parent->bf = SubL->bf = 0;
	}
	//先左旋再右旋--当新结点插入到高左子树的右侧
	void _RotateLR(Node *parent)
	{
		Node* SubL = parent->left;
		Node* SubLR = SubL->right;
		int _bf = SubLR->bf;
		_RotateL(parent->left);
		_RotateR(parent);
		if (_bf == 1)
		{
			SubL->bf -= 1;
		}
		else if(_bf == -1)
		{
			parent->bf = 1;
		}
	}
private:
	void Destory() //释放
	{
		if (root)
		{
			Destory(root->left);
			Destory(root->right);
			root == nullptr;
		}
	}
	Node *root;
};
int main()
{
	system("pause");
	return 0;
}