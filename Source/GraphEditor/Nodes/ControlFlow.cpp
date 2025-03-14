///////////////////////////////////////////////////////////////////////////////
// Dependencies
///////////////////////////////////////////////////////////////////////////////
#include "GraphEditor/Nodes/ControlFlow.hpp"
#include "GraphEditor/Core/UEvaluationContext.hpp"

///////////////////////////////////////////////////////////////////////////////
// Namespace UEB::Nodes
///////////////////////////////////////////////////////////////////////////////
namespace UEB::Nodes
{

///////////////////////////////////////////////////////////////////////////////
BranchNode::BranchNode(void)
    : UNode(
        "Branch",
        Type::Blueprint,
        ImColor(255, 255, 255),
        NodeIcon::Branch
    )
{
    AddInputPin(UPin::Type::Flow);
    AddInputPin(UPin::Type::Boolean, "Condition");
    AddOutputPin(UPin::Type::Flow, "True");
    AddOutputPin(UPin::Type::Flow, "False");
}

///////////////////////////////////////////////////////////////////////////////
void BranchNode::Evaluate(UEvaluationContext& context)
{
    bool flow = context.GetPinValue<bool>(mInputs[0]);
    bool condition = context.GetPinValue<bool>(mInputs[1]);

    if (flow) {
        context.SetPinValue<bool>(mOutputs[0], condition);
        context.SetPinValue<bool>(mOutputs[1], !condition);
    } else {
        context.SetPinValue<bool>(mOutputs[0], false);
        context.SetPinValue<bool>(mOutputs[1], false);
    }
}

///////////////////////////////////////////////////////////////////////////////
SequenceNode::SequenceNode(void)
    : UNode(
        "Sequence",
        Type::Blueprint,
        ImColor(255, 255, 255),
        NodeIcon::Sequence
    )
{
    AddInputPin(UPin::Type::Flow);
    AddOutputPin(UPin::Type::Flow, "Then 0");
    AddOutputPin(UPin::Type::Flow, "Then 1");
}

///////////////////////////////////////////////////////////////////////////////
void SequenceNode::Evaluate(UEvaluationContext& context)
{
    bool flow = context.GetPinValue<bool>(mInputs[0]);

    for (auto& output : mOutputs) {
        context.SetPinValue<bool>(output, flow);
    }
}

} // !namespace UEB::Nodes
