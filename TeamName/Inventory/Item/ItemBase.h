#pragma once
#include <string>

class ItemBase
{
public:
	ItemBase(const std::string& name, const std::string& description);
	~ItemBase();

	const std::string& GetName() const { return m_name; }
	const std::string& GetDescription() const { return m_description; }

	virtual void Use() = 0;
private:
	std::string m_name;
	std::string m_description;

};