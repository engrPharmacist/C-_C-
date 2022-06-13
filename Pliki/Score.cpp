#include "Score.h"

#include <string>

namespace Tomo
{
	Score::Score(GameDataRef data) : _data(data)
	{
		WynikText.setFont(this->_data->assets.GetFont("Main Menu Font Text"));
		WynikText.setCharacterSize(50);
		WynikText.setFillColor(sf::Color::Green);
		WynikText.setOrigin(sf::Vector2f(10,0));
		WynikText.setPosition(300,-15);
		WynikText.setOutlineThickness(2);
		WynikText.setOutlineColor(sf::Color::White);
	}

	Score::~Score()
	{
	}

	void Score::Draw()
	{
		_data->window.draw(WynikText);
	}

	void Score::UpdateScore(int score)
	{
		WynikText.setString(std::to_string(score));
	}

	
	void Score::SetPos()
	{
			WynikText.setPosition(700, -15);
			WynikText.setFillColor(sf::Color::Red);
	}
	void Score::SetColor()
	{
		WynikText.setFillColor(sf::Color::Red);
	}
	
}