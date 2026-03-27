/*
* 게임 내에서 생성되는 모든 아이템을 관리하는 DB
*/

#pragma once
#include <unordered_map>
#include "Inventory/Item/ItemBase.h"

class ItemManager
{
public:
	ItemManager();
	~ItemManager();

	// 아이템을 ID로 검색하여 반환하는 함수입니다. 아이템이 존재하지 않을 경우 nullptr을 반환합니다.
	const ItemBase* GetItem(const std::string& id);
private:
	// 아이템 ID를 키로, 아이템 데이터를 값으로 저장하는 해시맵입니다.
	std::unordered_map<std::string, ItemBase*> m_itemDataBase;

	// CSV 파일에서 아이템 데이터를 읽어와 m_itemDataBase에 저장하는 함수입니다.
	void LoadItemsFromFile(const std::string& filename);

	// CSV 파일에서 읽은 문자열을 TargetStat과 ItemRank 열거형으로 변환하는 함수입니다.
	TargetStat StringToTargetStat(const std::string& str);
	ItemRank StringToItemRank(const std::string& str);
};