#pragma once
#include <src/World.h>
#include <iostream>

class TestSystem : public nb::System
{
public:
	virtual void preInit( nb::World* world ) override;
	virtual void init() override;
	virtual void update() override;
};
