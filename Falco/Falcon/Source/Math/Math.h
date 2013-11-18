#ifndef MATH_H
#define MATH_H


namespace Math
{

	//TODO SW Move to correct lib
	const float Epsilon = 0.00001f;
	const float	PI	    = 3.141592f;



	//Check if the value is zero
	//TODO put somewhere better
	bool isZero(float _Value );
	float RadiansToDegrees( float _rad );
	float DegreesToRadians( float _deg );

}

#endif