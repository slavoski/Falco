#include "../stdafx.h"
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



Vector2 Vector2::operator+(  const Vector2 &_rhs)
{
	return Vector2( x + _rhs.x,	y += _rhs.y);
}

Vector2 Vector2::operator-( const Vector2 &_rhs) const
{


	return Vector2( x - _rhs.x, y - _rhs.y );
}

Vector2 Vector2::operator*( const Vector2 &_rhs)
{
	return Vector2( x * _rhs.x, y * _rhs.y );
}

Vector2 Vector2::operator/( const Vector2 &_rhs)
{
	if ( (_rhs.x < 0.000001 && _rhs.x > -0.000001)  ||   ( _rhs.y < 0.000001 && _rhs.y > -0.000001)  )
		cout << endl << "ERROR: DIVIDING BY ZERO!!: " << _rhs;


	return Vector2( x / _rhs.x, y / _rhs.y );
}

void Vector2::operator+= ( const Vector2 &_rhs)
{
	x += _rhs.x;
	y += _rhs.y;

}

void Vector2::operator-= ( const Vector2 &_rhs)
{
	x -= _rhs.x;
	y -= _rhs.y;

}


void Vector2::operator*= ( const Vector2 &_rhs)
{
	x *= _rhs.x;
	y *= _rhs.y;

}

void Vector2::operator/= ( const Vector2 &_rhs)
{
	//Dont want to divide by zero
	if ( (_rhs.x < 0.000001 && _rhs.x > -0.000001)  ||   ( _rhs.y < 0.000001 && _rhs.y > -0.000001)  )
	{
		cout << endl << "ERROR: DIVIDING BY ZERO!!: " << _rhs;
		return;
	}

	x /= _rhs.x;
	y /= _rhs.y;
	
}



//Used to access an element in the vector
float& Vector2::operator[] (unsigned int _index)
{
	if (_index == 0)
		return x;
	else if (_index == 1)
		return y;
	else 
		cout << "\nERROR! Vector2 Index is invalid: " << _index << endl;
		throw ("ERROR");
}

//Compares Two vectors and returns true if they are equal
bool Vector2::operator== (Vector2 const &_rhs)
{
	return (xy == _rhs);
}

//Compares Two Vectors and returns true if they are not equal
bool Vector2::operator!= (Vector2 const &_rhs)
{
	return xy != _rhs.x;
}

//Sets this equal to the right hand side vector
Vector2 Vector2::operator=  (Vector2 const &_rhs)
{
	return xy = _rhs.xy;
}
	
//Normalize's this
void Vector2::Normalize()
{
	float fMagnitude = Magnitude();

	if ( (fMagnitude > -EPSILON) && (fMagnitude < EPSILON) )
		fMagnitude = 1.0f;

	xy /= fMagnitude;

}

//Find the magnitude
float Vector2::Magnitude() const
{
	return sqrtf( (x * x) + (y * y) );
}

//Find the dot Product
float Vector2::Dot(Vector2 const &_rhs)
{
	return ((x * _rhs.x) + (y * _rhs.y));
}

//Fimd the angle between in Radians
float Vector2::AngleBetweenRadians( Vector2 const &_rhs)
{
	Vector2 c = xy - _rhs;

	float magA = Magnitude();
	float magB = _rhs.Magnitude();
	float magC = c.Magnitude();

	if( isZero(magA) || isZero(magB) || isZero(magC) )
		return 0;

	return acosf( Dot(_rhs) / (magA * magB)  );


		//crap need to find the dif between mag and length
}

//Find the angle between in Degrees
float Vector2::AngleBetweenDegrees( Vector2 const &_rhs)
{
	Vector2 c = xy - _rhs;

	float magA = Magnitude();
	float magB = _rhs.Magnitude();
	float magC = c.Magnitude();

	if( isZero(magA) || isZero(magB) || isZero(magC) )
		return 0;

	float resultInRadians = acosf( Dot(_rhs) / (magA * magB)  );

	return RadianToDegrees(resultInRadians) ;

}


//Rotate the vector with Radians
void Vector2::RotateAboutOriginRadians(float _radians)
{
	//Store the value so when we change it we dont mess up our calculations
	float prevX = x;

	//Calculate the rotation
	x = (cos(_radians) * x ) - (sin(_radians) * y);
	y = (sin(_radians) * prevX ) + (cos(_radians) * y);

	//Set it to zero if its close enough
	if ( isZero(x) )
		x = 0.0f;
	if ( isZero(y) )
		y = 0.0f;

}

//Rotate the vector with Degrees
void Vector2::RotateAboutOriginDegrees(float _degrees)
{
	//Convert to Radians
	float radians = DegreesToRadians(_degrees);
	
	//Store the value so when we change it we dont mess up our calculations
	float prevX = x;

	//Calculate the rotation
	x = ( x * cos(radians) ) - ( y * sin(radians) );
	y = ( prevX  * sin(radians) ) + (y * cos(radians) );

	//Set it to zero if its close enough
	if ( isZero(x) )
		x = 0.0f;
	if ( isZero(y) )
		y = 0.0f;

}


//Rotate around Vector with Radians
void Vector2::RotateAroundPointRadians(float _radians, Vector2 _point )
{
	//Moving the vector to the origin
	float posX = x - _point.x;
	float posY = y - _point.y;

	//Do the calculations and move back in relation to rotation point
	x = ( posX * cos(_radians) ) - ( posY * sin(_radians) ) + _point.x;
	y = ( posX  * sin(_radians) ) + (posY * cos(_radians) ) + _point.y;

	//If its close enough to zero make it zero
	if ( isZero(x) )
		x = 0.0f;
	if ( isZero(y) )
		y = 0.0f;
}

//Rotate around Vector with Degrees
void Vector2::RotateAroundPointDegrees(float _degrees, Vector2 _point )
{
	
	float radians = DegreesToRadians(_degrees);
	
	//Moving the vector to the origin
	float posX = x - _point.x;
	float posY = y - _point.y;

	//Do the calculations and move back in relation to rotation point
	x = ( posX * cos(radians) ) - ( posY * sin(radians) ) + _point.x;
	y = ( posX  * sin(radians) ) + (posY * cos(radians) ) + _point.y;

	//If its close enough to zero make it zero
	if ( isZero(x) )
		x = 0.0f;
	if ( isZero(y) )
		y = 0.0f;

}




//Negate the vector
void Vector2::Negate() 
{
	xy *= -1;
}


//TODO Move to Regular Math
//{
bool isZero(float _Value)
{
	return ( (_Value < EPSILON) && (_Value > -EPSILON ) );
}

float RadianToDegrees( float _rad )
{
	return _rad * 180 / PI;
}

float DegreesToRadians( float _deg )
{
	return _deg * PI / 180;
}

//}



std::ostream& operator<<(ostream &output, const Vector2 &vector )
{
	return output << "( " << vector.x << ", " << vector.y << " )" << std::endl;
}
	
float Dot(Vector2 const &_lhs, Vector2 const &_rhs)
{
	return ((_lhs.x * _rhs.x) + (_lhs.y * _rhs.y));
}

//Find the angle between
float AngleBetweenDegrees(Vector2 const &_lhs, Vector2 const &_rhs)
{
	Vector2 c = _lhs - _rhs;

	float magA = _lhs.Magnitude();
	float magB = _rhs.Magnitude();
	float magC = c.Magnitude();

	if( isZero(magA) || isZero(magB) || isZero(magC) )
		return 0;

	float resultInRadians = acosf( Dot(_lhs,_rhs) / (magA * magB)  );

	return RadianToDegrees(resultInRadians) ;


}

float AngleBetweenRadians(Vector2 const &_lhs, Vector2 const &_rhs)
{
	Vector2 c = _lhs - _rhs;

	float magA = _lhs.Magnitude();
	float magB = _rhs.Magnitude();
	float magC = c.Magnitude();

	if( isZero(magA) || isZero(magB) || isZero(magC) )
		return 0;

	float resultInRadians = acosf( Dot(_lhs,_rhs) / (magA * magB)  );

	return resultInRadians;


}




//Rotate the vector
void Rotate(Vector2 const &vector, float _radians);

