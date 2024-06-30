#pragma once
#include <iostream>
class Date {
private:
	int year;  //年
	int month; //月
	int day;   //日
	int totalDays; //该日期是从公元元年1月1日开始的第几天
public:
	Date(int year=2, int month=1, int day=1); //用年月日构造日期
	int getYear() const { return year; }
	int getMonth() const { return month; }
	int getDay() const { return day; }
	int getMaxDay() const; //获取当月有多少天
	bool isLeapYear() const { //判断当年是否为闰年
		return year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
	}
	void show() const; //输出当前日期
	//计算两个日期之间查多少天
	int operator-(const Date& date)const {
		return totalDays - date.totalDays;
	}
	//判断两个日期的前后顺序
	bool operator<(const Date& date) const {
		return totalDays < date.totalDays;
	}
};
std::istream& operator>>(std::istream& in, Date& date);
std::ostream& operator<<(std::ostream& out, const Date& date);