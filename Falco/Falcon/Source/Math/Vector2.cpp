#include "../Falcon/Source/stdafx.h"
#include "Vector2.h"


//If they pass in no variables
Vector2::Vector2() : x(0.0f), y(0.0f)
{

}

//if they pass in two unique variables
Vector2::Vector2(float _x, float _y) : x(_x), y(_y)
{
}

//if they pass in one variable
Vector2::Vector2(float _xy) : x(_xy), y(_xy)
{
}


Vector2::~Vector2(void)
{
}




void Vector2::Normalize(void)
{

}

Vector2& Vector2::operator+= ( const Vector2 &rhs)
{
	x += rhs.x;
	y += rhs.y;

	return *this;
}

Vector2& Vector2::operator-= ( const Vector2 &rhs)
{
	x -= rhs.x;
	y -= rhs.y;

	return *this;
}


Vector2& Vector2::operator*= ( const Vector2 &rhs)
{
	x *= rhs.x;
	y *= rhs.y;

	return *this;
}

Vector2& Vector2::operator/= ( const Vector2 &rhs)
{
	//Dont want to divide by zero
	if ( rhs.x > 0.000001 || rhs.x < -0.000001)
		x /= rhs.x;

	//Sanity check
	if ( rhs.y > 0.000001 || rhs.y < -0.000001)
		y /= rhs.y;

	return *this;
}


Vector2& operator+( const Vector2 &lhs, const Vector2 &rhs)
{
	return Vector2( lhs.x + rhs.x, lhs.y + rhs.y );
}

Vector2& operator-(const Vector2 &lhs, const Vector2 &rhs)
{
	return Vector2( lhs.x - rhs.x, lhs.y - rhs.y );
}

Vector2& operator*(const Vector2 &lhs, const Vector2 &rhs)
{
	return Vector2( lhs.x * rhs.x, lhs.y * rhs.y );
}

Vector2& operator/(const Vector2 &lhs, const Vector2 &rhs)
{
	return Vector2( lhs.x / rhs.x, lhs.y / rhs.y );
}


std::ostream& operator<<(ostream &output, const Vector2 &vector )
{
	return output << "( " << vector.x << ", " << vector.y << " )" << std::endl;
}
	
