#include "MyGame.h"
#include <iostream>
#define MEM_SIZE 1048576000 //1GB

int main()
{
	void* pMem = malloc(MEM_SIZE);
	FreeListAllocator* fListAlloc = new FreeListAllocator(MEM_SIZE, pMem);
	std::cout << sizeof(MyGame) << std::endl;
	MyGame* app = new (fListAlloc->allocate(sizeof(MyGame), 8)) MyGame(fListAlloc);
	app->run();
	fListAlloc->deallocate(app);

	delete fListAlloc;
	free(pMem);
	return 0;
}