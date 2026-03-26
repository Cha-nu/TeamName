#include "ItemBase.h"

ItemBase::ItemBase(const std::string& name, ItemRank rank, ItemID id)
	: m_name(name), m_rank(rank), m_id(id)
{
}

ItemBase::~ItemBase()
{
}

