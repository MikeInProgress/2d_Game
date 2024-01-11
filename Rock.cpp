#include "Rock.h"

 sf::Texture Rock::Rock_Texture;
 sf::Texture Rock::Rock_Texture_boost;

Rock::Rock() : sf::ConvexShape() {

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(1, 3500000);
    
	int points_of_Rock = distr(gen) % 5 + 3;

    this->boost = (! (distr(gen) ) % 20) ? true : false;

    this->setPointCount(points_of_Rock);
    this->speed_of_Rocks = distr(gen) % 7 + 1;

    float angle = 360.f / points_of_Rock;

    if (! this->boost)
    {
        this->setTexture(& Rock::Rock_Texture);
    }
    else
    {
        this->setTexture(& Rock::Rock_Texture_boost);
    }

    this->setPosition(sf::Vector2f(static_cast < float>(1120 + 150), static_cast<float>((distr(gen) % (630 - 50) + 25))));

    sf::Transform rotate = sf::Transform::Identity;
    float center_X = this->getPosition().x;
    float center_Y = this->getPosition().y;

    this->setPoint(0, sf::Vector2f(center_X,center_Y+100/(1 + this->speed_of_Rocks)));

    this->verterx_of_Rocks.push_back(this->getPoint(0));

    for (int nr = 1; nr < points_of_Rock; nr++)
    {
        this->setPoint(nr, rotate.transformPoint(this->getPoint(nr - 1)));
        this->verterx_of_Rocks.push_back(this->getPoint(nr));
    }


    this->setOrigin(center_X, center_Y);

    this->rotate(distr(gen) % 180);
    this->rot = distr(gen) % 5 - 2;
};

void Rock::update() {

    if (this->hit)
    {
        if (this->getPointCount() > 3)
        {
            this->setPointCount(this->getPointCount() - 1);
            this->verterx_of_Rocks.pop_back();

            this->move(50, 0);
            this->speed_of_Rocks = this->speed_of_Rocks * 1.2;
            this->direction = rand() % 7 - 3;
        }
        else
        {
            this->kill = true;
        }
        this->hit = false;
    }

    this->setPosition(this->getPosition().x - this->speed_of_Rocks, this->getPosition().y + this->direction);
    this->rotate(this->rot);

}

Rock::~Rock() {}