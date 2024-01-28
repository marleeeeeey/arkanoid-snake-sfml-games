#include <utils/SystemUtils.h>
#include <utils/Logger.h>

bool isKeyPressed( sf::Event event, sf::Keyboard::Key key )
{
    return event.type == sf::Event::EventType::KeyPressed && event.key.code == key;
}

sf::Font loadFontFromFile( const std::string& optFontPath = {} )
{
    // clang-format off
    std::vector<std::string> fontPaths = {
        // Windows standard fonts
        R"(C:\Windows\Fonts\calibri.ttf)",
        R"(C:\Windows\Fonts\arial.ttf)",
        R"(C:\Windows\Fonts\times.ttf)",
        R"(C:\Windows\Fonts\tahoma.ttf)",

        // Linux standard fonts (DejaVu, Ubuntu, FreeSans)
        "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf",
        "/usr/share/fonts/truetype/ubuntu/Ubuntu-R.ttf",
        "/usr/share/fonts/truetype/freefont/FreeSans.ttf",

        // macOS standard fonts
        "/System/Library/Fonts/Supplemental/Arial.ttf",
        "/System/Library/Fonts/Supplemental/Times New Roman.ttf",
        "/System/Library/Fonts/Supplemental/Verdana.ttf",

        // Additional common paths
        "/Library/Fonts/Arial.ttf",
        "/Library/Fonts/Tahoma.ttf",
        "/Library/Fonts/Verdana.ttf"
    };
    // clang-format on

    if ( !optFontPath.empty() )
        fontPaths.insert( fontPaths.begin(), optFontPath );

    sf::Font font;
    for ( const auto& path : fontPaths )
    {
        if ( font.loadFromFile( path ) )
        {
            MY_LOG_FMT( info, "Loaded font: `{}`.", path );
            return font;
        }
        MY_LOG_FMT( info, "Unable to load font `{}`.", path );
    }

    throw std::runtime_error( "Unable to load any system font." );
}

const sf::Font& getDefaultFont( const std::string& optFontPath )
{
    static sf::Font font = loadFontFromFile( optFontPath );
    return font;
}

std::filesystem::path getFullPath( const std::string& relativePath )
{
    std::filesystem::path fullPath = std::filesystem::absolute( relativePath );
    if ( !std::filesystem::exists( fullPath ) )
        throw std::runtime_error( MY_FMT( "File not found: `{}`.", fullPath.string() ) );

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
