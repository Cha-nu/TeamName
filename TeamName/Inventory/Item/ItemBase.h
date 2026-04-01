/*
* 아이템의 기본 클래스입니다.
 * 아이템의 이름, 설명, 등급 등의 공통 속성을 정의합니다.
 * 현재 Use 함수는 Player와 Monster 클래스가 상위 클래스를 상속하지 않는 경우 각각의 Use 함수를 만들어야 하는 상황을 고려하여 주석 처리되어 있습니다.
 */


#pragma once
#include <string>
#include "Type/GameTypes.h"

class Player;
class Monster;

class ItemBase
{
public:
	ItemBase(std::string id, const std::string& name, TargetStat stat, ItemRank rank, int gold);
	virtual ~ItemBase();

	const std::string& GetName() const { return m_name; }
	const std::string& GetDescription() const { return m_description; }
	ItemRank GetRank() const { return m_rank; }
	TargetStat GetTargetStat() const { return m_targetStat; }
	const std::string& GetID() const { return m_id; }
	int GetGold() const { return m_gold; }

	// 이 부분은 Player와 Monster가 상위 클래스를 상속하지 않으면 각각의 Use 함수를 만들어야 하는 경우 존재.
	// 플레이어 인자 전달 필요
	 virtual void Use(Player& player) const = 0;

	// 몬스터에게 사용하는 아이템
	 virtual void Use(Monster& target) const = 0; 
protected:
	std::string m_id;
	std::string m_name;
	std::string m_description;
	TargetStat m_targetStat;
	ItemRank m_rank;
	int m_gold;
};