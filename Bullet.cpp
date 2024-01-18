#include "Bullet.h"


unsigned int Bullet::size_of_bulllet = 10;
sf::Texture Bullet::Bullet_textuire;

Bullet::Bullet(const sf::Vector2f& vec, Interceptor* inter) : sf::CircleShape() {
	this->setRadius(static_cast<float>(Bullet::size_of_bulllet));
	this->setOrigin(static_cast<float>(Bullet::size_of_bulllet), static_cast<float>(Bullet::size_of_bulllet));
	this->setTexture(&Bullet::Bullet_textuire);
	this->frames = Bullet::Bullet_textuire.getSize().y / Bullet::size_of_bulllet;

	this->setPosition(vec.x, vec.y);
	this->interceptor = inter;
	this->setScale(0.5f, 0.5f);
}


void Bullet::update(Game& game) {
	int tempSpeed = static_cast<int>(this->speed_of_bullet);

	if (game.hasFocus() && sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		for (int i = 1; i <= tempSpeed + 2; i++)
		{
			this->move(1, 0);
			if (this->collTest()) break;
		}

	}
	else if (game.hasFocus() && sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		this->move(this->speed_of_bullet - 2, static_cast<float>(rand() % 5 - 2));
		this->collTest();
	}
	else
	{
		this->move(this->speed_of_bullet, 0.f);
		this->collTest();
	}

	int top = (this->getTextureRect().top + Bullet::size_of_bulllet) % (this->frames * Bullet::size_of_bulllet);
	this->setTextureRect(sf::IntRect(0, top, static_cast<int>(Bullet::size_of_bulllet), static_cast<int>(Bullet::size_of_bulllet)));

}

bool Bullet::collTest() {
	/*for (auto i = Game::Rocks.begin(); i != Game::Rocks.end(); i++)
	{
		return true;
	}
	return false;*/
	return false;

}

Bullet::~Bullet() {}
