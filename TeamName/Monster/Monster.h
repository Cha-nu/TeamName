#pragma once
#include<iostream>
#include <string>
#include <vector>
#include "../Player/Player.h"
#include "../Inventory/Inventory.h"

struct MonsterStat {
	std::string name = "Test Monster";
	int hp = 100;
	int atk = 10;
	int give_exp = 20;
};


class Monster{
protected:
	Inventory* droptable = nullptr;
	MonsterStat stat;	
	Monster() : droptable(new Inventory()) , stat() {}
public:
	virtual ~Monster() { 
		if ( droptable ) {
			delete droptable;
		}
		droptable = nullptr;
	}

	//스탯 초기화
	virtual void InitializeStat(MonsterStat stat = {}) {
		this->stat = stat;
	}

	//등장 대사 return
	virtual std::string introMonster() {
		std::string intro;
		intro = "몬스터 ";
		intro.append(this->stat.name);
		intro.append("(이)가 나타났다!");
		return intro;
	}



	//name, hp, atk, exp, droptable getter setter
	virtual std::string getName() const { return this->stat.name; }
	virtual int getHealth() const { return this->stat.hp; }
	virtual int getAttack() const { return this->stat.atk; }
	virtual int getExp() const { return this->stat.give_exp; }
	virtual Inventory* getDroptable() const { return this->droptable; }
	virtual void setName(std::string name) { this->stat.name = name; }
	virtual void setHealth(int hp) { this->stat.hp = hp; }
	virtual void setAttack(int atk) { this->stat.atk = atk; }
	virtual void setExp(int exp) { this->stat.give_exp = exp; }

	//드랍테이블(Inventory)에 아이템 추가
	virtual void addToDroptable(const std::string& id, int amount) {
		this->droptable->AddItem(id , amount);
	}

	//드랍테이블(Inventory)에 아이템 삭제
	virtual void removeToDroptable(const std::string& id , int amount) {
		this->droptable->RemoveItem(id , amount);
	}

	//몬스터 사망 플래그
	virtual bool isDead() const { 
		return this->stat.hp <= 0;
	}	

	//몬스터 피격
	virtual void takeDamage(int damage) {
		if ( !this->isDead() ) {
			if ( this->stat.hp - damage > 0 ) {
				this->stat.hp -= damage;
			}
			else {
				this->stat.hp = 0;

			}
		}

	}

	//몬스터 공격
	virtual bool attackPlayer(Player* player) {
		player->ApplyDamage(this->stat.atk);
		return true; // 공격 성공
		
		//공격 실패(빗나감, 아이템 사용 등) 로직
	}

	//복사 생성자 삭제
	//댕글링 포인터 원천차단
	//shared_ptr로 변경...?
	Monster(const Monster&) = delete;
	Monster& operator=(const Monster&) = delete;


};

//일반 몬스터 클래스
class NormalMonster : public Monster {
public:
	NormalMonster(MonsterStat stat = {});
	virtual ~NormalMonster() {}
	//디버그용 연산자 오버라이딩
	friend std::ostream& operator<<(std::ostream& os , const NormalMonster& m);
};