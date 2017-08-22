#include "System.h"
using namespace std;
using namespace nb;

System::System( UpdatePriotity updateOrder )
	: m_updateOrder( updateOrder )
{
}

System::UpdatePriotity nb::System::getUpdatePriority() const
{
	return m_updateOrder;
}
