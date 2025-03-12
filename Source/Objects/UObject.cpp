///////////////////////////////////////////////////////////////////////////////
// Dependencies
///////////////////////////////////////////////////////////////////////////////
#include "Objects/UObject.hpp"
#include "GraphEditor/Nodes/EventNodes.hpp"

///////////////////////////////////////////////////////////////////////////////
// Namespace UEB
///////////////////////////////////////////////////////////////////////////////
namespace UEB
{

///////////////////////////////////////////////////////////////////////////////
UObject::UObject(TSharedPtr<UClass> inClass)
    : mClass(inClass)
    , mActive(true)
{}

///////////////////////////////////////////////////////////////////////////////
void UObject::BeginPlay(void)
{
    mClass->GetGraph()->Execute<Nodes::BeginPlayNode>(mContext);
}

///////////////////////////////////////////////////////////////////////////////
void UObject::Tick(float deltaSeconds)
{
    mClass->GetGraph()->Execute<Nodes::TickNode>(mContext, deltaSeconds);
}

///////////////////////////////////////////////////////////////////////////////
void UObject::EndPlay(void)
{
    mClass->GetGraph()->Execute<Nodes::EndPlayNode>(mContext);
}

///////////////////////////////////////////////////////////////////////////////
bool UObject::IsActive(void) const
{
    return (mActive);
}

///////////////////////////////////////////////////////////////////////////////
void UObject::SetActive(bool active)
{
    mActive = active;
}

} // !namespace UEB
