#include<iostream>

using namespace std;


class Date
{
public:

	Date(int year = 2000, int month = 1, int day = 1) :_year(year), _month(month), _day(day)
	{
		if (!(year > 0 && (month > 0 && month < 13) && (day > 0 && day <= GetDayofMonth(year, month))))
		{
			_year = 2000;
			_month = 1;
			_day = 1;
		}
	}
	Date(const Date& d)
	{
		_year = d._year;
		_month = d._month;
		_day = d._day;
	}
	Date& operator=(const Date &d)
	{
		if (this != &d)
		{
			_day = d._day;
			_month = d._month;
			_year = d._year;
		}
		return *this;
	}

	bool operator==(const Date &d)
	{
		return _year == d._year&&_month == d._month&&_day == d._day;
	}

	bool operator!=(const Date &d)
	{
		return !(*this == d);
	}
	
	bool operator>(const Date &d)
	{
		return _year > d._year ||
			  (_year == d._year && _month > d._month) ||
			  (_year == d._year&&_month == d._month&&_day > d._day);
	}

	bool operator>=(const Date &d)
	{
		return *this > d || *this == d;
	}

	bool operator<(const Date &d)
	{
		return !(*this >= d);
	}

	bool operator<=(const Date &d)
	{
		return !(*this > d);
	}


	int GetDayofMonth(int year ,int month)  //判断天数
	{
		static int days[] = {0, 31,28,31,30,31,30,31,31,30,31,30,31 };
		int day = days[month];
		if (month == 2 && (0 == year % 4 && 0 != year % 100) || 0 == year % 400)
		{
			return day += 1;
		}
		else return day;
	}

	Date operator+(int day)
	{
		Date ret(*this);
		ret._day += day;
		while ( ret._day> GetDayofMonth(_year,_month))
		{
			ret._day -= GetDayofMonth(_year, _month);
			++ret._month;
			if (ret._month == 13)
			{
				ret._month = 1;
				++ret._year ;
			}
		}
		return ret;
	}


	Date  operator-(int day)  //找？天之前的日期
	{
		Date ret(*this);
		ret._day -= day;
		while (ret._day <=0)
		{
			if (ret._month == 1)
			{
				ret._month = 12;
				ret._year--;
			}
			ret._month--;
			ret._day += GetDayofMonth(_year, _month);
		}
		return ret;
	}

	Date& operator+=(int day)
	{
		_day += day;
		while (_day > GetDayofMonth(_year, _month))
		{
			_day -= GetDayofMonth(_year, _month);
			_month += 1;
			if (_month == 13)
			{
				_month = 1;
				_year += 1;
			}
		}
		return *this;
	}
	
	Date &operator-=(int day)
	{
		_day -= day;
		while (_day <= 0)
		{
			if (_month == 1)
			{
				_month = 12;
				_year --;
			}
			_month--;
			_day += GetDayofMonth(_year, _month);
		}
		return *this;
	}
	
	Date& operator++()
	{
		*this += 1;
		return *this;
	}

	Date operator++(int)
	{
		Date temp(*this);
		*this += 1;
		return temp;
	}

	Date &operator--()
	{
		*this -= 1;
		return *this;
	}

	Date operator--(int)
	{
		Date temp(*this);
		*this -= 1;
		return temp;
	}

	int operator-(const Date &d)
	{
		Date max = *this;
		Date min = d;
		if (*this < d)
		{
			max = d;
			min = *this;
		}
		int day = 0;
		while (min != max)
		{
			day++;
			++min;
		}
		return day;
	}

	void show()
	{
		cout << _year << " ：" << _month << "：" << _day << "：" << endl;
	}


private:
	int _year;
	int _month;
	int _day;
};


int main()
{
	Date d1(2019, 7,29);
	Date d2(2001,1,30);

	int i = d1 - d2;
	cout << i;
	system("pause");
	return 0;
}

