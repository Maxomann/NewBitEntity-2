#include <iostream>

#include <src\World.h>

#include "TestComponent.h"
#include "TestSystem.h"

using namespace std;
using namespace nb;

int main()
{
	World world;
	world.addSystem<TestSystem>();

	Entity myEntity;
	myEntity.addComponent<TestComponent>();
	myEntity.init();

	std::vector<Entity> addThese;
	addThese.push_back( move( myEntity ) );
	auto myEntitiesRef = world.addEntities( move( addThese ) );

	world.update();
	world.update();
	world.update();

	world.removeEntities( myEntitiesRef );

	world.update();

	system( "pause" );

	return 0;
}
