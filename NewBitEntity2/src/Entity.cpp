#include "Entity.h"
using namespace std;
using namespace nb;

Entity::Entity( Entity&& entity )
{
	components = move( entity.components );
	isInit = move( entity.isInit );
}

void nb::Entity::init()
{
	if( isInit )
	{
		throw std::logic_error( "Entity is already initialized" );
	}
	else
	{
		// init components
		for( auto& el : components )
			el.second->preInit( this );
		for( auto& el : components )
			el.second->init();

		isInit = true;
	}
}

bool nb::Entity::getInitStatus() const
{
	return isInit;
}
