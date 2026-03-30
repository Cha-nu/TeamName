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
	Monster() {}
	Inventory* droptable;
	MonsterStat stat;	

public:
    virtual ~Monster() {}

	//스탯 초기화
	virtual void InitializeStat(MonsterStat stat = {}) {
		this->stat = stat;
	}

	//등장 대사
	virtual void introMonster() {
		//std::cout << "몬스터 " << this->stat.name << "(이)가 나타났다!";
	}



	//name, hp, atk, exp getter setter
	virtual std::string getName() const { return this->stat.name; }
	virtual int getHealth() const { return this->stat.hp; }
	virtual int getAttack() const { return this->stat.atk; }
	virtual int getExp() const { return this->stat.give_exp; }
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

	//몬스터가 가지고 있는 아이템을 반환하는 Get함수 하나 만들어주시면 감사하겠습니다.

	//드랍테이블(Inventory) 출력
	virtual void printDropTable() {
		//std::cout << "드랍 테이블 " << std::endl;
		this->droptable->PrintItemList();
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
				//std::cout << "몬스터 " << this->stat.name << "가 " << damage << " 데미지를 입었습니다!" << std::endl;
				//std::cout << this->stat.name << " 남은 체력: " << this->stat.hp << std::endl;
			}
			else {
				this->stat.hp = 0;
				//std::cout << "몬스터 " << this->stat.name << "가 " << "사망했습니다!" << std::endl;				

			}
		}

	}

	//몬스터 공격
	virtual bool attackPlayer(Player* player) {
		//std::cout << "몬스터 " << this->stat.name << "가 플레이어를 " << this->stat.atk << " 데미지로 공격합니다!" << std::endl; 문구 출력 오류때문에 삭제 
		player->ApplyDamage(this->stat.atk);
		return true; // 공격 성공
		
		//공격 실패(빗나감, 아이템 사용 등) 로직
	}


};

//일반 몬스터 클래스
class NormalMonster : public Monster {
public:
	NormalMonster(MonsterStat stat = {});
	virtual ~NormalMonster() {}
	//디버그용 연산자 오버라이딩
	friend std::ostream& operator<<(std::ostream& os , const NormalMonster& m);
};