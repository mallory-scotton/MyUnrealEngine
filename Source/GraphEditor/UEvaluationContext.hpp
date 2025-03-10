///////////////////////////////////////////////////////////////////////////////
// Header guard
///////////////////////////////////////////////////////////////////////////////
#pragma once

///////////////////////////////////////////////////////////////////////////////
// Dependencies
///////////////////////////////////////////////////////////////////////////////
#include "Utils/Types.hpp"
#include "GraphEditor/UPin.hpp"
#include "GraphEditor/ULink.hpp"
#include "GraphEditor/UNode.hpp"

///////////////////////////////////////////////////////////////////////////////
// Namespace TKD
///////////////////////////////////////////////////////////////////////////////
namespace TKD
{

///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
class UNode;

///////////////////////////////////////////////////////////////////////////////
/// \brief
///
///////////////////////////////////////////////////////////////////////////////
class UEvaluationContext
{
private:
    ///////////////////////////////////////////////////////////////////////////
    //
    ///////////////////////////////////////////////////////////////////////////
    TUnorderedMap<FString, FAny> mProperties;   //<!
    TUnorderedMap<UPin::ID, FAny> mPinValues;   //<!
    TQueue<TWeakPtr<UNode>> mEvaluationQueue;   //<!
    TUnorderedSet<UNode::ID> mEvaluatedNodes;   //<!

public:
    ///////////////////////////////////////////////////////////////////////////
    /// \brief
    ///
    /// \tparam T
    ///
    /// \param pin
    /// \param value
    ///
    ///////////////////////////////////////////////////////////////////////////
    template <typename T>
    void SetPinValue(TSharedPtr<UPin> pin, const T& value)
    {
        mPinValues[pin->GetID()] = value;

        if (pin->GetKind() == UPin::Kind::Input) {
            return;
        }

        for (const auto& weakLink : pin->GetLinks()) {
            TSharedPtr<ULink> link = weakLink.lock();

            if (!link) {
                continue;
            }

            auto target = link->GetTarget();

            if (!target || target == pin) {
                continue;
            }

            SetPinValue<T>(target, value);
        }
    }

    ///////////////////////////////////////////////////////////////////////////
    /// \brief
    ///
    /// \tparam T
    ///
    /// \param name
    /// \param value
    ///
    ///////////////////////////////////////////////////////////////////////////
    template <typename T>
    void SetProperty(const FString& name, const T& value)
    {
        mProperties[name] = value;
    }

    ///////////////////////////////////////////////////////////////////////////
    /// \brief
    ///
    /// \tparam T
    ///
    /// \param pin
    ///
    /// \return
    ///
    ///////////////////////////////////////////////////////////////////////////
    template <typename T>
    T GetPinValue(TSharedPtr<UPin> pin) const
    {
        if (mPinValues.count(pin->GetID()) == 0) {
            if (pin->GetType() == UPin::Type::Flow) {
                return (T{1});
            }
            return (T{0});
        }
        return (std::any_cast<T>(mPinValues.at(pin->GetID())));
    }

    ///////////////////////////////////////////////////////////////////////////
    /// \brief
    ///
    /// \tparam T
    ///
    /// \param name
    ///
    /// \return
    ///
    ///////////////////////////////////////////////////////////////////////////
    template <typename T>
    T GetProperty(const FString& name) const
    {
        if (mProperties.count(name) == 0) {
            return (T{0});
        }
        return (std::any_cast<T>(mProperties.at(name)));
    }

    ///////////////////////////////////////////////////////////////////////////
    /// \brief
    ///
    /// \param node
    ///
    ///////////////////////////////////////////////////////////////////////////
    void AddToEvaluationQueue(TWeakPtr<UNode> node);

    ///////////////////////////////////////////////////////////////////////////
    /// \brief
    ///
    /// \return
    ///
    ///////////////////////////////////////////////////////////////////////////
    bool IsQueueEmpty(void) const;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief
    ///
    /// \return
    ///
    ///////////////////////////////////////////////////////////////////////////
    TWeakPtr<UNode> GetNextNode(void);

    ///////////////////////////////////////////////////////////////////////////
    /// \brief
    ///
    /// \param pin
    ///
    /// \return
    ///
    ///////////////////////////////////////////////////////////////////////////
    bool HasPinValue(TSharedPtr<UPin> pin) const;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief
    ///
    /// \param node
    ///
    ///////////////////////////////////////////////////////////////////////////
    void MarkAsEvaluated(TSharedPtr<UNode> node);

    ///////////////////////////////////////////////////////////////////////////
    /// \brief
    ///
    /// \param node
    ///
    /// \return
    ///
    ///////////////////////////////////////////////////////////////////////////
    bool IsEvaluated(TSharedPtr<UNode> node) const;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief
    ///
    ///////////////////////////////////////////////////////////////////////////
    void Reset(void);
};

} // !namespace TKD
