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
	auto root = ReadFileToJsonValue(filePath);
	if (root.size() > 0)
	{
		//For each entity
		for (auto jsonValue : root)
		{
			Entity::buildFromJson(entityManager, physicsSystem, jsonValue);
		}
	}
}

void FileLoader::WriteEntitiesToFile(EntityManager& entityManager, string filePath, bool readable)
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

	//Create json writer and write to string
	std::string string;
	if (readable)
	{
		Json::StyledWriter writer;
		string = writer.write(root);
	}
	else
	{
		Json::FastWriter writer;
		string = writer.write(root);
	}

	//Write to file
	outFile << string;
	//cleanup
	outFile.close();
}

Json::Value FileLoader::ReadFileToJsonValue(std::string filePath)
{
	ifstream ifs(filePath);
	string content((istreambuf_iterator<char>(ifs)),
		(istreambuf_iterator<char>()));

	Json::Value root;
	Json::Reader reader;

	if (!reader.parse(content, root))
	{
		cout << "Failed to load file" << endl;
	}

	return root;
}
