#pragma once

#include<iostream>

using namespace std;


class Date
{
public:
	Date(int year = 1900, int month = 1, int day = 1)
	{
		_year = year;
		_month = month;
		_day = day;
	}
	Date(const Date& d)
	{
		_year = d._year;
		_month = d._month;
		_year = d._year;
	}
	Date& operator=(const Date& d)
	{
		this->_year = d._year;
		this->_month = d._month;
		this->_day = d._day;
	}
	Date operator+(int days)
	{
		if (days > 30)
		{
			int temp = days - 30;
			this->_month += 1;
			this->_day += temp;	
		}
		else
		this->_day += days;
	}

	Date operator-(int days)
	{
		if (days > this->_day)
		{
			this->_month--;
			this->_day += (30 - days);
		}
		else
		{
			this->_day -= days;
		}
	}
	Date& operator++()   //ǰ++�Ƿ���++֮���ֵ
	{
		this->_day++;
		this->_month++;
		this->_year;
		return *this;
	}
	Date operator++(int) // ��++�Ƿ���++֮ǰ��ֵ
	{
		Date temp(*this);
		this->_day++;
		this->_month++;
		this->_year++;
		return temp;
	}
	Date& operator--() //��--�Ƿ���--֮���ֵ
	{
		this->_day --;
		this->_month--;
		this->_year--;
		return *this;
	}
	Date operator--(int)
	{
		Date temp(*this);
		this->_day--;
		this->_month--;
		this->_year--;
		return temp;
	}
	bool operator>(const Date& d)const
	{
		if (this->_year > d._year  &&
			this->_month > d._month &&
			this->_year > d._year)
		{
			return true;
		}
		return false;
	}
	bool operator>=(const Date& d)const
	{
		if (this->_year >= d._year  &&
			this->_month >= d._month &&
			this->_year >= d._year)
		{
			return true;
		}
		return false;
	}
	bool operator<(const Date& d)const
	{
		if (this->_year < d._year  &&
			this->_month < d._month &&
			this->_year < d._year)
		{
			return true;
		}
		return false;
	}
	bool operator<=(const Date& d)const
	{
		if (this->_year <= d._year  &&
			this->_month <= d._month &&
			this->_year <= d._year)
		{
			return true;
		}
		return false;
	}
	bool operator==(const Date& d)const
	{
		if (this->_year == d._year && this->_month == d._month &&this->_year == d._year)
		{
			return true;
		}
		return false;
	}
	bool operator!=(const Date& d)const
	{
		return (!operator==(d));
	}
	void show()
	{
		cout << _day << _month << _year << endl;
	}
private:
	int _year;
	int _month;
	int _day;
};