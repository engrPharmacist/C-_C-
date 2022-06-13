#pragma once

#include <sstream>
#include "SplashState.hpp"
#include "DEFINITIONS.hpp"
#include "MainMenuState.hpp"

#include <iostream>

namespace Tomo
{
	SplashState::SplashState(GameDataRef data) : _data(data)
	{

	}

	void SplashState::Init()
	{
		this->_data->assets.LoadTexture("Splash State Background", SPLASH_SCENE_BACKGROUND_FILEPATH);

		logo.setTexture(this->_data->assets.GetTexture("Splash State Background"));
		logo.setPosition(270.f, 200.f);
	}

	void SplashState::HandleInput()
	{
		sf::Event event;

		while (this->_data->window.pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
			{
				this->_data->window.close();
			}
		}
	}

	void SplashState::Update(float dt)
	{
		if (this->_clock.getElapsedTime().asSeconds() > SPLASH_STATE_SHOW_TIME)
		{
			// Switch To Main Menu
			this->_data->machine.AddState(StateRef(new MainMenuState(_data)), true);
		}
	}

	void SplashState::Draw(float dt)
	{
		this->_data->window.clear(sf::Color::Transparent);

		this->_data->window.draw(logo);

		this->_data->window.display();
	}

}