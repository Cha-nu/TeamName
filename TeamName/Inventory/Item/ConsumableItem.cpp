#include <unordered_map>
#include "ConsumableItem.h"
#include "Player/Player.h"
#include "Monster/Monster.h"

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

void ConsumableItem::Use(Player& player)
{
	int calculated_amount = m_amount * static_cast<int>(m_rank);

	// 2. 데미지 아이템이라면 값을 마이너스로 바꿉니다.
	if ( m_isDamage )
	{
		calculated_amount = -calculated_amount;
	}

	if ( m_targetStat == TargetStat::HP )
	{
		player.SetStat().HP += calculated_amount;
	}
	else if ( m_targetStat == TargetStat::Stamina )
	{
		player.SetStat().Stamina += calculated_amount;
	}
	else if ( m_targetStat == TargetStat::Attack )
	{
		player.SetStat().Atk_Damage += calculated_amount;
	}
}

void ConsumableItem::Use(Monster& target)
{
	int calculated_amount = m_amount * static_cast<int>(m_rank);
	if ( m_isDamage )
	{
		target.takeDamage(calculated_amount);
	}
	else
	{
		target.takeDamage(-calculated_amount);
	}
}