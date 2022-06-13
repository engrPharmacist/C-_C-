#pragma once

#include <sstream>
#include "DEFINITIONS.hpp"
#include "MainMenuState.hpp"
#include "GameState.hpp"
#include "game.hpp"
#include "zasady.h"
#include "CzyZamknac.h"
#include "WyborGry.h"

#include <iostream>

namespace Tomo
{
	MainMenuState::MainMenuState(GameDataRef data) : _data(data)
	{

	}

	void MainMenuState::Init()
	{
		//font styleE
		this->_data->assets.LoadFont("Main Menu Font Style", FONT_STYLEE_FILEPATH);

		//font textT
		this->_data->assets.LoadFont("Main Menu Font Text", FONT_TEXTT_FILEPATH);
		

		//t³o
		this->_data->assets.LoadTexture("Tlo Snake", MAIN_MENU_TLO_FILEPATH);
		tloS.setTexture(this->_data->assets.GetTexture("Tlo Snake"));
		tloS.setPosition(-175.f, 0.f);

		//ramka
		ramka.setSize(sf::Vector2f(750.f, 130.f));
		ramka.setPosition(25.f, 430.f);
		ramka.setFillColor(sf::Color(130, 60, 190));
		ramka.setOutlineThickness(15.f);
		ramka.setOutlineColor(sf::Color(0, 86, 0));

		//tekst
		Menu[0].setFont(this->_data->assets.GetFont("Main Menu Font Text"));
		Menu[0].setString("WYBIERZ TRYB GRY");
		Menu[0].setCharacterSize(64);
		Menu[0].setFillColor(sf::Color(124, 158, 2));
		Menu[0].setPosition(130.f, 450.f);
		//Menu[0].setOutlineColor(sf::Color::White);
		//Menu[0].setOutlineThickness(3);
		Menu[0].setOutlineColor(sf::Color(0, 86, 0));
		Menu[0].setOutlineThickness(2);

		Menu[1].setFont(this->_data->assets.GetFont("Main Menu Font Style"));
		Menu[1].setString("Zasady Gry");
		Menu[1].setCharacterSize(24);
		Menu[1].setStyle(sf::Text::Style::Underlined);
		Menu[1].setFillColor(sf::Color::Black);

		Menu[2].setFont(this->_data->assets.GetFont("Main Menu Font Style"));
		Menu[2].setString("Wyjdz z Gry");
		Menu[2].setCharacterSize(24);
		Menu[2].setPosition(650.f, 0.f);
		Menu[2].setStyle(sf::Text::Style::Underlined);
		Menu[2].setFillColor(sf::Color::Black);
		selectedItemIndex = 0;


	}

	void MainMenuState::HandleInput()
	{
		sf::Event event;

		while (this->_data->window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::MouseButtonPressed:
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					if (Menu[0].getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
					{
						this->_data->machine.RemoveState();
						this->_data->machine.AddState(StateRef(new WyborGry(_data)), true);
						break;
					}
					else if (Menu[1].getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
					{
						this->_data->machine.RemoveState();
						this->_data->machine.AddState(StateRef(new Zasady(_data)), true);
						break;
					}
			
					else if (Menu[2].getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
					{
						this->_data->machine.RemoveState();
						this->_data->machine.AddState(StateRef(new CzyZamknac(_data)), true);
						break;
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

	void MainMenuState::Update(float dt)
	{
		
	}

	void MainMenuState::Draw(float dt)
	{
		this->_data->window.clear(sf::Color::Black);

		this->_data->window.draw(this->tloS);
		this->_data->window.draw(this->ramka);

		for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
		{
			this->_data->window.draw(this->Menu[i]);
		}
	

		this->_data->window.display();
	}

}