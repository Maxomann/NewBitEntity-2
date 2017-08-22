#pragma once
#include "stdafx.h"

namespace nb
{
	class World;

	class System
	{
	public:
		using UpdatePriotity = int;

	private:
		const UpdatePriotity updatePriority;

	public:
		DLL_EXPORT System( UpdatePriotity updatePriority = 0 );
		DLL_EXPORT System( const System& system ) = delete;
		DLL_EXPORT System( System&& system ) = delete;
		DLL_EXPORT virtual ~System() = default;

		virtual void preInit( World* world ) = 0;
		virtual void init() = 0;
		virtual void update() = 0;

		DLL_EXPORT virtual UpdatePriotity getUpdatePriority()const;
	};

	/*
		virtual void preInit( World* world ) override;
		virtual void init() override;
		virtual void update() override;
	*/
}
