#pragma once
#include <src/World.h>
#include <iostream>

class TestComponent : public nb::Component
{
public:
	virtual void preInit( nb::Entity* entity )override;
	virtual void init() override;
};
