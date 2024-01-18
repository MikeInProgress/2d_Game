#pragma once
#ifndef Bullet_H
#define Bullet_H

#include "Classes.h"
class Interceptor;
#include "Interceptor.h"
class Game;
#include "Game.h"


class Bullet : public sf::CircleShape {

	static sf::Texture Bullet_textuire;
	static unsigned int size_of_bulllet;

	unsigned int frames = 6 * 3;
	float speed_of_bullet = 3;

	Interceptor* interceptor;

	bool kill = false;


	Bullet(const sf::Vector2f& vec, Interceptor* inter);

	void update(Game& game);

	bool collTest();

	virtual ~Bullet();

};


#endif // !Bullet_H





