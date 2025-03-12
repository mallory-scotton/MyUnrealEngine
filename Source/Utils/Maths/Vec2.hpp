///////////////////////////////////////////////////////////////////////////////
// Header guard
///////////////////////////////////////////////////////////////////////////////
#pragma once

///////////////////////////////////////////////////////////////////////////////
// Dependencies
///////////////////////////////////////////////////////////////////////////////
#include "Utils/Types.hpp"

///////////////////////////////////////////////////////////////////////////////
// Namespace UEB
///////////////////////////////////////////////////////////////////////////////
namespace UEB
{

///////////////////////////////////////////////////////////////////////////////
/// \brief
///
///////////////////////////////////////////////////////////////////////////////
class FVec2
{
public:
    ///////////////////////////////////////////////////////////////////////////
    //
    ///////////////////////////////////////////////////////////////////////////
    union
    {
        struct
        {
            float x;    //<!
            float y;    //<!
        };
        float xy[2];    //<!
    };

public:
    ///////////////////////////////////////////////////////////////////////////
    /// \brief
    ///
    ///////////////////////////////////////////////////////////////////////////
    FVec2(void);

    ///////////////////////////////////////////////////////////////////////////
    /// \brief
    ///
    /// \param all
    ///
    ///////////////////////////////////////////////////////////////////////////
    FVec2(float all);

    ///////////////////////////////////////////////////////////////////////////
    /// \brief
    ///
    /// \param x
    /// \param y
    ///
    ///////////////////////////////////////////////////////////////////////////
    FVec2(float x, float y);
};

} // !namespace UEB
