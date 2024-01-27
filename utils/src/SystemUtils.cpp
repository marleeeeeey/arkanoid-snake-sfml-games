#include <utils/SystemUtils.h>

bool isKeyPressed( sf::Event event, sf::Keyboard::Key key )
{
    return event.type == sf::Event::EventType::KeyPressed && event.key.code == key;
}

sf::Font getDefaultFont()
{
    sf::Font font;
    std::string fontFileName = R"(C:\Windows\Fonts\calibri.ttf)";
    if ( !font.loadFromFile( fontFileName ) )
    {
        throw std::runtime_error( MY_FMT( "Can't open font file '{}'", fontFileName ) );
    }

    return font;
}

std::filesystem::path getFullPath( const std::string& relativePath )
{
    std::filesystem::path fullPath = std::filesystem::absolute( relativePath );
    if ( !std::filesystem::exists( fullPath ) )
    {
        throw std::runtime_error( MY_FMT( "Can't load file: {}", fullPath.string() ) );
    }
    return fullPath;
}

std::string getExecutableName( const char* path )
{
    std::string fullPath( path );

    std::size_t lastSlashPos = fullPath.find_last_of( "/\\" );
    if ( lastSlashPos != std::string::npos )
        return fullPath.substr( lastSlashPos + 1 );

    return fullPath;
}
