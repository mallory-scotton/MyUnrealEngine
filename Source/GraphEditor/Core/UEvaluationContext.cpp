///////////////////////////////////////////////////////////////////////////////
// Dependencies
///////////////////////////////////////////////////////////////////////////////
#include "GraphEditor/Core/UEvaluationContext.hpp"
#include "Objects/AActor.hpp"
#include "Utils/Types.hpp"

///////////////////////////////////////////////////////////////////////////////
// Namespace UEB
///////////////////////////////////////////////////////////////////////////////
namespace UEB
{

///////////////////////////////////////////////////////////////////////////////
void UEvaluationContext::AddToEvaluationQueue(TWeakPtr<UNode> node)
{
    for (auto& pin : node.lock()->GetInputs()) {
        if (pin->GetType() == UPin::Type::Flow) {
            continue;
        }
        for (auto& weakLink : pin->GetLinks()) {
            auto link = weakLink.lock();

            if (!link) {
                continue;
            }

            TSharedPtr<UNode> target = link->GetSource()->GetOwner();

            if (target && !IsEvaluated(target)) {
                AddToEvaluationQueue(target);
            }
        }
    }
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

///////////////////////////////////////////////////////////////////////////////
AActor* UEvaluationContext::GetActor(void) const
{
    return (mActor);
}

///////////////////////////////////////////////////////////////////////////////
void UEvaluationContext::SetActor(AActor* actor)
{
    mActor = actor;
}

} // !namespace UEB
