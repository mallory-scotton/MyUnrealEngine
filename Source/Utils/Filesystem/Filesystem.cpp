///////////////////////////////////////////////////////////////////////////////
// Dependencies
///////////////////////////////////////////////////////////////////////////////
#include "Utils/Filesystem/Filesystem.hpp"
#include <filesystem>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <system_error>

///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
namespace fs = std::filesystem;

///////////////////////////////////////////////////////////////////////////////
// Namespace UEB::Fs
///////////////////////////////////////////////////////////////////////////////
namespace UEB::Fs
{

///////////////////////////////////////////////////////////////////////////////
bool Mkdir(const FPath& path)
{
    std::error_code ec;
    return (fs::create_directories(path.string(), ec) && !ec);
}

///////////////////////////////////////////////////////////////////////////////
bool FileExists(const FPath& path)
{
    std::error_code ec;
    return (fs::exists(path, ec) && fs::is_regular_file(path, ec) && !ec);
}

///////////////////////////////////////////////////////////////////////////////
FUint64 FileSize(const FPath& path)
{
    std::error_code ec;
    if (!FileExists(path))
        return (0);

    return (static_cast<FUint64>(fs::file_size(path, ec)));
}

///////////////////////////////////////////////////////////////////////////////
bool DeleteFile(const FPath& path)
{
    std::error_code ec;
    return (fs::remove(path, ec) && !ec);
}

///////////////////////////////////////////////////////////////////////////////
bool RenameFile(const FPath& oldPath, const FPath& newPath)
{
    std::error_code ec;
    fs::rename(oldPath, newPath, ec);
    return (!ec);
}

///////////////////////////////////////////////////////////////////////////////
bool CopyFile(const FPath& source, const FPath& destination)
{
    std::error_code ec;
    fs::copy_file(
        source, destination, fs::copy_options::overwrite_existing, ec
    );
    return (!ec);
}

///////////////////////////////////////////////////////////////////////////////
TVector<FString> ListDirectory(const FPath& path)
{
    TVector<FString> results;
    std::error_code ec;

    if (!fs::exists(path, ec) || !fs::is_directory(path, ec))
        return (results);

    for (const auto& entry : fs::directory_iterator(path, ec))
    {
        results.push_back(entry.path().filename().string());
    }

    return (results);
}

///////////////////////////////////////////////////////////////////////////////
TVector<FString> DiscoverFilesByExtension(
    const FPath& path,
    const TVector<FString>& extensions,
    bool recursive
)
{
    TVector<FString> results;
    std::error_code ec;

    if (!fs::exists(path, ec) || !fs::is_directory(path, ec) )
        return (results);

    if (recursive) {
        for (const auto& entry : fs::recursive_directory_iterator(path, ec))
        {
            if (!entry.is_regular_file(ec))
                continue;

            FString extension = entry.path().extension().string();
            if (extension.size() > 0 && extension[0] == '.')
                extension = extension.substr(1);

            if (
                std::find(
                    extensions.begin(), extensions.end(), extension
                ) != extensions.end()
            ) {
                results.push_back(entry.path().string());
            }
        }
    } else {
        for (const auto& entry : fs::directory_iterator(path, ec))
        {
            if (!entry.is_regular_file(ec))
                continue;

            FString extension = entry.path().extension().string();
            if (extension.size() > 0 && extension[0] == '.')
                extension = extension.substr(1);

            if (
                std::find(
                    extensions.begin(), extensions.end(), extension
                ) != extensions.end()
            ) {
                results.push_back(entry.path().string());
            }
        }
    }

    return (results);
}

///////////////////////////////////////////////////////////////////////////////
bool RemoveDirectory(const FPath& path)
{
    std::error_code ec;
    return (fs::remove_all(path, ec) > 0 && !ec);
}

///////////////////////////////////////////////////////////////////////////////
TVector<FUint8> ReadBinaryFile(const FPath& path)
{
    FIfStream file(path, std::ios::in | std::ios::binary);
    if (!file.is_open())
        return (TVector<FUint8>());
    TVector<FUint8> buffer(
        (std::istreambuf_iterator<char>(file)),
        std::istreambuf_iterator<char>()
    );
    return (buffer);
}

///////////////////////////////////////////////////////////////////////////////
FString ReadFile(const FPath& path)
{
    FIfStream file(path, std::ios::in | std::ios::binary);
    if (!file.is_open())
        return ("");

    std::stringstream buffer;
    buffer << file.rdbuf();
    return (buffer.str());
}

///////////////////////////////////////////////////////////////////////////////
bool WriteFile(const FPath& path, const FString& content)
{
    FPath parentPath = path.parent_path();
    if (!parentPath.empty() && !fs::exists(parentPath))
    {
        std::error_code ec;
        if (!fs::create_directories(parentPath, ec) || ec)
            return (false);
    }

    FOfStream file(path, std::ios::out | std::ios::binary | std::ios::trunc);
    if (!file.is_open())
        return (false);

    file << content;
    return (!file.fail());
}

///////////////////////////////////////////////////////////////////////////////
bool AppendToFile(const FPath& path, const FString& content)
{
    FPath parentPath = path.parent_path();
    if (!parentPath.empty() && !fs::exists(parentPath))
    {
        std::error_code ec;
        if (!fs::create_directories(parentPath, ec) || ec)
            return (false);
    }

    std::ofstream file(path, std::ios::out | std::ios::binary | std::ios::app);
    if (!file.is_open())
        return (false);

    file << content;
    return (!file.fail());
}

///////////////////////////////////////////////////////////////////////////////
FString GetFileExtension(const FPath& path)
{
    FString extension = fs::path(path).extension().string();
    if (extension.size() > 0 && extension[0] == '.')
        return (extension.substr(1));
    return (extension);
}

///////////////////////////////////////////////////////////////////////////////
bool IsDirectory(const FPath& path)
{
    std::error_code ec;
    return (fs::exists(path, ec) && fs::is_directory(path, ec) && !ec);
}

///////////////////////////////////////////////////////////////////////////////
bool IsFile(const FPath& path)
{
    std::error_code ec;
    return (fs::exists(path, ec) && fs::is_regular_file(path, ec) && !ec);
}

} // !namespace UEB::Fs
