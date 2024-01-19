 

#include "Game.h"

std::vector<Rock> Game::Rocks;
sf::Vertex Game::stars[2000];
sf::Clock Game::clock;
sf::Font Game::Font;
Game::Game() {
    
}

Game::Game(sf::String title) : sf::RenderWindow(sf::VideoMode(1120, 630,32), title) {
    this->setActive(true);
    this->setFramerateLimit(60);
    this->setVerticalSyncEnabled(true);

    this->setPosition(sf::Vector2i(0,0));
    this->setKeyRepeatEnabled(false);

    this->end_credits.setFont(Font);
    this->end_credits.setPosition(1120/6,630/3);
    this->end_credits.setCharacterSize(30);
    this->end_credits.setFillColor(sf::Color::White);
    this->end_credits.setStyle(sf::Text::Bold);

    this->Time_max = sf::seconds(90);

    this->Time_past.setFont(Font);
    this->Time_past.setPosition(100, 100);
    this->Time_past.setCharacterSize(24);
    this->Time_past.setFillColor(sf::Color(0xffffffff));

    

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(1, 3500000);
    int Random_number = distr(gen);

    if ((Random_number % 2) == 0)
    {
        std::cout << "%2 = " << Random_number << std::endl;
        this->Background_Tx.loadFromFile("D:/Projects/game/2D/img/Space_1.png");
    }
    else
    {
        std::cout << "Else = " << Random_number << std::endl;
        this->Background_Tx.loadFromFile("D:/Projects/game/2D/img/Space_2.png");
    }

    this->Background.setTexture(&(this->Background_Tx));
    this->Background.setPosition(0, 0);
    this->Background.setSize(sf::Vector2f(1120,630));

    for (int i = 0; i < 2000; i++)
    {

       Game::stars[i].position = sf::Vector2f(static_cast<float>(distr(gen)%1120), static_cast<float>(distr(gen)%630));
       std::cout <<"Numer i : " << i << ", " << distr(gen) % 1120 << " " << distr(gen) % 630 << std::endl;
       if (not(Random_number % 2))
       {
           Game::stars[i].color = sf::Color(155, 155, 155, 255);
       }
       else
       {
           Game::stars[i].color = sf::Color(0, 0, 0, 255);
       }

    }






}

 void Game::updateRockGame(Game& game)
{
    Rock* rock;
    for (auto i = Game::Rocks.begin(); i != Game::Rocks.end(); i++)
    {
        rock = &(*i);
        if (rock->kill || rock->getPosition().x < 0 || rock->getPosition().y < -50 || rock->getPosition().y > 680)
        {
            Game::Rocks.erase(i);
            i--;
            continue;
        }
        rock->update();
        game.draw(*rock);
    }
}


Game::~Game() {
    
}

void Game::run() {
    Font.loadFromFile("D:/Projects/game/2D/raleway/Raleway-Heavy.ttf");
    Set_Window(this->getSystemHandle());



    sf::Time Time_Start_game = Game::clock.getElapsedTime();
    sf::Time tick = sf::microseconds(0);
    sf::Time pausedTime;

    sf::Event E;
    sf::Transform Move;
    Interceptor ship;

    unsigned cage=0;

    while (this->isOpen())
    {
        if (ship.HP > 0 && this->Time_max.asSeconds() <= 0)
        {
            ship.points = ship.points + ship.HP * 2;
            ship.HP = 0;
            ship.destory = false;
        }

        while (this->pollEvent(E)) 
        {
            if (E.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) this->close();
            if (E.type == sf::Event::KeyPressed && E.key.code == sf::Keyboard::P)
            {
                this->pause = (this->pause) ? false : true;
                
                
            }
            if (!this->pause) ship.catchEvents(E);

           


        }

        if (this->pause)
        {

            this->clear(sf::Color(0x3c3c3cff));
            this->draw(this->Background);
            this->buffor.str("");
            this->Time_past.setString("clik p to start");
            this->draw(this->Time_past);
            this->display();

            Game::clock.restart();

            pausedTime = this->Time_max;
           
            continue;
        }
       
        
            
       
        if (ship.HP > 0 && !(rand()%20) )
        {
            Game::Rocks.push_back(Rock());
        }

       
       
    




        
       
        this->clear(sf::Color(0xffffffffff));
        this->draw(this->Background);
       

       this->draw(Game::stars, 1000, sf::PrimitiveType::Points);
       for (int i = 0; i < 1000; i++)
        {
         Game::stars[i].position.x -= (i % 5 + 1);
        
         if (Move.transformPoint(Game::stars[i].position).x <= 0)
         {
             Game::stars[i].position = sf::Vector2f(1120, Game::stars[i].position.y);
         }
        }

       if (ship.HP > 0)
       {
           Game::updateRockGame(*this);
       }
       else
       {
           this->end_game(&ship);
       }

       ship.paint(*this);

       this->buffor.str("");
       this->buffor.clear();
       this->buffor << "w,s -> move, a,d -> firemode, space -> shoot   ";

       if (ship.HP > 0)
       {
           this->buffor << "Pozostalo : " << static_cast<int>(this->Time_max.asSeconds()) << " sekund.";
           
       }
       this->buffor << ship.bullets.size() << ship.maxBullers << " bullets";

       this->Time_past.setString(this->buffor.str());

       this->buffor.str("");
       this->buffor.clear();

       this->draw(this->Time_past);


       sf::sleep(sf::milliseconds(10));
        this->display();

        if(!this->pause)   this->Time_max = pausedTime - Game::clock.getElapsedTime();

        tick = Game::clock.getElapsedTime() - Time_Start_game;
        if (tick.asMilliseconds() >= 1000)
        {
            std::cout << "k/s : " << cage << std::endl;
            Time_Start_game = Game::clock.getElapsedTime();
            cage = 0;
        }
        cage++;

    }
}



/*
bool Game::is_Point_Inside_Polygone(std::vector <sf::Vector2f>& points, const sf::Vector2f& vec)
{

}

bool Game::is_Point_Inside_Polygone(const sf::Transform& trans, std::vector <sf::Vector2f>& points, const sf::Vector2f& vec)
{

}
*/





















void Game::end_game(Interceptor* interceptor) {
    this->buffor << "Wynik = " << interceptor->points << " pkt";
    this->end_credits.setString(this->buffor.str());
    this->buffor.str("");
    this->buffor.clear();
    this->draw(this->end_credits);
    
}

void Game::startconsole()
{
    std::stringstream buffer;
    buffer << "Konsola" << time(0);
    std::string String = buffer.str();

    std::wstring Temporary_sring = std::wstring(String.begin(), String.end());

    LPCWSTR API_wc = Temporary_sring.c_str();
    HWND API_handle = GetConsoleWindow();

    SetWindowText(API_handle, API_wc);
    SetWindowPos(API_handle,HWND_TOPMOST,0,0,1120,630,SWP_NOMOVE);


}

void Game::Set_Window(HWND pointer_API)
{
    RECT rect;
    GetWindowRect(pointer_API, &rect);
    SetWindowPos(pointer_API, HWND_TOPMOST, rect.left, rect.top, rect.right, rect.bottom, SWP_NOMOVE);
    SetWindowLong(pointer_API, GWL_EXSTYLE, GetWindowLong(pointer_API, GWL_EXSTYLE) | WS_EX_LAYERED);
    SetLayeredWindowAttributes(pointer_API, 0x000000, 0xff, LWA_ALPHA);
}












