#pragma once
#include "json/json.h"
#include "EntityManager.h"

class PhysicsSystem;

class FileLoader
{
public:
	~FileLoader();

	static void LoadGameAssetsFromFile(EntityManager& entityManager, PhysicsSystem& physicsSystem, ResourceManager& resourceManager, std::string filePath);
	static void WriteEntitiesToFile(EntityManager& entityManager, std::string filePath, bool readable = true);

	static Json::Value ReadFileToJsonValue(std::string filePath);
};

