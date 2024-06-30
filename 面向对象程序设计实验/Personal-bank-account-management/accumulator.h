#pragma once
#include "date.h"
class Accumulator {  //��ĳ����ֵ�����ۼ�
private:
	Date lastDate;  //�ϴα����ֵ������
	double value;   //��ֵ�ĵ�ǰֵ
	double sum;     //��ֵ�����ۼ�֮��
public:
	//���캯����dateΪ��ʼ�ۼӵ����ڣ�valueΪ��ʼֵ
	Accumulator(const Date &date,double value):lastDate(date),value(value),sum(0){ }
	//��ȡ����date���ۼӽ��
	double getSum(const Date& date) const {
		return sum + value * (date-lastDate);
	}
	//��date����ֵ���Ϊvalue
	void change(const Date& date, double value) {
		sum = getSum(date);
		lastDate = date;
		this->value = value;
	}
	//��ʼ���������ڱ�Ϊdate����ֵ��Ϊvalue,�ۼ�������
	void reset(const Date& date, double value) {
		lastDate = date;
		this->value = value;
		sum = 0;
	}
};