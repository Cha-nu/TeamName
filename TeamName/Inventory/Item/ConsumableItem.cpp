#include <unordered_map>
#include "ConsumableItem.h"

ConsumableItem::ConsumableItem(std::string id, const std::string& name, ItemRank rank, TargetStat stat, int amount, bool isDamage)
	: ItemBase(id, name, rank), m_targetStat(stat), m_amount(amount), m_isDamage(isDamage)
{
	static const std::unordered_map<TargetStat, std::string> StatNames = {
		{ TargetStat::HP, "체력" },
		{ TargetStat::Stamina, "스테미나" },
		{ TargetStat::Attack, "공격력" }
	};

	if (m_isDamage)
	{
		m_description = "이 아이템은 몬스터에게" + std::to_string(m_amount * static_cast<int>(m_rank)) + "의 피해를 입힙니다.";
	}
	else
	{
		m_description = "이 아이템은 " + StatNames.at(m_targetStat) + "을 " + std::to_string(m_amount * static_cast<int>(m_rank)) + "만큼 회복합니다.";
	}
}

ConsumableItem::~ConsumableItem()
{

}


/*
ConsumableItem::Use()
{
// 캐릭터의 정보를 가져와서 m_targetStat에 따라 체력, 마나 등을 회복하는 로직을 구현 필요
}
*/