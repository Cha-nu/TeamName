/*
 * 게임에서 사용되는 다양한 타입들을 정의하는 헤더 파일입니다.
 * TargetStat과 ItemRank, ItemID 열거형을 포함하고 있습니다.
 * 필요에 따라 추가적인 타입들을 이 파일에 정의할 수 있습니다.
 */


#pragma once

// 버프에 영향을 주는 스탯을 정의하는 열거형입니다.
enum class TargetStat
{
	HP,
	Stamina,
	Attack,
	// 추가적인 스탯이 필요한 경우 여기에 추가

	None = 99
};

// 아이템의 등급을 정의하는 열거형입니다.
enum class ItemRank
{
	Common = 1,
	Rare,
	Epic,
	Legendary
	// 추가적인 등급이 필요한 경우 여기에 추가
};