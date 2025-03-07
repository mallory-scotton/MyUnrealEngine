///////////////////////////////////////////////////////////////////////////////
// Dependencies
///////////////////////////////////////////////////////////////////////////////
#include "GraphEditor/UNodesRegister.hpp"
#include "GraphEditor/UEvaluationContext.hpp"
#include "GraphEditor/Nodes/ArithmeticNodes.hpp"
#include "GraphEditor/Nodes/ControlFlow.hpp"

///////////////////////////////////////////////////////////////////////////////
// Namespace TKD
///////////////////////////////////////////////////////////////////////////////
namespace TKD
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

    // Register Control flow nodes
    mBuiltInCount += Register<Nodes::BranchNode>("Flow.Branch");

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

    return (it->second());
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

} // !namespace TKD
