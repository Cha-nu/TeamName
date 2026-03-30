#include "Monster.h"
//#include"Data/ItemKey.h"

ItemSlot Monster::getDropItem() {
	if ( this->droptable->GetItemSlots().size() > 0 ) {
		static std::random_device rd;
		static std::mt19937 gen(rd());
		static std::uniform_int_distribution<int> dis(1 , 100);
		if ( dis(gen) <= this->stat.drop_percent ) {
			dis.param(std::uniform_int_distribution<int>::param_type(0 , this->droptable->GetItemSlots().size() - 1));
			return this->droptable->GetItemSlot(dis(gen));
		}
	}
	return ItemSlot();

}

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
