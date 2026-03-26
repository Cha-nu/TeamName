#include "Player.h"



Player::Player(std::string name){
	Playerstat.HP = 200;
	Playerstat.Stamina = 0;
	Playerstat.name = name;
	Playerstat.Gender = "Male";
	Playerstat.Atk_Damage = 30;
	Playerstat.Level = 1;
	Playerstat.EXP = 0;
}

Player::~Player(){
}

void Player::InitializeStat(int _hp, std::string _name, int _atkdamage,int _level,int _stamina){
	Playerstat.HP = _hp;
	Playerstat.name = _name;
	Playerstat.Atk_Damage = _atkdamage;
	Playerstat.Level = _level;
	Playerstat.Stamina = _stamina;
}


void Player::AcquireEXP(int _exp)
{
	// if EXP amount over 100
	// EXP set zero
	// Level Plus 1
	Playerstat.EXP += _exp;
	if (Playerstat.EXP >= 100)
	{
		Playerstat.EXP = 0;
		Playerstat.Level++;
	}
}

void Player::Attack(){
    //Need to MonsterInterface
}

void Player::ApplyDamage(int _damage){
    Playerstat.HP -= _damage;
}
