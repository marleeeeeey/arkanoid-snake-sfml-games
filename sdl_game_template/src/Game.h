#pragma once

class Game
{
public:
    explicit Game();
    void setup( int windowWidth, int windowsHeight );
    void update( float deltaTime );
    void render( SDL_Renderer* window ) const;
    [[nodiscard]] bool isGameOver() const;
    void handleInput( SDL_Event event );
};
