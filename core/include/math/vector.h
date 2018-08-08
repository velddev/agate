#pragma once
template<int N>
struct Vector
{
	union {
		float[N] axes;
		float x;
		float y;
		float z;	
		float w;
	};

	Vector<N> operator+(Vector<N> other)
	{
		for (int i = 0; i < N; i++)
		{
			axes[i] += other.axes[i];
		}
	}

	Vector<N> operator-(Vector<N> other)
	{
		for (int i = 0; i < N; i++)
		{
			axes[i] -= other.axes[i];
		}
	}

	Vector<N> operator=(Vector<N> other)
	{
		for (int i = 0; i < N; i++)
		{
			axes[i] = other.axes[i];
		}
	}

	float Magnitude()
	{
		float magnitude = 0.f;
		for (int i = 0; i < N; i++)
		{
			magnitude += (axes[i] * axes[i]);
		}
		return sqrtf(magnitude);
	}
};

typedef Vector<2> Vector2;
typedef Vector<3> Vector3;
typedef Vector<4> Vector4;