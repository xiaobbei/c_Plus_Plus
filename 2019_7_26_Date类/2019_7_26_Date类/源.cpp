#include"Date.h"

using namespace std;

int main()
{
	Date d1(2019, 7, 26);
	Date d2 = d1 ++;
	std::cout << d2.show();
	system("pause");
	return 0;
}