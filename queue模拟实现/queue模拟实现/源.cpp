#include<iostream>
#include<deque>

using namespace std;

namespace bai
{

	template<class T, class D = deque<T>>
	class queue
	{
	public:
		queue()
		{}
		void push(const T& data)
		{
			_d.push_back(data);
		}
		void pop()
		{
			_d.pop_front();
		}
		T& top()
		{
			return _d.front();
		}
		size_t size()
		{
			return _d.size();
		}
		bool empty()
		{
			return _d.empty();
		}
		T& back()
		{
			return _d.back();
		}
	private:
		D  _d;
	};
}
int main()
{
	bai::queue<int> q;
	q.push(1);
	q.push(2);
	q.push(3);
	q.push(4);
	q.push(5);
	q.push(6);
	cout<<q.size();
	cout << q.top();
	q.pop();
	cout << q.top();
	system("pause");
	return 0;
}