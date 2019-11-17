#include<iostream>
#include<bitset>
using namespace std;

namespace bai
{
	template<size_t N, class T, 
					   class HF1 = STR1, 
					   class HF2 = STR2,
					   class HF3 = STR3, 
					   class HF4 = STR4, 
					   class HF5 = STR5 >
	class BloomFilter
	{
	public:
		BloomFilter()
			:_size(0)
		{}

		void Insert(const T& data)
		{
			size_t index1 = HF1()(data) % N;
			size_t index2 = HF5()(data) % N;
			size_t index3 = HF3()(data) % N;
			size_t index4 = HF4()(data) % N;
			size_t index5 = HF()(data) % N;

			_bs.set(index1);
			_bs.set(index2);
			_bs.set(index3);
			_bs.set(index4);
			_bs.set(index5);
			_size++;
		}

		bool IsIn(const T& data)
		{
			size_t index = HF1()(data) % N;
			if (!_bs.test(index))
				return false;
			index = HF2()(data) % N;
			if (!_bs.test(index))
				return false;
			index = HF3()(data) % N;
			if (!_bs.test(index))
				return false;
			index = HF4()(data) % N;
			if (!_bs.test(index))
				return false;
			index = HF5()(data) % N;
			if (!_bs.test(index))
				return false;

			return true;
		}
		
		size_t size()const
		{
			return _size;
		}
	private:
		bitset<N> _bs;
		size_t _size;
	};
}


struct STR1
{
	size_t operator()(const string& s)
	{
		return SDBMHash(s.c_str());
	}
	size_t SDBMHash(const char *str)
	{
		register size_t hash = 0;
		while (size_t ch = (size_t)*str++)
		{
			hash = 65599 * hash + ch;
			//hash = (size_t)ch + (hash << 6) + (hash << 16) - hash;  
		}
		return hash;
	}
};

struct STR2
{
	size_t operator()(const string& s)
	{
		return RSHash(s.c_str());
	}
	size_t RSHash(const char *str)
	{
		register size_t hash = 0;
		size_t magic = 63689;
		while (size_t ch = (size_t)*str++)
		{
			hash = hash * magic + ch;
			magic *= 378551;
		}
		return hash;
	}
};

struct STR3
{
	size_t operator()(const string& s)
	{
		return APHash(s.c_str());
	}
	size_t APHash(const char *str)
	{
		register size_t hash = 0;
		size_t ch;
		for (long i = 0; ch = (size_t)*str++; i++)
		{
			if ((i & 1) == 0)
			{
				hash ^= ((hash << 7) ^ ch ^ (hash >> 3));
			}
			else
			{
				hash ^= (~((hash << 11) ^ ch ^ (hash >> 5)));
			}
		}
		return hash;
	}
};

struct STR4
{
	size_t operator()(const string& s)
	{
		return JSHash(s.c_str());
	}
	size_t JSHash(const char *str)
	{
		if (!*str)        // 这是由本人添加，以保证空字符串返回哈希值0  
			return 0;
		register size_t hash = 1315423911;
		while (size_t ch = (size_t)*str++)
		{
			hash ^= ((hash << 5) + ch + (hash >> 2));
		}
		return hash;
	}
};

struct STR5
{
	size_t operator()(const string& s)
	{
		return DEKHash(s.c_str());
	}
	size_t DEKHash(const char* str)
	{
		if (!*str)        // 这是由本人添加，以保证空字符串返回哈希值0  
			return 0;
		register size_t hash = 1315423911;
		while (size_t ch = (size_t)*str++)
		{
			hash = ((hash << 5) ^ (hash >> 27)) ^ ch;
		}
		return hash;
	}
};


int main()
{
	system("pause");
	return 0;
}