
#include <iostream>
#include <cstring>
using namespace std;

class myString {
private:
	char* s;
	int Size;
public:
	myString() {                      //无参数构造函数 
		s = new char[1];
		s[0] = '\0';
		Size = 0;
	}
	myString(char str[]) {            //有参数构造函数 
		Size = strlen(str);
		s = new char[Size + 1];
		strcpy(s, str);
	}
	myString(const myString& b) {   //复制构造函数 
		Size = strlen(b.s);
		s = new char[Size + 1];
		strcpy(s, b.s);
	}
	~myString() {                     //析构函数 
		delete[]s;
		Size = 0;
	}


	int size() {                     //返回字符串长度 
		return Size;
	}
	int set(char str[]) {           //拷贝字符串str 
		Size = strlen(str);
		s = new char[Size + 1];
		strcpy(s, str);
		return Size;
	}
	myString& operator= (const myString& b) {    //重载运算符"=" 
		Size = b.Size;
		s = new char[Size + 1];
		strcpy(s, b.s);
		return *this;      //赋值运算，返回给自身this 
	}
	myString operator+ (const myString& b) {     //重载运算符"+" 
		myString m;
		int l = Size + b.Size;
		m.s = new char[l + 1];
		m.Size = l;
		strcat(s, b.s);
		strcpy(m.s, s);
		return m;       //返回一个新对象的字符串 
	}
	myString& operator+= (const myString& b) {   //重载运算符"+=" 
		myString m;
		int l = Size + b.Size;
		m.s = new char[l + 1];
		m.Size = l;
		strcat(s, b.s);
		strcpy(m.s, s);
		*this = m;
		return *this;       //相加完的字符串返回给自身this
	}
	char& operator[] (int l) {      //重载运算符"[]" 
		return s[l];        //返回字符串 
	}
	myString sub(int start, int l) {
		//返回一个 myString 对象m，其数据 s 为当前对象的 s[start, start + l] 范围内的字符 
		myString m;
		m.s = new char[l + 1];
		m.Size = l;
		for (int i = 0; i < l; i++)
			m.s[i] = '\0';

		int j = 0;
		for (int i = start - 1; (i < start + l - 1) && (i < Size); i++, j++) {
			m.s[j] = s[i];
		}
		return m;
	}
	void output() {           //输出字符串 
		cout << s << endl;
	}

};

int main()
{
	myString tmp;
	cout << tmp.size() << endl;  // 预期输出：0

	char t[20];                 //重载"[]" 
	strcpy(t, "Hello");
	tmp += t;
	cout << t << endl;          // 预期输出：Hello

	char s1[] = "abcd";
	myString a(s1);
	a.output();                // 预期输出：abcd
	cout << a.size() << endl;  // 预期输出：4

	char s2[] = "1234";
	myString b(s2);
	b.output();                // 预期输出：1234

	myString c;
	c = a;                     // 运算符"="重载 
	c.output();                // 预期输出：abcd
	cout << c.size() << endl;  // 预期输出：4

	c = a + b;                //运算符“+ ”重载 
	c.output();               // 预期输出：abcd1234
	cout << c.size() << endl;  // 预期输出：8

	myString d(c);             //复制构造函数 
	d.output();                // 预期输出：abcd1234
	d += c;                    //运算符“+= ”重载
	d.output();                //预期输出：abcd1234abcd1234

	char s3[] = "6666666666";
	c.set(s3);
	c.output();               // 预期输出10个6

	return 0;
}