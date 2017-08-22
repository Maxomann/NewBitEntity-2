#pragma once
#include "stdafx.h"

namespace nb
{
	class Entity;

	class Component
	{
	public:
		DLL_EXPORT Component() = default;
		DLL_EXPORT Component( const Component& component ) = delete;
		DLL_EXPORT Component( Component&& component ) = delete;
		DLL_EXPORT virtual ~Component() = default;

		// Do not store the entity pointer. It may be invalidated through move operations on Entity.
		virtual void preInit( Entity* entity ) = 0;
		virtual void init() = 0;
	};

	/*
		virtual void preInit( Entity* entity )override;
		virtual void init() override;
	*/
}
