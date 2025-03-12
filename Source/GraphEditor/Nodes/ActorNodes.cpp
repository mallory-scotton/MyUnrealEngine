///////////////////////////////////////////////////////////////////////////////
// Dependencies
///////////////////////////////////////////////////////////////////////////////
#include "GraphEditor/Nodes/ActorNodes.hpp"
#include "GraphEditor/Core/UEvaluationContext.hpp"
#include "Objects/AActor.hpp"

///////////////////////////////////////////////////////////////////////////////
// Namespace UEB::Nodes
///////////////////////////////////////////////////////////////////////////////
namespace UEB::Nodes
{

///////////////////////////////////////////////////////////////////////////////
GetActorLocationNode::GetActorLocationNode(void)
    : UNode(
        "Get Actor Location",
        Type::Blueprint,
        ImColor(110, 149, 104),
        NodeIcon::Function
    )
{
    AddInputPin(UPin::Type::Actor, "Target");
    AddOutputPin(UPin::Type::Vector, "Return Value");
}

///////////////////////////////////////////////////////////////////////////////
void GetActorLocationNode::Evaluate(UEvaluationContext& context)
{
    auto actor = context.template GetPinValue<AActor*>(mInputs[0]);

    if (actor) {
        context.template SetPinValue<FVec2>(mOutputs[0], actor->GetLocation());
    }
}

///////////////////////////////////////////////////////////////////////////////
SetActorLocationNode::SetActorLocationNode(void)
    : UNode(
        "Set Actor Location",
        Type::Blueprint,
        ImColor(78, 122, 150),
        NodeIcon::Function
    )
{
    AddInputPin(UPin::Type::Flow);
    AddInputPin(UPin::Type::Actor, "Target");
    AddInputPin(UPin::Type::Vector, "New Location");
    AddOutputPin(UPin::Type::Flow);
}

///////////////////////////////////////////////////////////////////////////////
void SetActorLocationNode::Evaluate(UEvaluationContext& context)
{
    auto flow = context.template GetPinValue<bool>(mInputs[0]);
    auto actor = context.template GetPinValue<AActor*>(mInputs[1]);
    auto vector = context.template GetPinValue<FVec2>(mInputs[2]);

    if (flow && actor) {
        actor->SetLocation(vector);
    }
    context.template SetPinValue<bool>(mOutputs[0], flow);
}

} // !namespace UEB::Nodes
