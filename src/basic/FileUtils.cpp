#include <basic/FileUtils.h>

#include <iostream>
#include <fstream>
#include <filesystem>

namespace Goto
{
    namespace Basic
    {
        FileReader::FileReader(std::string fileName)
        {
            m_frName = std::move(fileName);
            m_frSize = std::filesystem::file_size(fileName);
        }

        FileReader::~FileReader()
        {
            delete m_frCachedBuf;
        }

        void FileReader::OpenAndCache()
        {
            m_frCachedBuf = new char[m_frSize];
        }

        char* FileReader::GetBuffer()
        {
            // Read and cache file before we are returning buffer.
            if (m_frCachedBuf == nullptr)
            {
                OpenAndCache();
            }

            return m_frCachedBuf;
        }

        const std::string& FileReader::GetFileName() const
        {
            return m_frName;
        }

        size_t FileReader::GetFileSize() const
        {
            return m_frSize;
        }


        bool fuFileExists(std::string filePath)
        {
            return std::filesystem::file_size(filePath);
        }

        bool fuFileExists(std::string filePath, std::string basePath)
        {
            return fuFileExists(fuGetFullFilePath(filePath, basePath));
        }

        std::string fuGetFullFilePath(std::string filePath, std::string basePath)
        {
            if (basePath.back() == '\\' || basePath.back() == '/')
            {
                return basePath + filePath;
            }

            return basePath + "/" + filePath;
        }
    }
}