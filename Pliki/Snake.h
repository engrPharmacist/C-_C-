#pragma once


#include <SFML/Graphics.hpp>

#include "DEFINITIONS.hpp"
#include "Game.hpp"
#include "Friutt.h"
#include "Kolizje.h"
#include "zasady.h"

namespace Tomo
{
	
	struct bodyStatus
	{
	public:
		sf::Sprite _sprite;
		eDirection _direction;
		
	};
	

	class Snake
	{
	public:
		sf::Texture m_texture;

		Snake(GameDataRef data);


		//SNAKE 1
		void keyboardInput1();
		void Update(float deltaTime,int score1, int score2);//przenosi do GameOverState
		void UpdateDenerwuje(float deltaTime, int score1, int score2);//przenosi do GameOverDenerwujeState
		void DrawSnake(float deltaTime);
		void AddTail();
		//SNAKE 2 
		void keyboardInput2();
		
		
		void updateTail();
		int getTailLength() const { return m_length; }
		const sf::Vector2f& getBodyPos(int i) { return m_body[i]._sprite.getPosition(); }

		int SnakeMove(sf::Vector2f& ,eDirection&, float deltaTime);


		sf::Vector2f GetPosition() { return m_body[HEAD_OF_SNAKE]._sprite.getPosition(); }

		
		Collider GetCollider() { return Collider(m_body[0]._sprite); }

		void SetPos();

		void Stop();

		void WczytajPozycje();

		void RedTexture();

		void ZapiszWynik(int _score1,int _score2);
		
		
		
	private:
		
		
		struct bodyStatus m_body[200];
		int m_length = 1;
		float StepSize=30.0f;
		sf::Vector2f V;

		int _score1, _score2;
		class Fruit* Fruit1;
		//pauza
		Zasady* zasady;

		int Ax, Ay, Bx, By;

		GameDataRef _data;
	};
}
