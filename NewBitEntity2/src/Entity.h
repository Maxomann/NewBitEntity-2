#pragma once
#include "stdafx.h"
#include "Component.h"

namespace nb
{
	class Entity
	{
		std::map<std::type_index, std::unique_ptr<Component>> m_components;
		bool isInit = false;

	public:
		DLL_EXPORT Entity() = default;
		DLL_EXPORT Entity( const Entity& entity ) = delete;
		DLL_EXPORT Entity( Entity&& entity );

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

			auto insertResult = m_components.insert( std::make_pair( typeIndex, std::move( component ) ) );
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
				return (T*) m_components.at( typeIndex ).get();
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
			auto result = m_components.find( typeIndex );
			if( result != m_components.end() )
				return (T*) result->second.get();
			else
				return nullptr;
		};

		template < class T >
		void removeComponent()
		{
			const std::type_index typeIndex( typeid( T ) );
			try
			{
				auto& component = m_components.at( typeIndex );
				m_components.erase( typeIndex );
			}
			catch( std::out_of_range )
			{
				std::logic_error( "Component does not exist. Typename: "s + typeIndex.name() );
			}
		};

		/* must be called before Entity is added to world. init is supposed to set up the entity *internally* only */
		DLL_EXPORT void init();

		DLL_EXPORT bool getInitStatus()const;
	};
}
