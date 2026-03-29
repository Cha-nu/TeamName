#include "Monster.h"
//#include"Data/ItemKey.h"

//생성자
NormalMonster::NormalMonster(MonsterStat stat) {
	InitializeStat(stat);
	this->droptable = new Inventory();

	//미리 생성자때 포션을 랜덤으로 할당시키기?
	//this->addToDroptable(ItemKey::Health_Potion_Common , 1);//테스트용
}

// 디버그용

std::ostream& operator<<(std::ostream& os, const NormalMonster& m)
{
    os << "Monster 출력\nName: " << m.stat.name << ", HP: " << m.stat.hp << ", ATK: " << m.stat.atk << ", Type: " << typeid(m).name();
    return os;
}
