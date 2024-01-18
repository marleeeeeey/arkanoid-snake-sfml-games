#include <utils/Config.h>

std::shared_ptr<JsonLoader>& Config::getInstance( std::string_view jsonStrExample )
{
    static std::shared_ptr<JsonLoader> jsonLoader;

    if ( !jsonLoader )
    {
        if (!jsonStrExample.empty())
        {
            jsonLoader = std::make_shared<JsonLoader>(  );
            jsonLoader->loadFromString( jsonStrExample.data() );
            MY_LOG_FMT( info, "Config file loaded from string: `{}`", jsonStrExample.data() );
        }
        else
        {
            jsonLoader = std::make_shared<JsonLoader>();
            auto configPath = getFullPath( "config\\config.json" );
            jsonLoader->loadFromFile( configPath.string() );
            MY_LOG_FMT( info, "Config file loaded: {}", configPath.string() );
        }
    }

    return jsonLoader;
}
