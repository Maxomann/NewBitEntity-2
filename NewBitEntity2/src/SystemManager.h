#pragma once
#include "stdafx.h"
#include "System.h"

namespace nb
{
	class World;

	class SystemManager
	{
		std::unordered_map<std::type_index, std::unique_ptr<System>> systems;
		std::vector<System*> systemsByUpdateOrder;

		bool isInit = false;

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
			const auto typeIndex = std::type_index( typeid( T ) );

			if( isInit )
				throw std::logic_error( "Cannot add Systems after SystemManager has been initialized. SystemName: "s + typeIndex.name() );

			auto system = std::make_unique<T>();

			auto insertResult = systems.insert( std::make_pair( typeIndex, std::move( system ) ) );
			if( !insertResult.second )
			{
				throw std::logic_error( "Cannot register the same System more than once. SystemName: "s + typeIndex.name() );
			}
			auto systemPointer = (T*) insertResult.first->second.get();

			systemsByUpdateOrder.push_back( systemPointer );
			return systemPointer;
		};

		template < class T >
		T* getSystem()const
		{
			const auto typeIndex = std::type_index( typeid( T ) );
			try
			{
				return (T*) systems.at( typeIndex ).get();
			}
			catch( std::out_of_range )
			{
				throw std::logic_error( "System does not exist. SystemName: "s + typeIndex.name() );
			}
		};

		DLL_EXPORT void initSystems();
	};
}
