#ifndef VECTOR3_H
#define VECTOR3_H

class Vector3
{
private:
	//used to be able to pass any value in
	template< int a, int b, int c >
	class swizzle
	{
	private:
		//Allows access to the vector's values
		float m_fComponents[3];



	public:
		//Operator Overloads
		Vector3& operator=( const Vector3 &_rhs )
		{

			m_fComponents[a] = _rhs.x;
			m_fComponents[b] = _rhs.y;
			m_fComponents[c] = _rhs.z;

			return *(Vector3*)this;
		}

		Vector3& operator+=( const Vector3 &_rhs )
		{
			m_fComponents[a] += _rhs.x;
			m_fComponents[b] += _rhs.y;
			m_fComponents[c] += _rhs.z;

			return *(Vector3*)this;
		}

		Vector3& operator-=( const Vector3 &_rhs )
		{
			m_fComponents[a] -= _rhs.x;
			m_fComponents[b] -= _rhs.y;
			m_fComponents[c] -= _rhs.z;

			return *(Vector3*)this;
		}

		Vector3& operator*=( const Vector3 &_rhs )
		{
			m_fComponents[a] *= _rhs.x;
			m_fComponents[b] *= _rhs.y;
			m_fComponents[c] *= _rhs.z;

			return *(Vector3*)this;
		}


		Vector3& operator/=( const Vector3 &_rhs )
		{
			if ( !Math::isZero(_rhs.x) )
				m_fComponents[a] /= _rhs.x;

			if ( !Math::isZero(_rhs.y) )
				m_fComponents[b] /= _rhs.y;

			if ( !Math::isZero(_rhs.z) )
				m_fComponents[c] /= _rhs.z;

			return *(Vector3*)this;
		}

		Vector3 operator+(  const Vector3 &_rhs)
		{
			return Vector3( m_fComponents[a] + _rhs.x,	m_fComponents[b] += _rhs.y, m_fComponents[c] += _rhs.z);
		}

		Vector3 operator-( const Vector3 &_rhs)
		{
			return Vector3( m_fComponents[a] - _rhs.x, m_fComponents[b] - _rhs.y, m_fComponents[c] - _rhs.z  );
		}

		Vector3 operator*( const Vector3 &_rhs)
		{
			return Vector3( m_fComponents[a] * _rhs.x, m_fComponents[b] * _rhs.y, m_fComponents[c] * _rhs.z );
		}

		Vector3 operator/( const Vector3 &_rhs)
		{
			if ( Math::isZero( _rhs.x )  ||  Math::isZero( _rhs.y) || Math::isZero( _rhs.z )  )
				cout << endl << "ERROR: DIVIDING BY ZERO!!: " << _rhs;
				throw "Error Dividing Vector3";

			return Vector3( m_fComponents[a] / _rhs.x, m_fComponents[b] / _rhs.y, m_fComponents[c] / _rhs.z );
		}


		//Compares Two vectors and returns true if they are equal
		bool operator== (Vector3 const &_rhs)
		{
			return ((m_fComponents[a] == _rhs.x ) && (m_fComponents[b] == _rhs.y) && (m_fComponents[c] == _rhs.z) ); 
		}

		//Compares Two Vectors and returns true if they are not equla
		bool operator!= (Vector3 const &_rhs)
		{
			return ((m_fComponents[a] != _rhs.x ) || (m_fComponents[b] != _rhs.y) || (m_fComponents[c] != _rhs.z) ); 
		}


		//Allows you to invoke the vector without actually calling it
		operator Vector3()
		{
			return Vector3( m_fComponents[a], m_fComponents[b], m_fComponents[c] );
		}



	};



public:

	//Constructors
	Vector3();
	Vector3(float _x, float _y, float _z);
	Vector3(float _xyz);



	//Destructor
	~Vector3();


	//Overloading the operators

	//Returns the result of two vectors added
	Vector3 operator+( const Vector3 &_rhs);

	//Returns the result of two vectors subtracted
	Vector3 operator-( const Vector3 &_rhs) const;

	//Returns the result of two vectors multiplied
	Vector3 operator*( const Vector3 &_rhs);

	//Returns the result of two vectors divided
	Vector3 operator/( const Vector3 &_rhs);

	//Adds the right hand side vector to this
	void operator+= ( const Vector3 &_rhs);

	//Subtracts the right hand side vector from this
	void operator-= ( const Vector3 &_rhs);

	//Multiplies the right hand side vector to this
	void operator*= ( const Vector3 &_rhs);

	//Divides the right hand side vector from this
	void operator/= ( const Vector3 &_rhs);

	//Used to access an element in the vector
	float&  operator[] (unsigned int _index);

	//Compares Two vectors and returns true if they are equal
	bool    operator== (Vector3 const &_rhs);

	//Compares Two Vectors and returns true if they are not equla
	bool    operator!= (Vector3 const &_rhs);

	//Sets this equal to the right hand side vector
	Vector3 operator=  (Vector3 const &_rhs);

	

	//Normalize's this
	void Normalize();

	//GetNormalization
	Vector3 GetNormalization();

	//Find the magnitude
	float Magnitude() const;

	//Find the dot Product
	float Dot(Vector3 const &_rhs);

	//Find the angle between in Radians
	float AngleBetweenRadians( Vector3 const &_rhs);

	//Find the angle between in Degrees
	float AngleBetweenDegrees( Vector3 const &_rhs);

	//Rotate the vector with Radians
	void RotateAboutOriginRadians(float _radians);

	//Rotate the vector with Degrees
	void RotateAboutOriginDegrees(float _degrees);

	//Rotate around Vector with Radians
	void RotateAroundPointRadians(float _radians, Vector3 _point );

	//Rotate around Vector with Degrees
	void RotateAroundPointDegrees(float _degrees, Vector3 _point );

	//Negate the vector
	void Negate() ;

	//Reflect the Vector of the coinciding vector
	void Reflect( Vector3 _rhs);

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

			//Allowing the user to use z or b
			union
			{
				float z;
				float g;
			};

		};

		//Setting what value is getting passed into the swizzle depending on xy etc.
		swizzle<0,1,2> xyz;
		swizzle<0,2,1> xzy;

		swizzle<1,0,2> yxz;
		swizzle<1,2,0> yzx;
				
		swizzle<2,1,0> zyx;
		swizzle<2,0,1> zxy;
		

		swizzle<0,1,2> rgb;
		swizzle<0,2,1> rbg;

		swizzle<1,0,2> grb;
		swizzle<1,2,0> gbr;

		swizzle<2,1,0> bgr;
		swizzle<2,0,1> brg;


	};

};



//Allow you to print out the values in the vector
std::ostream& operator<<(ostream &output, const Vector3 &vector );

//Find the dot Product
float Dot(Vector3 const &_lhs, Vector3 const &_rhs);

//Find the angle between in Radians
float AngleBetweenRadians(Vector3 const &_lhs, Vector3 const &_rhs);

//Find the angle between in Radians
float AngleBetweenDegrees(Vector3 const &_lhs, Vector3 const &_rhs);

//Get the Normalization of the passed in Vector
Vector3 Normalize( Vector3 _vector );


#endif // !Vector3_H

