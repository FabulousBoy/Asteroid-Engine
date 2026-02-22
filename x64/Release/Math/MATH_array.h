#ifndef				MATH_ARRAY_H
#define				MATH_ARRAY_H

#include			<math.h>

class Array3x3
{
	
public:

	double _arr[3][3]{};

	Array3x3() = default;

	Array3x3 operator * (Array3x3 other)
	{
		Array3x3 result;

		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				for (int k = 0; k < 3; k++)
					result._arr[i][j] = _arr[i][k] * other._arr[k][j];

		return result;
	}

	static Array3x3 Screen(float W, float H,float asp)
	{
		Array3x3 S;

		S._arr[0][0] = W/asp;
		S._arr[1][1] = -H;

		S._arr[0][2] = W;
		S._arr[1][2] = H;

		S._arr[2][2] = 1;

		return S;
	}

	static Array3x3 rotate(float turn)
	{
		Array3x3 Z;

		float c = cosf(turn);
		float s = sinf(turn);

		Z._arr[0][0] = c;
		Z._arr[1][0] = -s;
		Z._arr[0][1] = s;
		Z._arr[1][1] = c;

		Z._arr[2][2] = 1;

		return Z;
	}

};

#endif