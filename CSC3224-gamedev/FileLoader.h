#pragma once
#include "json/json.h"
#include "EntityManager.h"

class PhysicsSystem;

class FileLoader
{
public:
	~FileLoader();

	static void LoadEntitiesFromFile(EntityManager& entityManager, PhysicsSystem& physicsSystem, std::string filePath);
};

