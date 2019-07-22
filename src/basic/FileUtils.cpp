#include <basic/FileUtils.h>

#include <iostream>
#include <fstream>
#include <filesystem>

namespace Goto
{
    namespace Basic
    {
        FileViewer::FileViewer(std::string fileName)
        {
            m_frName = std::move(fileName);
            m_frSize = std::filesystem::file_size(fileName);
        }

        FileViewer::~FileViewer()
        {
            FreeCache();
        }

        void FileViewer::OpenAndCache()
        {
            m_frCachedBuf = new char[m_frSize];

            {
                std::ifstream fileStream;

                fileStream.open(m_frName);
                fileStream.read(m_frCachedBuf, m_frSize);
                fileStream.close();
            }
        }

        char* FileViewer::GetBuffer()
        {
            // Read and cache file before we are returning buffer.
            if (m_frCachedBuf == nullptr)
            {
                OpenAndCache();
            }

            return m_frCachedBuf;
        }

        const std::string& FileViewer::GetFileName() const
        {
            return m_frName;
        }

        size_t FileViewer::GetFileSize() const
        {
            return m_frSize;
        }

        void FileViewer::FreeCache()
        {
            delete m_frCachedBuf;
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

        std::string fuGetFileExts(std::string fileName)
        {
            bool isRecording = false;
            std::string ext = "";

            for (char c : fileName)
            {
                if (c == '.')
                {
                    isRecording = true;
                }

                // The path name can be starting with '.'
                // we only records that filename's extensions.
                if (c == '\\' || c == '/')
                {
                    isRecording = false;
                    ext.clear();
                }

                if (isRecording)
                {
                    ext += c;
                }
            }

            return ext;
        }
    }
}