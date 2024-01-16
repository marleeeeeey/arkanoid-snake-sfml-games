#include <utils/SystemUtils.h>

bool isKeyPressed( sf::Event event, sf::Keyboard::Key key )
{
    return event.type == sf::Event::EventType::KeyPressed && event.key.code == key;
}

sf::Font getDefaultFont()
{
    sf::Font font;
    std::string fontFileName = R"(C:\Windows\Fonts\calibri.ttf)";
    if ( !font.loadFromFile( fontFileName ) )
    {
        throw std::runtime_error( MY_FMT( "Can't open font file '{}'", fontFileName ) );
    }

    return font;
}
