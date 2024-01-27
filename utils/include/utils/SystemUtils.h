#pragma once

bool isKeyPressed( sf::Event event, sf::Keyboard::Key key );

const sf::Font& getDefaultFont();

std::filesystem::path getFullPath( const std::string& relativePath );

std::string getExecutableName( const char* path );
