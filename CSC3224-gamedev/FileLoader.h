#pragma once
#include "json/json.h"
#include "EntityManager.h"

class FileLoader
{
public:
	~FileLoader();

	static void LoadEntitiesFromFile(EntityManager& entityManager, std::string filePath);
};

