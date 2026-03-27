#pragma once
#include "Monster.h"
#include <vector>

class BossMonster : public Monster {
private:
	MonsterStat stat;
	std::vector<std::string> dialogue;

public:
	BossMonster();
	BossMonster(MonsterStat stat = {});
	virtual ~BossMonster() {}
	//디버그용 연산자 오버라이딩
	friend std::ostream& operator<<(std::ostream& os , const BossMonster& m);
};