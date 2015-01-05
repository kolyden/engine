#pragma once
#include "math/uutMath.h"

namespace uut
{
	template<class T>class Vector2;
	template<class T>class Vector4;

	template <class T>
	class Vector3
	{
	public:
		typedef T value_type;
		int32_t size() const { return 3; }

		////////////////////////////////////////////////////////
		//
		//  Constructors
		//
		////////////////////////////////////////////////////////

		// Default/scalar constructor
		Vector3(const T & t = T()) {
			for (int32_t i = 0; i < size(); i++) _array[i] = t;
		}

		// Construct from array
		Vector3(const T * tp) {
			for (int32_t i = 0; i < size(); i++) _array[i] = tp[i];
		}

		// Construct from explicit values
		Vector3(const T v0, const T v1, const T v2) {
			x = v0;
			y = v1;
			z = v2;
		}

		explicit Vector3(const Vector4<T> &u) {
			for (int32_t i = 0; i < size(); i++) _array[i] = u._array[i];
		}

		explicit Vector3(const Vector2<T> &u, T v0) {
			x = u.x;
			y = u.y;
			z = v0;
		}

		const T * get_value() const {
			return _array;
		}

		Vector3<T> & set_value(const T * rhs) {
			for (int32_t i = 0; i < size(); i++) _array[i] = rhs[i];
			return *this;
		}

		// indexing operators
		T & operator [] (int32_t i) {
			return _array[i];
		}

		const T & operator [] (int32_t i) const {
			return _array[i];
		}

		// type-cast operators
		operator T * () {
			return _array;
		}

		operator const T * () const {
			return _array;
		}

		////////////////////////////////////////////////////////
		//
		//  Math operators
		//
		////////////////////////////////////////////////////////

		// scalar multiply assign
		friend Vector3<T> & operator *= (Vector3<T> &lhs, T d) {
			for (int32_t i = 0; i < lhs.size(); i++) lhs._array[i] *= d;
			return lhs;
		}

		// component-wise vector multiply assign
		friend Vector3<T> & operator *= (Vector3<T> &lhs, const Vector3<T> &rhs) {
			for (int32_t i = 0; i < lhs.size(); i++) lhs._array[i] *= rhs[i];
			return lhs;
		}

		// scalar divide assign
		friend Vector3<T> & operator /= (Vector3<T> &lhs, T d) {
			if (d == 0) return lhs;
			for (int32_t i = 0; i < lhs.size(); i++) lhs._array[i] /= d;
			return lhs;
		}

		// component-wise vector divide assign
		friend Vector3<T> & operator /= (Vector3<T> &lhs, const Vector3<T> & rhs) {
			for (int32_t i = 0; i < lhs.size(); i++) lhs._array[i] /= rhs._array[i];
			return lhs;
		}

		// component-wise vector add assign
		friend Vector3<T> & operator += (Vector3<T> &lhs, const Vector3<T> & rhs) {
			for (int32_t i = 0; i < lhs.size(); i++) lhs._array[i] += rhs._array[i];
			return lhs;
		}

		// component-wise vector subtract assign
		friend Vector3<T> & operator -= (Vector3<T> &lhs, const Vector3<T> & rhs) {
			for (int32_t i = 0; i < lhs.size(); i++) lhs._array[i] -= rhs._array[i];
			return lhs;
		}

		// unary negate
		friend Vector3<T> operator - (const Vector3<T> &rhs) {
			Vector3<T> rv;
			for (int32_t i = 0; i < rhs.size(); i++) rv._array[i] = -rhs._array[i];
			return rv;
		}

		// vector add
		friend Vector3<T> operator + (const Vector3<T> & lhs, const Vector3<T> & rhs) {
			Vector3<T> rt(lhs);
			return rt += rhs;
		}

		// vector subtract
		friend Vector3<T> operator - (const Vector3<T> & lhs, const Vector3<T> & rhs) {
			Vector3<T> rt(lhs);
			return rt -= rhs;
		}

		// scalar multiply
		friend Vector3<T> operator * (const Vector3<T> & lhs, T rhs) {
			Vector3<T> rt(lhs);
			return rt *= rhs;
		}

		// scalar multiply
		friend Vector3<T> operator * (T lhs, const Vector3<T> & rhs) {
			Vector3<T> rt(lhs);
			return rt *= rhs;
		}

		// vector component-wise multiply
		friend Vector3<T> operator * (const Vector3<T> & lhs, const Vector3<T> & rhs){
			Vector3<T> rt(lhs);
			return rt *= rhs;
		}

		// scalar multiply
		friend Vector3<T> operator / (const Vector3<T> & lhs, T rhs) {
			Vector3<T> rt(lhs);
			return rt /= rhs;
		}

		// vector component-wise multiply
		friend Vector3<T> operator / (const Vector3<T> & lhs, const Vector3<T> & rhs){
			Vector3<T> rt(lhs);
			return rt /= rhs;
		}

		// vector - axis rotation //harish
		void rotate(float angle, T vx, T vy, T vz) //harish
		{
			Vector3<T> NewPosition;

			// Calculate the sine and cosine of the angle once
			float cosTheta = (float)cos(angle);
			float sinTheta = (float)sin(angle);


			NewPosition._array[0] = (cosTheta + (1 - cosTheta) * vx * vx)            * _array[0];
			NewPosition._array[0] += ((1 - cosTheta) * vx * vy - vz * sinTheta)    * _array[1];
			NewPosition._array[0] += ((1 - cosTheta) * vx * vz + vy * sinTheta)    * _array[2];


			NewPosition._array[1] = ((1 - cosTheta) * vx * vy + vz * sinTheta)    * _array[0];
			NewPosition._array[1] += (cosTheta + (1 - cosTheta) * vy * vy)        * _array[1];
			NewPosition._array[1] += ((1 - cosTheta) * vy * vz - vx * sinTheta)    * _array[2];

			NewPosition._array[2] = ((1 - cosTheta) * vx * vz - vy * sinTheta)    *  _array[0];
			NewPosition._array[2] += ((1 - cosTheta) * vy * vz + vx * sinTheta)    *  _array[1];
			NewPosition._array[2] += (cosTheta + (1 - cosTheta) * vz * vz)        *  _array[2];

			_array[0] = NewPosition._array[0];
			_array[1] = NewPosition._array[1];
			_array[2] = NewPosition._array[2];
		}

		//Calculate the cross product
		Vector3<T> cross(Vector3<T> vec) //harish
		{
			Vector3<T> vNormal;                                    // The vector to hold the cross product

			vNormal._array[0] = ((_array[1] * vec._array[2]) - (_array[2] * vec._array[1]));
			vNormal._array[1] = ((_array[2] * vec._array[0]) - (_array[0] * vec._array[2]));
			vNormal._array[2] = ((_array[0] * vec._array[1]) - (_array[1] * vec._array[0]));

			return vNormal;
		}

		////////////////////////////////////////////////////////
		//
		//  Comparison operators
		//
		////////////////////////////////////////////////////////

		// equality
		friend bool operator == (const Vector3<T> &lhs, const Vector3<T> &rhs) {
			bool r = true;
			for (int32_t i = 0; i < lhs.size(); i++)
				r &= lhs._array[i] == rhs._array[i];
			return r;
		}

		// inequality
		friend bool operator != (const Vector3<T> &lhs, const Vector3<T> &rhs) {
			bool r = true;
			for (int32_t i = 0; i < lhs.size(); i++)
				r &= lhs._array[i] != rhs._array[i];
			return r;
		}

		////////////////////////////////////////////////////////////////////////////////
		//
		// dimension specific operations
		//
		////////////////////////////////////////////////////////////////////////////////

		// cross product
		static Vector3<T> cross(const Vector3<T> & lhs, const Vector3<T> & rhs) {
			Vector3<T> r;

			r.x = lhs.y * rhs.z - lhs.z * rhs.y;
			r.y = lhs.z * rhs.x - lhs.x * rhs.z;
			r.z = lhs.x * rhs.y - lhs.y * rhs.x;

			return r;
		}

		static T dot(const Vector3<T> & lhs, const Vector3<T> & rhs) {
			T r = 0;
			for (int32_t i = 0; i < lhs.size(); i++) r += lhs._array[i] * rhs._array[i];
			return r;
		}

		static T length(const Vector3<T> & vec) {
			T r = 0;
			for (int32_t i = 0; i < vec.size(); i++) r += vec._array[i] * vec._array[i];
			return T(sqrt(r));
		}

		static T square_norm(const Vector3<T> & vec) {
			T r = 0;
			for (int32_t i = 0; i < vec.size(); i++) r += vec._array[i] * vec._array[i];
			return r;
		}

		static Vector3<T> normalize(const Vector3<T> & vec) {
			T sum(0);
			Vector3<T> r;
			for (int32_t i = 0; i < vec.size(); i++)
				sum += vec._array[i] * vec._array[i];
			sum = T(sqrt(sum));
			if (sum > 0)
			for (int32_t i = 0; i < vec.size(); i++)
				r._array[i] = vec._array[i] / sum;
			return r;
		}

		//data intentionally left public to allow vec2.x
		union {
			struct {
				T x, y, z;          // standard names for components
			};
			struct {
				T s, t, r;          // standard names for components
			};
			T _array[3];     // array access
		};

		static const Vector3<T> ZERO;
		static const Vector3<T> ONE;
	};

	template<class T>const Vector3<T> Vector3<T>::ZERO(0, 0, 0);
	template<class T>const Vector3<T> Vector3<T>::ONE(1, 1, 1);

	typedef Vector3<float> Vector3f; ///< float 3-vectors
	typedef Vector3<int32_t> Vector3i; ///< signed integer 3-vectors
	typedef Vector3<uint32_t> Vector3ui; ///< unsigned integer 4-vectors
}