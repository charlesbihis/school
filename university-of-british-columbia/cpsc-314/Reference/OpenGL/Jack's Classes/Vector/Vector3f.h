//////////////////////////////////////////////////////////////////////////
//
// File: Vector3f.h
// Date: Jan 19, 2005
// 
// Author: Jack Liu
//
//////////////////////////////////////////////////////////////////////////

#ifndef VECTOR3F_H_
#define VECTOR3F_H_

#include <cmath>

namespace Math
{
	class Vector3f
	{	

	// constructors/destructors
	public:

		Vector3f			();
		explicit Vector3f	( float value );
		Vector3f			( float x_, float y_, float z_ );

	// interfaces
	public:

		Vector3f&	Set					( float x_, float y_, float z_ );

		float		Length				() const;
		float		LengthSquared		() const;

		Vector3f&	NormalizeSelf		();
		Vector3f	NormalizeClone		() const;

		Vector3f&	operator+=			( const Vector3f& rhs );
		Vector3f&	operator-=			( const Vector3f& rhs	);

		Vector3f&	operator^=			( const Vector3f& rhs );		// Cross product

		Vector3f&	operator*=			( float rhs );
		Vector3f&	operator/=			( float rhs );

		friend float operator%			( const Vector3f& lhs, const Vector3f& rhs );	// Dot product

		friend const Vector3f operator^	( const Vector3f& lhs, const Vector3f& rhs );
		friend const Vector3f operator+	( const Vector3f& lhs, const Vector3f& rhs );
		friend const Vector3f operator-	( const Vector3f& lhs, const Vector3f& rhs );
		
		friend const Vector3f operator*	( const Vector3f& lhs, float rhs );
		friend const Vector3f operator/	( const Vector3f& lhs, float rhs );

		static Vector3f ZERO			();
		static Vector3f UNIT_X			();
		static Vector3f UNIT_Y			();
		static Vector3f UNIT_Z			();

	// variables
	public:

		union
		{
			struct { float x, y ,z; };
			struct { float e[ 3 ]; 	};
			struct { float r, g, b; };
		};
	};
}

//////////////////////////////////////////////////////////////////////////
// constructors/destructors

inline Math::Vector3f::Vector3f() : 
	x( 0.0f ),
	y( 0.0f ),
	z( 0.0f )
{
	// empty
}

inline Math::Vector3f::Vector3f( float value ) :
	x( value ),
	y( value ),
	z( value )
{
	// empty
}

inline Math::Vector3f::Vector3f( float x_, float y_, float z_ ) :
	x( x_ ),
	y( y_ ),
	z( z_ )
{
	// empty
}

//////////////////////////////////////////////////////////////////////////
// interfaces

inline Math::Vector3f& Math::Vector3f::Set( float x_, float y_, float z_ )
{
	x = x_;
	y = y_;
	z = z_;

	return *this;
}

inline float Math::Vector3f::Length() const
{
	return sqrt( LengthSquared() );
}

inline float Math::Vector3f::LengthSquared() const
{
	return x * x + y * y + z * z;
}

inline Math::Vector3f& Math::Vector3f::NormalizeSelf()
{
	*this /= Length();

	return *this;
}

inline Math::Vector3f Math::Vector3f::NormalizeClone() const
{
	Math::Vector3f r = *this;

	return r.NormalizeSelf();
}

inline Math::Vector3f& Math::Vector3f::operator+=( const Math::Vector3f& rhs )
{
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;

	return *this;
}

inline Math::Vector3f& Math::Vector3f::operator-=( const Math::Vector3f& rhs )
{
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;
	
	return *this;
}

inline Math::Vector3f& Math::Vector3f::operator^=( const Math::Vector3f& rhs )
{
	x = y * rhs.z - z * rhs.y;
	y = z * rhs.x - x * rhs.z;
	z = x * rhs.y - y * rhs.x;

	return *this;
}

inline Math::Vector3f& Math::Vector3f::operator*=( float rhs )
{
	x *= rhs;
	y *= rhs;
	z *= rhs;

	return *this;
}

inline Math::Vector3f& Math::Vector3f::operator/=( float rhs )
{
	x /= rhs;
	y /= rhs;
	z /= rhs;

	return *this;
}

inline float Math::operator%( const Math::Vector3f& lhs, const Math::Vector3f& rhs )
{
	return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}

inline const Math::Vector3f Math::operator^( const Math::Vector3f& lhs, const Math::Vector3f& rhs )
{
	return Math::Vector3f( lhs.y * rhs.z - lhs.z * rhs.y, lhs.z * rhs.x - lhs.x * rhs.z, lhs.x * rhs.y - lhs.y * rhs.x );
}

inline const Math::Vector3f Math::operator+( const Math::Vector3f& lhs, const Math::Vector3f& rhs )
{
	return Math::Vector3f( lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z );
}

inline const Math::Vector3f Math::operator-( const Math::Vector3f& lhs, const Math::Vector3f& rhs )
{
	return Math::Vector3f( lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z );
}

inline const Math::Vector3f Math::operator*( const Math::Vector3f& lhs, float rhs )
{
	return Math::Vector3f( lhs.x * rhs, lhs.y * rhs, lhs.z * rhs );
}

inline const Math::Vector3f Math::operator/( const Math::Vector3f& lhs, float rhs )
{
	return Math::Vector3f( lhs.x / rhs, lhs.y / rhs, lhs.z / rhs );
}

#endif /* VECTOR3F_H_ */
