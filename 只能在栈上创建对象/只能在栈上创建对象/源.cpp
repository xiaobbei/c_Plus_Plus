#include<iostream>

using namespace std;

//����һ��

/*class stackOnly
{
public:
	static stackOnly GetObject()
	{
		return stackOnly(); //����һ�����󣬰���ֵ�����ͷ���
	}
	
private:
	stackOnly()
	{}
};*/


//��new����дΪ˽�еģ����ǲ��ܾ��Ե���ջ�ϴ�������ȫ���������£�û�а취��ֹ
class stackOnly
{
public:
	stackOnly()
	{

	}
	static stackOnly GetObject()
	{
		return stackOnly(); //����һ�����󣬰���ֵ�����ͷ���
	}

private:
	void* operator new(size_t size);
};
int main()
{
	//���÷���
	stackOnly::GetObject();
	//��������
	stackOnly s(stackOnly::GetObject());
	system("pause");
	return 0;
}