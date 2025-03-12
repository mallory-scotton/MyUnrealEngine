///////////////////////////////////////////////////////////////////////////////
// Header guard
///////////////////////////////////////////////////////////////////////////////
#pragma once

///////////////////////////////////////////////////////////////////////////////
// Dependencies
///////////////////////////////////////////////////////////////////////////////
#include "Utils/Types.hpp"
#include "GraphEditor/Core/UNode.hpp"

///////////////////////////////////////////////////////////////////////////////
// Namespace UEB
///////////////////////////////////////////////////////////////////////////////
namespace UEB
{

///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
class AActor;

} // !namespace UEB

///////////////////////////////////////////////////////////////////////////////
// Namespace UEB::Nodes
///////////////////////////////////////////////////////////////////////////////
namespace UEB::Nodes
{

///////////////////////////////////////////////////////////////////////////////
/// \brief
///
///////////////////////////////////////////////////////////////////////////////
class GetActorLocationNode : public UNode
{
public:
    ///////////////////////////////////////////////////////////////////////////
    /// \brief
    ///
    ///////////////////////////////////////////////////////////////////////////
    GetActorLocationNode(void);

public:
    ///////////////////////////////////////////////////////////////////////////
    /// \brief
    ///
    /// \param context
    ///
    ///////////////////////////////////////////////////////////////////////////
    void Evaluate(UEvaluationContext& context) override;
};

///////////////////////////////////////////////////////////////////////////////
/// \brief
///
///////////////////////////////////////////////////////////////////////////////
class SetActorLocationNode : public UNode
{
public:
    ///////////////////////////////////////////////////////////////////////////
    /// \brief
    ///
    ///////////////////////////////////////////////////////////////////////////
    SetActorLocationNode(void);

public:
    ///////////////////////////////////////////////////////////////////////////
    /// \brief
    ///
    /// \param context
    ///
    ///////////////////////////////////////////////////////////////////////////
    void Evaluate(UEvaluationContext& context) override;
};

///////////////////////////////////////////////////////////////////////////////
/// \brief
///
///////////////////////////////////////////////////////////////////////////////
class GetActorForwardVectorNode : public UNode
{
public:
    ///////////////////////////////////////////////////////////////////////////
    /// \brief
    ///
    ///////////////////////////////////////////////////////////////////////////
    GetActorForwardVectorNode(void);

public:
    ///////////////////////////////////////////////////////////////////////////
    /// \brief
    ///
    /// \param context
    ///
    ///////////////////////////////////////////////////////////////////////////
    void Evaluate(UEvaluationContext& context) override;
};

///////////////////////////////////////////////////////////////////////////////
/// \brief
///
///////////////////////////////////////////////////////////////////////////////
class GetActorUpVectorNode : public UNode
{
public:
    ///////////////////////////////////////////////////////////////////////////
    /// \brief
    ///
    ///////////////////////////////////////////////////////////////////////////
    GetActorUpVectorNode(void);

public:
    ///////////////////////////////////////////////////////////////////////////
    /// \brief
    ///
    /// \param context
    ///
    ///////////////////////////////////////////////////////////////////////////
    void Evaluate(UEvaluationContext& context) override;
};

} // !namespace UEB::Nodes
