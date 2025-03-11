///////////////////////////////////////////////////////////////////////////////
// Header guard
///////////////////////////////////////////////////////////////////////////////
#pragma once

///////////////////////////////////////////////////////////////////////////////
// Dependencies
///////////////////////////////////////////////////////////////////////////////
#include "Utils/Archive.hpp"

///////////////////////////////////////////////////////////////////////////////
// Namespace UEB
///////////////////////////////////////////////////////////////////////////////
namespace UEB
{

///////////////////////////////////////////////////////////////////////////////
/// \brief
///
///////////////////////////////////////////////////////////////////////////////
class ULoadArchive : public UArchive
{
private:
    ///////////////////////////////////////////////////////////////////////////
    //
    ///////////////////////////////////////////////////////////////////////////
    TVector<FUint8> mData;      //<!
    FUint64 mPosition;          //<!

public:
    ///////////////////////////////////////////////////////////////////////////
    /// \brief
    ///
    /// \param filepath
    ///
    ///////////////////////////////////////////////////////////////////////////
    ULoadArchive(const FPath& filepath);

    ///////////////////////////////////////////////////////////////////////////
    /// \brief
    ///
    /// \param data
    ///
    ///////////////////////////////////////////////////////////////////////////
    ULoadArchive(const TVector<FUint8>& data);

public:
    ///////////////////////////////////////////////////////////////////////////
    /// \brief
    ///
    /// \param position
    ///
    ///////////////////////////////////////////////////////////////////////////
    virtual void Seek(FUint64 position) override;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief
    ///
    /// \return
    ///
    ///////////////////////////////////////////////////////////////////////////
    virtual FUint64 Tell(void) const override;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief
    ///
    /// \return
    ///
    ///////////////////////////////////////////////////////////////////////////
    virtual FUint64 TotalSize(void) const override;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief
    ///
    /// \param data
    /// \param length
    ///
    ///////////////////////////////////////////////////////////////////////////
    virtual void Serialize(void* data, FUint64 length) override;
};

} // !namespace UEB
