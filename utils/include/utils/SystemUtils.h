#pragma once

bool isKeyPressed( sf::Event event, sf::Keyboard::Key key );

sf::Font getDefaultFont();

std::filesystem::path getFullPath( const std::string& relativePath );

std::string getExecutableName( const char* path );
