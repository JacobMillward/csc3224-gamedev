#include "Program.h"
#include "EntityManager.h"

Program::Program()
{
}


Program::~Program()
{
	EntityManager::destroyInstance();
}

SystemManager * Program::getSystemManager()
{
	return new SystemManager();
}

void Program::processInput()
{
}

void Program::update()
{
}

int main() {
	Program *game = new Program();

	while (game->isRunning()) {
		game->getSystemManager()->doUpdates();
		game->processInput();
		game->update();
	}
}