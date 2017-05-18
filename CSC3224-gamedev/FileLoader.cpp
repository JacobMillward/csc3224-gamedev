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
			auto entity = entityManager.createEntity(Sprite::buildFromJson(jsonValue["Sprite"]));
			//Loop though components
			for (auto jsonComponent : jsonValue["Components"])
			{
				auto type = jsonComponent.get("ComType", -1).asInt();
				if (type < 0)
				{
					cout << "Invalid component type" << endl;
					break;
				}
				auto comType = static_cast<ComponentType>(type);

				//Build component based on type
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
						component = PhysicsBody::buildFromJson(jsonComponent, &physicsSystem, entity->getSprite());
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
				if (component)
				{
					entity->addComponent(*component);
				}
			}
		}
	}
}

void FileLoader::WriteEntitiesToFile(EntityManager& entityManager, string filePath)
{
	Json::Value root;
	auto max = entityManager.getMaxIdUsed();

	for (uint32_t i = 0; i < max; ++i)
	{
		//We can't guarantee that every id is mapped to an entity; an entity might have been deleted and ids are not pooled.
		//Therefore we have to check
		auto comList = entityManager.getComponentList(i);
		if (comList)
		{
			Json::Value entityJson;
			for (auto component : *comList)
			{
				//If sprite, set mandatory field
				if (component->getType() == ComponentType::SPRITE)
				{
					entityJson["Sprite"] = component->toJson();
				}
				//Otherwise add to components array
				else
				{
					entityJson["Components"].append(component->toJson());
				}
			}
			root.append(entityJson);
		}
	}

	//Open file for writing
	ofstream outFile;
	//We want to overwrite any existing file
	outFile.open(filePath, ios::trunc);
	//Create json fast writer and write to string
	Json::FastWriter fast;
	auto string = fast.write(root);
	//Write to file
	outFile << string;
	//cleanup
	outFile.close();
}
