#pragma once
#include <SFML/Graphics.hpp>
#include "DEFINITIONS.hpp"

namespace Tomo
{
	class Collider
	{
	public:
		Collider(sf::Sprite& body);

		

		bool CheckCollision(Collider& other);
		sf::Vector2f GetPosition() { return body.getPosition(); }

		sf::Vector2f GetTailPosition() { return body.getPosition(); }
		

	private:
		sf::Sprite& body;

		

	};
}


