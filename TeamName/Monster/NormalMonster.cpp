#include "Monster.h"
#include <iostream>

//생성자
NormalMonster::NormalMonster(MonsterStat stat){
	InitializeStat(stat);
}

void NormalMonster::InitializeStat(MonsterStat stat) {
	this->stat = stat;
}

//name, hp, atk getter
std::string NormalMonster::getName() const{
	return this->stat.name;
}

int NormalMonster::getAttack() const {
	return this->stat.atk;
}

int NormalMonster::getHealth() const {
	return this->stat.hp;
}

int NormalMonster::getExp() const {
	return this->stat.give_exp;
}

bool NormalMonster::attackPlayer(Player& player) {	
	player.ApplyDamage(this->getAttack());
	return true; // 공격 성공 시 true 반환
	// 공격 실패시 false 반환
	// 플레이어 체력이 0 이하거나... 기타등등...
}

//피격 처리
void NormalMonster::takeDamage(int damage){
    this->stat.hp -= damage;
    if (this->isDead()) { // this->hp < 0
        std::cout << this->stat.name << " 사망" << std::endl; // 사망 로그
    }
    else {
        std::cout << this->stat.name << ", " << damage << " 데미지! 남은 체력: " << this->stat.hp <<  std::endl; // 피격 로그
    }
}
//사망 판정
bool NormalMonster::isDead() const{
    return this->stat.hp < 0;
}

// 디버그용

std::ostream& operator<<(std::ostream& os, const NormalMonster& m)
{
    os << "Monster 출력\nName: " << m.stat.name << ", HP: " << m.stat.hp << ", ATK: " << m.stat.atk << ", Type: " << typeid(m).name();
    return os;
}
