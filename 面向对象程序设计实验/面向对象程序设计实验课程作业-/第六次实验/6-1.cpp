#include <iostream>
using namespace std;
 
class Point{
	private:
		int x,y;
	public:
		Point(){x=0,y=0;}
		Point(int a,int b){
			x=a;
			y=b;
		}
		friend Point operator+(Point& c,Point& d);
		void display(){
			cout<<"("<<x<<","<<y<<")"<<endl;
		}
};
Point operator+(Point& c,Point& d)
{
	Point r;
	r.x=c.x+d.x;
	r.y=c.y+d.y;
	return r;		//注意返回的类型
}
 
int main() {
   Point p1(1,2), p2(-1,1), p3;
   p1.display();
   p2.display();
   
   p3 = p1 + p2;
   cout<<"p1+p2=";//若写为<<p3.display()，则会出现错误提示，因为没有定义重载运算符<<
   p3.display();
 
   return 0;
}