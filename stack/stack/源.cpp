#include<iostream>
#include<deque>
#include<stack>
#include<vector>
#include<queue>
using namespace std;

template<class T,class S = deque<T>>
class Stack
{
public:
	Stack()
	{
	}
	void push(const T& x)
	{
		_s.push_back(x);
	}
	void pop()
	{
		_s.pop_front();
	}
	T& top()
	{
		return _s.back();
	}
	size_t size()
	{
		return _s.size();
	}
	bool empty()
	{
		return _s.empty();
	}
private:
	S _s;
};
int main()
{
	stack<int> s;
	//Stack<int> s;
	queue<int> d;
	priority_queue<int> p;
	s.push(1);
	cout<<s.size()<<endl;
	s.push(2);
	s.push(2);
	s.push(2);
	s.push(2);
	cout<<s.top();
	cout << s.size() << endl;
	system("pause");
	return 0;
}