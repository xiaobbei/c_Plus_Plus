#include<iostream>

using namespace std;

class HeapOnly
{
public:
	static HeapOnly* GetObject()
	{
		return new HeapOnly;
	}
	~HeapOnly()
	{}
	HeapOnly(const HeapOnly&) = delete;

private:
	HeapOnly()
	{}
	//�������캯��
	//HeapOnly(const HeapOnly&);
};

int main()
{
	HeapOnly* p = HeapOnly::GetObject();
	system("pause");
	return 0;
}