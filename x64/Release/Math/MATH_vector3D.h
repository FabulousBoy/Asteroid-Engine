#ifndef				MATH_VECTOR3D_H
#define				MATH_VECTOR3D_H

#include			"MATH_array.h"

class Vector3D
{
	double _arr[3]{};
public:

	Vector3D(float x = 0, float y = 0, float w = 1)
		{_arr[0] = x;	_arr[1] = y;	_arr[2] = w;}

	Vector3D operator *(Array3x3 arr3x3)
	{
		return Vector3D
		(
			_arr[0] * arr3x3._arr[0][0] + _arr[1] * arr3x3._arr[0][1] + _arr[2] * arr3x3._arr[0][2],
			_arr[0] * arr3x3._arr[1][0] + _arr[1] * arr3x3._arr[1][1] + _arr[2] * arr3x3._arr[1][2],
			_arr[0] * arr3x3._arr[2][0] + _arr[1] * arr3x3._arr[2][1] + _arr[2] * arr3x3._arr[2][2]
		);

	}
	Vector3D operator *(Vector3D other)
	{
		return Vector3D(x()*other._arr[0], y()*other._arr[1]);
			
	}

	Vector3D operator + (Vector3D other)
	{
		return Vector3D(_arr[0] + other._arr[0], _arr[1] + other._arr[1]);
	}

	void operator +=(Vector3D other)
	{
		for (int i = 0; i < 3; i++)
			_arr[i] += other._arr[i];
	}

	void operator +(float value)
	{
		_arr[1] += value; 
		_arr[1] += value;
	}

	Vector3D operator / (float value)
	{
		Vector3D result;

		for (int i = 0; i < 2; i++)
			result._arr[i] =_arr[i]/ value;

		return result;
	}

	float distance(Vector3D other)
	{
		float xDif = other.x() - x();
		float yDif = other.y() - y();

		return sqrt(pow(xDif,2) + pow(yDif,2));
	}

	float x() { return _arr[0]; }
	float y() { return _arr[1]; }
	float w() { return _arr[2]; }
};


#endif