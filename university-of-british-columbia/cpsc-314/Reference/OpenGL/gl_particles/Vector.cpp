#include "vector.h"

CVector::CVector()
{
	v[0] = 0;
	v[1] = 0;
	v[2] = 0;
}

CVector::CVector(CVector &vec)
{
	v[0] = vec.v[0];
	v[1] = vec.v[1];
	v[2] = vec.v[2];
}

CVector::CVector(float x, float y, float z)
{
	v[0] = x;
	v[1] = y;
	v[2] = z;
}

CVector& CVector::operator=(CVector &vec)
{
	v[0] = vec.v[0];
	v[1] = vec.v[1];
	v[2] = vec.v[2];
	return *this;
}

CVector CVector::operator*(float s)
{
	return CVector(v[0]*s, v[1]*s, v[2]*s);
}

CVector& CVector::operator*=(float s)
{
	v[0] *= s;
	v[1] *= s;
	v[2] *= s;
	return *this;
}

CVector CVector::operator*(CVector &vec)
{
	return CVector(v[0]*vec.v[0], v[1]*vec.v[1], v[2]*vec.v[2]);
}

CVector CVector::operator+(CVector &vec)
{
	return CVector(v[0]+vec.v[0], v[1]+vec.v[1], v[2]+vec.v[2]);
}

CVector& CVector::operator+=(CVector &vec)
{
	v[0] += vec.v[0];
	v[1] += vec.v[1];
	v[2] += vec.v[2];
	return *this;
}

CVector CVector::operator-(CVector &vec)
{
	return CVector(v[0]-vec.v[0], v[1]-vec.v[1], v[2]-vec.v[2]);
}

CVector& CVector::operator-=(CVector &vec)
{
	v[0] -= vec.v[0];
	v[1] -= vec.v[1];
	v[2] -= vec.v[2];
	return *this;
}

bool CVector::operator==(CVector &vec)
{
	return (v[0]==vec.v[0] && v[1]==vec.v[1] && v[2]==vec.v[2]);
}

void CVector::Normalize(float n)
{
	float d = sqrtf(v[0]*v[0]+v[1]*v[1]+v[2]*v[2])/n;
	v[0]/= d;
	v[1]/= d;
	v[2]/= d;
}

void CVector::Set(float x, float y, float z)
{
	v[0] = x;
	v[1] = y;
	v[2] = z;
}

