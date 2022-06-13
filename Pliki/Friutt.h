#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

#include "DEFINITIONS.hpp"
#include "Game.hpp"
#include "Kolizje.h"
#include "Snake.h"

namespace Tomo
{
	

	class Fruit
	{
	public:
		sf::Texture m_texture;

		Fruit(GameDataRef data);


		sf::Vector2f chooseRandPos() const;
		void DrawFruit();
		void UpdateFriut();


		sf::Vector2f GetPosition() { return body.getPosition(); }

		class Collider GetCollider() { return Collider(body); }

	private:

		sf::Sprite body;




		GameDataRef _data;
	};
}