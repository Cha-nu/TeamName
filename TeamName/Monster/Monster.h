#pragma once

#include <string>
#include <vector>
#include "MonsterEnum.h"

class Monster{
private:
    std::string name;
    int hp;
    int atk;    
    MonsterType m_type;

public:
    Monster();
    Monster(std::string name);
    Monster(std::string name, int hp, int atk, MonsterType m_type);    
    virtual ~Monster() {}
    virtual std::string getName() const; 
    virtual int getHealth() const;
    virtual int getAttack() const;
    virtual void takeDamage(int damage);        
    virtual bool isDead() const;


    //디버그용 연산자 오버라이딩
    friend std::ostream& operator<<(std::ostream& os, const Monster& m);
};