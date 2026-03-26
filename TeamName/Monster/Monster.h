#pragma once

#include <string>
#include <vector>
#include "MonsterEnum.h"

struct MonsterStat {
	std::string name = "N/A";
	int hp = -1;
	int atk = -1;
};


class Monster{
private:
	MonsterStat stat;

public:
    Monster();    
    Monster(MonsterStat stat);    
    virtual ~Monster() {}
	virtual void InitializeStat(MonsterStat stat = {});
    virtual std::string getName() const; 
    virtual int getHealth() const;
    virtual int getAttack() const;
	virtual void playerAttack();
    virtual void takeDamage(int damage);        
    virtual bool isDead() const;


    //디버그용 연산자 오버라이딩
    friend std::ostream& operator<<(std::ostream& os, const Monster& m);
};