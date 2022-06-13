
#include "Denerwuje.h"

#include <iostream>

using namespace sf;

namespace Tomo
{
	Denerwuje::Denerwuje(GameDataRef data) : _data(data)
	{

		this->_data->assets.LoadTexture("Snake Texture", SNAKE_FILEPATH);
		denerwuje.setTexture(this->_data->assets.GetTexture("Snake Texture"));
		denerwuje.setTextureRect(sf::IntRect{ PIC_SIZE * (rand() % 2), 0, PIC_SIZE, PIC_SIZE });
		denerwuje.setPosition(Denerwuje::chooseRandPos());
	}

	sf::Vector2f Denerwuje::chooseRandPos() const
	{
		return sf::Vector2f{ (float)((rand() % 26) * (float)(PIC_SIZE)) +10, (float)((rand() % 19) * (float)(PIC_SIZE))+30 };
	}


	void Denerwuje::DrawFruit()
	{
		this->_data->window.draw(this->denerwuje);
	}
	
	void Denerwuje::UpdateFriut()
	{
		denerwuje.setPosition(Denerwuje::chooseRandPos());
		denerwuje.setTextureRect(sf::IntRect{ PIC_SIZE * (rand() % 2), 0, PIC_SIZE, PIC_SIZE });
	}
	

}