#pragma once

#include <string>
#include <vector>
#include "../Player/Player.h"

struct MonsterStat {
	std::string name = "N/A";
	int hp = -1;
	int atk = -1;
	int give_exp = 0;
};


class Monster{
public:
    virtual ~Monster() {}
	virtual void InitializeStat(MonsterStat stat = {}) = 0;
	virtual std::string getName() const { return "N/A"; }	
	virtual int getHealth() const { return -1; }
	virtual int getAttack() const { return -1; }
	virtual int getExp() const { return 0; }
	virtual bool isDead() const { return true; }	
	virtual void takeDamage(int damage) = 0;
	virtual bool attackPlayer(Player& player) = 0;	
};

class NormalMonster : public Monster {
private:
	MonsterStat stat;

public:
	NormalMonster(MonsterStat stat = {});
	virtual ~NormalMonster() {}

	void InitializeStat(MonsterStat stat = {}) override;
	virtual std::string getName() const override;
	virtual int getHealth() const override;
	virtual int getAttack() const override;
	virtual int getExp() const override;
	virtual bool isDead() const override;
	virtual void takeDamage(int damage) override;
	virtual bool attackPlayer(Player& player) override;	
	//디버그용 연산자 오버라이딩
	friend std::ostream& operator<<(std::ostream& os , const NormalMonster& m);
};