#pragma once
#include "DEFINITIONS.hpp"
#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"
#include <sstream>
#include <string>
#include <iostream>


#include <stdio.h>
#include <stdlib.h>
#include <fstream>

#include "Snake.h"
using namespace std;

namespace Tomo
{

	//--------------------------------------------------------------------------------------
	typedef struct Gracz
	{
		string Nick;
		int Wynik;

	};
	//-------------------------------------------------------------------------------------


	class WyborGry : public State
	{
	public:
		WyborGry(GameDataRef data);

		void Init();

		void HandleInput();
		void Update(float dt);
		void Draw(float dt);

		void MoveUp();
		void MoveDown();

		void SaveProfiles();
		void LoadProfiles();

		void DeleteProfile();
		
		void ClearWrite0();

		void ClearWrite1();



	private:
		GameDataRef _data;


		sf::Sprite tloW;
		sf::Sprite PlayButton[MAX_NUMBER_OF_PLAY_MODE];

		sf::RectangleShape nickramka[MAX_NUMBER_OF_PLAYERS];
		float NickNamePosition[2 * MAX_NUMBER_OF_PLAYERS] = { 140,40,140,240, };

		sf::Text NumerGracza[MAX_NUMBER_OF_PLAYERS];
		std::string texxt[MAX_NUMBER_OF_PLAYERS] = { "Gracz 1  ", "Gracz 2  "};

		sf::Text wroc;

		//nowe----------------------------------------------------
		sf::Text SAWENICK[MAX_NUMBER_OF_PLAYERS ];
		float Npozycja[(MAX_NUMBER_OF_PLAYERS ) * 2] = { 160, 50, 160, 250, };
		string ShowNick[MAX_NUMBER_OF_PLAYERS ] = { "wpisz nick", "wpisz nick" };


		sf::Text przypisy[2];
		float przypisyPosition[4] = { 0, 0, 500, 170 };
		string przypisytekst[2] = { "Wpisz Nick i Kliknij Zielony" , "Usuñ Profil Czerwonym " };

		string PlayerNick[MAX_NUMBER_OF_PLAYERS];
		int PlayerWynik[MAX_NUMBER_OF_PLAYERS];

		bool NR;//numer gracza 
		bool Created = false;//do sprawdzania warunku,czy profi³ zosta³ ju¿ stworzony 
		string NowyNick;
		
		sf::Sprite FileButton[MAX_NUMBER_OF_PLAYERS];
		sf::Sprite RemoveFileButton[MAX_NUMBER_OF_PLAYERS];

		Gracz* gracz[MAX_NUMBER_OF_PLAYERS];
		int LiczbaGraczy;
		
		sf::Text Wyswietl;
		
		sf::String PlayerInput;
		sf::Text CreateNew;

	};
}
