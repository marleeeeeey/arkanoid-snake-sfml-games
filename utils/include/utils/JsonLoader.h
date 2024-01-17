#pragma once
#include <nlohmann/json.hpp>
using Json = nlohmann::json;

class JsonLoader
{
    Json root_;
    std::optional<std::string> lastFilename_;
public:
    JsonLoader();
    JsonLoader( const JsonLoader& ) = delete;
    JsonLoader& operator=( const JsonLoader& ) = delete;

    Json& root();
    const Json& root() const;

    bool loadFromString( const std::string& jsonString );
    bool loadFromFile( const std::string& filename );

    bool saveToSameFile() const;
    bool saveToFile( const std::string& filename ) const;
};

// Function to access data at a specified path within JSON
std::optional<Json> getElementByPath( const Json& jsonData, const std::string& path );
