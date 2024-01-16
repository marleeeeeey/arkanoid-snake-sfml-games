#pragma once
#include <json/json.h>

class JsonLoader
{
    Json::Value root_;
    std::optional<std::string> lastFilename_;
public:
    JsonLoader();
    JsonLoader( const JsonLoader& ) = delete;
    JsonLoader& operator=( const JsonLoader& ) = delete;

    Json::Value& root();
    const Json::Value& root() const;

    bool loadFromString( const std::string& jsonString );
    bool loadFromFile( const std::string& filename );

    bool saveToSameFile() const;
    bool saveToFile( const std::string& filename ) const;
};
