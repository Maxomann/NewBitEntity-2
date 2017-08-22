#include "System.h"
using namespace std;
using namespace nb;

System::System( UpdatePriotity updatePriority )
	: updatePriority( updatePriority )
{
}

System::UpdatePriotity nb::System::getUpdatePriority() const
{
	return updatePriority;
}
