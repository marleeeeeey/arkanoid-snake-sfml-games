int main( int argc, char** argv )
{
    std::filesystem::path currentDir = std::filesystem::current_path();
    std::string execFileName = getExecutableName( argv[0] );
    MY_LOG_FMT( info, "Starting game `{}` from {}", execFileName, currentDir.string() );

    // 1. Configurate window
    const auto& windowWidth = getConfig<float, "window.width", 600>();
    const auto& windowHeight = getConfig<float, "window.height", 800>();
    const auto& windowFrameRate = getConfig<int, "window.frameRate", 120>();
    sf::Vector2f windowSize = { windowWidth, windowHeight };
    auto videoMode = sf::VideoMode( static_cast<unsigned>( windowSize.x ), static_cast<unsigned>( windowSize.y ) );
    sf::RenderWindow window(
        videoMode, MY_FMT( "{} ({}x{}x{})", execFileName, windowWidth, windowHeight, windowFrameRate ) );
    window.setFramerateLimit( windowFrameRate );

    std::ignore = ImGui::SFML::Init( window );
    sf::Clock deltaClock;
    auto lastTime = deltaClock.getElapsedTime();

    while ( window.isOpen() )
    {
        std::optional<sf::Event> optEvent;
        sf::Event curEvent{};

        while ( window.pollEvent( curEvent ) )
        {
            ImGui::SFML::ProcessEvent( curEvent );
            if ( curEvent.type == sf::Event::Closed || isKeyPressed( curEvent, sf::Keyboard::Escape ) )
            {
                window.close();
            }
            optEvent = curEvent;
        }

        auto currentTime = deltaClock.getElapsedTime();
        auto deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        ImGui::SFML::Update( window, deltaTime );

        window.clear();

        ImGui::SFML::Render( window );
        window.display(); // Frame rate is limited by windowFrameRate
    }

    ImGui::SFML::Shutdown();
    MY_LOG_FMT( info, "`{}` game finished", execFileName );
    return 0;
}
