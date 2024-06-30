#include<iostream>
using namespace std;

class cat {
public:
    cat()
    {
        numOfCats++;
    }
    static int getNumOfCats()
    {
        return numOfCats;
    }
    ~cat()
    {
        numOfCats--;
    }
private:
    static int numOfCats;
};
int cat::numOfCats = 0;  //类的静态成员变量必须在类外进行初始化

void numprintf()
{
    cout << "There are " << cat::getNumOfCats() << " cats alive!" << endl;
}

int main()
{
    cat a;
    cat b;
    cat c;
    numprintf();//定义3只猫

    cat* t1, * t2;
    t1 = new cat();
    t2 = new cat();//在堆区定义两个cat对象
    numprintf();

    delete t1;
    numprintf();

    return 0;
}