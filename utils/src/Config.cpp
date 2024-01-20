#include <utils/Config.h>

std::shared_ptr<JsonLoader>& Config::getInstance( Mode mode, std::string_view jsonSourceAsString )
{
    static std::shared_ptr<JsonLoader> jsonLoader;

    // Return already loaded config
    if ( jsonLoader && mode != Mode::ForceReload )
        return jsonLoader;

    if ( !jsonSourceAsString.empty() )
    {
        jsonLoader = std::make_shared<JsonLoader>();
        jsonLoader->loadFromString( jsonSourceAsString.data() );
        MY_LOG_FMT( info, "Config file loaded from string: `{}`", jsonSourceAsString );
    }
    else
    {
        jsonLoader = std::make_shared<JsonLoader>();
        auto configPath = getFullPath( "config\\config.json" );
        jsonLoader->loadFromFile( configPath.string() );
        MY_LOG_FMT( info, "Config file loaded: {}", configPath.string() );
    }

    return jsonLoader;
}
