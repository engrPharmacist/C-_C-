#pragma once

#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"
#include <string>

namespace Tomo
{
	class WyborGry : public State
	{
	public:
		WyborGry(GameDataRef data);

		void Init();

		void HandleInput();
		void Update(float dt);
		void Draw(float dt);

	private:
		GameDataRef _data;

		sf::Sprite tloW;
		sf::Sprite PlayButton;

		

		sf::Text wroc;

	};
}