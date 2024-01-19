#pragma once

#ifndef Interceptor_H
#define Interceptor_H

#include "Classes.h"
class Bullet;
#include "Bullet.h"
class Game;
#include "Game.h"

class Interceptor : public sf::Sprite {
public:

	float Speed_Y = 0;
	float boostSpeed = 4;
	float SpeedCooldown = 50;

	sf::Image skin;
	sf::Texture Texture_of_Skin;

	std::vector <sf::Vector2i> localCollisionPoints_From_Image;

	int HP = 30;
	int HP_MAX = 30;

	sf::RectangleShape HP_Rectangle;

	float HP_Picture = 50;

	//pociski
	std::vector <Bullet> bullets;
	unsigned int maxBullers = 12;

	sf::Text Point_Text;
	sf::Text HP_Text;

	int points = 0;

	std::stringstream buffor;


	bool destory = true;

	sf::Vertex jet[100];

	Interceptor();

	void paint(Game& game);

	void catchEvents(sf::Event& E);

	void update(Game& game);

	void shoot();

	virtual ~Interceptor();





};

#endif // !Interceptor_H






