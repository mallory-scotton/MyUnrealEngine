///////////////////////////////////////////////////////////////////////////////
// Dependencies
///////////////////////////////////////////////////////////////////////////////
#include "Utils/Strings.hpp"
#include <cctype>

///////////////////////////////////////////////////////////////////////////////
// Namespace TKD::String
///////////////////////////////////////////////////////////////////////////////
namespace TKD::String
{

///////////////////////////////////////////////////////////////////////////////
FString Trim(const FString& str)
{
    FString result = str;

    result.erase(
        result.begin(),
        std::find_if_not(result.begin(), result.end(), ::isspace)
    );

    result.erase(
        std::find_if_not(result.rbegin(), result.rend(), ::isspace).base(),
        result.end()
    );

    return (result);
}

///////////////////////////////////////////////////////////////////////////////
FString ToLower(const FString& str)
{
    FString result = str;

    std::transform(result.begin(), result.end(), result.begin(), ::tolower);

    return (result);
}

///////////////////////////////////////////////////////////////////////////////
FString ToUpper(const FString& str)
{
    FString result = str;

    std::transform(result.begin(), result.end(), result.begin(), ::toupper);

    return (result);
}

///////////////////////////////////////////////////////////////////////////////
TVector<FString> Tokenize(const FString& str)
{
    TVector<FString> tokens;
    FStringStream iss(str);
    FString token;

    while (iss >> token) {
        tokens.push_back(token);
    }

    return (tokens);
}

} // !namespace TKD::String
