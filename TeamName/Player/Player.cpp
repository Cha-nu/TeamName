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
	delete PlayerInventory();
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
	if (Playerstat.EXP >= 100){
		Playerstat.EXP -= MAX_EXP;
		if (Playerstat.Level < MAX_LEVEL){
			for (int i = 0; i < Playerstat.EXP / 100; i++){
				Playerstat.Level++;
			}
		}
		else{
			std::cout<< "Player already maxLevel" << std::endl;
		}
	}
	Playerstat.EXP = 0;
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
