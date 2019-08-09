#include "driver/DriverOption.h"

namespace Goto
{
namespace Driver
{


DriverOption::DriverOption(
    DriverOptionTable* Table, std::string Key, std::any Init, std::string Desc, DriverOptionLevel Level)
{
    m_doKey   = Key;
    m_doVal   = Init;
    m_doDesc  = Desc;
    m_doLevel = Level;

    Table->AddOption(this);
}

DriverOption::DriverOption(DriverOptionTable* Table, std::string Key, std::any Init, DriverOptionLevel Level)
    : DriverOption(Table, Key, Init, "" /* Empty Description*/, Level)
{
}

std::string DriverOption::GetKeyOf() const
{
    return m_doKey;
}

std::string DriverOption::GetDescriptionOf() const
{
    return m_doDesc.empty() ? "No Descriptions" : m_doDesc;
}

DriverOptionLevel DriverOption::GetLevelOf() const
{
    return m_doLevel;
}

const char* DriverOption::GetValTypeName() const
{
    return m_doVal.type().name();
}

std::any DriverOption::GetValOf()
{
    return m_doVal;
}

std::any DriverOption::SetValue(std::any newValue)
{
    std::swap(m_doVal, newValue);
    return m_doVal;
}

void DriverOptionTable::AddOption(DriverOption* Option)
{
    m_dotTable.insert(std::make_pair(Option->GetKeyOf(), Option));
}

DriverOption* DriverOptionTable::Lookup(std::string Key)
{
    return m_dotTable[Key];
}

} // namespace Driver
} // namespace Goto