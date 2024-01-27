#include "ScopeBoard.h"

ScoreBoard::ScoreBoard() : currentScore_( 0 )
{
    font_ = getDefaultFont();

    scoreText_.setFont( font_ );
    auto& fontSize = getConfig<int, "game.view.font_size_px">();
    scoreText_.setCharacterSize( fontSize );
    auto& fontColor = getConfig<sf::Color, "game.view.font_color">();
    scoreText_.setFillColor( fontColor );
    scoreText_.setPosition( 10, 10 );
    fmtScoreText();
}

void ScoreBoard::updateScore( int score )
{
    currentScore_ += score;
    fmtScoreText();
}

void ScoreBoard::reset()
{
    currentScore_ = 0;
    fmtScoreText();
}

void ScoreBoard::draw( sf::RenderWindow& window ) const
{
    window.draw( scoreText_ );
}

void ScoreBoard::fmtScoreText()
{
    scoreText_.setString( MY_FMT( "Score: {}", currentScore_ ) );
}
