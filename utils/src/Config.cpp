#include <utils/Config.h>

std::shared_ptr<JsonLoader>& Config::getInstance()
{
    static std::shared_ptr<JsonLoader> jsonLoader;

    if ( !jsonLoader )
    {
        jsonLoader = std::make_shared<JsonLoader>();
        auto configPath = getFullPath( "config\\config.json" );
        jsonLoader->loadFromFile( configPath.string() );
        MY_LOG_FMT( info, "Config file loaded: {}", configPath.string() );
    }

    return jsonLoader;
}
