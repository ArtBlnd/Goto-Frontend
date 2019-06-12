#ifndef __GTFW_C_FRONTNED_DRIVER_DRVIER_OPTION_H__
#define __GTFW_C_FRONTEND_DRIVER_DRIVER_OPTION_H__

#include <string>
#include <any>

namespace GTFW
{
    namespace Driver
    {
        enum class DriverOptionLevel
        {
            DOL_ALWAYS_REQ  = 0x01,
            DOL_HIDDEN      = 0x03,
            DOL_OPTIONAL    = 0x02,
        };

        class DriverOption
        {
            std::string       m_doKey;

            // Contains description of option
            // Note that this will be emitted if there is wrong value type on option or option helper is called.
            std::string       m_doDesc; 

            DriverOptionLevel m_doLevel;

        public:
            DriverOption() = delete;
            explicit DriverOption(std::string Key, std::string Desc, DriverOptionLevel Level);
            explicit DriverOption(std::string Key, DriverOptionLevel Level); // With no descprition

            std::string GetKeyOf() const;
            std::string GetDescriptionOf() const;
            DriverOptionLevel GetLevelOf() const;
        };
    }
}

#endif