#include<iostream>
#include<vector>

using namespace std;

priority_queue<int> p;
template<class T, class Container = vector<T>,class Compare = less<T>>
class priority_queue
{
public:
	priority_queue()
		:con()
	{}

	template<class iterator>
	priority_queue(iterator first, iterator last)
		: con(first,last)
	{
		int rear = con.size();
		int node = ((rear - 2) >> 1);
		for (; node >= 0; --node)
		{
			AdjustDown(node);
		}
	}

	void push(const T& x)
	{
		con.push_back(x);
		AdjustUp(con.size()-1);
	}

	void pop()
	{
		if (con.empty())
			return;
		swap(con.front(), con.back());
		con.pop_back();
		AdjustDown(0);
	}

	T& top()
	{
		return con.front();
	}

	bool empty()
	{
		return con.empty();
	}

private:
	void AdjustUp(int child_index)
	{
		int parent_index = (child_index - 1) >> 1;
		while (child_index != 0)
		{
			if (comp(con[parent_index], con[child_index]))
			{
				swap(con[parent_index], con[child_index]);
				child_index = parent_index;
				parent_index = (child_index - 1) >> 1;
			}
			else
				return;
		}
	}

	void AdjustDown(int parent_index)
	{
		int child_index = parent_index * 2 + 1;
		if (child_index < con.size() - 1 && comp(con[child_index], con[child_index+1]))
		{
			child_index += 1;
		}
		if (comp(con[parent_index], con[child_index]))
		{
			swap(con[parent_index], con[child_index]);
			parent_index = child_index;
			child_index = child_index * 2 + 1;
		}
		else
			return;
	}

	
	Container con;
	Compare comp;
};


void TestPQ()
{
	// 8  1  9  3  6  4  5  0  2  7
	int array[] = { 8, 1, 9, 3, 6, 4, 5, 0, 2, 7 };
	priority_queue<int> q(array, array + sizeof(array) / sizeof(array[0]));

	q.pop();

	priority_queue<int, vector<int>, less<int>> q2;
	q2.push(5);
	q2.push(0);
	q2.push(9);
	q2.push(3);
	q2.push(4);
	q2.push(2);
	q2.push(1);
	q2.push(6);
	q2.push(7);
	q2.push(8);
	cout << q2.top();
	q2.Print();
}

int main()
{
	TestPQ();
	system("pause");
	return 0;
}

