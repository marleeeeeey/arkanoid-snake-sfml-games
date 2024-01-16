#pragma once
#include "JsonLoader.h"

class Config
{
public:
    static std::shared_ptr<JsonLoader>& getInstance()
    {
        static std::shared_ptr<JsonLoader> jsonLoader;

        if ( !jsonLoader )
        {
            jsonLoader = std::make_shared<JsonLoader>();
            jsonLoader->loadFromFile( "config\\config.json" );
        }

        return jsonLoader;
    }

    // key = "a.b.c"
    template <typename T>
    static T getConfig( const std::string& key )
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
                return T();
            }
        }

        // Parse the JSON value
        Json::Value resultJson;
        Json::Reader reader;
        if ( !reader.parse( currentNode.toStyledString(), resultJson, false ) )
        {
            MY_LOG_FMT( warn, "Error parsing value for key: {}", key );
            return T();
        }

        // Convert the JSON value to the desired type T
        T result;
        std::istringstream resultSs( resultJson.asString() );
        if ( !( resultSs >> result ) )
        {
            MY_LOG_FMT( warn, "Error converting value for key: {}", key );
            return T();
        }

        return result;
    }
};

template <typename T>
T getConfig( const std::string& key )
{
    return Config::getConfig<T>( key );
}