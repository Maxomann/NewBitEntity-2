#include "SystemManager.h"

void nb::SystemManager::sortSystemsByUpdateOrder()
{
	if (!m_isSorted)
	{
		std::sort( m_systemsByUpdateOrder.begin(), m_systemsByUpdateOrder.end(), [&]( const System* lhs, const System* rhs ) {
			return lhs->getUpdatePriority() < rhs->getUpdatePriority();
		} );
		m_isSorted = true;
	}
}

void nb::SystemManager::updateSystems()
{
	sortSystemsByUpdateOrder();
	for (auto& el : m_systemsByUpdateOrder)
		el->update();
}

void nb::SystemManager::initSystems()
{
	if (m_isInit)
	{
		throw std::logic_error("SystemManager is already initialized");
	}
	for (auto& el : m_systems)
	{
		el.second->init();
	}
	m_isInit = true;
}
