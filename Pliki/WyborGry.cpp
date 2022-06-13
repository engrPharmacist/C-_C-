#pragma once

#include <sstream>
#include "MainMenuState.hpp"
#include "GameState.hpp"
#include "GameStateDenerwuje.h"
#include "zasady.h"
#include "CzyZamknac.h"


#include "WyborGry.h"


namespace Tomo
{
	WyborGry::WyborGry(GameDataRef data) : _data(data)
	{

	}

	void WyborGry::Init()
	{
		//³adowanie pliku
		LoadProfiles();

		//przycisk zapisu lub usuwania gracza
		//this->_data->assets.LoadFont("Frofile Button", PROFILE_BUTTON_FILEPATH);

		//font styleE
		this->_data->assets.LoadFont("Main Menu Font Style", FONT_STYLEE_FILEPATH);

		//font textT
		this->_data->assets.LoadFont("Main Menu Font Text", FONT_TEXTT_FILEPATH);

		

		//t³o
		this->_data->assets.LoadTexture("Tlo wybor", WYBOR_GRY_BACKGROUND_FILEPATH);
		tloW.setTexture(this->_data->assets.GetTexture("Tlo wybor"));
		tloW.setPosition(-105.f, 0.f);

		//Play Button DENERWUJE
		this->_data->assets.LoadTexture("Play Tricky Button", PLAY_TRICKY_BUTTON_FILEPATH);
		PlayButton[0].setTexture(this->_data->assets.GetTexture("Play Tricky Button"));
		PlayButton[0].setPosition(290.f, 430.f);

		//Play Button normalny
		this->_data->assets.LoadTexture("Play Normal Button", PLAY_NORMAL_BUTTON_FILEPATH);
		PlayButton[1].setTexture(this->_data->assets.GetTexture("Play Normal Button"));
		PlayButton[1].setPosition(0.f, 430.f);
		
		//ramka na nick
		for (int i = 0; i < MAX_NUMBER_OF_PLAYERS; i++)
		{
			nickramka[i].setSize(sf::Vector2f(300.f, 70.f));
			nickramka[i].setPosition(NickNamePosition[2 * i], NickNamePosition[(2 * i)+1 ]);
			nickramka[i].setFillColor(sf::Color(130, 60, 190));
			nickramka[i].setOutlineThickness(5.f);
			nickramka[i].setOutlineColor(sf::Color(0, 86, 0));
		
		//numer gracza
			NumerGracza[i].setFont(this->_data->assets.GetFont("Main Menu Font Style"));
			NumerGracza[i].setPosition(NickNamePosition[2 * i] - 135.f, NickNamePosition[(2 * i)+1 ]+ 8);
			NumerGracza[i].setCharacterSize(35);
			NumerGracza[i].setString(texxt[i]);
			
			//przycisk ³adowania pliku
			FileButton[i].setTexture(this->_data->assets.GetTexture("Play Normal Button"));
			FileButton[i].setTextureRect(sf::IntRect{ 115, 42, 70, 70 });
			FileButton[i].setPosition(sf::Vector2f(NickNamePosition[2 * i]+310, NickNamePosition[(2 * i) + 1]));
			
			//przyisk usuwania pliku 
			RemoveFileButton[i].setTexture(this->_data->assets.GetTexture("Play Tricky Button"));
			RemoveFileButton[i].setTextureRect(sf::IntRect{ 115, 42, 70, 70 });
			RemoveFileButton[i].setPosition(sf::Vector2f(NickNamePosition[2 * i] + 385, NickNamePosition[(2 * i) + 1]));

			//wyœwietlanie Nicku
			SAWENICK[i].setFont(this->_data->assets.GetFont("Main Menu Font Style"));
			SAWENICK[i].setCharacterSize(40);
			SAWENICK[i].setFillColor(sf::Color::White);
			SAWENICK[i].setString(ShowNick[i]);
			SAWENICK[i].setPosition(Npozycja[2 * i], Npozycja[(2 * i) + 1]);
			SAWENICK[i].setOutlineThickness(3);
			SAWENICK[i].setOutlineColor(sf::Color::Black);

			przypisy[i].setFont(this->_data->assets.GetFont("Main Menu Font Style"));
			przypisy[i].setFillColor(sf::Color(130, 60, 190));
			przypisy[i].setPosition(przypisyPosition[2 * i], przypisyPosition[(2 * i) + 1]);
			przypisy[i].setCharacterSize(24);
			przypisy[i].setString(przypisytekst[i]);
			przypisy[i].setOutlineThickness(1);
			przypisy[i].setOutlineColor(sf::Color(0, 86, 0));
		}
		NumerGracza[0].setOutlineThickness(3.f);
		NumerGracza[0].setOutlineColor(sf::Color::White);
		NumerGracza[0].setFillColor(sf::Color::Green);
		NumerGracza[1].setFillColor(sf::Color::Red);
	

		//przycisk powrotu
		wroc.setFont(this->_data->assets.GetFont("Main Menu Font Style"));
		wroc.setCharacterSize(20);
		wroc.setString("Wróc do Menu startowego");
		wroc.setPosition(520, 5);
		wroc.setFillColor(sf::Color(0, 110, 0, 255));

		
		//pierwsze zapisanie wartosci wejsciowych 
		CreateNew.setFont(this->_data->assets.GetFont("Main Menu Font Style"));
		CreateNew.setFillColor(sf::Color::Black);
		CreateNew.setPosition(160, 50);
		CreateNew.setCharacterSize(40);

		//"wskaŸnik" na w³aœciwego gracza 
		NR = 0;
		//LiczbaGraczy = 0;
	
	}

	void WyborGry::HandleInput()
	{
		sf::Event event;

		while (this->_data->window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::MouseButtonPressed:
				
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					if (PlayButton[0].getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
					{
						this->_data->machine.RemoveState();
						this->_data->machine.AddState(StateRef(new GameStateDenerwuje(_data)), true);
						break;
					}
					else if (PlayButton[1].getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
					{
						this->_data->machine.RemoveState();
						this->_data->machine.AddState(StateRef(new GameState(_data)), true);
						break;
					}
					else if (FileButton[0].getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
					{
						if (LiczbaGraczy != 2)
						{
							NowyNick = PlayerInput;
							PlayerInput.erase((PlayerInput.getSize() - PlayerInput.getSize()), PlayerInput.getSize());
							gracz[LiczbaGraczy] = new Gracz;
							gracz[LiczbaGraczy]->Nick = NowyNick;
							gracz[LiczbaGraczy]->Wynik = 0;
							cout << "New Player Name = " << gracz[LiczbaGraczy]->Nick << endl;
							cout << "New Player Points = " << gracz[LiczbaGraczy]->Wynik << endl;
							PlayerNick[LiczbaGraczy] = gracz[LiczbaGraczy]->Nick;
							PlayerWynik[LiczbaGraczy] = gracz[LiczbaGraczy]->Wynik;
							SAWENICK[0].setString(PlayerNick[LiczbaGraczy]);
							Created = true;
							LiczbaGraczy++;
							SaveProfiles();
						}
						break;
					}

					else if (FileButton[1].getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
					{
						if (LiczbaGraczy != 2)
						{
							NowyNick = PlayerInput;
							PlayerInput.erase((PlayerInput.getSize() - PlayerInput.getSize()), PlayerInput.getSize());
							gracz[LiczbaGraczy] = new Gracz;
							gracz[LiczbaGraczy]->Nick = NowyNick;
							gracz[LiczbaGraczy]->Wynik = 0;
							cout << "New Player Name = " << gracz[LiczbaGraczy]->Nick << endl;
							cout << "New Player Points = " << gracz[LiczbaGraczy]->Wynik << endl;
							PlayerNick[LiczbaGraczy] = gracz[LiczbaGraczy]->Nick;
							PlayerWynik[LiczbaGraczy] = gracz[LiczbaGraczy]->Wynik;
							SAWENICK[1].setString(PlayerNick[LiczbaGraczy]);
							Created = true;
							LiczbaGraczy++;
							SaveProfiles();
						}
				
						break;
					}
					if (wroc.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
					{
						this->_data->machine.AddState(StateRef(new MainMenuState(_data)), true);
					}
					if (RemoveFileButton[0].getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
					{
						NR = 0;
						DeleteProfile();
					}
					if (RemoveFileButton[1].getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
					{
						NR = 1;
						DeleteProfile();
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
			if (event.type == sf::Event::TextEntered)
			{
				if (event.text.unicode == 8)
				{
					if (PlayerInput.getSize() != NULL)
					{
						
						PlayerInput.erase((PlayerInput.getSize() - 1), 1);
						CreateNew.setString(PlayerInput);
					}
				}
				else
				{
					SAWENICK[NR].setString("");
					PlayerInput += static_cast<char>(event.text.unicode);
					CreateNew.setString(PlayerInput);
				}

			}
			

			switch (event.type)
			{
			case sf::Event::KeyPressed:
				switch (event.key.code)
				{

				case sf::Keyboard::Up:
					MoveUp();
					NR = 0;
					break;

				case sf::Keyboard::Down:
					MoveDown();
					NR = 1;
					break;


					             
				}
			}
		}
	}

	void WyborGry::Update(float dt)
	{

	}

	void WyborGry::Draw(float dt)
	{
		this->_data->window.clear(sf::Color::Black);

		this->_data->window.draw(this->tloW);

		for (int i = 0; i < MAX_NUMBER_OF_PLAYERS; i++)
		{
			
			this->_data->window.draw(this->nickramka[i]);
			this->_data->window.draw(this->SAWENICK[i]);
			this->_data->window.draw(this->NumerGracza[i]);
			this->_data->window.draw(this->FileButton[i]);
			this->_data->window.draw(this->RemoveFileButton[i]);
			this->_data->window.draw(this->przypisy[i]);
			this->_data->window.draw(PlayButton[i]);
		}
		this->_data->window.draw(wroc);
	
		this->_data->window.draw(this->CreateNew);

		if (Created == true)
		{
			this->_data->window.draw(this->Wyswietl);
		}







		this->_data->window.display();
	}

	
	void WyborGry::MoveUp()
	{
		if (NR == 1 )
		{
			CreateNew.setPosition(160, 50);
			NumerGracza[NR].setOutlineThickness(0);
			NR = 0;
			NumerGracza[NR].setOutlineThickness(3);
			NumerGracza[NR].setOutlineColor(sf::Color::White);
			
		}
	}
	void WyborGry::MoveDown()
	{
		if (NR == 0 )
		{
			CreateNew.setPosition(160, 250);
			NumerGracza[NR].setOutlineThickness(0);;
			NR = 1;
			NumerGracza[NR].setOutlineThickness(3);
			NumerGracza[NR].setOutlineColor(sf::Color::White);
			
		}

	}

	void WyborGry::SaveProfiles()
	{
		ofstream myfile(WYNIKI_FILE);

		if (myfile.is_open())
		{
			for (int i = 0; i < LiczbaGraczy; i++)
			{
				myfile << PlayerWynik[i] << endl;
			}
			myfile.close();
			cout << "Zapisany Poprawnie" << endl;
		}
		else cout << "Unable to open Wyniki file" << endl;

		ofstream myfile1(NICK_FILE);
		if (myfile1.is_open())
		{
			for (int i = 0; i < LiczbaGraczy; i++)
			{
				myfile1 << PlayerNick[i] << endl;
			}
			myfile1.close();
			cout << "Zapisany" << endl;
		}
		else cout << "Unable to open Nick file" << endl;

	}

	void WyborGry::LoadProfiles()
	{
		int n = 0;

		ifstream File1;
		File1.open(WYNIKI_FILE);

		while (!File1.eof())
		{
			File1 >> PlayerWynik[n];
			n++;
		}

		File1.close();

		string line;
		ifstream File;

		n = 0;

		File.open(NICK_FILE);
		while (getline(File, line))
		{
			gracz[n] = new Gracz;
			gracz[n]->Nick = line;
			PlayerNick[n] = gracz[n]->Nick;
			gracz[n]->Wynik = PlayerWynik[n];
			cout << gracz[n]->Wynik << endl;
			cout << gracz[n]->Nick << endl;
			if (PlayerNick[n] != "")
			{
				SAWENICK[LiczbaGraczy].setString(gracz[n]->Nick);
				LiczbaGraczy++;
			}
			n++;
			cout << "Gracz " << LiczbaGraczy << " za³adowany poprawnie" << endl;
		}

		File.close();

	}

	void WyborGry::DeleteProfile()
	{
		switch (NR)
		{
		case 0:
			PlayerWynik[0] = NULL;
			PlayerNick[0] = "";
			SaveProfiles();
			SAWENICK[0].setString("");
			if (LiczbaGraczy > 0)
				LiczbaGraczy--;
			break;
		case 1:
			PlayerWynik[1] = NULL;
			PlayerNick[1] = "";
			SaveProfiles();
			SAWENICK[1].setString("");
			if (LiczbaGraczy > 0)
				LiczbaGraczy--;
			break;
		}
	}

	void WyborGry::ClearWrite0()
	{
		SAWENICK[0].setString("");
	}

	void WyborGry::ClearWrite1()
	{
		SAWENICK[1].setString("");
	}

}