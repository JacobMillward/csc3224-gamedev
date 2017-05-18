#include "ScoreSystem.h"
#include "Components/Tag.h"
#include "World.h"


ScoreSystem::ScoreSystem(World& w): ISystem(w), playerEntity(nullptr), highScore(-200)
{
	world_->enableDebugText(true);
	world_->DebugText.setCharacterSize(24);
	world_->DebugText.setFillColor(sf::Color::Black);
	world_->DebugText.setPosition(10, 10);
	world_->DebugText.setString("HighScore:");
}


ScoreSystem::~ScoreSystem()
{
}

void ScoreSystem::step(const sf::Time& dt)
{
	/* Grab a reference to the player */
	if (!playerEntity)
	{
		auto list = this->world_->getEntityManager().getComponentList(ComponentType::TAG);
		for (auto pair : *list)
		{
			auto component = static_cast<Tag*>(pair.first);
			if (component->getTag() == "player")
			{
				playerEntity = pair.second;
				break;
			}
		}
	}

	auto playerHeight = playerEntity->getSprite()->getPosition().y;
	auto score = baseline - playerHeight;
	if (score > highScore)
	{
		highScore = score;
	}

	if(playerEntity->getComponent<Tag>()->getTag() != "dead")
	{
		std::stringstream ss;
		ss << "Highscore: " << highScore << endl << "Height: " << floor(-playerHeight + baseline);
		world_->DebugText.setString(ss.str());
	}
	
}
