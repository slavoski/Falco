#include "../stdafx.h"
#include "Math.h"

namespace Math
{

	bool isZero(float _Value)
	{
		return ( (_Value < Epsilon) && (_Value > -Epsilon ) );
	}

	float RadiansToDegrees( float _rad )
	{
		return _rad * 180 / PI;
	}

	float DegreesToRadians( float _deg )
	{
		return _deg * PI / 180;
	}

}
