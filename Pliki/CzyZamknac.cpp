#include <sstream>
#include "DEFINITIONS.hpp"
#include "MainMenuState.hpp"
#include "CzyZamknac.h"

namespace Tomo
{

	CzyZamknac::CzyZamknac(GameDataRef data) : _data(data)
	{
	}

	void Tomo::CzyZamknac::Init()
	{   //Snake
		this->_data->assets.LoadTexture("Quit Game Snake", CZY_ZAMKNAC_SNAKE_FILEPATH);
		quitgamesnake.setTexture(this->_data->assets.GetTexture("Quit Game Snake"));
		quitgamesnake.setPosition(25.f, 0.f);
		//Komunikat dostaje dziwnej pow³oki bo nie ma clear
		this->_data->assets.LoadTexture("Komunikat", CZY_ZAMKNAC_KOMUNIKAT_FILEPATH);
		komunikat.setTexture(this->_data->assets.GetTexture("Komunikat"));
		komunikat.setPosition(225.f, 150.f);
		//maskowanie tego, s³abo dopracowane xd 
		this->_data->assets.LoadTexture("Tlo Snake", MAIN_MENU_TLO_FILEPATH);
		tloS.setTexture(this->_data->assets.GetTexture("Tlo Snake"));
		tloS.setPosition(-175.f, 0.f);

		nie.setFont(this->_data->assets.GetFont("Main Menu Font Style"));
		nie.setCharacterSize(30);
		nie.setString("NIE");
		nie.setPosition(415, 265);
		nie.setFillColor(sf::Color(50, 210, 50, 255));

		pewien.setFont(this->_data->assets.GetFont("Main Menu Font Style"));
		pewien.setCharacterSize(24);
		pewien.setString("Na pewno chcesz\nwyjsc z Gry ? :c");
		pewien.setPosition(263, 180);
		pewien.setFillColor(sf::Color(0, 110, 0, 255));

		tak.setFont(this->_data->assets.GetFont("Main Menu Font Style"));
		tak.setCharacterSize(30);
		tak.setString("TAK");
		tak.setPosition(270, 265);
		tak.setFillColor(sf::Color(200, 0, 0, 255));

	}

	void Tomo::CzyZamknac::HandleInput()
	{
		sf::Event event;

		while (this->_data->window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::MouseButtonPressed:
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					if (nie.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
					{
						this->_data->machine.AddState(StateRef(new MainMenuState(_data)), true);
					}
					if (tak.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
					{
						this->_data->window.close();
							break;
					}
				}
			}



		}
	}

	void Tomo::CzyZamknac::Update(float dt)
	{
	}

	void Tomo::CzyZamknac::Draw(float dt)
	{
		//this->_data->window.clear();
		
		
		//this->_data->window.draw(tloS);   /* maskowanie obwódki  kumunikatu */
		this->_data->window.draw(quitgamesnake);
		this->_data->window.draw(komunikat);
		this->_data->window.draw(nie);
		this->_data->window.draw(tak);
		this->_data->window.draw(pewien);
		

		this->_data->window.display();
	}

}