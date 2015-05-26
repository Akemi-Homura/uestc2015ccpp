#include "MultiplayerStage.hpp"
#include "Sound.hpp"
#include "Hero2.hpp"
#include "Font.hpp"

extern sf::Clock gameClock;

MultiplayerStage::MultiplayerStage(sf::RenderWindow& window) : Stage(window)
{
	m_sendCounter = 0;
	m_hero2 = new Hero2();
	addEntity(m_hero2);
	m_hero->setId(-1);
	m_hero2->setId(-2);
	m_scoreText.setPosition(screenWidth / 2 - 50, 5);
	m_hpText.setPosition(10, 0);
	m_hp2Text.setFont(Font::getFont());
	m_hp2Text.setCharacterSize(30);
	m_hp2Text.setColor(heartColor);
	m_hp2Text.setStyle(sf::Text::Bold);
	m_hp2Text.setPosition(screenWidth - m_hpText.getLocalBounds().width - 10, 0);
}

MultiplayerStage::~MultiplayerStage()
{

}

void MultiplayerStage::init()
{
	m_isHeroFire = false;
	m_isHeroLeft = false;
	m_isHeroRight = false;
	m_isHeroUp = false;
	m_isHeroDown = false;
	m_isHero2Fire = false;
	m_isHero2Left = false;
	m_isHero2Right = false;
	m_isHero2Up = false;
	m_isHero2Down = false;
	m_score = 0;
	m_bombCount = 0;
	m_isRunning = true;
	m_scoreText.setString("Score: 0");
	setHpText(heroHp);
	setHp2Text(heroHp);
	m_gameStatus = Playing;
	((Hero*)m_hero)->revive();
	((Hero2*)m_hero2)->revive();
	m_hero->setPosition(screenWidth / 4, m_hero->getPosition().y);
	m_hero2->setPosition(screenWidth / 4 * 3, m_hero->getPosition().y);
	gameClock.restart();
	for (int i = 0; i < 3; ++i)
	{
		m_enemyClock[i].restart();
	}
	m_ufoClock.restart();
	for (std::vector<Entity*>::iterator it = m_entitys.begin(); it != m_entitys.end(); ++it)
	{
		if ((*it) != m_hero && (*it) != m_hero2)
		{
			delete *it;
			m_entitys.erase(it);
			it--;
		}
	}
	Sound::playGameMusicSound();
}

void MultiplayerStage::setHpText(int hp)
{
	if (hp < 0)
	{
		hp = 0;
	}
	wchar_t heartString[heroHp + 1];
	for (int i = 0; i < hp; ++i)
	{
		heartString[i] = L'♥';
	}
	heartString[hp] = 0;
	m_hpText.setString(heartString);
}

void MultiplayerStage::setHp2Text(int hp)
{
	if (hp < 0)
	{
		hp = 0;
	}
	wchar_t heartString[heroHp + 1];
	for (int i = 0; i < hp; ++i)
	{
		heartString[i] = L'♥';
	}
	heartString[hp] = 0;
	m_hp2Text.setString(heartString);
	m_hp2Text.setPosition(screenWidth - m_hpText.getLocalBounds().width - 10, 0);
}

void MultiplayerStage::draw()
{
	Stage::draw();
	m_window.draw(m_hp2Text);
}

bool MultiplayerStage::isOver()
{
	return !m_hero->isAlive() && !m_hero2->isAlive();
}