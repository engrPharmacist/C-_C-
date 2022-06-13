#pragma once

#include <sstream>
#include "DEFINITIONS.hpp"
#include "GameState.hpp"
#include "snake.h"
#include "Friutt.h"
#include"GameOverState.hpp"

#include <iostream>

namespace Tomo
{
	GameState::GameState(GameDataRef data) : _data(data)
	{
	}

	void GameState::Init()
	{
		string nick1, nick2;
		string linia;
		int nr_linii = 1;

		fstream plik;
		plik.open(NICK_FILE, ios::in);

		if (plik.good() == false) cout << "Nie mozna otworzyc pliku!";//Odczyt z pliku 

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

		cout << "nick1= " << nick1 << " nick2= " << nick2 << endl;

		for (int i = 0; i < MAX_NUMBER_OF_SCORES; i++)
		{
			SAWENICK[i].setFont(this->_data->assets.GetFont("Main Menu Font Style"));
			SAWENICK[i].setCharacterSize(30);
			SAWENICK[i].setFillColor(sf::Color::White);
			SAWENICK[i].setPosition(sf::Vector2f(140 + 400 * i, 1));
			SAWENICK[i].setOutlineThickness(3);

			NapisGracze[i].setFont(this->_data->assets.GetFont("Main Menu Font Style"));
			NapisGracze[i].setCharacterSize(30);
			NapisGracze[i].setFillColor(sf::Color::White);
			NapisGracze[i].setPosition(sf::Vector2f(0 + 400 * i, 1));
			NapisGracze[i].setOutlineThickness(3);
			NapisGracze[i].setOutlineColor(sf::Color::Black);
		}

		SAWENICK[0].setOutlineColor(sf::Color::Green);
		SAWENICK[0].setString(nick1);

		SAWENICK[1].setOutlineColor(sf::Color::Red);
		SAWENICK[1].setString(nick2);

		NapisGracze[0].setString("PLAYER1:");
		NapisGracze[1].setString("PLAYER2:");

		//t³o kosmos
		//this->_data->assets.LoadTexture("Game Background", GAME_BACKGROUND_FILEPATH);
		//_background.setTexture(this->_data->assets.GetTexture("Game Background"));

		//t³o trawa
		this->_data->assets.LoadTexture("Trawa Background", TRAWA2_FILEPATH);
		_background.setTexture(this->_data->assets.GetTexture("Trawa Background"));

		//font
		this->_data->assets.LoadFont("Main Menu Font Text", FONT_TEXTT_FILEPATH);

		Snake1 = new Snake(_data);
		Snake2 = new Snake(_data);
		Fruit1 = new Fruit(_data);
		Snake1->SetPos();
		Snake2->RedTexture();

		ZapiszWynik();
		
		//obs³uga zapisywania wyniku
		Score1 = new Score(_data);
		Score1->UpdateScore(Wynik);
		Score2 = new Score(_data);
		Score2->UpdateScore(_score2);
		Score2->SetPos();

		//pauza gry
		wroc.setFont(this->_data->assets.GetFont("Main Menu Font Style"));
		wroc.setCharacterSize(24);
		wroc.setString("Wróc do Gry");
		wroc.setPosition(800, 0);
		wroc.setFillColor(sf::Color(0, 110, 0, 255));

		this->_data->assets.LoadTexture("F1", F1_FILEPATH);
		F1.setTexture(this->_data->assets.GetTexture("F1"));
		F1.setPosition(800, 0);

		//Czy zamkn¹æ
		this->_data->assets.LoadTexture("Quit Game Snake", CZY_ZAMKNAC_SNAKE_FILEPATH);
		quitgamesnake.setTexture(this->_data->assets.GetTexture("Quit Game Snake"));
		quitgamesnake.setPosition(800, 0);
		//Dymek
		this->_data->assets.LoadTexture("Komunikat", CZY_ZAMKNAC_KOMUNIKAT_FILEPATH);
		komunikat.setTexture(this->_data->assets.GetTexture("Komunikat"));
		komunikat.setPosition(800, 0);

		nie.setFont(this->_data->assets.GetFont("Main Menu Font Style"));
		nie.setCharacterSize(30);
		nie.setString("NIE");
		nie.setPosition(800, 0);
		nie.setFillColor(sf::Color(50, 210, 50, 255));

		pewien.setFont(this->_data->assets.GetFont("Main Menu Font Style"));
		pewien.setCharacterSize(24);
		pewien.setString("Na pewno chcesz\nwyjsc z Gry ? :c");
		pewien.setPosition(800, 0);
		pewien.setFillColor(sf::Color(0, 110, 0, 255));

		tak.setFont(this->_data->assets.GetFont("Main Menu Font Style"));
		tak.setCharacterSize(30);
		tak.setString("TAK");
		tak.setPosition(800, 0);
		tak.setFillColor(sf::Color(200, 0, 0, 255));
	}

	void GameState::HandleInput()
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			Snake1->Stop();//zatrzymuje snake
			Snake2->Stop();
			CzyZamknac();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::F1))
		{
			Snake1->Stop();//zatrzymuje snake
			Snake2->Stop();
			STOP();//przesuwa obiekty na ekran
		}
		sf::Event event;

		while (this->_data->window.pollEvent(event))
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				if (wroc.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
				{
					START();
				}
				if (nie.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
				{
					Nie();
				}
				if (tak.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
				{
					this->_data->window.close();
					break;
				}
			}
		}
	}

	void GameState::Update(float dt)
	{
		Snake2->updateTail();
		Snake2->keyboardInput2();
		Snake2->Update(dt, Wynik,_score2);

		Snake1->updateTail();
		Snake1->keyboardInput1();
		Snake1->Update(dt,Wynik,_score2);

		UpdateSnakePosition();//Zapisywanie bierz¹cej pozycji Snake


		Collider SnakeColizion = Snake1->GetCollider();//inicjowanie zmiennej kolizi owocy 

		// kolizja z snake ze snakiem 
		if (Snake2->GetCollider().CheckCollision(SnakeColizion))
		{

			this->_data->machine.AddState(StateRef(new GameOverState(_data, Wynik, _score2)), true);
			std::cout << "Head toHEad colizion" << endl;
		}


		Collider FruitColizion = Fruit1->GetCollider();//inicjowanie zmiennej kolizi owocy 

		// kolizja z owocem snake 1 
		if (Snake1->GetCollider().CheckCollision(FruitColizion))
		{
			Snake1->AddTail();
			
			Fruit1->UpdateFriut();

			//zwiêkszanie wyniku
			Wynik++;
			Score1->UpdateScore(Wynik);
		
			std::cout << "Snake1 +1" << endl;
		}

		// kolizja z owocem snake 2
	
		if (Snake2->GetCollider().CheckCollision(FruitColizion))
		{
			Snake2->AddTail();

			Fruit1->UpdateFriut();

			//zwiêkszanie wyniku
			_score2++;
			Score2->UpdateScore(_score2);

			std::cout << "Snake2 +1" << endl;
		}

	}

	void GameState::Draw(float dt)
	{
		this->_data->window.clear(sf::Color::Black);

		this->_data->window.draw(this->_background);

		Snake1->DrawSnake(dt);
		Snake2->DrawSnake(dt);//DRUGI SNAKE
		Fruit1->DrawFruit();
		Score1->Draw();
		Score2->Draw();
		
		//z pliku
		for (int i = 0; i < MAX_NUMBER_OF_SCORES; i++)
		{
			this->_data->window.draw(SAWENICK[i]);
			this->_data->window.draw(NapisGracze[i]);
		}
		//Zasady
		this->_data->window.draw(this->F1);
		this->_data->window.draw(this->wroc);

		//Czy zamkn¹æ
		this->_data->window.draw(quitgamesnake);
		this->_data->window.draw(komunikat);
		this->_data->window.draw(nie);
		this->_data->window.draw(tak);
		this->_data->window.draw(pewien);

		this->_data->window.display();
	}
	void GameState::updateScore(int i)
	{
		std::stringstream _string;
		std::string newString = _string.str();
	}
	void GameState::ZapiszWynik()
	{


		ifstream File1;
		File1.open(WYNIKI_FILE);

		File1 >> Wynik;
		File1 >> _score2;

		File1.close();

		string line;
		ifstream File;
	}
	void GameState::STOP()
	{
		F1.setPosition(0, 0);
		wroc.setPosition(650, 10);

	}

	void GameState::START()
	{
		F1.setPosition(800, 0);
		wroc.setPosition(800, 0);

	}

	void GameState::CzyZamknac()
	{
		quitgamesnake.setPosition(25.f, 0.f);
		komunikat.setPosition(225.f, 150.f);
		nie.setPosition(415, 265);
		pewien.setPosition(263, 180);
		tak.setPosition(270, 265);

	}

	void GameState::Nie()
	{
		quitgamesnake.setPosition(800, 0);
		komunikat.setPosition(800, 0);
		nie.setPosition(800, 0);
		pewien.setPosition(800, 0);
		tak.setPosition(800, 0);
	}

	sf::Vector2f GameState::Snake1Pos()
	{
		return Snake2->GetPosition();
	}
	sf::Vector2f GameState::Snake2Pos()
	{
		return Snake1->GetPosition();
	}

	void GameState::ZapiszSnakePosition(int Ax, int Ay, int Bx, int By)
	{
		ofstream File(POZYCJA_FILE);
		if (File.is_open())
		{

			File << Ax << endl;
			File << Ay << endl;
			File << Bx << endl;
			File << By << endl;

			File.close();
			cout << "Points Saved properly" << endl;////////////////////////
		}
		else cout << "Unable to open file" << endl;////////////////////
	}
	void GameState::UpdateSnakePosition()
	{
		sf::Vector2f A = Snake1Pos();
		int Ax = A.x;
		int Ay = A.y;
		sf::Vector2f B = Snake2Pos();
		int Bx = B.x;
		int By = B.y;
		ZapiszSnakePosition(Ax, Ay, Bx, By);
	}
}
