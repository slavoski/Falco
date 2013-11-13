#ifndef CVECTOR2_H
#define CVECTOR2_H

class Vector2
{
private:
	template< int a, int b >
	class swizzle
	{
	private:
		float m_fComponents[2];


	public:
		Vector2& operator=( const Vector2 &rhs )
		{

			m_fComponents[a] = rhs.x;
			m_fComponents[b] = rhs.y;

			return *this;
		}

		Vector2& operator+=( const Vector2 &rhs )
		{
			m_fComponents[a] += rhs.x;
			m_fComponents[b] += rhs.y;

			return *this;
		}

		Vector2& operator-=( const Vector2 &rhs )
		{
			m_fComponents[a] -= rhs.x;
			m_fComponents[b] -= rhs.y;

			return *this;
		}

		Vector2& operator*=( const Vector2 &rhs )
		{
			m_fComponents[a] *= rhs.x;
			m_fComponents[b] *= rhs.y;

			return *(Vector2*)this;
		}


		Vector2& operator/=( const Vector2 &rhs )
		{
			if ( rhs.x > 0.000001 || rhs.x < -0.000001)
				m_fComponents[a] /= rhs.x;
			
			if ( rhs.y > 0.000001 || rhs.y < -0.000001)
				m_fComponents[b] /= rhs.y;

			return *this;
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
	Vector2& operator+= ( const Vector2 &rhs);
	Vector2& operator-= ( const Vector2 &rhs);
	Vector2& operator*= ( const Vector2 &rhs);
	Vector2& operator/= ( const Vector2 &rhs);

	void Normalize();





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


Vector2& operator+(const Vector2 &lhs, const Vector2 &rhs);
Vector2& operator-(const Vector2 &lhs, const Vector2 &rhs);
Vector2& operator*(const Vector2 &lhs, const Vector2 &rhs);
Vector2& operator/(const Vector2 &lhs, const Vector2 &rhs);

std::ostream& operator<<(ostream &output, const Vector2 &vector );





#endif // !VECTOR2_H

