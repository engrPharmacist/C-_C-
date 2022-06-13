#pragma once
#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"
#include <string>
#include <iostream>

namespace Tomo
{
	class Zasady : public State
	{

	public:
		Zasady(GameDataRef data);

		void Init();
		void HandleInput();
		void Update(float dt);
		void Draw(float dt);

	private:

		GameDataRef _data;

		sf::Sprite tloW;
		sf::Text wroc;
		sf::Text Zasadyy;
	
	};
}