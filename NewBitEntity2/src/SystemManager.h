#pragma once
#include "stdafx.h"
#include "System.h"

namespace nb
{
	class World;

	class SystemManager
	{
		std::unordered_map<std::type_index, std::unique_ptr<System>> m_systems;
		std::vector<System*> m_systemsByUpdateOrder;

		bool m_isInit = false;

		bool m_isSorted = false;
		void sortSystemsByUpdateOrder();

	protected:
		void updateSystems();

	public:
		SystemManager() = default;
		SystemManager( const SystemManager& ) = delete;
		SystemManager( SystemManager&& ) = default;
		~SystemManager() = default;

		template < class T >
		T* addSystem()
		{
			auto system = std::make_unique<T>();

			const auto typeIndex = std::type_index( typeid(T) );

			if (m_isInit)
				throw std::logic_error( "Cannot add Systems after SystemManager has been initialized. SystemName: "s + typeIndex.name() );

			auto insertResult = m_systems.insert( std::make_pair( typeIndex, std::move( system ) ) );
			if (!insertResult.second)
			{
				throw std::logic_error("Cannot register the same System more than once. SystemName: "s + typeIndex.name());
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
				throw std::logic_error("System does not exist. SystemName: "s + typeIndex.name());
			}
		};

		DLL_EXPORT void initSystems();
	};
}
