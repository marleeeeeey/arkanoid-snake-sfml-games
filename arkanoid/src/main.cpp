#include "ObjectFactory.h"
#include "World.h"
#include "LevelGenerator.h"

/*
 * TODO: Create global class "NotificationManager" which will be responsible for showing notifications.
 *  - It should be able to show notifications in the top of the screen.
 *  - It should keep always visible variables in the map.
 *    - They should be placed in game header.
 *  - Temporary notification should be shown for 3 seconds in the center of the screen.
 * TODO: Create integration test to check if bonus objects are created correctly in runtime.
 * TODO: If ball do not touch paddle or bricks for 5 seconds, then M-bonus should be applied.
 */

int main()
{
    std::filesystem::path currentDir = std::filesystem::current_path();
    MY_LOG_FMT( info, "Starting Arkanoid game from {}", currentDir.string() );

    const auto& windowWidth = getConfig<float, "window.width", 600>();
    const auto& windowHeight = getConfig<float, "window.height", 800>();
    const auto& windowFrameRate = getConfig<int, "window.frameRate", 60>();

    sf::Vector2f windowSize = { windowWidth, windowHeight };
    auto objectFactory = std::make_shared<ObjectFactory>();
    auto levelGenerator = std::make_shared<LevelGenerator>( objectFactory, windowSize );
    auto world = std::make_shared<World>( objectFactory, levelGenerator, windowSize );
    auto videoMode = sf::VideoMode( static_cast<unsigned>( windowSize.x ), static_cast<unsigned>( windowSize.y ) );
    sf::RenderWindow window( videoMode, "Arkanoid" );
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
        auto timeDiff = currentTime - lastTime;
        lastTime = currentTime;

        //// ImGui window
        // ImGui::Begin( "Debug Window" );
        // ImGui::Button( "Click me 2" );
        // ImGui::End();

        // Game logic
        ImGui::SFML::Update( window, timeDiff );
        world->updateState( optEvent, timeDiff );

        // Game rendering
        window.clear();
        world->draw( window );
        ImGui::SFML::Render( window );
        window.display();
    }

    ImGui::SFML::Shutdown();
    MY_LOG( info, "Arkanoid game finished" );
    return 0;
}
