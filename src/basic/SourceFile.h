#ifndef __GFWK_C_FRONTEND_BASIC_SOURCE_FILE_H__
#define __GFWK_C_FRONTEND_BASIC_SOURCE_FILE_H__

#include <string>

namespace GFWK
{
    namespace Basic
    {
        enum class SourceType
        {
            HEADER, SOURCE
        };

        class SourceFile
        {
            SourceType m_sfType;

            std::string m_sfFilePath;
            std::string m_sfFileName;
        };
    }
}

#endif