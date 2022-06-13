#include "Snake.h"
#include "Kolizje.h"
#include "GameOverState.hpp"
#include "CzyZamknac.h"
#include "GameOverDenerwujeState.h"
#include "wyborgry.h"


#include <iostream>

using namespace sf;

namespace Tomo
{
	Snake::Snake(GameDataRef data) : _data(data)
	{

		this->_data->assets.LoadTexture("Snake Texture", SNAKE_FILEPATH);

		this->_data->assets.LoadTexture("Snake Red Texture", SNAKE_RED_FILEPATH);

		m_body[HEAD_OF_SNAKE]._sprite.setTexture(this->_data->assets.GetTexture("Snake Texture"));
		m_body[HEAD_OF_SNAKE]._sprite.setTextureRect(sf::IntRect{ 120, 0, 30, PIC_SIZE });
		m_body[HEAD_OF_SNAKE]._sprite.setPosition(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
		m_body[HEAD_OF_SNAKE]._direction = UP;

		//jab³ko
		Fruit1 = new Fruit(_data);

		//Pauza
		zasady = new Zasady(_data);



		void SetPos();

	}
	void Snake::keyboardInput1()
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			if (m_body[HEAD_OF_SNAKE]._direction != DOWN)
			{
				m_body[HEAD_OF_SNAKE]._direction = UP;
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			if (m_body[HEAD_OF_SNAKE]._direction != LEFT)
			{
				m_body[HEAD_OF_SNAKE]._direction = RIGHT;
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			if (m_body[HEAD_OF_SNAKE]._direction != UP)
			{
				m_body[HEAD_OF_SNAKE]._direction = DOWN;
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			if (m_body[HEAD_OF_SNAKE]._direction != RIGHT)
			{
				m_body[HEAD_OF_SNAKE]._direction = LEFT;
			}
		}
		
	}

	void Snake::Update(float deltaTime, int score1, int score2)
	{
		V.x = 0.0f;
		V.y = 0.0f;


		int status = 1;
		switch (m_body[HEAD_OF_SNAKE]._direction)
		{
		case LEFT:

			V = sf::Vector2f(-30, 0);
			status = Snake::SnakeMove(V, m_body[HEAD_OF_SNAKE]._direction, deltaTime);
			break;


		case RIGHT:

			V = sf::Vector2f(30, 0);
			status = Snake::SnakeMove(V, m_body[HEAD_OF_SNAKE]._direction, deltaTime);
			break;

		case UP:

			V = sf::Vector2f(0, -30);
			status = Snake::SnakeMove(V, m_body[HEAD_OF_SNAKE]._direction, deltaTime);;
			break;

		case DOWN:

			V = sf::Vector2f(0, 30);
			status = Snake::SnakeMove(V, m_body[HEAD_OF_SNAKE]._direction, deltaTime);

			break;
		}
		if (status == 0)
		{
			//if (this->_clock.getElapsedTime().asSeconds() > SPLASH_STATE_SHOW_TIME)
			//{
				// Switch To Main Menu
			//	this->_data->machine.AddState(StateRef(new MainMenuState(_data)), true);
			//}
			this->_data->machine.AddState(StateRef(new GameOverState(_data, score1, score2)), true);
		}

		sf::Vector2f newPos = V + m_body[0]._sprite.getPosition();

	}

	void Snake::UpdateDenerwuje(float deltaTime, int score1, int score2)
	{
		V.x = 0.0f;
		V.y = 0.0f;


		int status = 1;
		switch (m_body[HEAD_OF_SNAKE]._direction)
		{
		case LEFT:

			V = sf::Vector2f(-30, 0);
			status = Snake::SnakeMove(V, m_body[HEAD_OF_SNAKE]._direction, deltaTime);
			break;


		case RIGHT:

			V = sf::Vector2f(30, 0);
			status = Snake::SnakeMove(V, m_body[HEAD_OF_SNAKE]._direction, deltaTime);
			break;

		case UP:

			V = sf::Vector2f(0, -30);
			status = Snake::SnakeMove(V, m_body[HEAD_OF_SNAKE]._direction, deltaTime);;
			break;

		case DOWN:

			V = sf::Vector2f(0, 30);
			status = Snake::SnakeMove(V, m_body[HEAD_OF_SNAKE]._direction, deltaTime);

			break;

		}
		if (status == 0)
		{


			ZapiszWynik(score1, score2);

			this->_data->machine.AddState(StateRef(new GameOverDenerwujeState(_data, score1, score2)), true);
		}

	}
	int Snake::SnakeMove(sf::Vector2f& V, eDirection& direction, float deltaTime)
	{
		sf::Vector2f newPos = V + m_body[0]._sprite.getPosition();

		m_body[HEAD_OF_SNAKE]._direction = direction;
		m_body[HEAD_OF_SNAKE]._sprite.move(V);


		if (newPos.x < 0 || newPos.y < 0 || newPos.x >= SCREEN_WIDTH || newPos.y >= SCREEN_HEIGHT)
		{

			std::cout << "Wyszed³ poza Zakres";
			return 0;			// Prze³acza na Game Over State
		}
		// Sprawdza kolizje z ogonem
		for (int i = 1; i < m_length; ++i)
			if (newPos == m_body[i]._sprite.getPosition())
			{
				std::cout << "head to tail";

				return 0;   // Prze³acza na Game Over State
			}

		WczytajPozycje();//////////////////////////////////////////////KOLIZJA SNAKE ZE ZNAKIEM!!!!!!!!!!!!!!!!!!!!!!!!
		std::cout << Ax << " " << Ay << " " << Bx << " " << By << endl;
		sf::Vector2f Snake1Pos = sf::Vector2f(Ax, Ay);
		for (int i = 1; i <= m_length; ++i)
			if (Snake1Pos == m_body[i + 1]._sprite.getPosition())
			{
				std::cout << "GRACZ 1 WYGRAL";

				return 0;   // Prze³acza na Game Over State
			}
		sf::Vector2f Snake2Pos = sf::Vector2f(Bx, By);
		for (int i = 1; i <= m_length; ++i)
			if (Snake2Pos == m_body[i+1]._sprite.getPosition())
			{
				std::cout << "GRACZ 2 WYGRAL";

				return 0;   // Prze³acza na Game Over State
			}
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		int status = 1;

		return status;
	}

	void Snake::AddTail()
	{
		m_length++;
		std::cout << "UPDATE TAIL";
	}


	void Snake::updateTail()
	{

		if (m_length > 1)
		{
			bodyStatus prev = m_body[1];
			m_body[1]._sprite = m_body[HEAD_OF_SNAKE]._sprite;
			m_body[1]._direction = m_body[HEAD_OF_SNAKE]._direction;


			for (int i = 2; i < m_length; ++i)
			{
				bodyStatus prev2 = m_body[i];
				m_body[i] = prev;
				prev = prev2;
			}
		}
	}
	void Snake::DrawSnake(float deltaTime)
	{

		//  rysuje g³owe snake w zale¿noœci od kierunku 
		switch (m_body[HEAD_OF_SNAKE]._direction)
		{
		case UP:
			m_body[HEAD_OF_SNAKE]._sprite.setTextureRect(sf::IntRect{ 180, 0, 30, PIC_SIZE });
			break;

		case RIGHT:
			m_body[HEAD_OF_SNAKE]._sprite.setTextureRect(sf::IntRect{ 150, 0, PIC_SIZE, 30 });
			break;

		case LEFT:
			m_body[HEAD_OF_SNAKE]._sprite.setTextureRect(sf::IntRect{ 120, 0, PIC_SIZE, 30 });
			break;

		case DOWN:
			m_body[HEAD_OF_SNAKE]._sprite.setTextureRect(sf::IntRect{ 210, 0, 30, PIC_SIZE });
			break;


		}
		this->_data->window.draw(this->m_body[HEAD_OF_SNAKE]._sprite);


		// rysuje ogon snake z uwzglêdnieniem poprzedniej pozycji 
		for (int i = 1; i < m_length; ++i)
		{
			if (m_body[i]._direction == UP || m_body[i]._direction == DOWN)
				m_body[i]._sprite.setTextureRect(sf::IntRect{ 90, 0, 30, PIC_SIZE });
			else
				m_body[i]._sprite.setTextureRect(sf::IntRect{ 60, 0, PIC_SIZE, 30 });


			if (m_body[i - 1]._direction == RIGHT && m_body[i]._direction == UP ||
				m_body[i - 1]._direction == DOWN && m_body[i]._direction == LEFT)
				m_body[i]._sprite.setTextureRect(sf::IntRect{ 240, 0, 30, PIC_SIZE });

			else if (m_body[i - 1]._direction == LEFT && m_body[i]._direction == UP ||
				m_body[i - 1]._direction == DOWN && m_body[i]._direction == RIGHT)
				m_body[i]._sprite.setTextureRect(sf::IntRect{ 270, 0, 30, PIC_SIZE });

			else if (m_body[i - 1]._direction == RIGHT && m_body[i]._direction == DOWN ||
				m_body[i - 1]._direction == UP && m_body[i]._direction == LEFT)
				m_body[i]._sprite.setTextureRect(sf::IntRect{ 300, 0, 30, PIC_SIZE });

			else if (m_body[i - 1]._direction == UP && m_body[i]._direction == RIGHT ||
				m_body[i - 1]._direction == LEFT && m_body[i]._direction == DOWN)
				m_body[i]._sprite.setTextureRect(sf::IntRect{ 330, 0, 30, PIC_SIZE });

			this->_data->window.draw(this->m_body[i]._sprite);
		}
	}




	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void Snake::keyboardInput2()
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			if (m_body[HEAD_OF_SNAKE]._direction != DOWN)
			{
				m_body[HEAD_OF_SNAKE]._direction = UP;
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			if (m_body[HEAD_OF_SNAKE]._direction != LEFT)
			{
				m_body[HEAD_OF_SNAKE]._direction = RIGHT;
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			if (m_body[HEAD_OF_SNAKE]._direction != UP)
			{
				m_body[HEAD_OF_SNAKE]._direction = DOWN;
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			if (m_body[HEAD_OF_SNAKE]._direction != RIGHT)
			{
				m_body[HEAD_OF_SNAKE]._direction = LEFT;
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
		{

			m_body[HEAD_OF_SNAKE]._direction = STOP;

		}
	}

	void Snake::SetPos()
	{
		m_body[HEAD_OF_SNAKE]._sprite.setPosition(sf::Vector2f((SCREEN_WIDTH / 2) - 60, SCREEN_HEIGHT / 2));
	}

	void Snake::ZapiszWynik(int _score1, int _score2)
	{

		ofstream File(WYNIKI_FILE);
		if (File.is_open())
		{
			for (int i = 0; i < 1; i++)
			{
				File << _score1 << endl;
				File << _score2 << endl;
			}
			File.close();
			//cout << "Points Saved properly" << endl;
		}
		else cout << "Unable to open file" << endl;
	}
	void Snake::Stop()
	{
		m_body[HEAD_OF_SNAKE]._direction = STOP;
	}
	void Snake::WczytajPozycje()
	{

		ifstream File1;
		File1.open(POZYCJA_FILE);

		File1 >> Ax;
		File1 >> Ay;
		File1 >> Bx;
		File1 >> By;

		File1.close();

		string line;
		ifstream File;
	}

	void Snake::RedTexture()
	{
		m_body[HEAD_OF_SNAKE]._sprite.setTexture(this->_data->assets.GetTexture("Snake Red Texture"));
	}
}

