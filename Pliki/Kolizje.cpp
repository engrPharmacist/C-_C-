#include "kolizje.h"
#include <cmath>
#include <iostream>




namespace Tomo
{
	Collider::Collider(sf::Sprite& body) :body(body)
	{

	}

	bool Collider::CheckCollision(Collider& other)
	{
		//std::cout << "Fruit POS" << other.GetPosition().x << " , " << other.GetPosition().y << std::endl;


		sf::Vector2f delta(this->GetPosition() - other.GetPosition());//okreœla ró¿nice odleg³oœci  

		sf::Vector2f halfSize(PIC_SIZE, PIC_SIZE);//okreœla wielkoœæ obiektów  


		if (abs(delta.x) - halfSize.x < 0 && abs(delta.y) - halfSize.y < 0)
		{
			return true;
		}
		return false; 
	}
}
