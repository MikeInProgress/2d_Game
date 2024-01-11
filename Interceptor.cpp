#include "Interceptor.h"
#include <iostream>

Interceptor::Interceptor() : sf::Sprite() {

	this->skin.loadFromFile("D:/Projects/game/2D/img/ship_low.png");

	

	for (unsigned int x = 0; x < this->skin.getSize().x; x++)
	{
		for (unsigned int y = 0; y < this->skin.getSize().y; y++)
		{
			if (this->skin.getPixel(x, y) == sf::Color(237,28,36,255))
			{
				this->localCollisionPoints_From_Image.push_back(sf::Vector2i(x, y));
				this->skin.setPixel(x, y, sf::Color(0xffffff00));
				
			}
			
		}
	}
	for (const auto& point : localCollisionPoints_From_Image) {
		std::cout << "Punkt kolizji: (" << point.x << ", " << point.y << ")" << std::endl;
	}

	this->Texture_of_Skin.loadFromImage(this->skin,sf::IntRect(0,0,this->skin.getSize().x, this->skin.getSize().y));
	this->setTexture(this->Texture_of_Skin);

	this->setOrigin(static_cast<float>(this->skin.getSize().x/2), static_cast<float>(this->skin.getSize().y/2));
	this->setPosition(this->skin.getSize().x * 2, 310);

	this->setTextureRect(sf::IntRect(0,0,this->skin.getSize().x, this->skin.getSize().y));

	

}

Interceptor::~Interceptor(){}


void Interceptor::paint(Game & game)
{
	this->update(game);
	game.draw(* this);
}

void Interceptor::catchEvents(sf::Event & E)
{
	bool move = false;
	if (E.type == sf::Event::KeyPressed && (E.key.code == sf::Keyboard::Up || E.key.code == sf::Keyboard::W))
	{
		this->Speed_Y = -(this->boostSpeed);
		//std::cout << "Up : " << Speed_Y << std::endl;
		
		move = true;
		
	}
	if (E.type == sf::Event::KeyPressed && (E.key.code == sf::Keyboard::Down || E.key.code == sf::Keyboard::S))
	{
		this->Speed_Y = this->boostSpeed;
		//std::cout << " Down : " << Speed_Y << std::endl;
		move = true;
		
	}

}

void Interceptor::update(Game & game)
{

	if (this->getGlobalBounds().top + this->getGlobalBounds().height >= 630)
	{
		this->Speed_Y *= ( - 0.75 );
		std::cout << " 1 " << std::endl;
		
	}

	if (this->getGlobalBounds().top <= 0)
	{
		this->Speed_Y *=  -( 0.75 );
		std::cout << " 2 " << std::endl;
	}

	if (this->Speed_Y > 0)
	{
		this->Speed_Y = std::max(0.f,this->Speed_Y - (this->boostSpeed/this->SpeedCooldown));
		
	}
	else if (Speed_Y < 0)
	{
		this->Speed_Y = std::min(0.f, this->Speed_Y + (this->boostSpeed / this->SpeedCooldown));
	
	}
	
	this->setPosition(this->getPosition().x, this->getPosition().y + this->Speed_Y);

	//std::cout << this->getPosition().y + this->Speed_Y << std::endl;
}

void Interceptor::shoot()
{

}
