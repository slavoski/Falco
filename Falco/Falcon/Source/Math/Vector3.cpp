#include "../stdafx.h"
#include "Vector3.h"

#include "Math.h"



//If they pass in no variables
Vector3::Vector3() : x(0.0f), y(0.0f)
{

}

//if they pass in two unique variables
Vector3::Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z)
{
}

//if they pass in one variable
Vector3::Vector3(float _xyz) : x(_xyz), y(_xyz), z(_xyz) 
{
}


Vector3::~Vector3(void)
{
}

//Operator Overloads

Vector3 Vector3::operator+(  const Vector3 &_rhs)
{
	return Vector3( x + _rhs.x,	y + _rhs.y, z + _rhs.z);
}

Vector3 Vector3::operator-( const Vector3 &_rhs) const
{
	return Vector3( x - _rhs.x, y - _rhs.y, z - _rhs.z );
}

Vector3 Vector3::operator*( const Vector3 &_rhs)
{
	return Vector3( x * _rhs.x, y * _rhs.y, z * _rhs.z  );
}

Vector3 Vector3::operator/( const Vector3 &_rhs)
{
	//Dont want to divide by zero
	if ( Math::isZero(_rhs.x)  ||  Math::isZero(_rhs.y) || Math::isZero(_rhs.z)  )
	{
		cout << endl << "ERROR: DIVIDING BY ZERO!!: " << _rhs;
		throw  "ERROR: DIVIDING BY ZERO!!: ", _rhs;
	}

	return Vector3( x / _rhs.x, y / _rhs.y, z / _rhs.z );
}


void Vector3::operator+= ( const Vector3 &_rhs)
{
	x += _rhs.x;
	y += _rhs.y;
	z += _rhs.z;
}

void Vector3::operator-= ( const Vector3 &_rhs)
{
	x -= _rhs.x;
	y -= _rhs.y;
	z -= _rhs.z;

}


void Vector3::operator*= ( const Vector3 &_rhs)
{
	x *= _rhs.x;
	y *= _rhs.y;
	z *= _rhs.z;

}

void Vector3::operator/= ( const Vector3 &_rhs)
{
	//Dont want to divide by zero
	if ( Math::isZero(_rhs.x)  ||   Math::isZero(_rhs.y) || Math::isZero(_rhs.z)  )
	{
		cout << endl << "ERROR: DIVIDING BY ZERO!!: " << _rhs;
		throw "ERROR: DIVIDING BY ZERO!!: ",  _rhs;
	}

	x /= _rhs.x;
	y /= _rhs.y;
	z /= _rhs.z;
	
}



//Used to access an element in the vector
float& Vector3::operator[] (unsigned int _index)
{
	if (_index == 0)
		return x;
	else if (_index == 1)
		return y;
	else if (_index == 2)
		return z;
	else 
		cout << "\nERROR! Vector3 Index is invalid: " << _index << endl;
		throw ("ERROR! Vector3 Index is invalid:");
}

//Compares Two vectors and returns true if they are equal
bool Vector3::operator== (Vector3 const &_rhs)
{
	return (xyz == _rhs);
}

//Compares Two Vectors and returns true if they are not equal
bool Vector3::operator!= (Vector3 const &_rhs)
{
	return xyz != _rhs;
}

//Sets this equal to the right hand side vector
Vector3 Vector3::operator=  (Vector3 const &_rhs)
{
	return xyz = _rhs.xyz;
}
	
//Normalize's this
void Vector3::Normalize()
{
	float fMagnitude = Magnitude();

	if ( Math::isZero(fMagnitude) )
		fMagnitude = 1.0f;

	xyz /= fMagnitude;

}


//GetNormalization
Vector3 Vector3::GetNormalization() 
{
	float fMagnitude = Magnitude();

	if ( Math::isZero(fMagnitude) )
		fMagnitude = 1.0f;

	return Vector3(xyz / fMagnitude);

}


//Find the magnitude
float Vector3::Magnitude() const
{
	return sqrtf( (x * x) + (y * y) + (z * z) );
}

//Find the dot Product
float Vector3::Dot(Vector3 const &_rhs)
{
	return ((x * _rhs.x) + (y * _rhs.y) + (z * _rhs.z));
}

//Fimd the angle between in Radians
float Vector3::AngleBetweenRadians( Vector3 const &_rhs)
{
	Vector3 c = xyz - _rhs;

	float magA = Magnitude();
	float magB = _rhs.Magnitude();
	float magC = c.Magnitude();

	if( Math::isZero(magA) || Math::isZero(magB) || Math::isZero(magC) )
		return 0;

	return acosf( Dot(_rhs) / (magA * magB)  );

}

//Find the angle between in Degrees
float Vector3::AngleBetweenDegrees( Vector3 const &_rhs)
{
	Vector3 c = xyz - _rhs;

	float magA = Magnitude();
	float magB = _rhs.Magnitude();
	float magC = c.Magnitude();

	if( Math::isZero(magA) || Math::isZero(magB) || Math::isZero(magC) )
		return 0;

	float resultInRadians = acosf( Dot(_rhs) / (magA * magB)  );

	return Math::RadiansToDegrees(resultInRadians) ;

}


//Rotate the vector with Radians
void Vector3::RotateAboutOriginRadians(float _radians)
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
void Vector3::RotateAboutOriginDegrees(float _degrees)
{
	//Convert to Radians
	float radians = Math::DegreesToRadians(_degrees);
	
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
void Vector3::RotateAroundPointRadians(float _radians, Vector3 _point )
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
void Vector3::RotateAroundPointDegrees(float _degrees, Vector3 _point )
{
	
	float radians = Math::DegreesToRadians(_degrees);
	
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
void Vector3::Negate() 
{
	xyz *= -1;
}

//Reflect the Vector of the coinciding vector
void Vector3::Reflect( Vector3 _rhs)
{
	if ( Math::isZero( Dot( _rhs ) )) 
	{
		Negate();
	}
	else
	{
		Vector3 normRhs;
		normRhs = _rhs.GetNormalization();
		float result = Dot(normRhs);
		result *= 2.0f;

		normRhs *= result;

		
		xyz = normRhs - xyz;

	}


}


//Get the Normalization of the passed in Vector
Vector3 Normalize( Vector3 _vector )
{
	float fMagnitude = _vector.Magnitude();

	if (Math::isZero(fMagnitude) )
		fMagnitude = 1.0f;

	return Vector3(_vector.xyz / fMagnitude);
}






std::ostream& operator<<(ostream &output, const Vector3 &vector )
{
	return output << "( " << vector.x << ", " << vector.y << ", " << vector.z << " )" << std::endl;
}
	
float Dot(Vector3 const &_lhs, Vector3 const &_rhs)
{
	return ((_lhs.x * _rhs.x) + (_lhs.y * _rhs.y) + (_lhs.z * _rhs.z));
}

//Find the angle between
float AngleBetweenDegrees(Vector3 const &_lhs, Vector3 const &_rhs)
{
	Vector3 c = _lhs - _rhs;

	float magA = _lhs.Magnitude();
	float magB = _rhs.Magnitude();
	float magC = c.Magnitude();

	if( Math::isZero(magA) || Math::isZero(magB) || Math::isZero(magC) )
		return 0;

	float resultInRadians = acosf( Dot(_lhs,_rhs) / (magA * magB)  );

	return Math::RadiansToDegrees(resultInRadians) ;


}

float AngleBetweenRadians(Vector3 const &_lhs, Vector3 const &_rhs)
{
	Vector3 c = _lhs - _rhs;

	float magA = _lhs.Magnitude();
	float magB = _rhs.Magnitude();
	float magC = c.Magnitude();

	if( Math::isZero(magA) || Math::isZero(magB) || Math::isZero(magC) )
		return 0;

	float resultInRadians = acosf( Dot(_lhs,_rhs) / (magA * magB)  );

	return resultInRadians;


}







