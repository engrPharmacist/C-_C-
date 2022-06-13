
#include <sstream>
#include "DEFINITIONS.hpp"
#include "Zasady.h"
#include "MainMenuState.hpp"
#include "CzyZamknac.h"
#include "GameStateDenerwuje.h"

namespace Tomo
{

	Zasady::Zasady(GameDataRef data) : _data(data)
	{
	}

	void Tomo::Zasady::Init()
	{
		//treœæ zasad
		Zasadyy.setFont(this->_data->assets.GetFont("Main Menu Font Style"));
		Zasadyy.setCharacterSize(24);
		Zasadyy.setString(" --------------------------------------------------------------------------\n Gracze sterujac przypisanymi im konrtolerami w:\n LEWO (<-------)\n PRAWO (------>)\n GORE (^)\n DOL (v)\n Zmieniaja kierunek na deklarowany\n Starajac sie ubiec przeciwnika oraz\n zjesc wiecej jablek od niego \n ------------------------------------------------------------------\n|Wybranie trybu Play Tricky                               |\n| spowoduje dodanie oszukanego jablka       |\n| ktore zamiast dodawac                                      |\n| odejmuje punkty!!!                                               |\n ------------------------------------------------------------------ \n [przycisk F1 pokazuje zasady]");
		Zasadyy.setPosition(20, 50);
		Zasadyy.setFillColor(sf::Color(110, 0, 255));
		//przycisk powrotu
		wroc.setFont(this->_data->assets.GetFont("Main Menu Font Style"));
		wroc.setCharacterSize(24);
		wroc.setString("Wróc do Menu startowego");
		wroc.setPosition(450, 10);
		wroc.setFillColor(sf::Color(0, 110, 0, 255));
		//t³o zasad
		this->_data->assets.LoadTexture("Tlo wybor", WYBOR_GRY_BACKGROUND_FILEPATH);
		tloW.setTexture(this->_data->assets.GetTexture("Tlo wybor"));
		tloW.setPosition(-105.f, 0.f);
	}

	void Tomo::Zasady::HandleInput()
	{
		sf::Event event;

		while (this->_data->window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::MouseButtonPressed:
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					if (wroc.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
					{
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

	void Tomo::Zasady::Update(float dt)
	{
	}

	void Tomo::Zasady::Draw(float dt)
	{
		this->_data->window.clear();
		
		this->_data->window.draw(this->tloW);
		this->_data->window.draw(wroc);
		this->_data->window.draw(Zasadyy);

		this->_data->window.display();
	}

}