#include "driver/DriverOption.h"

namespace GTFW
{
    namespace Driver
    {
        DriverOption::DriverOption(std::string Key, std::string Desc, DriverOptionLevel Level)
        {
            m_doKey   = Key;
            m_doDesc  = Desc;
            m_doLevel = Level;
        }

        DriverOption::DriverOption(std::string Key, DriverOptionLevel Level) :
            DriverOption(Key, "" /* Empty Description*/, Level)
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
    }
}