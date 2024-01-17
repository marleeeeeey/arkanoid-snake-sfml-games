#pragma once
#include <utils/JsonLoader.h>
#include <utils/Logger.h>
#include <spdlog/spdlog.h>

class Config
{
public:
    static std::shared_ptr<JsonLoader>& getInstance();
};

// key = "a.b.c"
template <typename T>
T getConfig( const std::string& key )
{
    std::optional<T> element = getElementByPath( Config::getInstance()->root(), key );

    if ( !element.has_value() )
        throw std::runtime_error( MY_FMT( "Can't get config value for key: {}", key ) );

    return element.value();
}

// key = "a.b.c" with default value
template <typename T>
T getConfig( const std::string& key, const T& defaultValue )
{
    std::optional<T> element = getElementByPath( Config::getInstance()->root(), key );

    if ( !element.has_value() )
        return defaultValue;

    return element.value();
}
