#include "contact_filter.h"

bool ContactFilter::ShouldCollide(b2Fixture * fixtureA, b2Fixture * fixtureB)
{
	uint16 catA = fixtureA->GetFilterData().categoryBits;
	uint16 maskA = fixtureA->GetFilterData().maskBits;
	uint16 catB = fixtureB->GetFilterData().categoryBits;
	uint16 maskB = fixtureB->GetFilterData().maskBits;
	 
	/*if ((catA & maskB) != 0 && (catB & maskA) != 0)
		return true;
	else
		return false;*/

	return ((catA & maskB) != 0 && (catB & maskA) != 0);
} // !ShouldCollide