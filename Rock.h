#pragma once
#include <SFML/Graphics.hpp>
#include <random>




class Rock : public sf::ConvexShape {

public:

	static sf::Texture Rock_Texture;
	static sf::Texture Rock_Texture_boost;

	float speed_of_Rocks;
	short direction = 0;

	std::vector <sf::Vector2f> verterx_of_Rocks;

	bool hit = false;
	bool kill = false;
	bool boost = false;
	int rot;



	Rock();

	void update();

	virtual ~Rock();

};