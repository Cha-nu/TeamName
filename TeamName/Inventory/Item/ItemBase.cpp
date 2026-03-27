#include "ItemBase.h"

ItemBase::ItemBase(std::string id, const std::string& name, ItemRank rank)
	: m_id(id), m_name(name), m_rank(rank)
{
}

ItemBase::~ItemBase()
{
}

