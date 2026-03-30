/*
 * 소모성 아이템을 정의하는 클래스입니다.
 *
 */


#pragma once

#include "ItemBase.h"

class ConsumableItem : public ItemBase
{
public:
	ConsumableItem(std::string id, const std::string& name, ItemRank rank, TargetStat stat, int gold, int amount, bool isDamage = false);
	virtual ~ConsumableItem();
	
	virtual void Use(Player& player) const override;
	virtual void Use(Monster& target) const override;

	// 아래는 Player가 MaxStat인지 확인하는 함수입니다.
	// 이를 활용해서 Use 함수에 사용 불가(0)/사용 완료(1)로 구분하여 반환할 수 있습니다. -> Scene의 텍스트 출력에 활용할 수 있습니다.
	// 이를 활용하려면 Use의 반환형을 바꿔야 하므로, 현재는 주석처리 하였습니다.
	/*bool IsMaxStat(Player& player) const;*/
private:
	int m_amount;
	bool m_isDamage;

	float StatClamp(float stat , float maxStat) const;
};