#pragma once

#include <math.h>

class CVector
{
public:
	union{
		float v[3];
		struct{
			float x, y, z;
		};
	};

	CVector();
	CVector(CVector &v);
	CVector(float x, float y, float z);

	CVector& operator=(CVector &v);
	CVector operator*(float s);
	CVector& operator*=(float s);
	CVector operator*(CVector &v);
	CVector operator+(CVector &v);
	CVector& operator+=(CVector &v);
	CVector operator-(CVector &v);
	CVector& operator-=(CVector &v);
	bool operator==(CVector &v);
	void Normalize(float n=1.0f);
	void Set(float x, float y, float z);
};