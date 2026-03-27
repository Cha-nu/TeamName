#pragma once

#include <string>
#include <vector>
#include "../Player/Player.h"

struct MonsterStat {
	std::string name;
	int hp;
	int atk;
	int give_exp;
};


class Monster{
public:
    virtual ~Monster() {}
	virtual void InitializeStat(MonsterStat stat = {}) = 0;
	virtual std::string getName() const { return "N/A"; }	
	virtual int getHealth() const { return -1; }
	virtual int getAttack() const { return -1; }
	virtual int getExp() const { return 0; }
	virtual void setName(std::string name) = 0;
	virtual void setHealth(int hp) = 0;
	virtual void setAttack(int atk) = 0;
	virtual void setExp(int exp) = 0;
	virtual bool isDead() const { return true; }	
	virtual void takeDamage(int damage) = 0;
	virtual bool attackPlayer(Player* player) = 0;
};

class NormalMonster : public Monster {
private:
	MonsterStat stat;

public:
	NormalMonster();
	NormalMonster(MonsterStat stat = {});
	virtual ~NormalMonster() {}

	void InitializeStat(MonsterStat stat = {}) override;
	virtual std::string getName() const override;
	virtual int getHealth() const override;
	virtual int getAttack() const override;
	virtual int getExp() const override;
	virtual void setName(std::string name) override;
	virtual void setHealth(int hp) override;
	virtual void setAttack(int atk) override;
	virtual void setExp(int exp) override;
	virtual bool isDead() const override;
	virtual void takeDamage(int damage) override;
	virtual bool attackPlayer(Player* player) override;
	//디버그용 연산자 오버라이딩
	friend std::ostream& operator<<(std::ostream& os , const NormalMonster& m);
};