///////////////////////////////////////////////////////////////////////////////
// Dependencies
///////////////////////////////////////////////////////////////////////////////
#include "Project/UAsset.hpp"
#include "Project/UProject.hpp"

///////////////////////////////////////////////////////////////////////////////
// Namespace UEB
///////////////////////////////////////////////////////////////////////////////
namespace UEB
{

///////////////////////////////////////////////////////////////////////////////
UAsset::UAsset(const FString& name, Type type, const FPath& path)
    : mName(name)
    , mType(type)
    , mPath(path)
    , mProject(nullptr)
    , mDirty(false)
{}

///////////////////////////////////////////////////////////////////////////////
FString UAsset::TypeToString(UAsset::Type type)
{
    switch (type) {
        case UAsset::Type::Blueprint:       return ("Blueprint");
        case UAsset::Type::Texture:         return ("Texture");
        case UAsset::Type::Sound:           return ("Sound");
        case UAsset::Type::Level:           return ("Level");
        case UAsset::Type::Font:            return ("Font");
        default:                            return ("Unknown");
    }
}

///////////////////////////////////////////////////////////////////////////////
UAsset::Type UAsset::StringToType(const FString& type)
{
    if (type == "Blueprint")    return (UAsset::Type::Blueprint);
    if (type == "Texture")      return (UAsset::Type::Texture);
    if (type == "Sound")        return (UAsset::Type::Sound);
    if (type == "Level")        return (UAsset::Type::Level);
    if (type == "Font")         return (UAsset::Type::Font);
    return (UAsset::Type::Unknown);
}

///////////////////////////////////////////////////////////////////////////////
const FString& UAsset::GetName(void) const
{
    return (mName);
}

///////////////////////////////////////////////////////////////////////////////
void UAsset::SetName(const FString& name)
{
    mName = name;
}

///////////////////////////////////////////////////////////////////////////////
UAsset::Type UAsset::GetType(void) const
{
    return (mType);
}

///////////////////////////////////////////////////////////////////////////////
const FPath& UAsset::GetPath(void) const
{
    return (mPath);
}

///////////////////////////////////////////////////////////////////////////////
void UAsset::SetPath(const FPath& path)
{
    mPath = path;
}

///////////////////////////////////////////////////////////////////////////////
TSharedPtr<UProject> UAsset::GetProject(void) const
{
    return (mProject);
}

///////////////////////////////////////////////////////////////////////////////
void UAsset::SetProject(TSharedPtr<UProject> project)
{
    mProject = project;
}

///////////////////////////////////////////////////////////////////////////////
bool UAsset::IsDirty(void) const
{
    return (mDirty);
}

///////////////////////////////////////////////////////////////////////////////
void UAsset::MarkDirty(bool dirty)
{
    mDirty = dirty;
}

///////////////////////////////////////////////////////////////////////////////
bool UAsset::Save(void)
{
    // TODO: Add assets saving
    return (true);
}

///////////////////////////////////////////////////////////////////////////////
bool UAsset::Load(void)
{
    // TODO: ADd assets loading
    return (true);
}

} // !namespace UEB
