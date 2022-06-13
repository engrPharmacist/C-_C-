#pragma once

#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"
#include "snake.h"
#include "Friutt.h"
#include "score.h"
#include "zasady.h"
#include "WyborGry.h"

namespace Tomo
{
	class GameState : public State
	{
	public:
		GameState(GameDataRef data);

		void Init();

		void HandleInput();
		void Update(float dt);
		void Draw(float dt);

		void updateScore(int i);

		void ZapiszWynik();

		void STOP();
		void START();

		void CzyZamknac();
		void Nie();

		sf::Vector2f Snake1Pos();
		sf::Vector2f Snake2Pos();

		void ZapiszSnakePosition(int Ax, int Ay, int Bx, int By);

		void UpdateSnakePosition();

	private:
		//Plik
		string PlayerNick[MAX_NUMBER_OF_PLAYERS];

		sf::Text SAWENICK[MAX_NUMBER_OF_PLAYERS];//pokazuje nick

		sf::Text NapisGracze[MAX_NUMBER_OF_PLAYERS];//wypisuje gracz 1 gracz 2  

		sf::Texture m_texture;
		
		Snake* Snake1;
		Snake* Snake2;
		Fruit* Fruit1;
		GameDataRef _data;

		//wynik snake 1 
		int Wynik;
		Score* Score1;
		//wynik snake 2 
		int _score2;
		Score* Score2;

		// F1
		sf::Sprite F1;
		sf::Text wroc;

		// czy zamkn¹æ
		sf::Sprite quitgamesnake;
		sf::Sprite komunikat;
		sf::Text tak;
		sf::Text nie;
		sf::Text pewien;

		sf::Sprite _background;
	};
}