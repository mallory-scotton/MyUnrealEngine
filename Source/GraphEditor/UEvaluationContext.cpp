///////////////////////////////////////////////////////////////////////////////
// Dependencies
///////////////////////////////////////////////////////////////////////////////
#include "GraphEditor/UEvaluationContext.hpp"

///////////////////////////////////////////////////////////////////////////////
// Namespace TKD
///////////////////////////////////////////////////////////////////////////////
namespace TKD
{

///////////////////////////////////////////////////////////////////////////////
void UEvaluationContext::AddToEvaluationQueue(TWeakPtr<UNode> node)
{
    mEvaluationQueue.push(node);
}

///////////////////////////////////////////////////////////////////////////////
bool UEvaluationContext::IsQueueEmpty(void) const
{
    return (mEvaluationQueue.empty());
}

///////////////////////////////////////////////////////////////////////////////
TWeakPtr<UNode> UEvaluationContext::GetNextNode(void)
{
    TWeakPtr<UNode> node = mEvaluationQueue.front();
    mEvaluationQueue.pop();
    return (node);
}

///////////////////////////////////////////////////////////////////////////////
bool UEvaluationContext::HasPinValue(TSharedPtr<UPin> pin) const
{
    return (mPinValues.count(pin->GetID()) > 0);
}

///////////////////////////////////////////////////////////////////////////////
void UEvaluationContext::MarkAsEvaluated(TSharedPtr<UNode> node)
{
    mEvaluatedNodes.insert(node->GetID());
}

///////////////////////////////////////////////////////////////////////////////
bool UEvaluationContext::IsEvaluated(TSharedPtr<UNode> node) const
{
    return (mEvaluatedNodes.count(node->GetID()) != 0);
}

///////////////////////////////////////////////////////////////////////////////
void UEvaluationContext::Reset(void)
{
    mProperties.clear();
    mPinValues.clear();
    mEvaluationQueue = TQueue<TWeakPtr<UNode>>();
    mEvaluatedNodes.clear();
}

} // !namespace TKD
