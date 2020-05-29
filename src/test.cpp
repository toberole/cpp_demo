#include <iostream>

#include "Student.h"

#include "Sensei.h"
/*
不使用友元的情况下使用类的私有属性
*/
// 方法1
// 内存偏移[需要知道内存布局 不同的编译器编译结果内存布局不一定相同]
void test1()
{
    Sensei sensei(100, 200, 'A');
    int height = *(int *)&sensei;
    int weight = *((int *)&sensei + 1);
    char cup = *(char *)((int *)&sensei + 2);

    std::cout << "test1 height: " << height << ",weight: " << weight << ",cup: " << cup << std::endl;
}
// 方法二 定义一个拥有同样字段的类[字段类型和顺序一致]
struct Sensei_Temp
{
    int height;
    int weight;
    char cup;
};
void test2()
{
    Sensei sensei(100, 200, 'A');
    Sensei_Temp sensei_tem = *((Sensei_Temp *)&sensei);
    std::cout << "test2 height: " << sensei_tem.height << ",weight: " << sensei_tem.weight << ",cup: " << sensei_tem.cup << std::endl;
}

// 方法三 用宏替换 把private替换成public
/*
    #define private public
    #include "Sensei.h"
    #undef private
*/

struct Test_4
{
};

// 方法四 在原始类中开个后门[在原始类中定一个模版函数]
void test4()
{
    Sensei sensei_tem(100, 200, 'A');
    sensei_tem.Print();
    // 使用模版函数间接的访问私有成员
    Test_4 t;
    sensei_tem.Func(t);
    sensei_tem.Print();
    std::cout << "weight: " << sensei_tem.Func1(t) << std::endl;
}

int main(int argc, char const *argv[])
{

    // test1();
    // test2();
    test4();
    Student stu;
    stu.name = "hello stu";
    std::cout << "hello world" << std::endl;
    return 0;
}
