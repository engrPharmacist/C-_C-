#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
//#include "Animation.hpp" 
//#include "Collider.hpp"
#include "DEFINITIONS.hpp"
#include "Game.hpp"
#include "Kolizje.h"
#include "Snake.h"

namespace Tomo
{
	
	class Denerwuje
	{
	public:
		sf::Texture m_texture;

		Denerwuje(GameDataRef data);


		sf::Vector2f chooseRandPos() const;
		void DrawFruit();
		void UpdateFriut();

		

		sf::Vector2f GetPosition() { return denerwuje.getPosition(); }

		class Collider GetCollider() { return Collider(denerwuje); }

	private:

	
		sf::Sprite  denerwuje;




		GameDataRef _data;
	};
}
