#include "BossMonster.h"

BossMonster::BossMonster() {
	MonsterStat stat;
	InitializeStat({ "Test Boss Mob", 200, 20, 100 }); // 이름 / 체력 / 공격력 / 잡았을 시 주는 경험치
}

BossMonster::BossMonster(MonsterStat stat) {
	InitializeStat(stat);
}


// 디버그용

std::ostream& operator<<(std::ostream& os , const BossMonster& m)
{
	os << "Monster 출력\nName: " << m.stat.name << ", HP: " << m.stat.hp << ", ATK: " << m.stat.atk << ", Type: " << typeid(m).name();
	return os;
}
