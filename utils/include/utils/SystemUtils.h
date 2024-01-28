#pragma once

bool isKeyPressed( sf::Event event, sf::Keyboard::Key key );

// Loads a font from the system. Try to find a font in more common paths in Windows, Linux and macOS.
// Once loaded, the font is cached and reused. If optFontPath is provided, it will be used as the first font to try to load.
const sf::Font& getDefaultFont( const std::string& optFontPath = {} );

std::filesystem::path getFullPath( const std::string& relativePath );

std::string getExecutableName( const char* path );
