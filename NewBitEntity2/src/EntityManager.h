#pragma once
#include "stdafx.h"
#include "Entity.h"

namespace nb
{
	class EntityManager
	{
		std::list<Entity> entitiesList;

	public:
		//entity must be initialized
		DLL_EXPORT Entity* addEntity( Entity&& entity );
		//entities must be initialized
		DLL_EXPORT std::vector<Entity*> addEntities( std::vector<Entity>&& entities );

		DLL_EXPORT void removeEntity( Entity* entity );
		DLL_EXPORT void removeEntities( std::vector<Entity*> entity );

		DLL_EXPORT std::vector<Entity> removeEntities_move( std::vector<Entity*> entities );

		DLL_EXPORT std::size_t getEntityCount()const;

		smartsignals::Signal<void( Entity* )> s_entityAdded;
		smartsignals::Signal<void( const std::vector<Entity*>& )> s_beforeEntitiesRemoved;
		smartsignals::Signal<void( std::size_t )> s_entityCountChanged;
	};
}
