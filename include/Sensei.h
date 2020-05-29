#pragma once
#include <iostream>

/*
    不使用友元的情况下访问类的私有成员
*/
class Sensei
{
private:
    int height;
    int weight;
    char cup;

public:
    void Print();
    Sensei(int weight, int height, char cup);
    ~Sensei();

public:
    // 声明一个模版函数 给外部任何类型访问内部私有成员开个后门
    template <class T>
    void Func(const T &t);

    template <class T>
    int Func1(const T &t);
};

Sensei::Sensei(int weight, int height, char cup) : weight(weight), height(height), cup(cup)
{
}

Sensei::~Sensei()
{
}

void Sensei::Print()
{
    std::cout << "test1 height: " << height << ",weight: " << weight << ",cup: " << cup << std::endl;
}

template <class T>
void Sensei::Func(const T &t)
{
    weight = 0;
}

template <class T>
int Sensei::Func1(const T &t)
{
    return weight;
}