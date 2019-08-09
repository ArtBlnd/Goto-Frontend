#ifndef __GOTO_C_FROTNEND_BASIC_FILE_UTILS_H__
#define __GOTO_C_FROTNEND_BASIC_FILE_UTILS_H__

#include <string>

namespace Goto
{
namespace Basic
{

class FileViewer
{
    std::string m_frName;
    size_t      m_frSize;

    char* m_frCachedBuf = nullptr;

    void OpenAndCache();

public:
    FileViewer() = delete;
    FileViewer(std::string fileName);
    ~FileViewer();

    // Read file buffer and cache, return it.
    char* GetBuffer();

    // Free buffer caches to reload it
    void FreeCache();

    const std::string& GetFileName() const;
    size_t             GetFileSize() const;
};

// Check that file exists. true means its exists.
bool fuFileExists(std::string filePath);
bool fuFileExists(std::string filePath, std::string basePath);

// Get full file path based on basePath which means returning absolute path.
std::string fuGetFullFilePath(std::string filePath, std::string basePath);

// Get file extension from file name.
std::string fuGetFileExts(std::string fileName);

} // namespace Basic
} // namespace Goto

#endif