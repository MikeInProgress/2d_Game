#pragma once
#ifndef Game_H
#define Game_H

#include "Classes.h"
class Rock;
#include "Rock.h"
class Interceptor;
#include "Interceptor.h"

//--------------------------
class Game : public sf::RenderWindow {
public:

	static sf::Clock clock;
	sf::Time Time_max;

	static std::vector <Rock> Rocks;
	static sf::Vertex stars[2000];

	static sf::Font font;
	sf::Text end_credits;
	sf::Text Time_past;

	sf::Texture Background_Tx;
	sf::RectangleShape Background;
	static sf::Font Font;
	bool pause = true;

	std::stringstream buffor;

	Game();
	Game(sf::String);


	void run();
	void end_game(Interceptor*);

	static void startconsole();
	static void Set_Window(HWND pointer_API);

	static bool is_Point_Inside_Polygone(std::vector <sf::Vector2f>&, const sf::Vector2f&);
	static bool is_Point_Inside_Polygone(const sf::Transform&, std::vector <sf::Vector2f>&, const sf::Vector2f&);

	static void updateRockGame(Game&);
	virtual ~Game();



};

#endif 




