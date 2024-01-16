#pragma once
#include "Logger.h"
#include <json/json.h>
#include <fstream>

class JsonLoader
{
    Json::Value root_;
    std::optional<std::string> lastFilename_;
public:
    JsonLoader() = default;
    JsonLoader( const JsonLoader& ) = delete;
    JsonLoader& operator=( const JsonLoader& ) = delete;

    // ********************************* ACCESS *********************************

    Json::Value& root() { return root_; }

    const Json::Value& root() const { return root_; }

    // ********************************** LOAD **********************************

    bool loadFromString( const std::string& jsonString )
    {
        try
        {
            Json::Reader reader;
            return reader.parse( jsonString, root_ );
        }
        catch ( const std::exception& e )
        {
            MY_LOG_FMT( warn, "Error parsing JSON from string: {}", e.what() );
            return false;
        }
    }

    bool loadFromFile( const std::string& filename )
    {
        try
        {
            std::ifstream inFile( filename );
            if ( !inFile.is_open() )
            {
                MY_LOG_FMT( warn, "Error opening file for reading: {}", filename );
                return false;
            }

            Json::Reader reader;
            bool result = reader.parse( inFile, root_ );
            if ( result )
                lastFilename_ = filename;
            else
                MY_LOG_FMT( warn, "Error parsing JSON from file: {}", filename );
        }
        catch ( const std::exception& e )
        {
            MY_LOG_FMT( warn, "Error loading JSON from file. File: {}. Error: {}", filename, e.what() );
            return false;
        }

        return true;
    }

    // ********************************** SAVE **********************************

    bool saveToSameFile() const
    {
        if ( !lastFilename_.has_value() )
        {
            MY_LOG( warn, "No filename specified for saving JSON" );
            return false;
        }

        return saveToFile( lastFilename_.value() );
    }

    bool saveToFile( const std::string& filename ) const
    {
        try
        {
            std::ofstream outFile( filename, std::ios::trunc );
            if ( !outFile.is_open() )
            {
                MY_LOG_FMT( warn, "Error opening file for writing: {}", filename );
                return false;
            }

            Json::StyledStreamWriter writer;
            writer.write( outFile, root_ );
            return true;
        }
        catch ( const std::exception& e )
        {
            MY_LOG_FMT( warn, "Error saving JSON to file. File: {}. Error: {}", filename, e.what() );
            return false;
        }
    }
};
