///////////////////////////////////////////////////////////////////////////////
// Dependencies
///////////////////////////////////////////////////////////////////////////////
#include "GraphEditor/Nodes/EventNodes.hpp"
#include "GraphEditor/Core/UEvaluationContext.hpp"

///////////////////////////////////////////////////////////////////////////////
// Namespace UEB::Nodes
///////////////////////////////////////////////////////////////////////////////
namespace UEB::Nodes
{

///////////////////////////////////////////////////////////////////////////////
BeginPlayNode::BeginPlayNode(void)
    : UNode(
        "Event BeginPlay",
        Type::Blueprint,
        ImColor(180, 28, 28),
        NodeIcon::Event
    )
{
    AddOutputPin(UPin::Type::Flow);
}

///////////////////////////////////////////////////////////////////////////////
void BeginPlayNode::Evaluate(UEvaluationContext& context)
{
    context.SetPinValue<bool>(mOutputs[0], true);
}

///////////////////////////////////////////////////////////////////////////////
EndPlayNode::EndPlayNode(void)
    : UNode(
        "Event EndPlay",
        Type::Blueprint,
        ImColor(180, 28, 28),
        NodeIcon::Event
    )
{
    AddOutputPin(UPin::Type::Flow);
}

///////////////////////////////////////////////////////////////////////////////
void EndPlayNode::Evaluate(UEvaluationContext& context)
{
    context.SetPinValue<bool>(mOutputs[0], true);
}

///////////////////////////////////////////////////////////////////////////////
TickNode::TickNode(void)
    : UNode(
        "Event Tick",
        Type::Blueprint,
        ImColor(180, 28, 28),
        NodeIcon::Event
    )
{
    AddOutputPin(UPin::Type::Flow);
    AddOutputPin(UPin::Type::Float, "Delta Seconds");
}

///////////////////////////////////////////////////////////////////////////////
void TickNode::Evaluate(UEvaluationContext& context)
{
    context.SetPinValue<bool>(mOutputs[0], true);
}

///////////////////////////////////////////////////////////////////////////////
KeyNode::KeyNode(const FString& key)
    : UNode(
        key,
        Type::Blueprint,
        ImColor(180, 28, 28),
        NodeIcon::KeyboardEvent
    )
{
    AddOutputPin(UPin::Type::Flow, "Pressed");
    AddOutputPin(UPin::Type::Flow, "Released");
}

///////////////////////////////////////////////////////////////////////////////
void KeyNode::Evaluate(UEvaluationContext& context)
{
    (void)context;
}

} // !namespace UEB::Nodes