#pragma once
#include "stdafx.h"
#include "Component.h"

namespace nb
{
	class Entity
	{
		std::map<std::type_index, std::unique_ptr<Component>> components;
		bool isInit = false;

	public:
		DLL_EXPORT Entity() = default;
		DLL_EXPORT Entity( const Entity& entity ) = delete;
		DLL_EXPORT Entity( Entity&& entity ) = default;

		// T must inherit from Component
		template < class T, class ... Args >
		T* addComponent( Args&& ... args )
		{
			auto component = std::make_unique<T>( ( std::forward<Args>( args ) )... );
			if( isInit )
			{
				component->preInit( this );
				component->init();
			}

			const std::type_index typeIndex( typeid( T ) );

			auto insertResult = components.insert( std::make_pair( typeIndex, std::move( component ) ) );
			if( !insertResult.second )
			{
				throw std::logic_error( "Cannot register the same Component more than once. Name: "s + typeIndex.name() );
			}
			return static_cast<T*>( insertResult.first->second.get() );
		};

		template < class T >
		T* getComponent()const
		{
			const std::type_index typeIndex( typeid( T ) );
			try
			{
				return (T*) components.at( typeIndex ).get();
			}
			catch( std::out_of_range )
			{
				throw std::logic_error( "Component does not exist. Typename: "s + typeIndex.name() );
			}
		};

		template < class T >
		T* getComponent_try()const
		{
			const std::type_index typeIndex( typeid( T ) );
			auto result = components.find( typeIndex );
			if( result != components.end() )
				return (T*) result->second.get();
			else
				return nullptr;
		};

		/* must be called before Entity is added to world. init is supposed to set up the entity *internally* only */
		DLL_EXPORT void init();

		DLL_EXPORT bool getInitStatus()const;
	};
}
