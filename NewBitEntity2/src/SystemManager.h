#pragma once
#include "stdafx.h"
#include "System.h"

namespace nb
{
	class World;

	class SystemManager
	{
		World* r_world;

		std::unordered_map<std::type_index, std::unique_ptr<System>> m_systems;
		std::vector<System*> m_systemsByUpdateOrder;

		bool m_isInit = false;

		bool m_isSorted = false;
		void sortSystemsByUpdateOrder();

	protected:
		void updateSystems();

	public:
		SystemManager( World& world );

		template < class T >
		T* addSystem()
		{
			auto system = std::make_unique<T>();

			system->linkToWorld( r_world );
			if (m_isInit)
				system->init();

			const auto typeIndex = std::type_index( typeid(T) );

			auto insertResult = m_systems.insert( std::make_pair( typeIndex, std::move( system ) ) );
			if (!insertResult.second)
			{
				throw std::logic_error("Cannot register the same System more than once. Name: "s + typeIndex.name());
			}
			auto systemPointer = (T*)insertResult.first->second.get();

			m_systemsByUpdateOrder.push_back( systemPointer );
			m_isSorted = false;
			return systemPointer;
		};

		template < class T >
		T* getSystem()const
		{
			const auto typeIndex = std::type_index( typeid(T) );
			try
			{
				return (T*)m_systems.at( typeIndex ).get();
			}
			catch (std::out_of_range)
			{
				throw std::logic_error("System does not exist. Typename: "s + typeIndex.name());
			}
		};

		template < class T >
		void removeSystem()
		{
			const auto typeIndex = std::type_index( typeid(T) );
			try
			{
				auto& system = m_systems.at( typeIndex );
				system->destroy();
				m_systemsByUpdateOrder.erase(
					std::remove( m_systemsByUpdateOrder.begin(),
								 m_systemsByUpdateOrder.end(),
								 system.get() )
				);
				m_systems.erase( typeIndex );
			}
			catch (std::out_of_range)
			{
				throw std::logic_error("System does not exist. Typename: "s + typeIndex.name());
			}
		};

		DLL_EXPORT void initSystems();
	};
}
