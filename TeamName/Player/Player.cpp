#include "Player.h"
#include "../Monster/Monster.h"
#include "Inventory/Inventory.h"


Player::Player(std::string name, EPlayerStatus _playerstatus){
	
	float divisionvalue = static_cast<float>(_playerstatus) / 100;
	
	switch (_playerstatus)
	{
	case EPlayerStatus::GoldSpoon: // 디버프율 0%
		Playerstat.HP = Playerstat.HP * divisionvalue;
		Playerstat.Atk_Damage = Playerstat.Atk_Damage * divisionvalue;
		break;
	case EPlayerStatus::SliverSpoon: // 디버프율 20%
		Playerstat.HP = Playerstat.HP * divisionvalue;
		Playerstat.Atk_Damage =Playerstat.Atk_Damage * divisionvalue;
		break;
	case EPlayerStatus::MudSpoon: // 디버프율 50%
		Playerstat.HP = Playerstat.HP * divisionvalue;
		Playerstat.Atk_Damage =Playerstat.Atk_Damage * divisionvalue;
		break;
	}
	
	Playerstat.name = name;
	PlayerInventory = new Inventory();
}

Player::~Player(){
	PlayerInventory = nullptr;
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
		Playerstat.EXP -= MAX_EXP;
		Playerstat.Level++;
	}
}

void Player::Attack(Monster* _monster){
	
	if (!_monster) return;
	
	_monster->takeDamage(Playerstat.Atk_Damage);
}

void Player::ApplyDamage(int _damage){
    Playerstat.HP -= _damage;
	
	if (Playerstat.HP <= 0)
	{
		// 게임매니저 클래스에서 초기화나 캐릭터 생성 함수에서
		// 파라미터로 Player& player를 받고 람다나 std::bind로 실행할 함수주소를 넘겨주시면 될것같습니다.
		OnDead();
	}
}
