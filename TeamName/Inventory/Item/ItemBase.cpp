#include "ItemBase.h"

ItemBase::ItemBase(std::string id, const std::string& name, TargetStat stat, ItemRank rank)
	: m_id(id), m_name(name), m_targetStat(stat), m_rank(rank)
{
}

ItemBase::~ItemBase()
{
}

