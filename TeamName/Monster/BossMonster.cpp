#include "BossMonster.h"

BossMonster::BossMonster(MonsterStat stat) {
	InitializeStat(stat);
	initializeIntro();
}

//등장 대사 초기화 
void BossMonster::initializeIntro(std::string dialog) {
	this->dialogue = dialog;
}

//등장 대사 return
std::string BossMonster::introMonster() {
	std::string intro;
	intro = this->dialogue;	
	intro.append("\n보스 몬스터 ");
	intro.append(this->stat.name);
	intro.append(" (이)가 등장했습니다.");
	return intro;
}

// 디버그용

std::ostream& operator<<(std::ostream& os , const BossMonster& m)
{
	os << "Monster 출력\nName: " << m.stat.name << ", HP: " << m.stat.hp << ", ATK: " << m.stat.atk << ", Type: " << typeid(m).name() << "\nIntro: " << m.dialogue;
	return os;
}
