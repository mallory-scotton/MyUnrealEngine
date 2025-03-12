///////////////////////////////////////////////////////////////////////////////
// Dependencies
///////////////////////////////////////////////////////////////////////////////
#include "GraphEditor/Core/UNodesRegister.hpp"
#include "GraphEditor/Core/UEvaluationContext.hpp"
#include "GraphEditor/Nodes/ArithmeticNodes.hpp"
#include "GraphEditor/Nodes/ControlFlow.hpp"
#include "GraphEditor/Nodes/EventNodes.hpp"
#include "Utils/SFML/Enumerations.hpp"
#include <SFML/Graphics.hpp>

///////////////////////////////////////////////////////////////////////////////
// Namespace UEB
///////////////////////////////////////////////////////////////////////////////
namespace UEB
{

///////////////////////////////////////////////////////////////////////////////
UNodesRegister::FactoryMap UNodesRegister::mFactories;

///////////////////////////////////////////////////////////////////////////////
TVector<FString> UNodesRegister::mNames;

///////////////////////////////////////////////////////////////////////////////
FUint64 UNodesRegister::mBuiltInCount = 0;

///////////////////////////////////////////////////////////////////////////////
FUint64 UNodesRegister::RegisterBuiltIn(void)
{
    mBuiltInCount = 0;

    // Register Float arithmetic nodes
    mBuiltInCount += Register<Nodes::FloatAddNode>("Float.Add");
    mBuiltInCount += Register<Nodes::FloatSubtractNode>("Float.Subtract");
    mBuiltInCount += Register<Nodes::FloatMultiplyNode>("Float.Multiply");
    mBuiltInCount += Register<Nodes::FloatDivideNode>("Float.Divide");
    mBuiltInCount += Register<Nodes::FloatEqualsNode>("Float.Equals");
    mBuiltInCount += Register<Nodes::FloatNotEqualsNode>("Float.NotEquals");
    mBuiltInCount += Register<Nodes::FloatLessNode>("Float.Less");
    mBuiltInCount += Register<Nodes::FloatGreaterNode>("Float.Greater");
    mBuiltInCount += Register<Nodes::FloatLessOrEqualsNode>("Float.LessOrEquals");
    mBuiltInCount += Register<Nodes::FloatGreaterOrEqualsNode>("Float.GreaterOrEquals");
    mBuiltInCount += Register<Nodes::FloatCastInteger>("Float.Cast.Integer");
    mBuiltInCount += Register<Nodes::FloatCastInteger64>("Float.Cast.Integer64");

    // Register Integer arithmetic nodes
    mBuiltInCount += Register<Nodes::IntegerAddNode>("Integer.Add");
    mBuiltInCount += Register<Nodes::IntegerSubtractNode>("Integer.Subtract");
    mBuiltInCount += Register<Nodes::IntegerMultiplyNode>("Integer.Multiply");
    mBuiltInCount += Register<Nodes::IntegerDivideNode>("Integer.Divide");
    mBuiltInCount += Register<Nodes::IntegerEqualsNode>("Integer.Equals");
    mBuiltInCount += Register<Nodes::IntegerNotEqualsNode>("Integer.NotEquals");
    mBuiltInCount += Register<Nodes::IntegerLessNode>("Integer.Less");
    mBuiltInCount += Register<Nodes::IntegerGreaterNode>("Integer.Greater");
    mBuiltInCount += Register<Nodes::IntegerLessOrEqualsNode>("Integer.LessOrEquals");
    mBuiltInCount += Register<Nodes::IntegerGreaterOrEqualsNode>("Integer.GreaterOrEquals");
    mBuiltInCount += Register<Nodes::IntegerCastFloat>("Integer.Cast.Float");
    mBuiltInCount += Register<Nodes::IntegerCastInteger64>("Integer.Cast.Integer64");

    // Register Integer64 arithmetic nodes
    mBuiltInCount += Register<Nodes::Integer64AddNode>("Integer64.Add");
    mBuiltInCount += Register<Nodes::Integer64SubtractNode>("Integer64.Subtract");
    mBuiltInCount += Register<Nodes::Integer64MultiplyNode>("Integer64.Multiply");
    mBuiltInCount += Register<Nodes::Integer64DivideNode>("Integer64.Divide");
    mBuiltInCount += Register<Nodes::Integer64EqualsNode>("Integer64.Equals");
    mBuiltInCount += Register<Nodes::Integer64NotEqualsNode>("Integer64.NotEquals");
    mBuiltInCount += Register<Nodes::Integer64LessNode>("Integer64.Less");
    mBuiltInCount += Register<Nodes::Integer64GreaterNode>("Integer64.Greater");
    mBuiltInCount += Register<Nodes::Integer64LessOrEqualsNode>("Integer64.LessOrEquals");
    mBuiltInCount += Register<Nodes::Integer64GreaterOrEqualsNode>("Integer64.GreaterOrEquals");
    mBuiltInCount += Register<Nodes::Integer64CastFloat>("Integer64.Cast.Float");
    mBuiltInCount += Register<Nodes::Integer64CastInteger>("Integer64.Cast.Integer");

    // Register Control flow nodes
    mBuiltInCount += Register<Nodes::BranchNode>("Flow.Branch");
    mBuiltInCount += Register<Nodes::SequenceNode>("Flow.Sequence");

    // Register Events nodes
    mBuiltInCount += Register<Nodes::BeginPlayNode>("Event.BeginPlay");
    mBuiltInCount += Register<Nodes::EndPlayNode>("Event.EndPlay");
    mBuiltInCount += Register<Nodes::TickNode>("Event.Tick");

    // Register Key Events nodes
    for (FUint32 i = 0; i < sf::Keyboard::KeyCount; i++) {
        mBuiltInCount += Register<Nodes::KeyNode>(
            "Event.Key." + KeyNames[i], KeyNames[i]
        );
    }

    return (mBuiltInCount);
}

///////////////////////////////////////////////////////////////////////////////
bool UNodesRegister::Unregister(const FString& name)
{
    auto it = mFactories.find(name);
    if (it == mFactories.end()) {
        return (false);
    }

    auto end = std::remove(mNames.begin(), mNames.end(), name);
    mNames.erase(end, mNames.end());

    return (true);
}

///////////////////////////////////////////////////////////////////////////////
TSharedPtr<UNode> UNodesRegister::Create(const FString& name)
{
    auto it = mFactories.find(name);
    if (it == mFactories.end()) {
        return (nullptr);
    }

    TSharedPtr<UNode> node = it->second();

    node->SetRegister(name);

    return (node);
}

///////////////////////////////////////////////////////////////////////////////
bool UNodesRegister::IsRegistered(const FString& name)
{
    return (mFactories.find(name) != mFactories.end());
}

///////////////////////////////////////////////////////////////////////////////
TVector<FString> UNodesRegister::GetNames(void)
{
    if (mBuiltInCount == 0) {
        RegisterBuiltIn();
    }
    return (mNames);
}

///////////////////////////////////////////////////////////////////////////////
void UNodesRegister::Reset(void)
{
    mFactories.clear();
    mNames.clear();
    RegisterBuiltIn();
}

} // !namespace UEB
