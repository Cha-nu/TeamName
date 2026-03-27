#pragma once

// Item을 사용할 때, 아이템의 고유 ID를 문자열로 정의하는 헤더 파일입니다.
// 아이템이 많아지면 이름을 기억하기 어렵기 때문에 편의상 작성한 파일입니다.
// 
// 만약 특정 상황에서 아이템을 추가한다면 이 헤더파일을 추가하신 뒤, Inventory::AddItem(ItemKey::Potion_HP_Common, 1)처럼 사용할 수 있습니다. (삭제도 동일합니다.)
// 데이터 시트에 아이템을 추가할 때마다 Key의 이름을 작성해야 합니다.
// 변수 이름과 값은 동일한 이름으로 작성하는 것이 좋습니다.
// 즉, 데이터 시트의 Key, 변수 이름, 값은 모두 동일한 게 좋습니다.
namespace ItemKey
{
	const char* Potion_HP_Common = "Potion_HP_Common";
	const char* Potion_HP_Uncommon = "Potion_HP_Uncommon";
	const char* Stamina_Potion_Common = "Stamina_Potion_Common";
	const char* Stamina_Potion_Rare = "Stamina_Potion_Rare";
}