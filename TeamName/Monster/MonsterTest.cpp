//Monster 디버그용

#include <iostream>
#include <string>
#include "Monster.h"

int main(void){
    Monster* monster = new Monster();
	Monster* monster2 = new Monster({ "abc", 10, 10});
    std::cout << monster->getName() << std::endl;
    std::cout << *monster << std::endl;
    std::cout << *monster2 << std::endl;
    while (!monster2->isDead()) {
        monster2->takeDamage(1);
    }

    delete monster;
    delete monster2;

    return 0;
}