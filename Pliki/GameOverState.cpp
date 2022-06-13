#pragma once

#include <sstream>
#include "DEFINITIONS.hpp"
#include "GameOverState.hpp"
#include "CzyZamknac.h"
#include "MainMenuState.hpp"
#include "GameState.hpp"

#include <iostream>

namespace Tomo
{
	GameOverState::GameOverState(GameDataRef data, int score1,int score2) : _data(data), _score1(score1), _score2(score2)
	{

	}

	void GameOverState::Init()
	{
		//odczyt z pliku
		string nick1, nick2;
		string linia;
		int nr_linii = 1;

		fstream plik;
		plik.open(NICK_FILE, ios::in);

		if (plik.good() == false) cout << "Nie mozna otworzyc pliku!";

		while (getline(plik, linia))
		{
			switch (nr_linii)
			{
			case 1: nick1 = linia; break;
			case 2: nick2 = linia; break;

			}
			nr_linii++;
		}

		plik.close();

		fstream plikwynik;
		plikwynik.open(WYNIKI_FILE);

		while (!plikwynik.eof())
		{
			plikwynik >> wynik[i];
			i++;
		}

		plikwynik.close();


		SAWENICK[0].setOutlineColor(sf::Color::Green);
		SAWENICK[0].setString(nick1);

		SAWENICK[1].setOutlineColor(sf::Color::Red);
		SAWENICK[1].setString(nick2);

		cout << "nick1= " << nick1 << "nick2= " << nick2 << endl;


		//font styleE
		this->_data->assets.LoadFont("Main Menu Font Style", FONT_STYLEE_FILEPATH);

		//font textT
		this->_data->assets.LoadFont("Main Menu Font Text", FONT_TEXTT_FILEPATH);

		//t³o
		this->_data->assets.LoadTexture("Game Over Background", WYBOR_GRY_BACKGROUND_FILEPATH);
		background.setTexture(this->_data->assets.GetTexture("Game Over Background"));
		background.setPosition(-105.f, 0.f);

		// Powrót to menu gównego
		wroc.setFont(this->_data->assets.GetFont("Main Menu Font Style"));
		wroc.setCharacterSize(20);
		wroc.setString("Wróc do Menu startowego");
		wroc.setPosition(520, 5);
		wroc.setFillColor(sf::Color(0, 110, 0, 255));
		//Play Button
		this->_data->assets.LoadTexture("Play Button", PLAY_NORMAL_BUTTON_FILEPATH);
		PlayButton.setTexture(this->_data->assets.GetTexture("Play Button"));
		PlayButton.setPosition(130.f, 430.f);



		for (int i = 0; i < MAX_NUMBER_OF_SCORES; i++)
		{

			SAWENICK[i].setFont(this->_data->assets.GetFont("Main Menu Font Style"));
			SAWENICK[i].setCharacterSize(40);
			SAWENICK[i].setFillColor(sf::Color::White);
			SAWENICK[i].setPosition(sf::Vector2f(160, 253 + 100 * i));
			SAWENICK[i].setOutlineThickness(3);

			scoreText[i].setFont(this->_data->assets.GetFont("Main Menu Font Text"));
			scoreText[i].setCharacterSize(56);
			scoreText[i].setPosition(sf::Vector2f(505, 240 + 100 * i));

			NapisGracze[i].setFont(this->_data->assets.GetFont("Main Menu Font Style"));
			NapisGracze[i].setCharacterSize(30);
			NapisGracze[i].setFillColor(sf::Color::White);
			NapisGracze[i].setPosition(sf::Vector2f(10, 260 + 100 * i));
			NapisGracze[i].setOutlineThickness(3);
			NapisGracze[1].setOutlineColor(sf::Color::Black);

			NapisScore[i].setFont(this->_data->assets.GetFont("Main Menu Font Style"));
			NapisScore[i].setCharacterSize(30);
			NapisScore[i].setFillColor(sf::Color::White);
			NapisScore[i].setPosition(sf::Vector2f(400, 260 + 100 * i));
			NapisScore[i].setOutlineThickness(3);
			NapisScore[i].setOutlineColor(sf::Color::Black);
			NapisScore[i].setString("SCORE:");
		}

		NapisGracze[0].setString("PLAYER1:");
		NapisGracze[1].setString("PLAYER2:");

		scoreText[0].setFillColor(sf::Color::Green);
		scoreText[1].setFillColor(sf::Color::Red);

		scoreText[0].setString(std::to_string(wynik[0]));
		scoreText[1].setString(std::to_string(wynik[1]));

		//pokazuje kto wygra³
		WINER.setFont(this->_data->assets.GetFont("Main Menu Font Style"));
		WINER.setCharacterSize(70);
		WINER.setFillColor(sf::Color::Cyan);
		WINER.setPosition(sf::Vector2f(10, 50));
		WINER.setOutlineThickness(3);
		WINER.setOutlineColor(sf::Color::Black);

		SAWENICK[2].setFont(this->_data->assets.GetFont("Main Menu Font Style"));
		SAWENICK[2].setCharacterSize(80);
		SAWENICK[2].setFillColor(sf::Color::Green);
		SAWENICK[2].setPosition(sf::Vector2f(240, 140));
		SAWENICK[2].setOutlineThickness(3);
		SAWENICK[2].setString(nick1);//dziedziczy Nick 1

		SAWENICK[3].setFont(this->_data->assets.GetFont("Main Menu Font Style"));
		SAWENICK[3].setCharacterSize(80);
		SAWENICK[3].setFillColor(sf::Color::Red);
		SAWENICK[3].setPosition(sf::Vector2f(240, 140));
		SAWENICK[3].setOutlineThickness(3);
		SAWENICK[3].setString(nick2);//dziedziczy Nick 1


	}

	void GameOverState::HandleInput()
	{
		sf::Event event;

		while (this->_data->window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::MouseButtonPressed:
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					if (PlayButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
					{
						WynikUpdate();
						this->_data->machine.RemoveState();
						this->_data->machine.AddState(StateRef(new GameState(_data)), true);
						break;
					}
					if (wroc.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
					{
						WynikUpdate();
						this->_data->machine.RemoveState();
						this->_data->machine.AddState(StateRef(new MainMenuState(_data)), true);
					}
				}
			}
			if (sf::Event::KeyPressed == event.type)
			{
				if (event.key.code == sf::Keyboard::Escape)
				{
					this->_data->machine.AddState(StateRef(new CzyZamknac(_data)), true);
				}
			}
		}
	}

	void GameOverState::Update(float dt)
	{
		
	}

	void GameOverState::Draw(float dt)
	{
		this->_data->window.clear(sf::Color::Black);

		this->_data->window.draw(this->background);

		this->_data->window.draw(wroc);

		for (int i = 0; i < MAX_NUMBER_OF_SCORES; i++)
			{
			_data->window.draw(scoreText[i]);
			this->_data->window.draw(SAWENICK[i]);
			this->_data->window.draw(NapisGracze[i]);
			this->_data->window.draw(NapisScore[i]);
			}
		switch (Winer(_score1, _score2))
		{
		case 0:
			this->_data->window.draw(SAWENICK[2]);
			WINER.setString("AND THE WINNER IS!!!!!");
			this->_data->window.draw(WINER);
			break;
		case 1:

			this->_data->window.draw(SAWENICK[3]);
			WINER.setString("AND THE WINNER IS!!!!!");
			this->_data->window.draw(WINER);
			break;
		case 2:
			WINER.setCharacterSize(90);
			WINER.setString("ROWNA WALKA !");
			this->_data->window.draw(WINER);
			break;
		}
		this->_data->window.draw(PlayButton);

		this->_data->window.display();
	}
	int GameOverState::Winer(int a, int b)
	{
		if (a > b)
		{
			return 0;
		}
		else if (a < b)
			return 1;
		else return 2;
	};
	void GameOverState::WynikUpdate()
	{
		ofstream myfile(WYNIKI_FILE);
		if (myfile.is_open())
		{

			myfile << _score1 << endl;
			myfile << _score2 << endl;

			myfile.close();
		}
	}
}