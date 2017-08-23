#include "World.h"
using namespace std;

nb::World::World()
	: EntityManager(), SystemManager()
{}

void nb::World::update()
{
	updateSystems();
}
