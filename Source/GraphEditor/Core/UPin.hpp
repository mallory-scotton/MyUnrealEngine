///////////////////////////////////////////////////////////////////////////////
// Header guard
///////////////////////////////////////////////////////////////////////////////
#pragma once

///////////////////////////////////////////////////////////////////////////////
// Dependencies
///////////////////////////////////////////////////////////////////////////////
#include "Utils/Types.hpp"
#include <imgui.h>
#include <imgui_node_editor.h>

///////////////////////////////////////////////////////////////////////////////
// Namespace UEB
///////////////////////////////////////////////////////////////////////////////
namespace UEB
{

///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
class ULink;
class UNode;

///////////////////////////////////////////////////////////////////////////////
/// \brief
///
///////////////////////////////////////////////////////////////////////////////
class UPin
{
public:
    ///////////////////////////////////////////////////////////////////////////
    //
    ///////////////////////////////////////////////////////////////////////////
    using ID = ax::NodeEditor::PinId;       //<!
    using Kind = ax::NodeEditor::PinKind;   //<!

public:
    ///////////////////////////////////////////////////////////////////////////
    /// \brief
    ///
    ///////////////////////////////////////////////////////////////////////////
    enum class Type
    {
        Float,          //<!
        Integer,        //<!
        Integer64,      //<!
        Boolean,        //<!
        Byte,           //<!
        String,         //<!
        Vector,         //<!
        Actor,          //<!
        Flow            //<!
    };

private:
    ///////////////////////////////////////////////////////////////////////////
    //
    ///////////////////////////////////////////////////////////////////////////
    Type mType;                         //<!
    Kind mKind;                         //<!
    ID mID;                             //<!
    FString mName;                      //<!
    TVector<TWeakPtr<ULink>> mLinks;    //<!
    TWeakPtr<UNode> mOwner;             //<!
    FAny mValue;                        //<!

public:
    ///////////////////////////////////////////////////////////////////////////
    /// \brief
    ///
    /// \param type
    /// \param kind
    /// \param name
    ///
    ///////////////////////////////////////////////////////////////////////////
    UPin(Type type, Kind kind, const FString& name = "");

public:
    ///////////////////////////////////////////////////////////////////////////
    /// \brief
    ///
    /// \param a
    /// \param b
    ///
    /// \return
    ///
    ///////////////////////////////////////////////////////////////////////////
    static bool CanConnectTo(TSharedPtr<UPin> a, TSharedPtr<UPin> b);

private:
    ///////////////////////////////////////////////////////////////////////////
    /// \brief
    ///
    /// \param alpha
    ///
    ///////////////////////////////////////////////////////////////////////////
    void DrawPinIcon(float alpha);

    ///////////////////////////////////////////////////////////////////////////
    /// \brief
    ///
    ///////////////////////////////////////////////////////////////////////////
    void RenderInput(void);

public:
    ///////////////////////////////////////////////////////////////////////////
    /// \brief
    ///
    /// \return
    ///
    ///////////////////////////////////////////////////////////////////////////
    ImColor GetColor(void) const;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief
    ///
    /// \return
    ///
    ///////////////////////////////////////////////////////////////////////////
    Type GetType(void) const;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief
    ///
    /// \return
    ///
    ///////////////////////////////////////////////////////////////////////////
    Kind GetKind(void) const;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief
    ///
    /// \return
    ///
    ///////////////////////////////////////////////////////////////////////////
    ID GetID(void) const;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief
    ///
    /// \return
    ///
    ///////////////////////////////////////////////////////////////////////////
    FString GetName(void) const;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief
    ///
    /// \return
    ///
    ///////////////////////////////////////////////////////////////////////////
    const TVector<TWeakPtr<ULink>>& GetLinks(void) const;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief
    ///
    /// \param owner
    ///
    ///////////////////////////////////////////////////////////////////////////
    void SetOwner(TWeakPtr<UNode> owner);

    ///////////////////////////////////////////////////////////////////////////
    /// \brief
    ///
    /// \return
    ///
    ///////////////////////////////////////////////////////////////////////////
    TSharedPtr<UNode> GetOwner(void) const;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief
    ///
    /// \param link
    ///
    ///////////////////////////////////////////////////////////////////////////
    void AddLink(TWeakPtr<ULink> link);

    ///////////////////////////////////////////////////////////////////////////
    /// \brief
    ///
    /// \param Link
    ///
    ///////////////////////////////////////////////////////////////////////////
    void RemoveLink(TWeakPtr<ULink> link);

    ///////////////////////////////////////////////////////////////////////////
    /// \brief
    ///
    ///////////////////////////////////////////////////////////////////////////
    void Render(void);
};

} // !namespace UEB
