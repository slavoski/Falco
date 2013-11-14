#ifndef CVECTOR2_H
#define CVECTOR2_H

#define EPSILON 0.000001f 
#define PI	3.141592f




class Vector2
{
private:



	template< int a, int b >
	class swizzle
	{
	private:
		float m_fComponents[2];



	public:
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
			if ( _rhs.x > 0.000001 || _rhs.x < -0.000001)
				m_fComponents[a] /= _rhs.x;

			if ( _rhs.y > 0.000001 || _rhs.y < -0.000001)
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
			if ( (_rhs.x < 0.000001 && _rhs.x > -0.000001)  ||   ( _rhs.y < 0.000001 && _rhs.y > -0.000001)  )
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

	//Find the magnitude
	float Magnitude() const;

	//Find the dot Product
	float Dot(Vector2 const &_rhs);

	//Find the angle between in Radians
	float AngleBetweenRadians( Vector2 const &_rhs);

	//Find the angle between in Degrees
	float AngleBetweenDegrees( Vector2 const &_rhs);

	//Rotate the vector
	void Rotate(float _radians);




	//Variables
	//The X and Y of the Vector
	union
	{

		struct
		{
			//Allowing the user to use x or a
			union 
			{
				float x;
				float r;

			};

			//Allowing the user to use y or b
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




std::ostream& operator<<(ostream &output, const Vector2 &vector );

//Find the dot Product
float Dot(Vector2 const &_lhs, Vector2 const &_rhs);

//Find the angle between in Radians
float AngleBetweenRadians(Vector2 const &_lhs, Vector2 const &_rhs);

//Find the angle between in Radians
float AngleBetweenDegrees(Vector2 const &_lhs, Vector2 const &_rhs);

//Rotate the vector
void Rotate(Vector2 const &vector, float _radians);


//Check if the value is zero
//TODO put somewhere better
bool isZero(float _Value );
float RadianToDegrees( float _rad );


#endif // !VECTOR2_H

