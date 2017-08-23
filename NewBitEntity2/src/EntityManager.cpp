#include "EntityManager.h"
using namespace std;
using namespace nb;

Entity * nb::EntityManager::addEntity( Entity&& entity )
{
	entitiesList.push_back( std::move( entity ) );

	Entity* en = &entitiesList.back();
	if( !en->getInitStatus() )
		throw std::logic_error( "cannot add uninitialized Entity to world" );

	s_entityAdded.call( en );
	s_entityCountChanged.call( getEntityCount() );

	return en;
}

std::vector<Entity*> nb::EntityManager::addEntities( std::vector<Entity>&& entities )
{
	std::vector<Entity*> retVal;

	for( auto& el : entities )
		retVal.push_back( addEntity( move( el ) ) );

	return retVal;
}

void nb::EntityManager::removeEntity( Entity * entity )
{
	s_beforeEntitiesRemoved.call( {entity} );

	bool gotRemoved = false;

	entitiesList.remove_if( [&] ( auto& el ){
		if( entity == &el )
		{
			gotRemoved = true;
			return true;
		}
		return false;
	} );

	if( !gotRemoved )
		throw std::logic_error( "An Entity that is not registered was marked for removal." );

	s_entityCountChanged.call( getEntityCount() );
}

void nb::EntityManager::removeEntities( std::vector<Entity*> toRemove )
{
	if( toRemove.size() > 0 )
		s_beforeEntitiesRemoved.call( toRemove );

	entitiesList.remove_if( [&] ( auto& el ){
		for( auto it = toRemove.begin(); it != toRemove.end(); ++it )
		{
			if( *it == &el )
			{
				toRemove.erase( remove( toRemove.begin(), toRemove.end(), &el ), toRemove.end() );
				return true;
			}
		}
		return false;
	} );

	if( toRemove.size() != 0 )
		throw std::logic_error( "An Entity that is not registered was marked for removal." );

	s_entityCountChanged.call( getEntityCount() );
}

std::vector<Entity> nb::EntityManager::removeEntities_move( std::vector<Entity*> entities )
{
	std::vector<Entity> retVal;

	if( entities.size() > 0 )
		s_beforeEntitiesRemoved.call( entities );

	entitiesList.remove_if( [&] ( auto& el ){
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

	return retVal;
}

std::size_t nb::EntityManager::getEntityCount() const
{
	return entitiesList.size();
}
