#pragma once
#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"
#include <string>
#include <iostream>

namespace Tomo
{
	class CzyZamknac : public State
	{

	public:
		CzyZamknac(GameDataRef data);

		void Init();
		void HandleInput();
		void Update(float dt);
		void Draw(float dt);

	private:

		GameDataRef _data;

		sf::Sprite quitgamesnake;
		sf::Sprite komunikat;
		sf::Sprite tloS;
		sf::Text tak;
		sf::Text nie;
		sf::Text pewien;

		StateRef _newstate;
	
		
	};
}