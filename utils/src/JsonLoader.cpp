#include <utils/JsonLoader.h>
#include <utils/Logger.h>

JsonLoader::JsonLoader() = default;

Json& JsonLoader::root()
{
    return root_;
}

const Json& JsonLoader::root() const
{
    return root_;
}

bool JsonLoader::loadFromFile( const std::string& filename )
{
    try
    {
        std::ifstream inputFile( filename );
        if ( !inputFile.is_open() )
        {
            MY_LOG_FMT( warn, "Error opening file for reading: {}", filename );
            return false;
        }

        inputFile >> root_;
    }
    catch ( const std::exception& e )
    {
        MY_LOG_FMT( warn, "Error loading JSON from file. File: {}. Error: {}", filename, e.what() );
        return false;
    }

    return true;
}

bool JsonLoader::saveToSameFile() const
{
    if ( !lastFilename_.has_value() )
    {
        MY_LOG( warn, "No filename specified for saving JSON" );
        return false;
    }

    return saveToFile( lastFilename_.value() );
}

bool JsonLoader::saveToFile( const std::string& filename ) const
{
    try
    {
        std::ofstream output_file( filename );
        if ( !output_file.is_open() )
        {
            MY_LOG_FMT( warn, "Error opening file for writing: {}", filename );
            return false;
        }

        output_file << root_.dump( 2 );
        output_file.close();

        MY_LOG_FMT( info, "JSON data has been written to {}", filename );
        return true;
    }
    catch ( const std::exception& e )
    {
        MY_LOG_FMT( warn, "Error saving JSON to file. File: {}. Error: {}", filename, e.what() );
        return false;
    }
}

bool JsonLoader::loadFromString( const std::string& jsonString )
{
    try
    {
        root_ = Json::parse( jsonString );
        return true;
    }
    catch ( const std::exception& e )
    {
        MY_LOG_FMT( warn, "Error parsing JSON from string: {}", e.what() );
        return false;
    }
}

std::optional<Json> getElementByPath( const Json& jsonData, const std::string& path )
{
    Json currentNode = jsonData;
    std::istringstream ss( path );
    std::string segment;

    while ( std::getline( ss, segment, '.' ) )
    {
        if ( currentNode.is_object() && currentNode.find( segment ) != currentNode.end() )
        {
            currentNode = currentNode[segment];
        }
        else
        {
            return {};
        }
    }

    return currentNode;
}
