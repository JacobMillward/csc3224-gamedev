#include "FileLoader.h"
#include <fstream>
#include <iostream>
#include "Components/Tag.h"


FileLoader::~FileLoader()
{
}

void FileLoader::LoadEntitiesFromFile(EntityManager& entityManager, std::string filePath)
{
	/* INCOMPLETE */
	std::ifstream ifs(filePath);
	std::string content((std::istreambuf_iterator<char>(ifs)),
		(std::istreambuf_iterator<char>()));

	Json::Value root;
	Json::Reader reader;
	
	if(!reader.parse(content, root))
	{
		std::cout << "Failed to load config" << std::endl;
		return;
	}

	if (root.size() > 0)
	{

		//For each entity
		for (Json::ValueIterator itr = root.begin(); itr != root.end(); ++itr) {
			auto entity = entityManager.createEntity(itr.key()["Sprite"]["TextureID"].asString(),
				sf::IntRect(root["Sprite"]["rectTL"].asInt(),
					itr.key()["Sprite"]["rectTR"].asInt(),
					itr.key()["Sprite"]["width"].asInt(),
					itr.key()["Sprite"]["height"].asInt()));
			//Loop though components
			for (auto component : itr.key()) {
				auto type = component.get("Type", "-1").asInt();
				if (type < 0) {
					std::cout << "Invalid component type" << std::endl;
					break;
				}
				auto comType = static_cast<ComponentType>(type);
				switch (comType) {
				case ComponentType::SPRITE: break;
				case ComponentType::TAG: 
					entity->addComponent(*Tag::buildFromJson(component));
					break;
				case ComponentType::PHYSICSBODY: break;
				case ComponentType::AUDIO: break;
				case ComponentType::TYPE_END: break;
				default: ;
				}
			}
		}
	}
}
