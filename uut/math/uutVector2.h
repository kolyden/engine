#pragma once
#include "math/uutMath.h"

namespace uut
{
	template<class T>class Vector3;
	template<class T>class Vector4;

	/// Template class for 2-tuple vector.
	template <class T>
	class Vector2
	{
	public:
		typedef T value_type;
		int32_t size() const { return 2; }

		/// Default/scalar constructor
		Vector2(const T & t = T()) {
			for (int32_t i = 0; i < size(); i++) _array[i] = t;
		}

		/// Construct from array
		Vector2(const T * tp) {
			for (int32_t i = 0; i < size(); i++) _array[i] = tp[i];
		}

		/// Construct from explicit values
		Vector2(const T v0, const T v1) {
			x = v0;
			y = v1;
		}

		template<class C>
		explicit Vector2(const Vector2<C>& u)
			: x((T)u.x), y((T)u.y)
		{}

		/// "Cropping" explicit constructor from vec3 to vec2
		explicit Vector2(const Vector3<T> &u) {
			for (int32_t i = 0; i < size(); i++) _array[i] = u._array[i];
		}

		/// "Cropping" explicit constructor from vec4 to vec2
		explicit Vector2(const Vector4<T> &u) {
			for (int32_t i = 0; i < size(); i++) _array[i] = u._array[i];
		}

		const T * get_value() const {
			return _array;
		}

		Vector2<T> & set_value(const T * rhs) {
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
		friend Vector2<T> & operator *= (Vector2<T> &lhs, T d) {
			for (int32_t i = 0; i < lhs.size(); i++) lhs._array[i] *= d;
			return lhs;
		}

		// component-wise vector multiply assign
		friend Vector2<T> & operator *= (Vector2<T> &lhs, const Vector2<T> &rhs) {
			for (int32_t i = 0; i < lhs.size(); i++) lhs._array[i] *= rhs[i];
			return lhs;
		}

		// scalar divide assign
		friend Vector2<T> & operator /= (Vector2<T> &lhs, T d) {
			if (d == 0) return lhs;
			for (int32_t i = 0; i < lhs.size(); i++) lhs._array[i] /= d;
			return lhs;
		}

		// component-wise vector divide assign
		//    friend vec2<T> & operator /= ( vec2<T> &lhs, const vec2<T> & rhs ) {
		//        for(int32_t i = 0; i < lhs.size(); i++) lhs._array[i] /= rhs._array[i];
		//        return *this;
		//    }

		// component-wise vector add assign
		friend Vector2<T> & operator += (Vector2<T> &lhs, const Vector2<T> & rhs) {
			for (int32_t i = 0; i < lhs.size(); i++) lhs._array[i] += rhs._array[i];
			return lhs;
		}

		// component-wise vector subtract assign
		friend Vector2<T> & operator -= (Vector2<T> &lhs, const Vector2<T> & rhs) {
			for (int32_t i = 0; i < lhs.size(); i++) lhs._array[i] -= rhs._array[i];
			return lhs;
		}

		// unary negate
		friend Vector2<T> operator - (const Vector2<T> &rhs) {
			Vector2<T> rv;
			for (int32_t i = 0; i < rhs.size(); i++) rv._array[i] = -rhs._array[i];
			return rv;
		}

		// vector add
		friend Vector2<T> operator + (const Vector2<T> & lhs, const Vector2<T> & rhs) {
			Vector2<T> rt(lhs);
			return rt += rhs;
		}

		// vector subtract
		friend Vector2<T> operator - (const Vector2<T> & lhs, const Vector2<T> & rhs) {
			Vector2<T> rt(lhs);
			return rt -= rhs;
		}

		// scalar multiply
		friend Vector2<T> operator * (const Vector2<T> & lhs, T rhs) {
			Vector2<T> rt(lhs);
			return rt *= rhs;
		}

		// scalar multiply
		friend Vector2<T> operator * (T lhs, const Vector2<T> & rhs) {
			Vector2<T> rt(lhs);
			return rt *= rhs;
		}

		// vector component-wise multiply
		friend Vector2<T> operator * (const Vector2<T> & lhs, const Vector2<T> & rhs){
			Vector2<T> rt(lhs);
			return rt *= rhs;
		}

		// scalar multiply
		friend Vector2<T> operator / (const Vector2<T> & lhs, T rhs) {
			Vector2<T> rt(lhs);
			return rt /= rhs;
		}

		// vector component-wise multiply
		friend Vector2<T> operator / (const Vector2<T> & lhs, const Vector2<T> & rhs){
			Vector2<T> rt(lhs);
			return rt /= rhs;
		}

		////////////////////////////////////////////////////////
		//
		//  Comparison operators
		//
		////////////////////////////////////////////////////////

		// equality
		friend bool operator == (const Vector2<T> &lhs, const Vector2<T> &rhs) {
			bool r = true;
			for (int32_t i = 0; i < lhs.size(); i++)
				r &= lhs._array[i] == rhs._array[i];
			return r;
		}

		// inequality
		friend bool operator != (const Vector2<T> &lhs, const Vector2<T> &rhs) {
			bool r = true;
			for (int32_t i = 0; i < lhs.size(); i++)
				r &= lhs._array[i] != rhs._array[i];
			return r;
		}

		static T dot(const Vector2<T> & lhs, const Vector2<T> & rhs) {
			T r = 0;
			for (int32_t i = 0; i < lhs.size(); i++) r += lhs._array[i] * rhs._array[i];
			return r;
		}

		static T length(const Vector2<T> & vec) {
			T r = 0;
			for (int32_t i = 0; i < vec.size(); i++) r += vec._array[i] * vec._array[i];
			return T(sqrt(r));
		}

		static T square_norm(const Vector2<T> & vec) {
			T r = 0;
			for (int32_t i = 0; i < vec.size(); i++) r += vec._array[i] * vec._array[i];
			return r;
		}

		static Vector2<T> normalize(const Vector2<T> & vec) {
			T sum(0);
			Vector2<T> r;
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
				T x, y;          // standard names for components
			};
			struct {
				T s, t;          // standard names for components
			};
			T _array[2];     // array access
		};

		static const Vector2<T> ZERO;
		static const Vector2<T> ONE;
	};

	template<class T>const Vector2<T> Vector2<T>::ZERO(0, 0);
	template<class T>const Vector2<T> Vector2<T>::ONE(1, 1);

	typedef Vector2<float> Vector2f; ///< float 2-vectors
	typedef Vector2<int32_t> Vector2i; ///< signed integer 2-vectors
	typedef Vector2<uint32_t> Vector2ui; ///< unsigned integer 2-vectors
}