#include "BossMonster.h"

BossMonster::BossMonster(MonsterStat stat) {
	InitializeStat(stat);
	initializeIntro();
}

//등장 대사 초기화 
void BossMonster::initializeIntro(std::string dialog) {
	this->dialogue = dialog;
}

//등장 대사 출력
void BossMonster::introMonster() {
	std::cout << this->dialogue << std::endl;
	std::cout << "보스 몬스터 " << this->stat.name << " 이 등장했습니다." << std::endl;
}

// 디버그용

std::ostream& operator<<(std::ostream& os , const BossMonster& m)
{
	os << "Monster 출력\nName: " << m.stat.name << ", HP: " << m.stat.hp << ", ATK: " << m.stat.atk << ", Type: " << typeid(m).name() << "\nIntro: " << m.dialogue;
	return os;
}
