#include<iostream>
#include<string>
using namespace std;




//类的构造顺序
//class Person
//{
//public:
//	Person(const char* name = "xiaoming")
//		:_name(name)
//	{
//		cout << "Person()" << endl;
//	}
//	Person(const Person& s)
//		:_name(s._name)
//	{
//		cout << "Person(const Person&)" << endl;
//	}
//	Person& operator = (const Person& s)
//	{
//		if (this != &s)
//		{
//			_name = s._name;
//		}
//		cout << "Person operator " << endl;
//		return *this;
//	}
//	~Person()
//	{
//		cout << "~Person" << endl;
//	}
//protected:
//	string _name; // 姓名
//};
//
//class Student :public Person
//{
//public:
//	Student(const char* name, int _age)
//		:Person()
//		,age(_age)
//	{	
//		cout << "Student()" << endl;
//	}
//	Student(const Student& s)
//		:Person(s)
//		,age(s.age)
//	{
//		cout << "Student(const Student&)" << endl;
//	}
//	Student& operator = (const Student& s)
//	{
//		if (this != &s)
//		{
//			cout << "Student operator = " << endl;
//		}
//		return *this;
//	}
//	~Student()
//	{
//		cout << "~Student()" << endl;
//	}
//private:
//	int age;
//};

//class Person
//{
//public:
//	void Print()
//	{
//		cout << "name: " << name << endl;
//		cout << "age: " << age;
//	}
//protected:
//	string name = "xiaoming";
//	int age = 18;
//	static int count;
//};
//
//int Person::count = 0;
//class Student :public Person
//{
//public:
//	void Print()
//	{
//		cout << name << " ";
//		cout << age << " ";
//		cout << _Id;
//		Person::Print();
//	}
//
//protected:
//	int _Id = 0001;
//};


//class Person
//{
//public:
//	Person() { ++_count; }
//protected:
//	string _name; // 姓名
//public:
//	static int _count; // 统计人的个数。
//};
//int Person::_count = 0;
//class Student : public Person
//{
//protected:
//	int _stuNum; // 学号
//};
//class Graduate : public Student
//{
//protected:
//	string _seminarCourse; // 研究科目
//};
//void TestPerson()
//{
//	Student s1;
//	Student s2;
//	Student s3;
//	Graduate s4;
//	cout << " 人数 :" << Person::_count << endl;
//	Student::_count = 0;
//	cout << " 人数 :" << Person::_count << endl;
//}

//static只会保存一份
//class Person
//{
//public:
//	Person()
//	{
//		++_count;
//	}
//	static int _count;
//};
//int Person::_count;
//
//
//class Student :public Person
//{
//protected:
//	int _num;
//};
//
//class Graduate:public Student
//{
//protected:
//	string _seminarCourse; 
//};


//菱形继承
class Person
{
public:
	int A;
};

class Student :virtual public Person
{
protected:
	int B;
};

class Teacher :virtual public Person
{
protected:
	int C;
};

class Assistant :virtual public Student, virtual public Teacher
{
protected:
	int D;
};
int main()
{
	Student s1;	
	Assistant d; 
	d.Student::A = 1;
	d.Teacher::A = 2;
	
	system("pause");
	return 0;
}