#pragma once
#include <utils/JsonLoader.h>
#include <utils/Logger.h>
#include <utils/JsonFormatter.h>

// TODO: check incorrect usage of config parameters on application start
class Config
{
public:
    enum class Mode
    {
        NoReload,
        ForceReload
    };

    // jsonSourceAsString - optional json string to load instead of file. Mostly for tests.
    static std::shared_ptr<JsonLoader>& getInstance( Mode mode, std::string_view jsonSourceAsString = {} );
};

// Literal class type that wraps a constant expression string.
// Uses implicit conversion to allow templates to *seemingly* accept constant strings.
template <size_t N>
struct StringLiteral
{
    constexpr StringLiteral( const char ( &str )[N] ) { std::copy_n( str, N, value ); }
    char value[N];
};

template <StringLiteral Lit>
std::string_view toStringView()
{
    return { Lit.value };
}

// Read any built-it type from Json. Return optional. Key = "a.b.c"
template <typename T, StringLiteral Key>
std::optional<T>& getConfigOpt()
{
    static std::optional<T> result =
        getElementByPath( Config::getInstance( Config::Mode::NoReload )->root(), toStringView<Key>() );
    return result;
}

// Read any built-it type from Json. Throw exception if key not found. Key = "a.b.c"
template <typename T, StringLiteral Key>
const T& getConfig()
{
    static std::optional<T>& result = getConfigOpt<T, Key>();
    return result.value();
}

// Read json serializable type from Json. Throw exception if key not found. Key = "a.b.c"
template <typename T, StringLiteral Key>
    requires requires( T key ) { adl_serializer::from_json( std::declval<json&>(), key ); }
const T& getConfig()
{
    static std::optional<T> valueOpt;

    if ( !valueOpt.has_value() )
    {
        json elementJson = getConfigOpt<json, Key>().value();
        T result;
        adl_serializer::from_json( elementJson, result );
        valueOpt = result;
    }

    return valueOpt.value();
}

// Read any type from Json with default value. Key = "a.b.c".
template <typename T, StringLiteral Key, auto DefaultValue>
const T& getConfig()
{
    static std::optional<T> valueOpt = getConfigOpt<T, Key>();

    if ( !valueOpt.has_value() )
        valueOpt = static_cast<T>( DefaultValue );

    return valueOpt.value();
}
