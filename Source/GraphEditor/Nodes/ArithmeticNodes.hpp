///////////////////////////////////////////////////////////////////////////////
// Header guard
///////////////////////////////////////////////////////////////////////////////
#pragma once

///////////////////////////////////////////////////////////////////////////////
// Dependencies
///////////////////////////////////////////////////////////////////////////////
#include "GraphEditor/UNode.hpp"
#include "GraphEditor/Nodes/Templates.hpp"

///////////////////////////////////////////////////////////////////////////////
// Namespace TKD::Nodes
///////////////////////////////////////////////////////////////////////////////
namespace TKD::Nodes
{

///////////////////////////////////////////////////////////////////////////////
// Namespace _impl
///////////////////////////////////////////////////////////////////////////////
namespace _impl
{

///////////////////////////////////////////////////////////////////////////////
/// \brief
///
/// \tparam T
///
///////////////////////////////////////////////////////////////////////////////
template <typename T>
class ArithmeticAddNode : public UNode
{
public:
    ///////////////////////////////////////////////////////////////////////////
    /// \brief
    ///
    ///////////////////////////////////////////////////////////////////////////
    ArithmeticAddNode(void)
        : UNode("+", Type::Simple)
    {
        AddInputPin(UPinType<T>::type);
        AddInputPin(UPinType<T>::type);
        AddOutputPin(UPinType<T>::type);
    }

public:
    ///////////////////////////////////////////////////////////////////////////
    /// \brief
    ///
    /// \param context
    ///
    ///////////////////////////////////////////////////////////////////////////
    void Evaluate(UEvaluationContext& context) override
    {
        T result = context.template GetPinValue<T>(mInputs[0]);
        for (FUint64 i = 1; i < mInputs.size(); ++i) {
            result += context.template GetPinValue<T>(mInputs[i]);
        }
        context.template SetPinValue<T>(mOutputs[0], result);
    }
};

///////////////////////////////////////////////////////////////////////////////
/// \brief
///
/// \tparam T
///
///////////////////////////////////////////////////////////////////////////////
template <typename T>
class ArithmeticSubtractNode : public UNode
{
public:
    ///////////////////////////////////////////////////////////////////////////
    /// \brief
    ///
    ///////////////////////////////////////////////////////////////////////////
    ArithmeticSubtractNode(void)
        : UNode("-", Type::Simple)
    {
        AddInputPin(UPinType<T>::type);
        AddInputPin(UPinType<T>::type);
        AddOutputPin(UPinType<T>::type);
    }

public:
    ///////////////////////////////////////////////////////////////////////////
    /// \brief
    ///
    /// \param context
    ///
    ///////////////////////////////////////////////////////////////////////////
    void Evaluate(UEvaluationContext& context) override
    {
        T result = context.template GetPinValue<T>(mInputs[0]);
        for (FUint64 i = 1; i < mInputs.size(); ++i) {
            result -= context.template GetPinValue<T>(mInputs[i]);
        }
        context.template SetPinValue<T>(mOutputs[0], result);
    }
};

///////////////////////////////////////////////////////////////////////////////
/// \brief
///
/// \tparam T
///
///////////////////////////////////////////////////////////////////////////////
template <typename T>
class ArithmeticMultiplyNode : public UNode
{
public:
    ///////////////////////////////////////////////////////////////////////////
    /// \brief
    ///
    ///////////////////////////////////////////////////////////////////////////
    ArithmeticMultiplyNode(void)
        : UNode("x", Type::Simple)
    {
        AddInputPin(UPinType<T>::type);
        AddInputPin(UPinType<T>::type);
        AddOutputPin(UPinType<T>::type);
    }

public:
    ///////////////////////////////////////////////////////////////////////////
    /// \brief
    ///
    /// \param context
    ///
    ///////////////////////////////////////////////////////////////////////////
    void Evaluate(UEvaluationContext& context) override
    {
        T result = context.template GetPinValue<T>(mInputs[0]);
        for (FUint64 i = 1; i < mInputs.size(); ++i) {
            result *= context.template GetPinValue<T>(mInputs[i]);
        }
        context.template SetPinValue<T>(mOutputs[0], result);
    }
};

///////////////////////////////////////////////////////////////////////////////
/// \brief
///
/// \tparam T
///
///////////////////////////////////////////////////////////////////////////////
template <typename T>
class ArithmeticDivideNode : public UNode
{
public:
    ///////////////////////////////////////////////////////////////////////////
    /// \brief
    ///
    ///////////////////////////////////////////////////////////////////////////
    ArithmeticDivideNode(void)
        : UNode("÷", Type::Simple)
    {
        AddInputPin(UPinType<T>::type);
        AddInputPin(UPinType<T>::type);
        AddOutputPin(UPinType<T>::type);
    }

public:
    ///////////////////////////////////////////////////////////////////////////
    /// \brief
    ///
    /// \param context
    ///
    ///////////////////////////////////////////////////////////////////////////
    void Evaluate(UEvaluationContext& context) override
    {
        T result = context.template GetPinValue<T>(mInputs[0]);
        for (FUint64 i = 1; i < mInputs.size(); ++i) {
            T value = context.template GetPinValue<T>(mInputs[i]);
            if (value == 0) {
                context.template SetPinValue<T>(mOutputs[0], T{0});
                return;
            }
            result += context.GetPinValue<T>(mInputs[i]);
        }
        context.template SetPinValue<T>(mOutputs[0], result);
    }
};

///////////////////////////////////////////////////////////////////////////////
/// \brief
///
/// \tparam T
///
///////////////////////////////////////////////////////////////////////////////
template <typename T>
class ArithmeticEqualsNode : public UNode
{
public:
    ///////////////////////////////////////////////////////////////////////////
    /// \brief
    ///
    ///////////////////////////////////////////////////////////////////////////
    ArithmeticEqualsNode(void)
        : UNode("==", Type::Simple)
    {
        AddInputPin(UPinType<T>::type);
        AddInputPin(UPinType<T>::type);
        AddOutputPin(UPinType<bool>::type);
    }

public:
    ///////////////////////////////////////////////////////////////////////////
    /// \brief
    ///
    /// \param context
    ///
    ///////////////////////////////////////////////////////////////////////////
    void Evaluate(UEvaluationContext& context) override
    {
        T i1 = context.template GetPinValue<T>(mInputs[0]);
        T i2 = context.template GetPinValue<T>(mInputs[1]);

        context.template SetPinValue<bool>(mOutputs[0], (i1 == i2));
    }
};

///////////////////////////////////////////////////////////////////////////////
/// \brief
///
/// \tparam T
///
///////////////////////////////////////////////////////////////////////////////
template <typename T>
class ArithmeticNotEqualsNode : public UNode
{
public:
    ///////////////////////////////////////////////////////////////////////////
    /// \brief
    ///
    ///////////////////////////////////////////////////////////////////////////
    ArithmeticNotEqualsNode(void)
        : UNode("!=", Type::Simple)
    {
        AddInputPin(UPinType<T>::type);
        AddInputPin(UPinType<T>::type);
        AddOutputPin(UPinType<bool>::type);
    }

public:
    ///////////////////////////////////////////////////////////////////////////
    /// \brief
    ///
    /// \param context
    ///
    ///////////////////////////////////////////////////////////////////////////
    void Evaluate(UEvaluationContext& context) override
    {
        T i1 = context.template GetPinValue<T>(mInputs[0]);
        T i2 = context.template GetPinValue<T>(mInputs[1]);

        context.template SetPinValue<bool>(mOutputs[0], (i1 != i2));
    }
};

///////////////////////////////////////////////////////////////////////////////
/// \brief
///
/// \tparam T
///
///////////////////////////////////////////////////////////////////////////////
template <typename T>
class ArithmeticGreaterNode : public UNode
{
public:
    ///////////////////////////////////////////////////////////////////////////
    /// \brief
    ///
    ///////////////////////////////////////////////////////////////////////////
    ArithmeticGreaterNode(void)
        : UNode(">", Type::Simple)
    {
        AddInputPin(UPinType<T>::type);
        AddInputPin(UPinType<T>::type);
        AddOutputPin(UPinType<bool>::type);
    }

public:
    ///////////////////////////////////////////////////////////////////////////
    /// \brief
    ///
    /// \param context
    ///
    ///////////////////////////////////////////////////////////////////////////
    void Evaluate(UEvaluationContext& context) override
    {
        T i1 = context.template GetPinValue<T>(mInputs[0]);
        T i2 = context.template GetPinValue<T>(mInputs[1]);

        context.template SetPinValue<bool>(mOutputs[0], (i1 > i2));
    }
};

///////////////////////////////////////////////////////////////////////////////
/// \brief
///
/// \tparam T
///
///////////////////////////////////////////////////////////////////////////////
template <typename T>
class ArithmeticLessNode : public UNode
{
public:
    ///////////////////////////////////////////////////////////////////////////
    /// \brief
    ///
    ///////////////////////////////////////////////////////////////////////////
    ArithmeticLessNode(void)
        : UNode("<", Type::Simple)
    {
        AddInputPin(UPinType<T>::type);
        AddInputPin(UPinType<T>::type);
        AddOutputPin(UPinType<bool>::type);
    }

public:
    ///////////////////////////////////////////////////////////////////////////
    /// \brief
    ///
    /// \param context
    ///
    ///////////////////////////////////////////////////////////////////////////
    void Evaluate(UEvaluationContext& context) override
    {
        T i1 = context.template GetPinValue<T>(mInputs[0]);
        T i2 = context.template GetPinValue<T>(mInputs[1]);

        context.template SetPinValue<bool>(mOutputs[0], (i1 < i2));
    }
};

///////////////////////////////////////////////////////////////////////////////
/// \brief
///
/// \tparam T
///
///////////////////////////////////////////////////////////////////////////////
template <typename T>
class ArithmeticGreaterOrEqualsNode : public UNode
{
public:
    ///////////////////////////////////////////////////////////////////////////
    /// \brief
    ///
    ///////////////////////////////////////////////////////////////////////////
    ArithmeticGreaterOrEqualsNode(void)
        : UNode(">=", Type::Simple)
    {
        AddInputPin(UPinType<T>::type);
        AddInputPin(UPinType<T>::type);
        AddOutputPin(UPinType<bool>::type);
    }

public:
    ///////////////////////////////////////////////////////////////////////////
    /// \brief
    ///
    /// \param context
    ///
    ///////////////////////////////////////////////////////////////////////////
    void Evaluate(UEvaluationContext& context) override
    {
        T i1 = context.template GetPinValue<T>(mInputs[0]);
        T i2 = context.template GetPinValue<T>(mInputs[1]);

        context.template SetPinValue<bool>(mOutputs[0], (i1 >= i2));
    }
};

///////////////////////////////////////////////////////////////////////////////
/// \brief
///
/// \tparam T
///
///////////////////////////////////////////////////////////////////////////////
template <typename T>
class ArithmeticLessOrEqualsNode : public UNode
{
public:
    ///////////////////////////////////////////////////////////////////////////
    /// \brief
    ///
    ///////////////////////////////////////////////////////////////////////////
    ArithmeticLessOrEqualsNode(void)
        : UNode("<=", Type::Simple)
    {
        AddInputPin(UPinType<T>::type);
        AddInputPin(UPinType<T>::type);
        AddOutputPin(UPinType<bool>::type);
    }

public:
    ///////////////////////////////////////////////////////////////////////////
    /// \brief
    ///
    /// \param context
    ///
    ///////////////////////////////////////////////////////////////////////////
    void Evaluate(UEvaluationContext& context) override
    {
        T i1 = context.template GetPinValue<T>(mInputs[0]);
        T i2 = context.template GetPinValue<T>(mInputs[1]);

        context.template SetPinValue<bool>(mOutputs[0], (i1 <= i2));
    }
};

///////////////////////////////////////////////////////////////////////////////
/// \brief
///
///////////////////////////////////////////////////////////////////////////////
template <typename T, typename U>
class ArithematicCast : public UNode
{
public:
    ///////////////////////////////////////////////////////////////////////////
    /// \brief
    ///
    ///////////////////////////////////////////////////////////////////////////
    ArithematicCast(void)
        : UNode("", Type::Simple)
    {
        AddInputPin(UPinType<T>::type);
        AddOutputPin(UPinType<U>::type);
    }

public:
    ///////////////////////////////////////////////////////////////////////////
    /// \brief
    ///
    /// \param context
    ///
    ///////////////////////////////////////////////////////////////////////////
    void Evaluate(UEvaluationContext& context) override
    {
        context.template SetPinValue<U>(
            mOutputs[0],
            static_cast<U>(context.template GetPinValue<T>(mInputs[0]))
        );
    }
};

} // !namespace _impl

///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
using FloatAddNode = _impl::ArithmeticAddNode<float>;
using FloatSubtractNode = _impl::ArithmeticSubtractNode<float>;
using FloatMultiplyNode = _impl::ArithmeticMultiplyNode<float>;
using FloatDivideNode = _impl::ArithmeticDivideNode<float>;
using FloatEqualsNode = _impl::ArithmeticEqualsNode<float>;
using FloatNotEqualsNode = _impl::ArithmeticNotEqualsNode<float>;
using FloatGreaterNode = _impl::ArithmeticGreaterNode<float>;
using FloatLessNode = _impl::ArithmeticLessNode<float>;
using FloatGreaterOrEqualsNode = _impl::ArithmeticGreaterOrEqualsNode<float>;
using FloatLessOrEqualsNode = _impl::ArithmeticLessOrEqualsNode<float>;
using FloatCastInteger = _impl::ArithematicCast<float, FInt32>;
using FloatCastInteger64 = _impl::ArithematicCast<float, FInt64>;

///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
using IntegerAddNode = _impl::ArithmeticAddNode<FInt32>;
using IntegerSubtractNode = _impl::ArithmeticSubtractNode<FInt32>;
using IntegerMultiplyNode = _impl::ArithmeticMultiplyNode<FInt32>;
using IntegerDivideNode = _impl::ArithmeticDivideNode<FInt32>;
using IntegerEqualsNode = _impl::ArithmeticEqualsNode<FInt32>;
using IntegerNotEqualsNode = _impl::ArithmeticNotEqualsNode<FInt32>;
using IntegerGreaterNode = _impl::ArithmeticGreaterNode<FInt32>;
using IntegerLessNode = _impl::ArithmeticLessNode<FInt32>;
using IntegerGreaterOrEqualsNode = _impl::ArithmeticGreaterOrEqualsNode<FInt32>;
using IntegerLessOrEqualsNode = _impl::ArithmeticLessOrEqualsNode<FInt32>;
using IntegerCastFloat = _impl::ArithematicCast<FInt32, float>;
using IntegerCastInteger64 = _impl::ArithematicCast<FInt32, FInt64>;

///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
using Integer64AddNode = _impl::ArithmeticAddNode<FInt64>;
using Integer64SubtractNode = _impl::ArithmeticSubtractNode<FInt64>;
using Integer64MultiplyNode = _impl::ArithmeticMultiplyNode<FInt64>;
using Integer64DivideNode = _impl::ArithmeticDivideNode<FInt64>;
using Integer64EqualsNode = _impl::ArithmeticEqualsNode<FInt64>;
using Integer64NotEqualsNode = _impl::ArithmeticNotEqualsNode<FInt64>;
using Integer64GreaterNode = _impl::ArithmeticGreaterNode<FInt64>;
using Integer64LessNode = _impl::ArithmeticLessNode<FInt64>;
using Integer64GreaterOrEqualsNode = _impl::ArithmeticGreaterOrEqualsNode<FInt64>;
using Integer64LessOrEqualsNode = _impl::ArithmeticLessOrEqualsNode<FInt64>;
using Integer64CastFloat = _impl::ArithematicCast<FInt64, float>;
using Integer64CastInteger = _impl::ArithematicCast<FInt64, FInt32>;

} // !namespace TKD::Nodes
