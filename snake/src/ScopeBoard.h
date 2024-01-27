#pragma once

class ScoreBoard
{
public:
    ScoreBoard();
    void updateScore( int score );
    void reset();
    void draw( sf::RenderWindow& window ) const;
private:
    void fmtScoreText();

    int currentScore_;
    sf::Text scoreText_;
    sf::Font font_;
};
