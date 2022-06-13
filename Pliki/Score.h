#pragma once

#include <SFML/Graphics.hpp>

#include "DEFINITIONS.hpp"
#include "Game.hpp"

namespace Tomo
{
	class Score
	{
	public:
		Score(GameDataRef data);
		~Score();

		void Draw();
		void UpdateScore(int score);

		void SetColor();
		void SetPos();
	private:
		GameDataRef _data;

		sf::Text WynikText;

	};
}
