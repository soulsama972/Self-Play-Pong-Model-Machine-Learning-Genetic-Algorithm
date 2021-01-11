#pragma once
#include<cmath>
#include<assert.h>
#include<iostream>




#define PI 3.1415926535897932384626433832795f
//template<typename T>
//class vec3;
//template<typename T>
//class vec2;
//template<typename T>
//class vec3;
//template<typename T>
//class vec4;




template<typename T>
class Type2
{
public:
	union
	{
		struct
		{
			T x, y;
		};
		T arr[2];
	};
};

template<typename T>
class Type3
{
public:
	union
	{
		struct
		{
			T x, y, z;
		};
		T arr[3];
	};
};

template<typename T>
class Type4
{
public:
	union
	{
		struct
		{
			T x, y, z, w;
		};
		T arr[4];
	};
};

template<typename T, typename K, int count>
class Vector;

template<typename T, int Row, int Col>
class Matrix;


using fVec2 = Vector<float, Type2<float>, 2>;
using fVec3 = Vector<float, Type3<float>, 3>;
using fVec4 = Vector<float, Type4<float>, 4>;

using iVec2 = Vector<int, Type2<int>, 2>;



class Matrix4x4
{
public:
#pragma warning (push)
#pragma warning (disable : 26495)
	Matrix4x4() { Identity(); }
	Matrix4x4(float* viewMatrix)
#pragma warning (pop)
	{
		pFloatToMatrix(viewMatrix);
	}
	union
	{

		float m[16];
		float u[4][4];

	};


	inline void operator *= (float v)
	{
		for (int i = 0; i < 16; i++)
			m[i] *= v;

	}

	inline void operator /= (float v)
	{
		for (int i = 0; i < 16; i++)
			m[i] /= v;

	}

	inline Matrix4x4 operator * (Matrix4x4 m)
	{
		Matrix4x4 mm;
		mm.Mul(*this, m);
		return mm;
	}

	inline void RotX(float Angle)
	{
		float cosAng = cosf(Angle);
		float sinAng = sinf(Angle);

		u[1][1] = cosAng;
		u[2][2] = cosAng;
		u[1][2] = sinAng;
		u[2][1] = -sinAng;

	}

	inline void RotY(float Angle)
	{
		float cosAng = cosf(Angle);
		float sinAng = sinf(Angle);

		u[0][0] = cosAng;
		u[2][2] = cosAng;
		u[0][2] = sinAng;
		u[2][0] = -sinAng;
	}

	inline void RotZ(float Angle)
	{
		float cosAng = cosf(Angle);
		float sinAng = sinf(Angle);

		u[0][0] = cosAng;
		u[1][1] = cosAng;
		u[0][1] = sinAng;
		u[1][0] = -sinAng;
	}

	inline void Identity()
	{
		for (int i = 0; i < 16; i++)
			m[i] = 0;

		u[0][0] = 1;
		u[1][1] = 1;
		u[2][2] = 1;
		u[3][3] = 1;
	}

	inline Matrix4x4 Transpose()
	{
		Matrix4x4 res;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				res.u[i][j] = this->u[j][i];
			}
		}
		return res;
	}

	inline void pFloatToMatrix(float* viewMatrix)
	{
		for (int i = 0; i < 16; i++)
		{
			m[i] = viewMatrix[i];
		}
	}

	inline void Mul(const Matrix4x4 src1, const Matrix4x4 src2)
	{

		u[0][0] = src1.u[0][0] * src2.u[0][0] + src1.u[0][1] * src2.u[1][0] + src1.u[0][2] * src2.u[2][0] + src1.u[0][3] * src2.u[3][0];
		u[0][1] = src1.u[0][0] * src2.u[0][1] + src1.u[0][1] * src2.u[1][1] + src1.u[0][2] * src2.u[2][1] + src1.u[0][3] * src2.u[3][1];
		u[0][2] = src1.u[0][0] * src2.u[0][2] + src1.u[0][1] * src2.u[1][2] + src1.u[0][2] * src2.u[2][2] + src1.u[0][3] * src2.u[3][2];
		u[0][3] = src1.u[0][0] * src2.u[0][3] + src1.u[0][1] * src2.u[1][3] + src1.u[0][2] * src2.u[2][3] + src1.u[0][3] * src2.u[3][3];

		u[1][0] = src1.u[1][0] * src2.u[0][0] + src1.u[1][1] * src2.u[1][0] + src1.u[1][2] * src2.u[2][0] + src1.u[1][3] * src2.u[3][0];
		u[1][1] = src1.u[1][0] * src2.u[0][1] + src1.u[1][1] * src2.u[1][1] + src1.u[1][2] * src2.u[2][1] + src1.u[1][3] * src2.u[3][1];
		u[1][2] = src1.u[1][0] * src2.u[0][2] + src1.u[1][1] * src2.u[1][2] + src1.u[1][2] * src2.u[2][2] + src1.u[1][3] * src2.u[3][2];
		u[1][3] = src1.u[1][0] * src2.u[0][3] + src1.u[1][1] * src2.u[1][3] + src1.u[1][2] * src2.u[2][3] + src1.u[1][3] * src2.u[3][3];

		u[2][0] = src1.u[2][0] * src2.u[0][0] + src1.u[2][1] * src2.u[1][0] + src1.u[2][2] * src2.u[2][0] + src1.u[2][3] * src2.u[3][0];
		u[2][1] = src1.u[2][0] * src2.u[0][1] + src1.u[2][1] * src2.u[1][1] + src1.u[2][2] * src2.u[2][1] + src1.u[2][3] * src2.u[3][1];
		u[2][2] = src1.u[2][0] * src2.u[0][2] + src1.u[2][1] * src2.u[1][2] + src1.u[2][2] * src2.u[2][2] + src1.u[2][3] * src2.u[3][2];
		u[2][3] = src1.u[2][0] * src2.u[0][3] + src1.u[2][1] * src2.u[1][3] + src1.u[2][2] * src2.u[2][3] + src1.u[2][3] * src2.u[3][3];

		u[3][0] = src1.u[3][0] * src2.u[0][0] + src1.u[3][1] * src2.u[1][0] + src1.u[3][2] * src2.u[2][0] + src1.u[3][3] * src2.u[3][0];
		u[3][1] = src1.u[3][0] * src2.u[0][1] + src1.u[3][1] * src2.u[1][1] + src1.u[3][2] * src2.u[2][1] + src1.u[3][3] * src2.u[3][1];
		u[3][2] = src1.u[3][0] * src2.u[0][2] + src1.u[3][1] * src2.u[1][2] + src1.u[3][2] * src2.u[2][2] + src1.u[3][3] * src2.u[3][2];
		u[3][3] = src1.u[3][0] * src2.u[0][3] + src1.u[3][1] * src2.u[1][3] + src1.u[3][2] * src2.u[2][3] + src1.u[3][3] * src2.u[3][3];


	}

	inline void Translate(float t[3])
	{
		this->u[3][0] = t[0];
		this->u[3][1] = t[1];
		this->u[3][2] = t[2];
	}

	inline Matrix4x4 InvertMatrix()
	{
		Matrix4x4 inv;
		float det;
		int i;

		inv.m[0] = m[5] * m[10] * m[15] -
			m[5] * m[11] * m[14] -
			m[9] * m[6] * m[15] +
			m[9] * m[7] * m[14] +
			m[13] * m[6] * m[11] -
			m[13] * m[7] * m[10];

		inv.m[4] = -m[4] * m[10] * m[15] +
			m[4] * m[11] * m[14] +
			m[8] * m[6] * m[15] -
			m[8] * m[7] * m[14] -
			m[12] * m[6] * m[11] +
			m[12] * m[7] * m[10];

		inv.m[8] = m[4] * m[9] * m[15] -
			m[4] * m[11] * m[13] -
			m[8] * m[5] * m[15] +
			m[8] * m[7] * m[13] +
			m[12] * m[5] * m[11] -
			m[12] * m[7] * m[9];

		inv.m[12] = -m[4] * m[9] * m[14] +
			m[4] * m[10] * m[13] +
			m[8] * m[5] * m[14] -
			m[8] * m[6] * m[13] -
			m[12] * m[5] * m[10] +
			m[12] * m[6] * m[9];

		inv.m[1] = -m[1] * m[10] * m[15] +
			m[1] * m[11] * m[14] +
			m[9] * m[2] * m[15] -
			m[9] * m[3] * m[14] -
			m[13] * m[2] * m[11] +
			m[13] * m[3] * m[10];

		inv.m[5] = m[0] * m[10] * m[15] -
			m[0] * m[11] * m[14] -
			m[8] * m[2] * m[15] +
			m[8] * m[3] * m[14] +
			m[12] * m[2] * m[11] -
			m[12] * m[3] * m[10];

		inv.m[9] = -m[0] * m[9] * m[15] +
			m[0] * m[11] * m[13] +
			m[8] * m[1] * m[15] -
			m[8] * m[3] * m[13] -
			m[12] * m[1] * m[11] +
			m[12] * m[3] * m[9];

		inv.m[13] = m[0] * m[9] * m[14] -
			m[0] * m[10] * m[13] -
			m[8] * m[1] * m[14] +
			m[8] * m[2] * m[13] +
			m[12] * m[1] * m[10] -
			m[12] * m[2] * m[9];

		inv.m[2] = m[1] * m[6] * m[15] -
			m[1] * m[7] * m[14] -
			m[5] * m[2] * m[15] +
			m[5] * m[3] * m[14] +
			m[13] * m[2] * m[7] -
			m[13] * m[3] * m[6];

		inv.m[6] = -m[0] * m[6] * m[15] +
			m[0] * m[7] * m[14] +
			m[4] * m[2] * m[15] -
			m[4] * m[3] * m[14] -
			m[12] * m[2] * m[7] +
			m[12] * m[3] * m[6];

		inv.m[10] = m[0] * m[5] * m[15] -
			m[0] * m[7] * m[13] -
			m[4] * m[1] * m[15] +
			m[4] * m[3] * m[13] +
			m[12] * m[1] * m[7] -
			m[12] * m[3] * m[5];

		inv.m[14] = -m[0] * m[5] * m[14] +
			m[0] * m[6] * m[13] +
			m[4] * m[1] * m[14] -
			m[4] * m[2] * m[13] -
			m[12] * m[1] * m[6] +
			m[12] * m[2] * m[5];

		inv.m[3] = -m[1] * m[6] * m[11] +
			m[1] * m[7] * m[10] +
			m[5] * m[2] * m[11] -
			m[5] * m[3] * m[10] -
			m[9] * m[2] * m[7] +
			m[9] * m[3] * m[6];

		inv.m[7] = m[0] * m[6] * m[11] -
			m[0] * m[7] * m[10] -
			m[4] * m[2] * m[11] +
			m[4] * m[3] * m[10] +
			m[8] * m[2] * m[7] -
			m[8] * m[3] * m[6];

		inv.m[11] = -m[0] * m[5] * m[11] +
			m[0] * m[7] * m[9] +
			m[4] * m[1] * m[11] -
			m[4] * m[3] * m[9] -
			m[8] * m[1] * m[7] +
			m[8] * m[3] * m[5];

		inv.m[15] = m[0] * m[5] * m[10] -
			m[0] * m[6] * m[9] -
			m[4] * m[1] * m[10] +
			m[4] * m[2] * m[9] +
			m[8] * m[1] * m[6] -
			m[8] * m[2] * m[5];

		det = m[0] * inv.m[0] + m[1] * inv.m[4] + m[2] * inv.m[8] + m[3] * inv.m[12];

		if (det == 0)
		{
			Matrix4x4 id;
			return id;
		}

		det = 1.0f / det;

		for (i = 0; i < 16; i++)
			inv.m[i] = inv.m[i] * det;

		return inv;
	}

};

//
//template<typename T>
//class vec2
//{
//public:
//	T x, y;
//
//	inline vec2()
//	{
//		x = (T)0;
//		y = (T)0;
//	}
//
//	inline vec2(const vec2& src)
//	{
//		x = src.x;
//		y = src.y;
//	}
//
//	template<typename K>
//	inline vec2(const K& x, const K& y)
//	{
//		this->x = static_cast<T>(x);
//		this->y = static_cast<T>(y);
//	}
//
//	inline T GetLength()
//	{
//		return x * x + y * y;
//	}
//
//	inline T GetMagnitude()
//	{
//		return (T)sqrt(GetLength());
//	}
//
//	inline vec2 GetNormalize()
//	{
//		T magnitude = GetMagnitude();
//		return vec2(x / magnitude, y / magnitude);
//	}
//
//	inline vec2 operator+(const vec2 v)
//	{
//		return vec2(x + v.x, y + v.y);
//	}
//
//	inline vec2 operator-(const vec2 v)
//	{
//		return vec2(x - v.x, y - v.y);
//	}
//
//	inline vec2 operator*(const vec2 v)
//	{
//		return vec2(x * v.x, y * v.y);
//	}
//
//	inline vec2 operator/(const vec2 v)
//	{
//		return vec2(x / v.x, y / v.y);
//	}
//
//	inline vec2 operator/(float f)
//	{
//		return vec2(x / f, y / f);
//	}
//
//	inline void operator/=(float f)
//	{
//		x /= 2;
//		y /= 2;
//	}
//
//	inline vec2 operator-(const float f)
//	{
//		return vec2(x - f, y - f);
//	}
//
//	inline T* ToPointer()
//	{
//		return reinterpret_cast<T*>(this);
//	}
//
//	/*inline vec3<T> ToFVec3()
//	{
//		return vec3<T>((T)x, (T)y, (T)0);
//	}*/
//
//};
//
//
//template<typename T>
//class vec3
//{
//public:
//	T x, y, z;
//
//	inline vec3()
//	{
//		x = (T)0;
//		y = (T)0;
//		z = (T)0;
//	}
//
//	inline vec3(const vec3& src)
//	{
//		x = src.x;
//		y = src.y;
//		z = src.z;
//	}
//
//	template<typename K>
//	inline vec3(const K& x, const K& y,const K & z)
//	{
//		this->x = static_cast<T>(x);
//		this->y = static_cast<T>(y);
//		this->z = static_cast<T>(z);
//	}
//
//	inline T GetDot(const vec3<T>& v)
//	{
//		return x * v.x + y * v.y + z * v.z;
//	}
//
//	inline T GetLength()
//	{
//		return (T)sqrt(GetDot(*this));
//	}
//
//	inline vec3 GetNormalize()
//	{
//		T magnitude = GetLength();
//		return vec3(x / magnitude, y / magnitude,z/magnitude);
//	}
//	
//	inline bool	 operator==(const vec3 v)
//	{
//		return (x == v.x && y == v.y && v.z == z);
//	}
//
//	inline vec3 operator+(const vec3 v)
//	{
//		return vec3(x + v.x, y + v.y, z + v.z);
//	}
//
//	inline vec3 operator-(const vec3 v)
//	{
//		return vec3(x - v.x, y - v.y, z - v.z);
//	}
//
//
//	inline vec3 operator*(const vec3 v)
//	{
//		return vec3(x * v.x, y * v.y, z * v.z);
//	}
//
//	inline vec3 operator/(const vec3 v)
//	{
//		return vec3(x / v.x, y / v.y, z / v.z);
//	}
//
//	inline vec3 operator/(float  v)
//	{
//		return vec3(x / v, y / v, z / v);
//	}
//
//	inline void operator/=(float  v)
//	{
//		x /= v;
//		y /= v;
//		z /= v;
//		
//	}
//
//
//	inline vec3 operator*(float  v)
//	{
//		return vec3(x * v, y * v, z * v);
//	}
//
//
//	inline T* ToPointer()
//	{
//		return reinterpret_cast<T*>(this);
//	}
//
//	inline vec3 Transfrom(Matrix4x4 m)
//	{
//		vec3 v;
//		v.x = x * m.u[0][0] + y * m.u[1][0] + z * m.u[2][0] + m.u[3][0];
//		v.y = x * m.u[0][1] + y * m.u[1][1] + z * m.u[2][1] + m.u[3][1];
//		v.z = x * m.u[0][2] + y * m.u[1][2] + z * m.u[2][2] + m.u[3][2];
//		return v;
//	}
//
//	inline vec2<T> ToVec2()
//	{
//		return vec2<T>((T)x, (T)y);
//	}
//
//	inline vec3 ToNegativeY()
//	{
//		return vec3(x, -y, z);
//	}
//};
//
//
//template<typename T>
//class vec4
//{
//public:
//	T x, y, z, w;
//
//	inline vec4()
//	{
//		x = (T)0;
//		y = (T)0;
//		z = (T)0;
//		w = (T)0;
//	}
//
//	inline vec4(const vec4& src)
//	{
//		x = src.x;
//		y = src.y;
//		z = src.z;
//		w = src.w;
//	}
//
//	template<typename K>
//	inline vec4(const K& x, const K& y, const K& z , const K& w)
//	{
//		this->x = static_cast<T>(x);
//		this->y = static_cast<T>(y);
//		this->z = static_cast<T>(z);
//		this->w = static_cast<T>(w);
//	}
//
//	inline T GetLength()
//	{
//		return x * x + y * y + z * z + w * w;
//	}
//
//	inline T GetMagnitude()
//	{
//		return (T)sqrt(GetLength());
//	}
//
//	inline vec4 GetNormalize()
//	{
//		T magnitude = GetMagnitude();
//		return vec4(x / magnitude, y / magnitude);
//	}
//
//	inline void Transform(const vec3<float>  v, const Matrix4x4  m)
//	{
//		
//		x = v.x * m.u[0][0] + v.y * m.u[1][0] + v.z * m.u[2][0] + m.u[3][0];
//		y = v.x * m.u[0][1] + v.y * m.u[1][1] + v.z * m.u[2][1] + m.u[3][1];
//		z = v.x * m.u[0][2] + v.y * m.u[1][2] + v.z * m.u[2][2] + m.u[3][2];
//		w = v.x * m.u[0][3] + v.y * m.u[1][3] + v.z * m.u[2][3] + m.u[3][3];
//	}
//
//	inline vec4 operator+(const vec4 v)
//	{
//		return vec4(x + v.x, y + v.y, z + v.z, w + v.w);
//	}
//
//	inline vec4 operator-(const vec4 v)
//	{
//		return vec4(x - v.x, y - v.y, z - v.z, w - v.w);
//	}
//
//	inline vec4 operator*(const vec4 v)
//	{
//		return vec4(x * v.x, y * v.y, z * v.z, w * v.w);
//	}
//
//	inline vec4 operator/(const vec4 v)
//	{
//		return vec4(x / v.x, y / v.y, z / v.z, w / v.w);
//	}
//
//	inline T* ToPointer()
//	{
//		return reinterpret_cast<T*>(this);
//	}
//};
//



template<typename T, typename K, int count>
class Vector : public K
{

public:
	inline Vector()
	{
		std::memset(this->arr, 0, sizeof(T) * count);
	}

	inline Vector(const Vector& src)
	{
		std::memcpy(this->arr, src.arr, sizeof(T) * count);
	}

	inline Vector(const T& x, const T& y, const T& z, const T& w)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	inline Vector(const T& x, const T& y, const T& z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	inline Vector(const T& x, const T& y)
	{
		this->x = x;
		this->y = y;
	}

	inline T GetLength()const
	{
		T res = 0;
		for (int i = 0; i < count; i++)
		{
			res += (this->arr[i] * this->arr[i]);
		}
		return res;
	}

	inline T GetMagnitude()const
	{
		return (T)sqrt(GetLength());
	}

	inline Vector GetNormalize()const
	{
		Vector v;
		T magnitude = GetMagnitude();
		for (int i = 0; i < count; i++)
			v.arr[i] = this->arr[i] / magnitude;
		return v;
	}

	inline T* ToPointer()
	{
		return reinterpret_cast<T*>(this);
	}

	inline T GetDot(const Vector& v)const
	{
		T res = 0;
		for (int i = 0; i < count; i++)
		{
			res += (this->arr[i] * v.arr[i]);
		}
		return res;
	}

	inline T GetDot()const
	{
		return GetLength();
	}

	inline Vector TransfromV4(const Matrix4x4& m)
	{
		Vector v;
		for (int i = 0; i < count; i++)
		{
			v.arr[i] = this->x * m.u[0][i] + this->y * m.u[1][i] + this->z * m.u[2][i] + this->w * m.u[3][i];
		}
		return v;
	}

	inline Vector TransfromV3(const Matrix4x4& m)
	{
		Vector v;
		for (int i = 0; i < count; i++)
		{
			v.arr[i] = this->x * m.u[0][i] + this->y * m.u[1][i] + this->z * m.u[2][i] + m.u[3][i];
		}
		return v;
	}

	inline Vector ToNegativeY()const
	{
		Vector v;
		for (int i = 0; i < count; i++)
		{
			if (i == 1)
				v.arr[i] = -this->arr[i];
			else
				v.arr[i] = this->arr[i];
		}


		return v;
	}

	inline Vector<T, Type2<T>, 2> ToVec2()const
	{
		Vector<T, Type2<T>, 2>v;
		for (int i = 0; i < 2; i++)
			v.arr[i] = i < count ? this->arr[i] : 0;
		return v;
	}

	inline Vector<T, Type3<T>, 3> ToVec3()const
	{
		Vector<T, Type3<T>, 3>v;
		for (int i = 0; i < 3; i++)
			v.arr[i] = i < count ? this->arr[i] : 0;


		return v;
	}

	inline Vector<T, Type4<T>, 4> ToVec4()const
	{
		Vector<T, Type4<T>, 4>v;
		for (int i = 0; i < 4; i++)
			v.arr[i] = i < count ? this->arr[i] : 0;
		return v;
	}

	inline Vector operator+(const Vector& v)const
	{
		Vector res;
		for (int i = 0; i < count; i++)
			res.arr[i] = this->arr[i] + v.arr[i];
		return res;
	}

	inline Vector operator+=(const Vector& v)const
	{
		return *this + v;
	}

	inline Vector operator-(const Vector& v)const
	{
		Vector res;
		for (int i = 0; i < count; i++)
			res.arr[i] = this->arr[i] - v.arr[i];
		return res;
	}

	inline Vector operator-=(const Vector& v)const
	{
		return *this - v;
	}

	inline Vector operator/(const T& v)const
	{
		Vector res;
		for (int i = 0; i < count; i++)
			res.arr[i] = this->arr[i] / v;
		return res;
	}

	inline Vector operator/=(const T& v)const
	{
		return *this / v;
	}

	inline Vector operator*(const T& v)const
	{
		Vector res;
		for (int i = 0; i < count; i++)
			res.arr[i] = this->arr[i] * v;
		return res;
	}

	inline Vector operator*=(const T& v)const
	{
		return *this * v;
	}

	inline bool operator==(const Vector& v)const
	{
		for (int i = 0; i < count; i++)
		{
			if (this->arr[i] != v.arr[i])
				return false;
		}
		return true;
	}

	inline Vector operator*(const Vector& v)const
	{
		Vector res;
		for (int i = 0; i < count; i++)
			res.arr[i] = this->arr[i] * v.arr[i];
		return res;
	}

	inline Vector operator/(const Vector& v)const
	{
		Vector res;
		for (int i = 0; i < count; i++)
			res.arr[i] = this->arr[i] / v.arr[i];
		return res;
	}

};


template<typename T, int Row, int Col>
class Matrix 
{
public:

	T arr[Row][Col] = { 0 };

	Matrix() = default;

	Matrix(const Matrix<T, Row, Col>& m)
	{
		memcpy(this->arr, m.arr,sizeof(T) * Row * Col);
	}
	using Func = T(*)(T);
	inline Matrix<T,Row,Col> Map(Func func)
	{
		Matrix<T, Row, Col>m;
		for (size_t i = 0; i < Row; i++)
		{
			for (size_t j = 0; j < Col; j++)
			{
				m.arr[i][j] = func(this->arr[i][j]);
			}
		}
		return m;
	}
	using Func2 = T(*)();
	inline Matrix<T, Row, Col> Map(Func2 func)
	{
		Matrix<T, Row, Col>m;
		for (size_t i = 0; i < Row; i++)
		{
			for (size_t j = 0; j < Col; j++)
			{
				m.arr[i][j] = func();
			}
		}
		return m;
	}

	using Func3 = void(*)(T&,const T&,T rate);
	inline Matrix<T, Row, Col> Map(Func3 func,Matrix<T, Row, Col> arg, T rate)
	{
		Matrix<T, Row, Col>m;
		for (size_t i = 0; i < Row; i++)
		{
			for (size_t j = 0; j < Col; j++)
			{
				func(arr[i][j],arg.arr[i][j], rate);
			}
		}
		return m;
	}

	using Func = T(*)(T);
	inline T  Sum(Func func)
	{
		T res = 0;
		for (size_t i = 0; i < Row; i++)
		{
			for (size_t j = 0; j < Col; j++)
			{
				res += func(arr[i][j]);
			}
		}
		return res;
	}

	inline Matrix operator*=(T val)
	{
		
		for (size_t i = 0; i < Row; i++)
		{
			for (size_t  j= 0; j< Col; j++)
			{
			 this->arr[i][j] *= val;
			}
		}
		return *this;
	}

	inline T Sum()
	{
		T res = 0;
		for (size_t i = 0; i < Row; i++)
		{
			for (size_t j = 0; j < Col; j++)
			{
				res += arr[i][j];
			}
		}
		return res;
	}
	inline unsigned int GetIndexByMax()
	{
		unsigned int index = 0;
		for (unsigned int j = 1; j < Col; j++)
			if (arr[0][index] < arr[0][j])
				index = j;

		return index;
	}




	inline void Print()const
	{
		for (size_t i = 0; i < Row; i++)
		{
			std::cout << "[";
			for (size_t j = 0; j < Col; j++)
			{
				std::cout << this->arr[i][j] << " ";
			}
			std::cout << "]" << std::endl;
		}
	}

};

template<typename T, int Row, int Col,int Row2,int Col2>
inline Matrix<T,Row,Col2> dot(const Matrix<T,Row,Col>& a, const Matrix<T,Row2,Col2>& b)
{
	Matrix<T, Row, Col2>m;
	static_assert(Col == Row2, "row != col");
	for (size_t i = 0; i < Row; i++)
	{
		for (size_t j = 0; j < Col2; j++)
		{
			T sum = 0;
			for (size_t k = 0; k < Col;k++)
			{
				sum += a.arr[i][k] * b.arr[k][j];
			}
			m.arr[i][j] = sum;
		}
	}
	return m;
}

template<typename T, int Row, int Col>
inline Matrix<T, Col, Row> Transpose(const Matrix<T, Row, Col>& a)
{
	Matrix<T, Col, Row> m;
	for (size_t i = 0; i < Col; i++)
	{
		for (size_t j = 0; j < Row; j++)
		{
			m.arr[i][j] = a.arr[j][i];
		}
	}
	return m;
}



inline Matrix4x4 SetScaleMatrix(const fVec3& scale)
{
	Matrix4x4 m;
	m.u[0][0] = scale.x;
	m.u[1][1] = scale.y;
	m.u[2][2] = scale.z;
	return m;
}

inline Matrix4x4 SetScaleMatrix(const fVec2& scale)
{
	Matrix4x4 m;
	m.u[0][0] = scale.x;
	m.u[1][1] = scale.y;
	return m;
}


inline fVec3 Cross(const fVec3& v, const fVec3& v2)
{
	return fVec3(v.y * v2.z - v.z * v2.y, v.x * v2.z - v.z * v2.x, v.x * v2.y - v.y * v2.x);
}



