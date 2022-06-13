#pragma once

#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"
#include "DEFINITIONS.hpp"

namespace Tomo
{
	class MainMenuState : public State
	{
	public:
		MainMenuState(GameDataRef data);

		void Init();

		void HandleInput();
		void Update(float dt);
		void Draw(float dt);

	private:
		GameDataRef _data;

		sf::Sprite tloS;
		sf::RectangleShape ramka;
		int selectedItemIndex;
		sf::Text Menu[MAX_NUMBER_OF_ITEMS];
	};
}