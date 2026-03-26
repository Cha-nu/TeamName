#include "Player.h"

Player::Player() : Playerstat(){
    Playerstat.HP = 0;
    Playerstat.name = "None";
    Playerstat.Stamina = 0;
    Playerstat.Gender = "Male";
}

Player::~Player(){
}

void Player::InitializeStat(int _hp, int _stamina, std::string _name){
    Playerstat.HP = _hp;
    Playerstat.Stamina = _stamina;
    Playerstat.name = _name;
}

void Player::Attack(){
    //Need to MonsterInterface
}

void Player::ApplyDamage(int _damage){
    Playerstat.HP -= _damage;
}
