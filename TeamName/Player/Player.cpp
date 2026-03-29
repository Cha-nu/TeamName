#include "Player.h"
#include "../Monster/Monster.h"
#include "Inventory/Inventory.h"
#include "Inventory/Item/ItemBase.h"
#include "../Manager/ItemManager/ItemManager.h"
#include <iostream>


Player::Player(std::string name, EPlayerStatus _playerstatus){
	
	float divisionvalue = static_cast<float>(_playerstatus) / 100;
	
	switch (_playerstatus){
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
	delete PlayerInventory;
	PlayerInventory = nullptr;
}

void Player::InitializeStat(float _hp, std::string _name, float _atkdamage, int _level, int _stamina){
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
	LevelUp();//레벨업을 안했는데 여기 함수가 호출되어서 플레이어 체력,공격력이 오르는거 같습니다.
}

void Player::Attack(Monster* _monster){
	
	if (!_monster) return;
	
	_monster->takeDamage(static_cast<int>(Playerstat.Atk_Damage));
}

void Player::ApplyDamage(int _damage){
    Playerstat.HP -= _damage;
	
	// 임시로 bool값으로 캐릭터의 사망여부를 판단
	if (Playerstat.HP <= 0)
	{
		bIsDead = true;
	}
	
	//if (Playerstat.HP <= 0){
	//	// 게임매니저 클래스에서 초기화나 캐릭터 생성 함수에서
	//	// 파라미터로 Player& player를 받고 람다나 std::bind로 실행할 함수주소를 넘겨주시면 될것같습니다.
	//	OnDead();
	//}
}

void Player::P_UseItem(int _index){
	
	ItemSlot CurrentItem = PlayerInventory->GetItemSlot(_index - 1);
	CurrentItem.GetItem()->Use(*this);
	PlayerInventory->RemoveItem(CurrentItem.GetItem()->GetID());
}

// Player의 스탯확인용 디버깅 함수
void Player::ShowPlayerStat(){
	std::cout << "Player Name: " << Playerstat.name << "\n";
	std::cout << "Player Gender: " << Playerstat.Gender << "\n";
	std::cout << "Player HP: " << Playerstat.HP << "\n";
	std::cout << "Player Atk_damage: " << Playerstat.Atk_Damage << "\n";
	std::cout << "Player Level: " << Playerstat.Level << "\n";
	std::cout << "Player Stamina: " << Playerstat.Stamina << "\n";
}

void Player::LevelUp()
{
	int count = Playerstat.EXP / MAX_EXP;
	int reamin = Playerstat.EXP % MAX_EXP;
	
	if (reamin == 0)
	{
		Playerstat.Level += count;
		Playerstat.EXP = 0;
	}
	else
	{
		Playerstat.Level += count;
		Playerstat.EXP = reamin;
	}
	
	PlayerMaxstat.MaxHP += Playerstat.Level * 20;//레벌업을 안했는데 여기 구문이 작동되서 Max체력이 올라감
	PlayerMaxstat.MaxAtk_Damage += Playerstat.Level * 5;//공격력도 같음 
	
	Playerstat.HP = PlayerMaxstat.MaxHP;//레벨업을 안했는데 위에서 Max값이 변경되어서 현재 체력에 덮어씌워서 이길 때 마다 체력이 늘어가는 버그 발생
	Playerstat.Atk_Damage = PlayerMaxstat.MaxAtk_Damage;

}
