#pragma once
#include <string>
#include <functional>
#include "PlayerTypes.h"
#define MAX_EXP 100

class Inventory;
class Monster;

struct FPlayerStat{
    float HP = 200.f; // PlayerHP
    unsigned int Stamina = 0; // PlayerStamina
	float Atk_Damage = 30; // Player Attack Damage
	unsigned int Level = 1; // PlayerLevel
	unsigned short EXP = 0; // PlayerEXP
    std::string name = "None"; // PlayerName
    std::string Gender = "Male"; // PlayerGender
};
class IPlayer{
public:
    virtual void InitializeStat(float _hp, std::string _name, float _atkdamage,int _level,int _stamina = 0) = 0;
    virtual const FPlayerStat& Getstat() = 0;
    virtual FPlayerStat& SetStat() = 0;
    virtual void Attack(Monster* _monster) = 0;
    virtual void ApplyDamage(int _damage) = 0;
};

class Player : public IPlayer{
public:
    Player(std::string name,EPlayerStatus _playerstatus = EPlayerStatus::GoldSpoon);
    ~Player();
	/*****함수객체*****/
	// 언리얼엔진의 델리게이트랑 비슷하다 생각하시면 됩니다.
	std::function<void()> OnDead;
    /*****Stat*****/
    void InitializeStat(float _hp,std::string _name,float _atkdamage, int _level,int _stamina = 0) override;
    _forceinline const FPlayerStat& Getstat() override{return Playerstat;}
    _forceinline FPlayerStat& SetStat() override {return Playerstat;}
	void AcquireEXP(int _exp);
    /*****Battle*****/
    void Attack(Monster* _monster) override;
    void ApplyDamage(int _damage) override;
	/*****Utility*****/
	_forceinline Inventory* GetInventory() const {return PlayerInventory;}
    
private:
    FPlayerStat Playerstat;
	Inventory* PlayerInventory;
};
