#include "SystemManager.h"

void nb::SystemManager::sortSystemsByUpdateOrder()
{
	if( !isInit )
		throw std::logic_error( "Cannot sort Systems after initilaization" );

	std::sort( systemsByUpdateOrder.begin(), systemsByUpdateOrder.end(), [&] ( const System* lhs, const System* rhs ){
		return lhs->getUpdatePriority() < rhs->getUpdatePriority();
	} );
}

void nb::SystemManager::updateSystems()
{
	for( auto& el : systemsByUpdateOrder )
		el->update();
}

void nb::SystemManager::initSystems()
{
	if( isInit )
	{
		throw std::logic_error( "SystemManager is already initialized" );
	}
	for( auto& el : systems )
	{
		el.second->init();
	}
	sortSystemsByUpdateOrder();

	isInit = true;
}
