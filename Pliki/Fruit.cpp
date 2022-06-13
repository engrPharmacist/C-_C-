
#include "Friutt.h"
//#include "snake.h"
#include <iostream>

using namespace sf;

namespace Tomo
{
	Fruit::Fruit(GameDataRef data) : _data(data)
	{

		this->_data->assets.LoadTexture("Snake Texture", SNAKE_FILEPATH);
		body.setTexture(this->_data->assets.GetTexture("Snake Texture"));
		body.setTextureRect(sf::IntRect{ PIC_SIZE * (rand() % 2), 0, PIC_SIZE, PIC_SIZE });
		body.setPosition(Fruit::chooseRandPos());
	}

	sf::Vector2f Fruit::chooseRandPos() const//randowoma pozycja owocu 
	{
		return sf::Vector2f{ (float)((rand() % 26) * (float)(PIC_SIZE)) +10, (float)((rand() % 19) * (float)(PIC_SIZE)) + 30 };
	}


	void Fruit::DrawFruit()
	{
		this->_data->window.draw(this->body);
	}

	void Fruit::UpdateFriut()//zmienia po³o¿enie owocu, po kolizji ze snakiem 
	{
		body.setPosition(Fruit::chooseRandPos());
		body.setTextureRect(sf::IntRect{ PIC_SIZE * (rand() % 2), 0, PIC_SIZE, PIC_SIZE });
	}


}
