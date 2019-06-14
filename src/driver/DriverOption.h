#ifndef __GTFW_C_FRONTNED_DRIVER_DRIVER_OPTION_H__
#define __GTFW_C_FRONTEND_DRIVER_DRIVER_OPTION_H__

#include <string>
#include <any>
#include <unordered_map>

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

        class DriverOptionTable;
        class DriverOption
        {
            std::any    m_doVal;
            std::string m_doKey;

            // Contains description of option
            // Note that this will be emitted if there is wrong value type on option or option helper is called.
            std::string m_doDesc; 

            DriverOptionLevel m_doLevel;

        public:
            DriverOption() = delete;
            DriverOption(DriverOptionTable* Table, std::string Key, std::string Desc, DriverOptionLevel Level);
            DriverOption(DriverOptionTable* Table, std::string Key, DriverOptionLevel Level); // With no descprition

            std::string GetKeyOf() const;
            std::string GetDescriptionOf() const;
            DriverOptionLevel GetLevelOf() const;

            const char* GetValTypeName() const;
            std::any GetValOf();
            std::any SetValue(std::any newValue);
        };

        class DriverOptionTable
        {
            friend class DriverOption;
            std::unordered_map<std::string, DriverOption*> m_dotTable;

        protected:
            void AddOption(DriverOption* Option);

        public:
            DriverOption* Lookup(std::string Key);
        };

#define DEF_DRV_OPTION(Table, Name, Key, Desc, Level) DriverOption Name = DriverOption(Table, Key, Desc, Level);
    }
}

#endif