///////////////////////////////////////////////////////////////////////////////
// Dependencies
///////////////////////////////////////////////////////////////////////////////
#include "Utils/Archive/LoadArchive.hpp"
#include "Utils/Filesystem/Filesystem.hpp"
#include "Utils/Maths/Maths.hpp"
#include <string.h>

///////////////////////////////////////////////////////////////////////////////
// Namespace UEB
///////////////////////////////////////////////////////////////////////////////
namespace UEB
{

///////////////////////////////////////////////////////////////////////////////
ULoadArchive::ULoadArchive(const FPath& filepath)
    : UArchive()
    , mData(Fs::ReadBinaryFile(filepath))
    , mPosition(0)
{
    mIsLoading = true;
    mAllowSeek = true;
}

///////////////////////////////////////////////////////////////////////////////
ULoadArchive::ULoadArchive(const TVector<FUint8>& data)
    : UArchive()
    , mData(data)
    , mPosition(0)
{
    mIsLoading = true;
    mAllowSeek = true;
}

///////////////////////////////////////////////////////////////////////////////
void ULoadArchive::Seek(FUint64 position)
{
    mPosition = Math::Min(position, mData.size());
}

///////////////////////////////////////////////////////////////////////////////
FUint64 ULoadArchive::Tell(void) const
{
    return (mPosition);
}

///////////////////////////////////////////////////////////////////////////////
FUint64 ULoadArchive::TotalSize(void) const
{
    return (mData.size());
}

///////////////////////////////////////////////////////////////////////////////
void ULoadArchive::Serialize(void* data, FUint64 length)
{
    if (length == 0 || mPosition >= mData.size()) {
        return;
    }
    FUint64 bytesToRead = Math::Min(length, mData.size() - mPosition);

    ::memcpy(data, &mData[mPosition], bytesToRead);
    mPosition += bytesToRead;

    if (bytesToRead < length) {
        ::memset((FUint8*)data + bytesToRead, 0, length - bytesToRead);
    }
}

} // !namespace UEB
