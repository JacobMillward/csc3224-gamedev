#include "FileLoader.h"
#include <fstream>
#include <iostream>
#include "Components/Tag.h"
#include "Components/PhysicsBody.h"
#include "Components/SoundEffect.h"


FileLoader::~FileLoader()
{
}

void FileLoader::LoadEntitiesFromFile(EntityManager& entityManager, PhysicsSystem& physicsSystem, string filePath)
{
	ifstream ifs(filePath);
	string content((istreambuf_iterator<char>(ifs)),
	               (istreambuf_iterator<char>()));

	Json::Value root;
	Json::Reader reader;

	if (!reader.parse(content, root))
	{
		cout << "Failed to load config" << endl;
		return;
	}

	if (root.size() > 0)
	{
		//For each entity
		for (auto jsonValue : root)
		{
			auto entity = entityManager.createEntity(jsonValue["Sprite"]["TextureID"].asString(),
			                                         sf::IntRect(root["Sprite"]["rectTL"].asInt(),
			                                                     jsonValue["Sprite"]["rectTR"].asInt(),
			                                                     jsonValue["Sprite"]["width"].asInt(),
			                                                     jsonValue["Sprite"]["height"].asInt()));
			//Loop though components
			for (auto jsonComponent : jsonValue)
			{
				auto type = jsonComponent.get("ComType", -1).asInt();
				if (type < 0)
				{
					cout << "Invalid component type" << endl;
					break;
				}
				auto comType = static_cast<ComponentType>(type);

				Component* component = nullptr;
				switch (comType)
				{
				case ComponentType::TAG:
					{
						component = Tag::buildFromJson(jsonComponent);
						break;
					}
				case ComponentType::PHYSICSBODY:
					{
						component = PhysicsBody::buildFromJson(jsonComponent);
						break;
					}
				case ComponentType::AUDIO:
					{
						component = SoundEffect::buildFromJson(jsonComponent);
						break;
					}

				//We must have a sprite, so don't bother creating additional ones (undefined behaviour)
				case ComponentType::SPRITE: break;
				case ComponentType::TYPE_END:
				default: ;
				}
				if(component)
				{
					entity->addComponent(*component);
				}
			}
		}
	}
}
