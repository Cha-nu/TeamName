#pragma once
#include "Monster.h"

class BossMonster : public Monster {
private:
	MonsterStat stat;
	std::string dialogue; // 보스몹 등장 대사

public:
	BossMonster(MonsterStat stat = {});
	virtual void initializeIntro(std::string dialog = "!! 보스몹 등장 !!");
	virtual void introMonster() override;
	virtual ~BossMonster() {}
	//디버그용 연산자 오버라이딩
	friend std::ostream& operator<<(std::ostream& os , const BossMonster& m);
};