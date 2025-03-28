///////////////////////////////////////////////////////////////////////////////
// Header guard
///////////////////////////////////////////////////////////////////////////////
#pragma once

///////////////////////////////////////////////////////////////////////////////
// Dependencies
///////////////////////////////////////////////////////////////////////////////
#include "Utils/Types.hpp"
#include "GraphEditor/Core/UPin.hpp"
#include "GraphEditor/Core/ULink.hpp"
#include "GraphEditor/Core/UNode.hpp"

///////////////////////////////////////////////////////////////////////////////
// Namespace UEB
///////////////////////////////////////////////////////////////////////////////
namespace UEB
{

///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
class UNode;
class AActor;

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
    AActor* mActor;                             //<!

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
                if constexpr (std::is_convertible_v<int, T>) {
                    return (T{1});
                }
                return (T{});
            }
            if (pin->GetType() == UPin::Type::Actor) {
                if constexpr (std::is_convertible_v<AActor*, T>) {
                    return (static_cast<T>(GetActor()));
                }
                return (T{});
            }
            return (T{});
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

    ///////////////////////////////////////////////////////////////////////////
    /// \brief
    ///
    /// \return
    ///
    ///////////////////////////////////////////////////////////////////////////
    AActor* GetActor(void) const;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief
    ///
    /// \param actor
    ///
    ///////////////////////////////////////////////////////////////////////////
    void SetActor(AActor* actor);
};

} // !namespace UEB
