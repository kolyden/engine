#pragma once
#include "uutMath.h"

namespace uut
{
	template <class T>
	class Vector4
	{
	public:
		typedef T value_type;
		int32_t size() const { return 4; }

		////////////////////////////////////////////////////////
		//
		//  Constructors
		//
		////////////////////////////////////////////////////////

		// Default/scalar constructor
		Vector4(const T & t = T()) {
			for (int32_t i = 0; i < size(); i++) _array[i] = t;
		}

		// Construct from array
		Vector4(const T * tp) {
			for (int32_t i = 0; i < size(); i++) _array[i] = tp[i];
		}

		// Construct from explicit values
		Vector4(const T v0, const T v1, const T v2, const T v3) {
			x = v0;
			y = v1;
			z = v2;
			w = v3;
		}

		explicit Vector4(const Vector3<T> &u, T v0) {
			x = u.x;
			y = u.y;
			z = u.z;
			w = v0;
		}

		explicit Vector4(const Vector2<T> &u, T v0, T v1) {
			x = u.x;
			y = u.y;
			z = v0;
			w = v1;
		}

		const T * get_value() const {
			return _array;
		}

		Vector4<T> & set_value(const T * rhs) {
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
		friend Vector4<T> & operator *= (Vector4<T> &lhs, T d) {
			for (int32_t i = 0; i < lhs.size(); i++) lhs._array[i] *= d;
			return lhs;
		}

		// component-wise vector multiply assign
		friend Vector4<T> & operator *= (Vector4<T> &lhs, const Vector4<T> &rhs) {
			for (int32_t i = 0; i < lhs.size(); i++) lhs._array[i] *= rhs[i];
			return lhs;
		}

		// scalar divide assign
		friend Vector4<T> & operator /= (Vector4<T> &lhs, T d) {
			if (d == 0) return lhs;
			for (int32_t i = 0; i < lhs.size(); i++) lhs._array[i] /= d;
			return lhs;
		}

		// component-wise vector divide assign
		friend Vector4<T> & operator /= (Vector4<T> &lhs, const Vector4<T> & rhs) {
			for (int32_t i = 0; i < lhs.size(); i++) lhs._array[i] /= rhs._array[i];
			return lhs;
		}

		// component-wise vector add assign
		friend Vector4<T> & operator += (Vector4<T> &lhs, const Vector4<T> & rhs) {
			for (int32_t i = 0; i < lhs.size(); i++) lhs._array[i] += rhs._array[i];
			return lhs;
		}

		// component-wise vector subtract assign
		friend Vector4<T> & operator -= (Vector4<T> &lhs, const Vector4<T> & rhs) {
			for (int32_t i = 0; i < lhs.size(); i++) lhs._array[i] -= rhs._array[i];
			return lhs;
		}

		// unary negate
		friend Vector4<T> operator - (const Vector4<T> &rhs) {
			Vector4<T> rv;
			for (int32_t i = 0; i < rhs.size(); i++) rv._array[i] = -rhs._array[i];
			return rv;
		}

		// vector add
		friend Vector4<T> operator + (const Vector4<T> & lhs, const Vector4<T> & rhs) {
			Vector4<T> rt(lhs);
			return rt += rhs;
		}

		// vector subtract
		friend Vector4<T> operator - (const Vector4<T> & lhs, const Vector4<T> & rhs) {
			Vector4<T> rt(lhs);
			return rt -= rhs;
		}

		// scalar multiply
		friend Vector4<T> operator * (const Vector4<T> & lhs, T rhs) {
			Vector4<T> rt(lhs);
			return rt *= rhs;
		}

		// scalar multiply
		friend Vector4<T> operator * (T lhs, const Vector4<T> & rhs) {
			Vector4<T> rt(lhs);
			return rt *= rhs;
		}

		// vector component-wise multiply
		friend Vector4<T> operator * (const Vector4<T> & lhs, const Vector4<T> & rhs){
			Vector4<T> rt(lhs);
			return rt *= rhs;
		}

		// scalar multiply
		friend Vector4<T> operator / (const Vector4<T> & lhs, T rhs) {
			Vector4<T> rt(lhs);
			return rt /= rhs;
		}

		// vector component-wise multiply
		friend Vector4<T> operator / (const Vector4<T> & lhs, const Vector4<T> & rhs){
			Vector4<T> rt(lhs);
			return rt /= rhs;
		}

		////////////////////////////////////////////////////////
		//
		//  Comparison operators
		//
		////////////////////////////////////////////////////////

		// equality
		friend bool operator == (const Vector4<T> &lhs, const Vector4<T> &rhs) {
			bool r = true;
			for (int32_t i = 0; i < lhs.size(); i++)
				r &= lhs._array[i] == rhs._array[i];
			return r;
		}

		// inequality
		friend bool operator != (const Vector4<T> &lhs, const Vector4<T> &rhs) {
			bool r = true;
			for (int32_t i = 0; i < lhs.size(); i++)
				r &= lhs._array[i] != rhs._array[i];
			return r;
		}

		//data intentionally left public to allow vec2.x
		union {
			struct {
				T x, y, z, w;          // standard names for components
			};
			struct {
				T s, t, r, q;          // standard names for components
			};
			T _array[4];     // array access
		};
	};



	////////////////////////////////////////////////////////////////////////////////
	//
	// Generic vector operations
	//
	////////////////////////////////////////////////////////////////////////////////

	// compute the dot product of two vectors
	//template<class T>
	//inline typename T::value_type dot( const T & lhs, const T & rhs ) {
	//    T::value_type r = 0;
	//    for(int32_t i = 0; i < lhs.size(); i++) r += lhs._array[i] * rhs._array[i];
	//    return r;
	//}

	template<class T>
	inline T dot(const Vector2<T> & lhs, const Vector2<T> & rhs) {
		T r = 0;
		for (int32_t i = 0; i < lhs.size(); i++) r += lhs._array[i] * rhs._array[i];
		return r;
	}

	template<class T>
	inline T dot(const Vector3<T> & lhs, const Vector3<T> & rhs) {
		T r = 0;
		for (int32_t i = 0; i < lhs.size(); i++) r += lhs._array[i] * rhs._array[i];
		return r;
	}

	template<class T>
	inline T dot(const Vector4<T> & lhs, const Vector4<T> & rhs) {
		T r = 0;
		for (int32_t i = 0; i < lhs.size(); i++) r += lhs._array[i] * rhs._array[i];
		return r;
	}

	// return the length of the provided vector
	//template< class T>
	//inline typename T::value_type length( const T & vec) {
	//    T::value_type r = 0;
	//    for(int32_t i = 0; i < vec.size(); i++) r += vec._array[i]*vec._array[i];
	//    return T::value_type(sqrt(r));
	//}


	template<class T>
	inline T length(const Vector2<T> & vec) {
		T r = 0;
		for (int32_t i = 0; i < vec.size(); i++) r += vec._array[i] * vec._array[i];
		return T(sqrt(r));
	}

	template<class T>
	inline T length(const Vector3<T> & vec) {
		T r = 0;
		for (int32_t i = 0; i < vec.size(); i++) r += vec._array[i] * vec._array[i];
		return T(sqrt(r));
	}

	template<class T>
	inline T length(const Vector4<T> & vec) {
		T r = 0;
		for (int32_t i = 0; i < vec.size(); i++) r += vec._array[i] * vec._array[i];
		return T(sqrt(r));
	}

	// return the squared norm
	//template< class T>
	//inline typename T::value_type square_norm( const T & vec) {
	//    T::value_type r = 0;
	//    for(int32_t i = 0; i < vec.size(); i++) r += vec._array[i]*vec._array[i];
	//    return r;
	//}

	template< class T>
	inline T square_norm(const Vector2<T> & vec) {
		T r = 0;
		for (int32_t i = 0; i < vec.size(); i++) r += vec._array[i] * vec._array[i];
		return r;
	}

	template< class T>
	inline T square_norm(const Vector3<T> & vec) {
		T r = 0;
		for (int32_t i = 0; i < vec.size(); i++) r += vec._array[i] * vec._array[i];
		return r;
	}

	template< class T>
	inline T square_norm(const Vector4<T> & vec) {
		T r = 0;
		for (int32_t i = 0; i < vec.size(); i++) r += vec._array[i] * vec._array[i];
		return r;
	}

	// return the normalized version of the vector
	//template< class T>
	//inline T normalize( const T & vec) {
	//    T::value_type sum(0);
	//    T r;
	//    for(int32_t i = 0; i < vec.size(); i++)
	//        sum += vec._array[i] * vec._array[i];
	//    sum = T::value_type(sqrt(sum));
	//    if (sum > 0)
	//        for(int32_t i = 0; i < vec.size(); i++)
	//            r._array[i] = vec._array[i] / sum;
	//    return r;
	//}

	template< class T>
	inline Vector2<T> normalize(const Vector2<T> & vec) {
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

	template< class T>
	inline Vector3<T> normalize(const Vector3<T> & vec) {
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

	template< class T>
	inline Vector4<T> normalize(const Vector4<T> & vec) {
		T sum(0);
		Vector4<T> r;
		for (int32_t i = 0; i < vec.size(); i++)
			sum += vec._array[i] * vec._array[i];
		sum = T(sqrt(sum));
		if (sum > 0)
		for (int32_t i = 0; i < vec.size(); i++)
			r._array[i] = vec._array[i] / sum;
		return r;
	}

	// In VC8 : min and max are already defined by a #define...
#ifdef min
#undef min
#endif
#ifdef max
#undef max
#endif
	//componentwise min
	template< class T>
	inline T min(const T & lhs, const T & rhs) {
		T rt;
		for (int32_t i = 0; i < lhs.size(); i++) rt._array[i] = std::min(lhs._array[i], rhs._array[i]);
		return rt;
	}

	// componentwise max
	template< class T>
	inline T max(const T & lhs, const T & rhs) {
		T rt;
		for (int32_t i = 0; i < lhs.size(); i++) rt._array[i] = std::max(lhs._array[i], rhs._array[i]);
		return rt;
	}

	typedef Vector4<float> Vector4f; ///< float 4-vectors
	typedef Vector4<int32_t> Vector4i; ///< signed integer 4-vectors
	typedef Vector4<uint32_t> Vector4ui; ///< unsigned integer 4-vectors
}