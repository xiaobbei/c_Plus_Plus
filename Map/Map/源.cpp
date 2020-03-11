#include<iostream>

#include<map>

int main()
{
	std::map<char, int> mymap; //构造

	// 使用insert插入元素，pair<T1,T2>(key,value)创建键值对
	mymap.insert(std::pair<char, int>('a', 100));
	mymap.insert(std::pair<char, int>('z', 200));

	std::pair<std::map<char, int>::iterator, bool> ret;
	ret = mymap.insert(std::pair<char, int>('z', 500));
	if (ret.second == false) {
		std::cout << "element 'z' already existed";
		std::cout << " with a value of " << ret.first->second << '\n';
	}

	// 在it的位置插入键值对
	std::map<char, int>::iterator it = mymap.begin();
	mymap.insert(it, std::pair<char, int>('b', 300));  // max efficiency inserting
	mymap.insert(it, std::pair<char, int>('c', 400));  // no max efficiency inserting

	// 区间构造，同时使用find查找
	std::map<char, int> anothermap;
	anothermap.insert(mymap.begin(), mymap.find('c'));

	// 使用迭代器打印
	std::cout << "mymap contains:\n";
	for (it = mymap.begin(); it != mymap.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';

	std::cout << "anothermap contains:\n";
	for (it = anothermap.begin(); it != anothermap.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';


	//将mymap与anothermap进行交换
	mymap.swap(anothermap);

	//反向迭代器的使用
	std::cout << "mymap contains:\n";
	std::map<char, int>::reverse_iterator rit;
	for (rit = mymap.rbegin(); rit != mymap.rend(); ++rit)
		std::cout << it->first << " => " << it->second << '\n';

	std::cout << mymap.count('a') << std::endl;
	std::cout << mymap.size() << std::endl;
	std::cout << mymap.max_size() ;

	//删除key == a的元素
	mymap.erase('a');
	
	system("pause");
	return 0;
}