#include "EntityManager.h"
using namespace std;
using namespace nb;

std::vector<Entity*> nb::EntityManager::addEntities( std::vector<Entity>&& entities )
{
	std::vector<Entity*> retVal;

	for( auto& el : entities )
	{
		if( !el.getInitStatus() )
			throw std::logic_error( "cannot add uninitialized Entity to world" );

		entitiyList.push_back( move( el ) );
		retVal.push_back( &entitiyList.back() );
	}

	s_entitiesAdded.call( retVal );
	s_entityCountChanged.call( getEntityCount() );

	return retVal;
}

std::vector<Entity> nb::EntityManager::removeEntities( std::vector<Entity*> entities )
{
	std::vector<Entity> retVal;

	if( entities.size() > 0 )
	{
		s_beforeEntitiesRemoved.call( entities );

		entitiyList.remove_if( [&] ( auto& el ){
			for( auto it = entities.begin(); it != entities.end(); ++it )
			{
				if( *it == &el )
				{
					entities.erase( remove( entities.begin(), entities.end(), &el ), entities.end() );
					retVal.push_back( move( el ) );
					return true;
				}
			}
			return false;
		} );

		if( entities.size() != 0 )
			throw std::logic_error( "An Entity that is not registered was marked for removal." );

		s_entityCountChanged.call( getEntityCount() );
	}

	return retVal;
}

std::size_t nb::EntityManager::getEntityCount() const
{
	return entitiyList.size();
}
