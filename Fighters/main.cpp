#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cstdlib>
#include <ctime>
#include "SpriteSheet.hpp"
#include "Background.hpp"
#include "Hero.hpp"
#include "Enemy.hpp"
#include "Global.hpp"
#include "Stage.hpp"

using namespace std;

int main()
{
	srand((int)time(0));
	SpriteSheet::loadFromFile(packPath);
	Background::loadResources();
	Hero::loadResources();
	Enemy::loadResources();
	Bullet::loadResources();
    sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "Fighters");
    window.setSize(sf::Vector2u(360, 600));
    Stage stage(window);
    Background background;
    Hero hero;
    stage.addEntity(&background);
    stage.addEntity(&hero);
    window.setFramerateLimit(60);
    while (window.isOpen())
    {
        sf::Event event;
        if (stage.getGameStatus() == Waiting || stage.getGameStatus() == Over)
		{
			while (window.pollEvent(event))
			{
				switch (event.type)
				{
				case sf::Event::Closed:
					window.close();
					break;
				case sf::Event::KeyPressed:
					stage.play();
					break;
				default:
					break;
				}
			}
		}
		else if (stage.getGameStatus() == Playing)
		{
			while (window.pollEvent(event))
			{
				switch (event.type)
				{
				case sf::Event::Closed:
					window.close();
					break;
				default:
					break;
				}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				hero.moveLeft();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				hero.moveRight();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				hero.fire();
			}
		}
		stage.update();
    }
    return 0;
}
