//////////////////////////////////////////////////////////////////////////
//
// File: Vector3f.cpp
// Date: Jan 19, 2005
// 
// Author: Jack Liu
//
//////////////////////////////////////////////////////////////////////////

#include "Vector3f.h"

using namespace Math;

//////////////////////////////////////////////////////////////////////////
// 

Vector3f Vector3f::ZERO()
{
	return Vector3f( 0.0f );
}

Vector3f Vector3f::UNIT_X()
{
	return Vector3f( 1.0f, 0.0f, 0.0f );
}

Vector3f Vector3f::UNIT_Y()
{
	return Vector3f( 0.0f, 1.0f, 0.0f );
}

Vector3f Vector3f::UNIT_Z()
{
	return Vector3f( 0.0f, 0.0f, 1.0f );
}
