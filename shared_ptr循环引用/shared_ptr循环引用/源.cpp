#include<iostream>
#include<memory>
using namespace std;

//���ⳡ��
struct ListNode
{
	ListNode(int _data = int())
		:data(_data)
	{
		cout << "ListNode()" << this << endl;
	}

	~ListNode()
	{
		cout << "~ListNode()" << endl;
	}
	weak_ptr<ListNode> _pre;
	weak_ptr<ListNode> _next;
	int data;
};


void TestFunc()
{
	shared_ptr<ListNode> p1(new ListNode(10));
	shared_ptr<ListNode> p2(new ListNode(20));
	cout << p1.use_count() << endl;//�鿴p1�е����ü���
	cout << p2.use_count() << endl;
	p1->_next = p2;
	p2->_pre = p1;
	cout << p1.use_count() << endl;
	cout << p2.use_count() << endl;

}
int main()
{
	TestFunc();
	system("pause");
	return 0;
}