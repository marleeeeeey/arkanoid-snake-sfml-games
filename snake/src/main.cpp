#include "Game.h"

int main( int argc, char** argv )
{
    std::filesystem::path currentDir = std::filesystem::current_path();
    std::string execFileName = getExecutableName( argv[0] );
    MY_LOG_FMT( info, "Starting game `{}` from {}", execFileName, currentDir.string() );

    // 1. Configurate window
    const auto& windowWidth = getConfig<unsigned, "window.width", 600>();
    const auto& windowHeight = getConfig<unsigned, "window.height", 800>();
    const auto& windowFrameRate = getConfig<unsigned, "window.frameRate", 120>();
    sf::Vector2u windowSize = { windowWidth, windowHeight };
    auto videoMode = sf::VideoMode( windowSize.x, windowSize.y );
    sf::RenderWindow window(
        videoMode, MY_FMT( "{} ({}x{}x{})", execFileName, windowWidth, windowHeight, windowFrameRate ) );
    window.setFramerateLimit( windowFrameRate );
    std::ignore = ImGui::SFML::Init( window );

    // 2. Create clock
    sf::Clock clock;
    auto lastTime = clock.getElapsedTime();

    // 3. Create game base classes
    Game game;
    bool isGameRunning = true;
    game.setup( windowSize );

    while ( window.isOpen() && isGameRunning )
    {
        // 4. Handle events
        sf::Event event{};
        while ( window.pollEvent( event ) )
        {
            ImGui::SFML::ProcessEvent( event );
            if ( event.type == sf::Event::Closed )
                window.close();

            game.handleInput( event );
        }

        // 5. Calculate delta time
        auto currentTime = clock.getElapsedTime();
        auto deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        // 6. Update game
        game.update( deltaTime );
        if ( game.isGameOver() )
            isGameRunning = false;

        // 7. Render game
        ImGui::SFML::Update( window, deltaTime );
        window.clear();
        game.render( window );
        ImGui::SFML::Render( window );
        window.display(); // Frame rate is limited by windowFrameRate
    }

    // 8. Shutdown
    ImGui::SFML::Shutdown();
    MY_LOG_FMT( info, "`{}` game finished", execFileName );
    return 0;
}
