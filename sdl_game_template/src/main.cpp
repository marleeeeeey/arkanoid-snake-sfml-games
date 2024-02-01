// #include "Game.h"
//
// int main( int argc, char** argv )
//{
//     std::filesystem::path currentDir = std::filesystem::current_path();
//     std::string execFileName = getExecutableName( argv[0] );
//     MY_LOG_FMT( info, "Starting game `{}` from {}", execFileName, currentDir.string() );
//
//     // 1. Configurate window
//     const auto& windowWidth = getConfig<unsigned, "window.width", 600>();
//     const auto& windowHeight = getConfig<unsigned, "window.height", 800>();
//     const auto& windowFrameRate = getConfig<unsigned, "window.frameRate", 120>();
//     sf::Vector2u windowSize = { windowWidth, windowHeight };
//     std::string windowTitle = MY_FMT( "{} ({}x{}x{})", execFileName, windowWidth, windowHeight, windowFrameRate );
//     auto videoMode = sf::VideoMode( windowSize.x, windowSize.y );
//     sf::RenderWindow window( videoMode, windowTitle );
//     window.setFramerateLimit( windowFrameRate );
//     std::ignore = ImGui::SFML::Init( window );
//
//     // 2. Create clock
//     sf::Clock clock;
//     auto lastTime = clock.getElapsedTime();
//
//     // 3. Create game base classes
//     Game game;
//     bool isGameRunning = true;
//     game.setup( windowSize );
//
//     while ( window.isOpen() && isGameRunning )
//     {
//         // 4. Handle events
//         sf::Event event{};
//         while ( window.pollEvent( event ) )
//         {
//             ImGui::SFML::ProcessEvent( event );
//             if ( event.type == sf::Event::Closed )
//                 window.close();
//
//             game.handleInput( event );
//         }
//
//         // 5. Calculate delta time
//         auto currentTime = clock.getElapsedTime();
//         auto deltaTime = currentTime - lastTime;
//         lastTime = currentTime;
//
//         // 6. Update game
//         game.update( deltaTime );
//         if ( game.isGameOver() )
//             isGameRunning = false;
//
//         // 7. Render game
//         ImGui::SFML::Update( window, deltaTime );
//         window.clear();
//         game.render( window );
//         ImGui::SFML::Render( window );
//         window.display(); // Frame rate is limited by windowFrameRate
//     }
//
//     // 8. Shutdown
//     ImGui::SFML::Shutdown();
//     MY_LOG_FMT( info, "`{}` game finished", execFileName );
//     return 0;
// }

#include "SDL.h"
#include "Game.h"

int main( int argc, char** argv )
{
    std::filesystem::path currentDir = std::filesystem::current_path();
    std::string execFileName = getExecutableName( argv[0] );
    MY_LOG_FMT( info, "Starting game `{}` from {}", execFileName, currentDir.string() );

    // 1. Initialize SDL
    if ( SDL_Init( SDL_INIT_VIDEO ) != 0 )
    {
        MY_LOG_FMT( error, "Unable to initialize SDL: {}", SDL_GetError() );
        return 1;
    }

    // 2. Create a window
    const int windowWidth = getConfig<int, "window.width", 600>();
    const int windowHeight = getConfig<int, "window.height", 800>();
    const int windowFrameRate = getConfig<int, "window.frameRate", 120>();
    std::string windowTitle = MY_FMT( "{} ({}x{}x{})", execFileName, windowWidth, windowHeight, windowFrameRate );

    SDL_Window* window = SDL_CreateWindow(
        windowTitle.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight,
        SDL_WINDOW_SHOWN );

    if ( window == nullptr )
    {
        MY_LOG_FMT( error, "Unable to create window: {}", SDL_GetError() );
        SDL_Quit();
        return 1;
    }

    // 3. Create renderer
    SDL_Renderer* renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
    if ( renderer == nullptr )
    {
        MY_LOG_FMT( error, "Unable to create renderer: {}", SDL_GetError() );
        SDL_DestroyWindow( window );
        SDL_Quit();
        return 1;
    }

    // 4. Initialize game
    Game game;
    game.setup( windowWidth, windowHeight );

    // 5. Main loop
    bool isGameRunning = true;
    Uint32 lastTick = SDL_GetTicks();
    while ( isGameRunning )
    {
        // Handle events
        SDL_Event event;
        while ( SDL_PollEvent( &event ) )
        {
            if ( event.type == SDL_QUIT )
                isGameRunning = false;

            game.handleInput( event );
        }

        // Calculate delta time
        Uint32 currentTick = SDL_GetTicks();
        float deltaTime = ( currentTick - lastTick ) / 1000.0f;
        lastTick = currentTick;

        //// Limit frame rate to windowFrameRate
        // Uint32 frameStart = SDL_GetTicks();
        // int frameTime = SDL_GetTicks() - frameStart;
        // if ( frameTime < 1000 / windowFrameRate )
        //{
        //     SDL_Delay( 1000 / windowFrameRate - frameTime );
        // }

        // Update game
        game.update( deltaTime );
        if ( game.isGameOver() )
            isGameRunning = false;

        // Render game
        SDL_SetRenderDrawColor( renderer, 0, 0, 0, SDL_ALPHA_OPAQUE );
        SDL_RenderClear( renderer );
        game.render( renderer );
        SDL_RenderPresent( renderer ); // Frame rate is limited by windowFrameRate
    }

    // 6. Shutdown
    SDL_DestroyRenderer( renderer );
    SDL_DestroyWindow( window );
    SDL_Quit();

    return 0;
}
