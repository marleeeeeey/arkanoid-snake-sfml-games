#pragma once
#include "SystemUtils.h"
#include <utils/JsonLoader.h>
#include <utils/Logger.h>
#include <spdlog/spdlog.h>

class Config
{
public:
    static std::shared_ptr<JsonLoader>& getInstance()
    {
        static std::shared_ptr<JsonLoader> jsonLoader;

        if ( !jsonLoader )
        {
            jsonLoader = std::make_shared<JsonLoader>();
            auto configPath = getFullPath( "config\\config.json" );
            jsonLoader->loadFromFile( configPath.string() );
            MY_LOG_FMT( info, "Config file loaded: {}", configPath.string() );
        }

        return jsonLoader;
    }

    // key = "a.b.c"
    template <typename T>
    static bool getConfig( const std::string& key, T& retValue )
    {
        // Find the JSON value for the key
        Json::Value& root = getInstance()->root();
        Json::Value currentNode = root;
        std::istringstream ss( key );
        std::string segment;
        while ( std::getline( ss, segment, '.' ) )
        {
            if ( currentNode.isMember( segment ) )
            {
                currentNode = currentNode[segment];
            }
            else
            {
                MY_LOG_FMT( warn, "Config key not found: {}", key );
                return false;
            }
        }

        // Parse the JSON value
        Json::Value resultJson;
        Json::Reader reader;
        if ( !reader.parse( currentNode.toStyledString(), resultJson, false ) )
        {
            MY_LOG_FMT( warn, "Error parsing value for key: {}", key );
            return false;
        }

        // Convert the JSON value to the desired type T
        T result;
        std::istringstream resultSs( resultJson.asString() );
        if ( !( resultSs >> result ) )
        {
            MY_LOG_FMT( warn, "Error converting value for key: {}", key );
            return false;
        }

        retValue = result;
        return true;
    }
};

// key = "a.b.c"
template <typename T>
T getConfig( const std::string& key )
{
    T result;
    bool success = Config::getConfig<T>( key, result );

    if ( !success )
        throw std::runtime_error( MY_FMT( "Can't get config value for key: {}", key ) );

    return result;
}

// key = "a.b.c" with default value
template <typename T>
T getConfig( const std::string& key, const T& defaultValue )
{
    T result;
    bool success = Config::getConfig<T>( key, result );

    if ( !success )
    {
        MY_LOG_FMT( warn, "Can't get config value for key: {}. Using default value: {}", key, defaultValue );
        return defaultValue;
    }

    return result;
}
