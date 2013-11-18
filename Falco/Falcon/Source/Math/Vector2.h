#ifndef VECTOR2_H
#define VECTOR2_H


#include "Math.h"
using namespace Math;


class Vector2
{
private:
	//used to be able to pass any value in
	template< int a, int b >
	class swizzle
	{
	private:
		//Allows access to the vector's values
		float m_fComponents[2];



	public:
		//Operator Overloads
		Vector2& operator=( const Vector2 &_rhs )
		{

			m_fComponents[a] = _rhs.x;
			m_fComponents[b] = _rhs.y;

			return *(Vector2*)this;
		}

		Vector2& operator+=( const Vector2 &_rhs )
		{
			m_fComponents[a] += _rhs.x;
			m_fComponents[b] += _rhs.y;

			return *(Vector2*)this;
		}

		Vector2& operator-=( const Vector2 &_rhs )
		{
			m_fComponents[a] -= _rhs.x;
			m_fComponents[b] -= _rhs.y;

			return *(Vector2*)this;
		}

		Vector2& operator*=( const Vector2 &_rhs )
		{
			m_fComponents[a] *= _rhs.x;
			m_fComponents[b] *= _rhs.y;

			return *(Vector2*)this;
		}


		Vector2& operator/=( const Vector2 &_rhs )
		{
			if ( !Math::isZero(_rhs.x) )
				m_fComponents[a] /= _rhs.x;

			if ( !Math::isZero(_rhs.y) )
				m_fComponents[b] /= _rhs.y;


			return *(Vector2*)this;
		}

		Vector2 operator+(  const Vector2 &_rhs)
		{
			return Vector2( m_fComponents[a] + _rhs.x,	m_fComponents[b] += _rhs.y);
		}

		Vector2 operator-( const Vector2 &_rhs)
		{
			return Vector2( m_fComponents[a] - _rhs.x, m_fComponents[b] - _rhs.y );
		}

		Vector2 operator*( const Vector2 &_rhs)
		{
			return Vector2( m_fComponents[a] * _rhs.x, m_fComponents[b] * _rhs.y );
		}

		Vector2 operator/( const Vector2 &_rhs)
		{
			if ( Math::isZero(_rhs.x)  ||  Math::isZero(_rhs.y)  )
				cout << endl << "ERROR: DIVIDING BY ZERO!!: " << _rhs;


			return Vector2( m_fComponents[a] / _rhs.x, m_fComponents[b] / _rhs.y );
		}


		//Compares Two vectors and returns true if they are equal
		bool operator== (Vector2 const &_rhs)
		{
			return ((m_fComponents[a] == _rhs.x ) && (m_fComponents[b] == _rhs.y)); 
		}

		//Compares Two Vectors and returns true if they are not equla
		bool operator!= (Vector2 const &_rhs)
		{
			return ((m_fComponents[a] != _rhs.x ) || (m_fComponents[b] != _rhs.y)); 
		}


		//Allows you to invoke the vector without actually calling it
		operator Vector2()
		{
			return Vector2( m_fComponents[a], m_fComponents[b] );
		}



	};



public:

	//Constructors
	Vector2();
	Vector2(float _x, float _y);
	Vector2(float _xy);



	//Destructor
	~Vector2();


	//Overloading the operators

	//Returns the result of two vectors added
	Vector2 operator+( const Vector2 &_rhs);

	//Returns the result of two vectors subtracted
	Vector2 operator-( const Vector2 &_rhs) const;

	//Returns the result of two vectors multiplied
	Vector2 operator*( const Vector2 &_rhs);

	//Returns the result of two vectors divided
	Vector2 operator/( const Vector2 &_rhs);

	//Adds the right hand side vector to this
	void operator+= ( const Vector2 &_rhs);

	//Subtracts the right hand side vector from this
	void operator-= ( const Vector2 &_rhs);

	//Multiplies the right hand side vector to this
	void operator*= ( const Vector2 &_rhs);

	//Divides the right hand side vector from this
	void operator/= ( const Vector2 &_rhs);

	//Used to access an element in the vector
	float&  operator[] (unsigned int _index);

	//Compares Two vectors and returns true if they are equal
	bool    operator== (Vector2 const &_rhs);

	//Compares Two Vectors and returns true if they are not equla
	bool    operator!= (Vector2 const &_rhs);

	//Sets this equal to the right hand side vector
	Vector2 operator=  (Vector2 const &_rhs);

	

	//Normalize's this
	void Normalize();

	//GetNormalization
	Vector2 GetNormalization();

	//Find the magnitude
	float Magnitude() const;

	//Find the dot Product
	float Dot(Vector2 const &_rhs);

	//Find the angle between in Radians
	float AngleBetweenRadians( Vector2 const &_rhs);

	//Find the angle between in Degrees
	float AngleBetweenDegrees( Vector2 const &_rhs);

	//Rotate the vector with Radians
	void RotateAboutOriginRadians(float _radians);

	//Rotate the vector with Degrees
	void RotateAboutOriginDegrees(float _degrees);

	//Rotate around Vector with Radians
	void RotateAroundPointRadians(float _radians, Vector2 _point );

	//Rotate around Vector with Degrees
	void RotateAroundPointDegrees(float _degrees, Vector2 _point );

	//Negate the vector
	void Negate() ;

	//Reflect the Vector of the coinciding vector
	void Reflect( Vector2 _rhs);

	//Variables
	//The X and Y of the Vector
	union
	{

		struct
		{
			//Allowing the user to use x or r
			union 
			{
				float x;
				float r;

			};

			//Allowing the user to use y or g
			union
			{
				float y;
				float g;
			};

		};

		//Setting what value is getting passed into the swizzle depending on xy etc.
		swizzle<0,1> xy;
		swizzle<1,0> yx;

		swizzle<0,1> rg;
		swizzle<1,0> gr;


	};

};



//Allow you to print out the values in the vector
std::ostream& operator<<(ostream &output, const Vector2 &vector );

//Find the dot Product
float Dot(Vector2 const &_lhs, Vector2 const &_rhs);

//Find the angle between in Radians
float AngleBetweenRadians(Vector2 const &_lhs, Vector2 const &_rhs);

//Find the angle between in Radians
float AngleBetweenDegrees(Vector2 const &_lhs, Vector2 const &_rhs);

//Get the Normalization of the passed in Vector
Vector2 Normalize( Vector2 _vector );



#endif // !VECTOR2_H

