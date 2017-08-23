#include "TestComponent.h"
#include <iostream>
using namespace nb;
using namespace std;

void TestComponent::preInit( nb::Entity * entity )
{
	cout << "TestComponent::preInit" << endl;
}

void TestComponent::init()
{
	cout << "TestComponent::init" << endl;
}
