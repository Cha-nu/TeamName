#pragma once
#include "Monster.h"

class BossMonster : public Monster {
private:
	std::string dialogue; // 보스몹 등장 대사

public:
	BossMonster(MonsterStat stat = {});
	virtual void initializeIntro(std::string dialog = "!! 보스몹 등장 !!"); //별도 csv or json으로 등장 문구 관리?
	virtual std::string introMonster() override;
	virtual ~BossMonster() {}

	virtual bool getDropTableFromFile();
	//디버그용 연산자 오버라이딩
	friend std::ostream& operator<<(std::ostream& os , const BossMonster& m);
};