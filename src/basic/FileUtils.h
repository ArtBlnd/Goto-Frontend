#ifndef __GOTO_C_FROTNEND_BASIC_FILE_UTILS_H__
#define __GOTO_C_FROTNEND_BASIC_FILE_UTILS_H__

#include <string>

namespace Goto
{
    namespace Basic
    {
        class FileReader
        {
            std::string m_frName;
            size_t      m_frSize;
            
            char* m_frCachedBuf = nullptr;

            void OpenAndCache();
        public:
            FileReader() = delete;
            FileReader(std::string fileName);
            ~FileReader();

            char* GetBuffer();

            const std::string& GetFileName() const;
            size_t GetFileSize() const;
        };

        bool fuFileExists(std::string filePath);
        bool fuFileExists(std::string filePath, std::string basePath);

        std::string fuGetFullFilePath(std::string filePath, std::string basePath);
    }
}

#endif