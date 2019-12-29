#include<iostream>

using namespace std;

//方法一：

/*class stackOnly
{
public:
	static stackOnly GetObject()
	{
		return stackOnly(); //创建一个对象，按照值的类型返回
	}
	
private:
	stackOnly()
	{}
};*/


//将new函数写为私有的，但是不能绝对的在栈上创建对象，全局作用域下，没有办法禁止
class stackOnly
{
public:
	stackOnly()
	{

	}
	static stackOnly GetObject()
	{
		return stackOnly(); //创建一个对象，按照值的类型返回
	}

private:
	void* operator new(size_t size);
};
int main()
{
	//调用方法
	stackOnly::GetObject();
	//拷贝构造
	stackOnly s(stackOnly::GetObject());
	system("pause");
	return 0;
}