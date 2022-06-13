#pragma once

#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"

namespace Tomo
{
	class GameOverState : public State
	{
	public:
		GameOverState(GameDataRef data, int score1, int score2);

		void Init();

		void HandleInput();
		void Update(float dt);
		void Draw(float dt);

		int Winer(int a, int b);
		void WynikUpdate();

	private:
		GameDataRef _data;

		sf::Sprite background;
		sf::Text wroc;
		sf::Sprite PlayButton;

		//wynik gracza 
		sf::Text scoreText[MAX_NUMBER_OF_SCORES];
		int _score1;
		int _score2;
		int i = 0;
		int wynik[MAX_NUMBER_OF_PLAYERS];

		//odczyt z pliku
		sf::Text SAWENICK[4];
		sf::Text NapisGracze[MAX_NUMBER_OF_PLAYERS];//wypisuje gracz 1 gracz 2  
		sf::Text NapisScore[MAX_NUMBER_OF_PLAYERS];//wypisuje Score:

		sf::Text WINER;//wypisuje  tekst zwyciê¿cy 
	};
}