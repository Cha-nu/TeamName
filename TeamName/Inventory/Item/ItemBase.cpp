#include "ItemBase.h"

ItemBase::ItemBase(std::string id, const std::string& name, TargetStat stat, ItemRank rank, int gold)
	: m_id(id), m_name(name), m_targetStat(stat), m_rank(rank), m_gold(gold)
{
}

ItemBase::~ItemBase()
{
}

