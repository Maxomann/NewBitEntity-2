#pragma once
#include "stdafx.h"
#include "Entity.h"

namespace nb
{
	class EntityManager
	{
		std::list<Entity> entitiyList;

	public:
		//entities must be initialized
		DLL_EXPORT std::vector<Entity*> addEntities( std::vector<Entity>&& entities );

		DLL_EXPORT std::vector<Entity> removeEntities( std::vector<Entity*> entities );

		DLL_EXPORT std::size_t getEntityCount()const;

		smartsignals::Signal<void( const std::vector<Entity*>& )> s_entitiesAdded;
		smartsignals::Signal<void( const std::vector<Entity*>& )> s_beforeEntitiesRemoved;
		smartsignals::Signal<void( std::size_t )> s_entityCountChanged;
	};
}
