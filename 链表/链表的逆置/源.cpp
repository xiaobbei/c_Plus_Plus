#include<iostream>
#include<assert.h>
using namespace std;

struct ListNode
{
	int val;
	ListNode *next;
};

void InitListNode(ListNode* L)
{
	L = nullptr;
	cout << "初始化成功！" << endl;
}

ListNode * CreateList_back()
{
	ListNode *head = new ListNode;
	if (head == nullptr)
	{
		cout << "申请空间失败";
		return NULL;
	}
	head->next = nullptr;
	int input;
	ListNode *cur = head;
	while (cin >> input && input != 0)
	{
		ListNode *p = new ListNode;
		if (p == nullptr)
		{
			return NULL;
		}
		p->val = input;
		cur->next = p;
		cur = p;
		cur->next = nullptr;
	}
	return head;
}


ListNode * CreateList_head()
{
	ListNode *head, *L;
	head = new ListNode;
	if (head == nullptr)
	{
		cout << "申请空间失败！";
	}
	head->next = nullptr;
	int input;
	while (cin >> input && input != -1)
	{
		L = new ListNode;
		if (L == nullptr)
		{
			cout << "申请空间失败2";
		}
		L->val = input;
		L->next = head ->next;
		head->next = L;
	}
	return head;
}

int ListNode_Len(ListNode *head)
{
	ListNode *phead = head;
	int count = 0;
	while(phead->next != nullptr)
	{ 
		count++;
		phead = phead->next;
	}
	return count;
}
//插入
void InsertListNode(ListNode *head, int value, int pos) 
{
	if (pos<0 || pos>ListNode_Len(head) + 1)
	{
		cout << "插入位置有误！";
		return;
	}
	ListNode* cur = new ListNode;
	if (cur == nullptr)
	{
		return;
	}
	cur->val = value;
	cur->next = nullptr;

	ListNode *phead = head;
	while (phead->next != nullptr &&pos > 0)
	{
		phead = phead->next;
		pos--;
	}
	cur->next = phead->next;
	phead->next = cur;

}

ListNode* DeleteList(ListNode* L, int pos)//按照位置删除
{
	assert(L);
	ListNode* pL = L;
	ListNode* qL;
	int j = 0;
	if (pos<0 || pos>ListNode_Len(L))
	{
		return nullptr;
	}
	while (pL->next && j < pos - 1)
	{
		pL = pL->next;
	}
	qL = pL->next;
	pL->next = qL->next;
	return L;
}

void DeleteList_2(ListNode*& L,int val)
{
	ListNode *pL = L;
	if (L->val == val)
	{
		L = L->next;
		delete pL;
		return ;
	}
	ListNode *qL = nullptr;
	while (pL->next!=nullptr && pL->val != val)
	{
		qL = pL;
		pL = pL->next;
	}
	if (pL == nullptr)
	{
		cout << "not found val in L.";
	}
	if (pL->val == val)
	{
		qL->next = pL->next;
		delete pL;
	}
	return ;
}

void DisplayList(ListNode * L)
{
	ListNode * list = L ->next;

	while (list!= nullptr)
	{
		cout << list->val<< " -> ";
		list = list->next;
	}
}


ListNode* FindKthList(ListNode* L,int k)  //找到倒数第k个数
{
	if (ListNode_Len(L) < k)
	{
		return nullptr;
	}
	ListNode *pFront = nullptr, *pBack = nullptr;
	pFront = pBack = L->next;
	while (k >= 0)
	{
		pFront = pFront->next;
		k--;
	}
	while (pFront != nullptr)
	{
		pFront = pFront->next;
		pBack = pBack->next;
	}
	return pBack;
}

ListNode *ReverseList(ListNode *L)  //链表翻转
{
	ListNode *p, *q;
	p = L->next;
	L->next = nullptr;
	while (p != nullptr)
	{
		q = p;
		p = p->next;
		q->next = nullptr;
		q->next = L->next;
		L->next = q;
	}
	return L;
}

//合并两个有序链表

ListNode *MergeList(ListNode *L1, ListNode *L2)  
{
	if (L1 == nullptr)
		return L2;
	if (L2 == nullptr)
		return L1;
	ListNode *p1 = L1->next, *p2 = L2->next;
	ListNode *res = new ListNode; 
	ListNode *Res = res;
	res->next = nullptr;
	while (p1 != nullptr &&p2 != nullptr)
	{
		if (p1->val < p2->val)
		{
			res->next = p1;
			p1 = p1->next;
		}
		else
		{
			res->next = p2;
			p2 = p2->next;
		}
		res = res->next;
	}
	if (p1 == nullptr)
	{
		res->next = p2;
	}
	if (p2 == nullptr)
	{
		res->next = p1;
	}
	return Res;
}


//删除重复的元素，只保留一份
ListNode *DeleteDupVal(ListNode* L)
{
	ListNode *cur = L;
	while (cur && cur->next)
	{
		if (cur->val == cur->next->val)
		{
			cur->next = cur->next->next;
		}
		else
		{
			cur = cur->next;
		}
	}
	return L;
}

ListNode * DeleteDupVal_2(ListNode* L)
{
	assert(L);
	ListNode* pPre = nullptr; //最后一个不重复的
	ListNode* pCur = L; //当前节点
	ListNode* pNext = nullptr; //当前节点后面值相同的节点
	ListNode* pNode = nullptr;//存放临时节点
	
	while (pCur != nullptr)
	{
		if (pCur->next != nullptr&&pCur->next->val == pCur->val)
		{
			pNext = pCur->next;
			while (pNext != nullptr &&pNext->val == pCur->val)
			{
				pNode = pNext->next;
				free(pNext);
				pNext = pNode;
			}
			if (pCur == L)
			{
				L = pNext;
			}
			else
			{
				pPre->next = pNext;
			}
			free(pCur);
			pCur = pNext;
		}
		else
		{
			pPre = pCur;
			pCur = pCur->next;
		}
	}
	return L;
}


ListNode* DeleteDupVal_3(ListNode * L)
{
	assert(L);
	if (L->next==nullptr)
	{
		return nullptr;
	}
	ListNode* pPre = nullptr;		//最后一个不相同的元素
	ListNode* pCur = L;				//当前元素
	ListNode* pNext = nullptr;		//当前节点后面相同的节点
	ListNode* pNode = nullptr;		//临时空间

	while (pCur != nullptr)
	{
		if (pCur->next != nullptr && pCur->next->val == pCur->val)
		{
			pNext = pCur->next;
			while (pNext != nullptr && pNext->val == pCur->val)
			{
				pNode = pNext->next;
				free(pNext);
				pNext = pNode;
			}
			if (pCur == L)
			{
				L = pNext;
			}
			else
			{
				pPre->next = pNext;
			}
			free(pCur);
			pCur = pNext;
		}
		else
		{
			pPre = pCur;
			pPre = pCur->next;
		}
	}
	return L;
}

int main()
{
	ListNode * L1,*L2;
	L1 = CreateList_back();	
	DisplayList(L1);
	cout << endl;
	L1 = deleteDuplicates(L1);
	DisplayList(L1);
	/*L2 = CreateList_back();
	L1 = MergeList(L1, L2);
	DisplayList(L1);*/
	system("pause"); 
	return 0;
}