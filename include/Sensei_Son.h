#include "Sensei.h"
#include <string>

class Sensei_Son : private Sensei
{
private:
    std::string chs;
public:
    Sensei_Son(int weight, int height, char cup);
    ~Sensei_Son();
};

Sensei_Son::Sensei_Son(int weight, int height, char cup)
    : Sensei(weight, height, cup)
{
}

Sensei_Son::~Sensei_Son()
{
}
