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

//Operator Overloads

Vector2 Vector2::operator+(  const Vector2 &_rhs)
{
	return Vector2( x + _rhs.x,	y + _rhs.y);
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
	//Dont want to divide by zero
	if ( Math::isZero(_rhs.x)  ||  Math::isZero(_rhs.y)  )
	{
		cout << endl << "ERROR: DIVIDING BY ZERO!!: " << _rhs;
	}

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
	if ( Math::isZero(_rhs.x)  ||   Math::isZero(_rhs.y)  )
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
	return xy != _rhs;
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

	if ( Math::isZero(fMagnitude) )
		fMagnitude = 1.0f;

	xy /= fMagnitude;

}


//GetNormalization
Vector2 Vector2::GetNormalization() 
{
	float fMagnitude = Magnitude();

	if ( Math::isZero(fMagnitude) )
		fMagnitude = 1.0f;

	return Vector2(this->xy / fMagnitude);

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

	if( Math::isZero(magA) || Math::isZero(magB) || Math::isZero(magC) )
		return 0;

	return acosf( Dot(_rhs) / (magA * magB)  );

}

//Find the angle between in Degrees
float Vector2::AngleBetweenDegrees( Vector2 const &_rhs)
{
	Vector2 c = xy - _rhs;

	float magA = Magnitude();
	float magB = _rhs.Magnitude();
	float magC = c.Magnitude();

	if( Math::isZero(magA) || Math::isZero(magB) || Math::isZero(magC) )
		return 0;

	float resultInRadians = acosf( Dot(_rhs) / (magA * magB)  );

	return Math::RadiansToDegrees(resultInRadians) ;

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
	if ( Math::isZero(x) )
		x = 0.0f;
	if ( Math::isZero(y) )
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
	if ( Math::isZero(x) )
		x = 0.0f;
	if ( Math::isZero(y) )
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
	if ( Math::isZero(x) )
		x = 0.0f;
	if ( Math::isZero(y) )
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
	if ( Math::isZero(x) )
		x = 0.0f;
	if ( Math::isZero(y) )
		y = 0.0f;

}


//Negate the vector
void Vector2::Negate() 
{
	xy *= -1;
}

//Reflect the Vector of the coinciding vector
void Vector2::Reflect( Vector2 _rhs)
{
	if ( Math::isZero( Dot( _rhs ) )) 
	{
		Negate();
	}
	else
	{
		Vector2 normRhs;
		normRhs = _rhs.GetNormalization();
		float result = Dot(normRhs);
		result *= 2.0f;

		normRhs *= result;

		
		xy = normRhs - xy;

	}


}


//Get the Normalization of the passed in Vector
Vector2 Normalize( Vector2 _vector )
{
	float fMagnitude = _vector.Magnitude();

	if ( isZero(fMagnitude) )
		fMagnitude = 1.0f;

	return Vector2(_vector.xy / fMagnitude);
}







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

	if( Math::isZero(magA) || Math::isZero(magB) || Math::isZero(magC) )
		return 0;

	float resultInRadians = acosf( Dot(_lhs,_rhs) / (magA * magB)  );

	return RadiansToDegrees(resultInRadians) ;


}

float AngleBetweenRadians(Vector2 const &_lhs, Vector2 const &_rhs)
{
	Vector2 c = _lhs - _rhs;

	float magA = _lhs.Magnitude();
	float magB = _rhs.Magnitude();
	float magC = c.Magnitude();

	if( Math::isZero(magA) || Math::isZero(magB) || Math::isZero(magC) )
		return 0;

	float resultInRadians = acosf( Dot(_lhs,_rhs) / (magA * magB)  );

	return resultInRadians;


}







