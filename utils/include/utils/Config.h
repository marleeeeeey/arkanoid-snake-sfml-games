#pragma once
#include <utils/JsonLoader.h>
#include <utils/Logger.h>

// TODO: check incorrect usage of config parameters on application start
class Config
{
public:
    // jsonStrExample - optional json string to load instead of file. Mostly for tests.
    static std::shared_ptr<JsonLoader>& getInstance( std::string_view jsonStrExample = {} );
};

// Literal class type that wraps a constant expression string.
// Uses implicit conversion to allow templates to *seemingly* accept constant strings.
template <size_t N>
struct StringLiteral
{
    constexpr StringLiteral( const char ( &str )[N] ) { std::copy_n( str, N, value ); }
    char value[N];
};

template <StringLiteral lit>
std::string_view toStringView()
{
    constexpr auto contents = lit.value;
    return { contents };
}

// Key = "a.b.c"
template <typename T, StringLiteral key>
T& getConfig()
{
    static std::optional<T> valueOpt = getElementByPath( Config::getInstance()->root(), toStringView<key>() );
    return valueOpt.value();
}

// key = "a.b.c" with default value
template <typename To, StringLiteral key, auto defaultValue>
To& getConfig()
{
    static std::optional<To> valueOpt = getElementByPath( Config::getInstance()->root(), toStringView<key>() );

    if ( !valueOpt.has_value() )
        valueOpt = static_cast<To>( defaultValue );

    return valueOpt.value();
}
