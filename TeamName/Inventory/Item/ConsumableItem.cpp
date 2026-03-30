#include <unordered_map>
#include "ConsumableItem.h"
#include "Player/Player.h"
#include "Monster/Monster.h"

ConsumableItem::ConsumableItem(std::string id, const std::string& name, ItemRank rank, TargetStat stat, int gold, int amount, bool isDamage)
	: ItemBase(id, name, stat, rank, gold), m_amount(amount), m_isDamage(isDamage)
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
 * 제가 생각한 Use의 사용 흐름은 다음과 같습니다.
 * 1. 사용자는 각 번호로 구분된 아이템을 선택합니다.
 * 예시) 인벤토리에 체력, 스테미나 포션이 각각 있으면 1. 체력 포션, 2. 스테미나 포션으로 표기되며, 사용자는 1 또는 2를 입력하여 아이템을 선택합니다. 그 이외의 입력은 무시되어야 합니다.
 * 2. 선택된 아이템은 아이템의 is_damage에 따라 GetItemSlots()[선택된 번호 -1].GetItem()->Use(player) 또는 GetItemSlots()[선택된 번호 -1].GetItem()->Use(monster)로 호출됩니다.
 * 3. 이후 플레이어는 RemoveItem(GetItemSlots()[선택된 번호 -1].GetItem()->GetID(), 1)로 아이템을 인벤토리에서 제거합니다.
 * 4. 만약, 아이템을 여러 번 사용한다면 위 과정을 해당 횟수만큼 반복합니다.
 * 5. 혹시나 디버프 아이템(플레이어의 체력을 깎는 아이템 or 몬스터 체력을 회복하는 아이템)을 사용하는 상황이 추가된다면 2번 과정의 로직 수정이 필요합니다.(데이터 시트에 플래그 추가)
 * 
*/

void ConsumableItem::Use(Player& player) const
{
	//if (IsMaxStat(player))
	//{
	//	// 이미 최대치인 경우 아이템 사용을 무시하고 메시지를 출력할 수 있습니다.
	//	return;
	//}

	float calculated_amount = m_amount * static_cast<float>(m_rank);

	if ( m_isDamage )
	{
		calculated_amount = -calculated_amount;
	}

	if ( m_targetStat == TargetStat::HP )
	{
		player.SetStat().HP = StatClamp(player.Getstat().HP + calculated_amount, player.GetMaxStat().MaxHP);
	}
	else if ( m_targetStat == TargetStat::Stamina )
	{
		player.SetStat().Stamina += static_cast<int>(calculated_amount);
	}
	else if ( m_targetStat == TargetStat::Attack )
	{
		player.SetStat().Atk_Damage += static_cast<int>(calculated_amount);
	}
}

void ConsumableItem::Use(Monster& target) const
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

//bool ConsumableItem::IsMaxStat(Player& player) const
//{
//	if (m_targetStat == TargetStat::HP)
//	{
//		return player.Getstat().HP == player.GetMaxStat().MaxHP;
//	}
//	else if (m_targetStat == TargetStat::Attack)
//	{
//		return player.Getstat().Atk_Damage == player.GetMaxStat().MaxAtk_Damage;
//	}
//
//	return false;
//}

float ConsumableItem::StatClamp(float stat, float maxStat) const
{
	if ( stat < 0.0f )
	{
		return 0.0f;
	}

	if ( stat > maxStat )
	{
		return maxStat;
	}

	return stat;
}
