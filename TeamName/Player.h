#pragma once
#include <string>


struct FPlayerStat{
    unsigned int HP; // PlayerHP
    unsigned int Stamina; // PlayerStamina
    std::string name; // PlayerName
    std::string Gender; // PlayerGender
};
class IPlayer{
public:
    virtual void InitializeStat(int _hp, int _stamina, std::string _name) = 0;
    virtual const FPlayerStat& Getstat() = 0;
    virtual FPlayerStat& SetStat() = 0;
    virtual void Attack() = 0;
    virtual void ApplyDamage(int _damage) = 0;
};

class Player : public IPlayer{
public:
    Player();
    ~Player();
    /*****Stat*****/
    void InitializeStat(int _hp, int _stamina, std::string _name) override;
    _forceinline const FPlayerStat& Getstat() override{return Playerstat;}
    _forceinline FPlayerStat& SetStat() override {return Playerstat;}
    /*****Battle*****/
    void Attack() override;
    void ApplyDamage(int _damage) override;
    
private:
    FPlayerStat& Playerstat;
};
