#pragma once
#include <iostream>
class Date {
private:
	int year;  //��
	int month; //��
	int day;   //��
	int totalDays; //�������Ǵӹ�ԪԪ��1��1�տ�ʼ�ĵڼ���
public:
	Date(int year=2, int month=1, int day=1); //�������չ�������
	int getYear() const { return year; }
	int getMonth() const { return month; }
	int getDay() const { return day; }
	int getMaxDay() const; //��ȡ�����ж�����
	bool isLeapYear() const { //�жϵ����Ƿ�Ϊ����
		return year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
	}
	void show() const; //�����ǰ����
	//������������֮��������
	int operator-(const Date& date)const {
		return totalDays - date.totalDays;
	}
	//�ж��������ڵ�ǰ��˳��
	bool operator<(const Date& date) const {
		return totalDays < date.totalDays;
	}
};
std::istream& operator>>(std::istream& in, Date& date);
std::ostream& operator<<(std::ostream& out, const Date& date);