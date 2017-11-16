#include "stdafx.h"

void Normalize(float & f1, float & f2)
{
	float temp1 = f1, temp2 = f2;
	f1 = f1 / sqrt(temp1*temp1 + temp2*temp2);
	f2 = f2 / sqrt(temp1*temp1 + temp2*temp2);
}
