#include <SFML/Graphics.hpp>
#include <glm/glm.hpp>
#include <iostream>

int main()
{
    // Create a window
    sf::RenderWindow window( sf::VideoMode( 800, 600 ), "Bouncing Ball" );
    window.setFramerateLimit( 60 );

    // Create a circle (representing the ball)
    sf::CircleShape ball( 20.0f );
    ball.setFillColor( sf::Color::Red );

    // Initialize ball position and velocity using glm
    glm::vec2 position( 400.0f, 300.0f );
    glm::vec2 velocity( 5.0f, 5.0f );

    while ( window.isOpen() )
    {
        sf::Event event;
        while ( window.pollEvent( event ) )
        {
            if ( event.type == sf::Event::Closed )
                window.close();
        }

        // Update ball position
        position += velocity;

        // Check for collisions with window boundaries
        if ( position.x + ball.getRadius() > 800.0f || position.x - ball.getRadius() < 0.0f )
        {
            velocity.x = -velocity.x; // Reverse horizontal velocity
        }
        if ( position.y + ball.getRadius() > 600.0f || position.y - ball.getRadius() < 0.0f )
        {
            velocity.y = -velocity.y; // Reverse vertical velocity
        }

        // Set the new position of the ball
        ball.setPosition( position.x - ball.getRadius(), position.y - ball.getRadius() );

        window.clear();
        window.draw( ball );
        window.display();
    }

    return 0;
}
