///////////////////////////////////////////////////////////////////////////////
// Header guard
///////////////////////////////////////////////////////////////////////////////
#pragma once

///////////////////////////////////////////////////////////////////////////////
// Dependencies
///////////////////////////////////////////////////////////////////////////////
#include "Utils/Types.hpp"

///////////////////////////////////////////////////////////////////////////////
// Namespace TKD
///////////////////////////////////////////////////////////////////////////////
namespace TKD
{

///////////////////////////////////////////////////////////////////////////////
/// \brief
///
///////////////////////////////////////////////////////////////////////////////
class UProject
{
public:
    UProject(void);
    ~UProject();

private:
    FString mName;
    FPath mLocation;
    // TODO: Add settings
    // TODO: Add content browser (TUniquePtr)
    bool mInitialized;
    bool mIsDirty;

public:
    static TSharedPtr<UProject> CreateProject(const FString& name, const FPath& location);
    static TSharedPtr<UProject> LoadProject(const FPath& location);

public:
    bool Initialize(void);
    bool Save(void);
    bool Close(void);
    bool HasUnsavedChanges(void) const;
    // TODO: Add settings
    // TODO: Add content browser *
    FPath GetProjectDirectory(void) const;
    FPath GetContentDirectory(void) const;
};

} // !namespace TKD
