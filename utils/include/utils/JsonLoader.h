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

    bool loadFromString( std::string_view jsonString );
    bool loadFromFile( std::string_view filename );

    bool saveToSameFile() const;
    bool saveToFile( const std::string& filename ) const;
};

// Function to access data at a specified path within JSON
std::optional<Json> getElementByPath( const Json& jsonData, std::string_view path );
