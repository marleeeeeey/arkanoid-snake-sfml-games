#include <SFML/Graphics.hpp>
#include <imgui.h>
#include <imgui-SFML.h>

int main()
{
    sf::RenderWindow window( sf::VideoMode( 800, 600 ), "Arkanoid with ImGui and SFML" );
    window.setFramerateLimit( 60 );
    std::ignore = ImGui::SFML::Init( window );

    sf::Clock deltaClock;
    while ( window.isOpen() )
    {
        sf::Event event{};
        while ( window.pollEvent( event ) )
        {
            ImGui::SFML::ProcessEvent( event );
            if ( event.type == sf::Event::Closed )
            {
                window.close();
            }
        }

        ImGui::SFML::Update( window, deltaClock.restart() );

        // ImGui window
        ImGui::Begin( "Debug Window" );
        ImGui::Button( "Click me" );
        ImGui::End();

        // Game rendering
        window.clear();
        ImGui::SFML::Render( window );
        window.display();
    }

    ImGui::SFML::Shutdown();
    return 0;
}
