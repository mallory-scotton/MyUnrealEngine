///////////////////////////////////////////////////////////////////////////////
// Dependencies
///////////////////////////////////////////////////////////////////////////////
#include "Project/UProject.hpp"
#include "Utils/Filesystem/Filesystem.hpp"
#include "Utils/Archive/Archive.hpp"
#include "Utils/Archive/SaveArchive.hpp"
#include "Config/Config.hpp"

///////////////////////////////////////////////////////////////////////////////
// Namespace UEB
///////////////////////////////////////////////////////////////////////////////
namespace UEB
{

///////////////////////////////////////////////////////////////////////////////
UProject::UProject(void)
{}

///////////////////////////////////////////////////////////////////////////////
UProject::~UProject()
{}

///////////////////////////////////////////////////////////////////////////////
TSharedPtr<UProject> UProject::CreateProject(
    const FString& name,
    const FPath& location
)
{
    FPath root = location / name;
    FPath content = root / "Content";

    try {
        Fs::Mkdir(root);
        Fs::Mkdir(content);

        USaveArchive project(root / (name + ".uproject"));

        FUint8 major = (FUint8)UEB_VERSION_MAJOR;
        FUint8 minor = (FUint8)UEB_VERSION_MINOR;
        FUint8 patch = (FUint8)UEB_VERSION_PATCH;
        FString projectName = name;

        project << major << minor << patch << projectName;

    } catch (const std::exception& e) {}
    return (LoadProject(location));
}

///////////////////////////////////////////////////////////////////////////////
TSharedPtr<UProject> UProject::LoadProject(const FPath& location)
{
    if (!Fs::FileExists(location))
        return (nullptr);
    // TODO: Add project loading
    return (nullptr);
}

} // !namespace UEB
