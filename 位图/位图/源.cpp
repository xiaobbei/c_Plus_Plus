#include<iostream>
#include<bitset>
#include<vector>
#include<assert.h>
using namespace std;

/*调用库函数--位图
void TestBitSet()
{
	bitset<100> bs;//类模板参数为需要多少个比特位
	int array[] = { 1,3,7,4,12,16,19,13,21 };
	for (auto e : array)
		bs.set(e);  
	cout << bs.count();
	cout << bs.size() << endl;
	bs.reset(1);
	if (bs.test(1) == 0)
	{
		cout << "1 is not in";
	}
}*/

namespace bai
{
	template<size_t N>
	class bitset
	{
	public:
		bitset()
			:_count(0)
		{
			_bs.resize((N >> 3) + 1); //所需要的字节数
		}

		bitset<N>& set(size_t num) //将num的比特位置1
		{
			assert(num < N);
			//先计算所在的字节
			size_t index = (num >> 3);
			//计算num所对应字节的比特位
			size_t pos = num % 8;
			_bs[index] |= (1 << pos);
			_count++;
			return *this;
		}

		bitset<N>& reset(size_t num)//将num的比特位置0
		{
			assert(num < N);
			int index = (num >> 3);
			int pos = num % 8;
			_bs[index] &= (~(1 << pos));
			_count--;
			return *this;
		}
		
		bool test(size_t num)
		{
			assert(num < N);
			int index = (num >> 3);
			int pos = num % 8;
			return 0 != (_bs[index] & (1 << pos));
		}
		size_t size()const
		{
			return N;
		}
		size_t count()const
		{
			return _count;
		}
	private:
		vector<char> _bs;
		size_t _count;
	};
}

int main()
{
	bai::bitset<100> bs;
	int array[] = { 1,3,7,4,12,16,19,13,21 };
	for (auto e : array)
		bs.set(e);
	bs.reset(1);
	if (bs.test(1))
		cout << "in" << endl;
	else
		cout << "not in" << endl;
	cout << bs.count() << endl;
	cout<< bs.size();
	system("pause");
	return 0;
}