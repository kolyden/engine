#pragma once
#include "math/uutMath.h"

namespace uut
{
	template<class T>class Vector3;
	template<class T>class Rect;

	template<class T>
	class Matrix4
	{
	public:
		Matrix4() { make_identity(); }

		Matrix4(T t)
		{
			set_value(t);
		}

		Matrix4(const T * m)
		{
			set_value(m);
		}

		Matrix4(T a00, T a01, T a02, T a03,
			T a10, T a11, T a12, T a13,
			T a20, T a21, T a22, T a23,
			T a30, T a31, T a32, T a33) :
			_11(a00), _12(a01), _13(a02), _14(a03),
			_21(a10), _22(a11), _23(a12), _24(a13),
			_31(a20), _32(a21), _33(a22), _34(a23),
			_41(a30), _42(a31), _43(a32), _44(a33)
		{}


		void get_value(T * mp) const {
			int32_t c = 0;
			for (int32_t j = 0; j < 4; j++)
			for (int32_t i = 0; i < 4; i++)
				mp[c++] = element(i, j);
		}

		const T * get_value() const {
			return _array;
		}

		void set_value(T * mp) {
			int32_t c = 0;
			for (int32_t j = 0; j < 4; j++)
			for (int32_t i = 0; i < 4; i++)
				element(i, j) = mp[c++];
		}

		void set_value(T r) {
			for (int32_t i = 0; i < 4; i++)
			for (int32_t j = 0; j < 4; j++)
				element(i, j) = r;
		}

		void make_identity() {
			element(0, 0) = 1.0;
			element(0, 1) = 0.0;
			element(0, 2) = 0.0;
			element(0, 3) = 0.0;

			element(1, 0) = 0.0;
			element(1, 1) = 1.0;
			element(1, 2) = 0.0;
			element(1, 3) = 0.0;

			element(2, 0) = 0.0;
			element(2, 1) = 0.0;
			element(2, 2) = 1.0;
			element(2, 3) = 0.0;

			element(3, 0) = 0.0;
			element(3, 1) = 0.0;
			element(3, 2) = 0.0;
			element(3, 3) = 1.0;
		}

		// set a uniform scale
		void set_scale(T s) {
			element(0, 0) = s;
			element(1, 1) = s;
			element(2, 2) = s;
		}

		void set_scale(const Vector3<T> & s) {
			for (int32_t i = 0; i < 3; i++) element(i, i) = s[i];
		}


		void set_translate(const Vector3<T> & t) {
			for (int32_t i = 0; i < 3; i++) element(i, 3) = t[i];
		}

		void set_row(int32_t r, const Vector4<T> & t) {
			for (int32_t i = 0; i < 4; i++) element(r, i) = t[i];
		}

		void set_column(int32_t c, const Vector4<T> & t) {
			for (int32_t i = 0; i < 4; i++) element(i, c) = t[i];
		}

		Vector4<T> get_row(int32_t r) const {
			Vector4<T> v;
			for (int32_t i = 0; i < 4; i++) v[i] = element(r, i);
			return v;
		}

		Vector4<T> get_column(int32_t c) const {
			Vector4<T> v;
			for (int32_t i = 0; i < 4; i++) v[i] = element(i, c);
			return v;
		}

		Matrix4 & operator *= (const Matrix4 & rhs) {
			Matrix4 mt(*this);
			set_value(T(0));

			for (int32_t i = 0; i < 4; i++)
			for (int32_t j = 0; j < 4; j++)
			for (int32_t c = 0; c < 4; c++)
				element(i, j) += mt(i, c) * rhs(c, j);
			return *this;
		}

		friend Matrix4 operator * (const Matrix4 & lhs, const Matrix4 & rhs) {
			Matrix4 r(T(0));

			for (int32_t i = 0; i < 4; i++)
			for (int32_t j = 0; j < 4; j++)
			for (int32_t c = 0; c < 4; c++)
				r.element(i, j) += lhs(i, c) * rhs(c, j);
			return r;
		}

		// dst = M * src
		Vector4<T> operator *(const Vector4<T> &src) const {
			Vector4<T> r;
			for (int32_t i = 0; i < 4; i++)
				r[i] = (src[0] * element(i, 0) + src[1] * element(i, 1) +
				src[2] * element(i, 2) + src[3] * element(i, 3));
			return r;
		}

		// dst = src * M
		friend Vector4<T> operator *(const Vector4<T> &lhs, const Matrix4 &rhs) {
			Vector4<T> r;
			for (int32_t i = 0; i < 4; i++)
				r[i] = (lhs[0] * rhs.element(0, i) + lhs[1] * rhs.element(1, i) +
				lhs[2] * rhs.element(2, i) + lhs[3] * rhs.element(3, i));
			return r;
		}

		T & operator () (int32_t row, int32_t col) {
			return element(row, col);
		}

		const T & operator () (int32_t row, int32_t col) const {
			return element(row, col);
		}

		T & element(int32_t row, int32_t col) {
			return _array[row | (col << 2)];
		}

		const T & element(int32_t row, int32_t col) const {
			return _array[row | (col << 2)];
		}

		Matrix4 & operator *= (const T & r) {
			for (int32_t i = 0; i < 4; ++i) {
				element(0, i) *= r;
				element(1, i) *= r;
				element(2, i) *= r;
				element(3, i) *= r;
			}
			return *this;
		}

		Matrix4 & operator += (const Matrix4 & mat) {
			for (int32_t i = 0; i < 4; ++i) {
				element(0, i) += mat.element(0, i);
				element(1, i) += mat.element(1, i);
				element(2, i) += mat.element(2, i);
				element(3, i) += mat.element(3, i);
			}
			return *this;
		}


		friend bool operator == (const Matrix4 & lhs, const Matrix4 & rhs) {
			bool r = true;
			for (int32_t i = 0; i < 16; i++)
				r &= lhs._array[i] == rhs._array[i];
			return r;
		}

		friend bool operator != (const Matrix4 & lhs, const Matrix4 & rhs)  {
			bool r = true;
			for (int32_t i = 0; i < 16; i++)
				r &= lhs._array[i] != rhs._array[i];
			return r;
		}

		template<class T>
		static Matrix4<T> inverse(const Matrix4<T> & m) {
			Matrix4<T> minv;

			T r1[8], r2[8], r3[8], r4[8];
			T *s[4], *tmprow;

			s[0] = &r1[0];
			s[1] = &r2[0];
			s[2] = &r3[0];
			s[3] = &r4[0];

			register int32_t i, j, p, jj;
			for (i = 0; i < 4; i++) {
				for (j = 0; j < 4; j++) {
					s[i][j] = m.element(i, j);
					if (i == j) s[i][j + 4] = 1.0;
					else     s[i][j + 4] = 0.0;
				}
			}
			T scp[4];
			for (i = 0; i < 4; i++) {
				scp[i] = T(fabs(s[i][0]));
				for (j = 1; j<4; j++)
				if (T(fabs(s[i][j])) > scp[i]) scp[i] = T(fabs(s[i][j]));
				if (scp[i] == 0.0) return minv; // singular matrix!
			}

			int32_t pivot_to;
			T scp_max;
			for (i = 0; i < 4; i++) {
				// select pivot row
				pivot_to = i;
				scp_max = T(fabs(s[i][i] / scp[i]));
				// find out which row should be on top
				for (p = i + 1; p<4; p++)
				if (T(fabs(s[p][i] / scp[p])) > scp_max) {
					scp_max = T(fabs(s[p][i] / scp[p]));
					pivot_to = p;
				}
				// Pivot if necessary
				if (pivot_to != i) {
					tmprow = s[i];
					s[i] = s[pivot_to];
					s[pivot_to] = tmprow;
					T tmpscp;
					tmpscp = scp[i];
					scp[i] = scp[pivot_to];
					scp[pivot_to] = tmpscp;
				}

				T mji;
				// perform gaussian elimination
				for (j = i + 1; j < 4; j++) {
					mji = s[j][i] / s[i][i];
					s[j][i] = 0.0;
					for (jj = i + 1; jj < 8; jj++)
						s[j][jj] -= mji*s[i][jj];
				}
			}
			if (s[3][3] == 0.0) return minv; // singular matrix!

			//
			// Now we have an upper triangular matrix.
			//
			//  x x x x | y y y y
			//  0 x x x | y y y y
			//  0 0 x x | y y y y
			//  0 0 0 x | y y y y
			//
			//  we'll back substitute to get the inverse
			//
			//  1 0 0 0 | z z z z
			//  0 1 0 0 | z z z z
			//  0 0 1 0 | z z z z
			//  0 0 0 1 | z z z z
			//

			T mij;
			for (i = 3; i > 0; i--) {
				for (j = i - 1; j > -1; j--) {
					mij = s[j][i] / s[i][i];
					for (jj = j + 1; jj < 8; jj++)
						s[j][jj] -= mij*s[i][jj];
				}
			}

			for (i = 0; i < 4; i++)
			for (j = 0; j < 4; j++)
				minv(i, j) = s[i][j + 4] / s[i][i];

			return minv;
		}


		//
		// transpose
		//
		//   return the transposed matrix
		////////////////////////////////////////////////////////////
		template<class T>
		static Matrix4<T> transpose(const Matrix4<T> & m) {
			Matrix4<T> mtrans;

			for (int32_t i = 0; i < 4; i++)
			for (int32_t j = 0; j < 4; j++)
				mtrans(i, j) = m.element(j, i);
			return mtrans;
		}

		//
		// Rotation matrix creation
		// From rotation angle around X axis [radians]
		//
		//   return the rotation matrix
		////////////////////////////////////////////////////////////
		template<class T>
		static Matrix4<T>& rotationX(Matrix4<T> & M, const T angle)
		{
			T cosa = cos(angle);
			T sina = sin(angle);

			M.element(0, 0) = 1.0;
			M.element(0, 1) = 0.0;
			M.element(0, 2) = 0.0;
			M.element(0, 3) = 0.0;

			M.element(1, 0) = 0.0;
			M.element(1, 1) = cosa;
			M.element(1, 2) = -sina;
			M.element(1, 3) = 0.0;

			M.element(2, 0) = 0.0;
			M.element(2, 1) = sina;
			M.element(2, 2) = cosa;
			M.element(2, 3) = 0.0;

			M.element(3, 0) = 0.0;
			M.element(3, 1) = 0.0;
			M.element(3, 2) = 0.0;
			M.element(3, 3) = 1.0;

			return M;
		}

		//
		// Rotation matrix creation
		// From rotation angle around Y axis [radians]
		//
		//   return the rotation matrix
		////////////////////////////////////////////////////////////
		template<class T>
		static Matrix4<T>& rotationY(Matrix4<T> & M, const T angle)
		{
			T cosa = cos(angle);
			T sina = sin(angle);

			M.element(0, 0) = cosa;
			M.element(0, 1) = 0.0;
			M.element(0, 2) = sina;
			M.element(0, 3) = 0.0;

			M.element(1, 0) = 0.0;
			M.element(1, 1) = 1.0;
			M.element(1, 2) = 0.0;
			M.element(1, 3) = 0.0;

			M.element(2, 0) = -sina;
			M.element(2, 1) = 0.0;
			M.element(2, 2) = cosa;
			M.element(2, 3) = 0.0;

			M.element(3, 0) = 0.0;
			M.element(3, 1) = 0.0;
			M.element(3, 2) = 0.0;
			M.element(3, 3) = 1.0;

			return M;
		}

		//
		// Rotation matrix creation
		// From rotation angle around Y axis [radians]
		//
		//   return the rotation matrix
		////////////////////////////////////////////////////////////
		template<class T>
		static Matrix4<T>& rotationZ(Matrix4<T> & M, const T angle)
		{
			T cosa = cos(angle);
			T sina = sin(angle);

			M.element(0, 0) = cosa;
			M.element(0, 1) = -sina;
			M.element(0, 2) = 0.0;
			M.element(0, 3) = 0.0;

			M.element(1, 0) = sina;
			M.element(1, 1) = cosa;
			M.element(1, 2) = 0.0;
			M.element(1, 3) = 0.0;

			M.element(2, 0) = 0.0;
			M.element(2, 1) = 0.0;
			M.element(2, 2) = 1.0;
			M.element(2, 3) = 0.0;

			M.element(3, 0) = 0.0;
			M.element(3, 1) = 0.0;
			M.element(3, 2) = 0.0;
			M.element(3, 3) = 1.0;

			return M;
		}

		//
		// Rotation matrix creation
		// From euler angles
		//      1/ Yaw around Y axis in radians
		//      2/ Pitch around X axis in radians
		//      3/ Roll around Z axis in radians
		//
		//   return the rotation matrix [R] = [Roll].{Pitch].[Yaw]
		////////////////////////////////////////////////////////////
		template<class T>
		static Matrix4<T>& rotationYawPitchRoll(Matrix4<T> & M, const T yaw, const T pitch, const T roll)
		{
			M.make_identity();
			Matrix4<T> rot;

			if (roll)
			{
				nv::rotationZ(M, roll);
			}
			if (pitch)
			{
				M *= nv::rotationX(rot, pitch);
			}
			if (yaw)
			{
				M *= nv::rotationY(rot, yaw);
			}

			return M;
		}

		//
		// Translation matrix creation
		// From absolute translation values along X, Y and Z axis
		//
		//   return the translation matrix
		////////////////////////////////////////////////////////////
		template<class T>
		static Matrix4<T>& translation(Matrix4<T> & M, const T tx, const T ty, const T tz)
		{
			M.element(0, 0) = 1.0;
			M.element(1, 0) = 0.0;
			M.element(2, 0) = 0.0;
			M.element(3, 0) = 0.0;

			M.element(0, 1) = 0.0;
			M.element(1, 1) = 1.0;
			M.element(2, 1) = 0.0;
			M.element(3, 1) = 0.0;

			M.element(0, 2) = 0.0;
			M.element(1, 2) = 0.0;
			M.element(2, 2) = 1.0;
			M.element(3, 2) = 0.0;

			M.element(0, 3) = tx;
			M.element(1, 3) = ty;
			M.element(2, 3) = tz;
			M.element(3, 3) = 1.0;

			return M;
		}

		template<class T>
		static Matrix4<T>& translation(Matrix4<T> & M, const Vector3<T>& vec)
		{
			return translation(M, vec.x, vec.y, vec.z);
		}


		//
		// Look At matrix creation
		//
		//   return the inverse view matrix
		////////////////////////////////////////////////////////////
		template<class T>
		static Matrix4<T> & lookAt(Matrix4<T>& M, const Vector3<T>& eye, const Vector3<T>& center, const Vector3<T>& up)
		{
			Vector3<T> x, y, z;

			// make rotation matrix

			// Z vector
			z.x = eye.x - center.x;
			z.y = eye.y - center.y;
			z.z = eye.z - center.z;
			z = normalize(z);

			// Y vector
			y.x = up.x;
			y.y = up.y;
			y.z = up.z;

			// X vector = Y cross Z
			x = cross(y, z);

			// Recompute Y = Z cross X
			y = cross(z, x);

			// cross product gives area of parallelogram, which is < 1.0 for
			// non-perpendicular unit-length vectors; so normalize x, y here
			x = normalize(x);
			y = normalize(y);

			M._11 = x.x; M._21 = x.y; M._31 = x.z; M._41 = -x.x * eye.x - x.y * eye.y - x.z*eye.z;
			M._12 = y.x; M._22 = y.y; M._32 = y.z; M._42 = -y.x * eye.x - y.y * eye.y - y.z*eye.z;
			M._13 = z.x; M._23 = z.y; M._33 = z.z; M._43 = -z.x * eye.x - z.y * eye.y - z.z*eye.z;
			M._14 = 0.0; M._24 = 0.0; M._34 = 0.0; M._44 = 1.0;
			return M;
		}

		//
		// Projection matrix creation (Right Handed, OpenGL standard)
		// From the frustum definition
		//
		//   return the projection matrix
		////////////////////////////////////////////////////////////
		template<class T>
		static Matrix4<T>& frustum(Matrix4<T> & M, const T l, const T r, const T b, const T t, const T n, const T f)
		{
			M.element(0, 0) = ((T)(2.0))*n / (r - l);
			M.element(1, 0) = 0.0;
			M.element(2, 0) = 0.0;
			M.element(3, 0) = 0.0;

			M.element(0, 1) = 0.0;
			M.element(1, 1) = ((T)(2.0))*n / (t - b);
			M.element(2, 1) = 0.0;
			M.element(3, 1) = 0.0;

			M.element(0, 2) = (r + l) / (r - l);
			M.element(1, 2) = (t + b) / (t - b);
			M.element(2, 2) = -(f + n) / (f - n);
			M.element(3, 2) = -1.0;

			M.element(0, 3) = 0.0;
			M.element(1, 3) = 0.0;
			M.element(2, 3) = -(((T)(2.0))*f*n) / (f - n);
			M.element(3, 3) = 0.0;

			return M;
		}

		//
		// Projection matrix creation (Right Handed, OpenGL standard)
		// From the fovy in radians, aspect ratio and near far definition
		//
		//   return the projection matrix
		////////////////////////////////////////////////////////////
		template<class T>
		static Matrix4<T>& perspective(Matrix4<T> & M, const T fovy, const T aspect, const T n, const T f)
		{
			T xmin, xmax, ymin, ymax;

			ymax = n * (T)tan(fovy * 0.5);
			ymin = -ymax;

			xmin = ymin * aspect;
			xmax = ymax * aspect;

			return frustum(M, xmin, xmax, ymin, ymax, n, f);
		}

		template<class T>
		static Matrix4<T>& perspectivex(Matrix4<T> & M, const T fovx, const T aspect, const T near, const T far)
		{
			float e = 1.0f / tanf(fovx / 2.0f);
			float aspectInv = 1.0f / aspect;
			float fovy = 2.0f * atanf(aspectInv / e);
			float xScale = 1.0f / tanf(0.5f * fovy);
			float yScale = xScale / aspectInv;

			M._array[0] = xScale;
			M._array[1] = 0.0f;
			M._array[2] = 0.0f;
			M._array[3] = 0.0f;

			M._array[4] = 0.0f;
			M._array[5] = yScale;
			M._array[6] = 0.0f;
			M._array[7] = 0.0f;

			M._array[8] = 0.0f;
			M._array[9] = 0.0f;
			M._array[10] = (far + near) / (near - far);
			M._array[11] = -1.0f;

			M._array[12] = 0.0f;
			M._array[13] = 0.0f;
			M._array[14] = (2.0f * far * near) / (near - far);
			M._array[15] = 0.0f;

			return M;
		}


		template<class T>
		static Matrix4<T>& ortho2D(Matrix4<T> & M, T left, T right, T bottom, T top)
		{
			float zNear = -1.0; float zFar = 1.0;

			float sx = 2.0f / (right - left);
			float sy = 2.0f / (top - bottom);
			float sz = 2.0f / (zFar - zNear);

			float tx = -(right + left) / (right - left);
			float ty = -(top + bottom) / (top - bottom);
			float tz = -(zFar + zNear) / (zFar - zNear);

			//matrix is stored column major
			M._array[0] = sx, M._array[4] = 0.0f, M._array[8] = 0.0f, M._array[12] = tx;
			M._array[1] = 0.0f, M._array[5] = sy, M._array[9] = 0.0f, M._array[13] = ty;
			M._array[2] = 0.0f, M._array[6] = 0.0f, M._array[10] = sz, M._array[14] = tz;
			M._array[3] = 0.0f, M._array[7] = 0.0f, M._array[11] = 0.0f, M._array[15] = 1.0f;

			return M;
		}

		template<class T>
		static Matrix4<T>& ortho2D(Matrix4<T> & M, const Rect<T>& rect)
		{
			return ortho2D(M, rect.pos.x, rect.size.x, rect.size.y, rect.pos.y);
		}

		template<class T>
		static Matrix4<T>& ortho3D(Matrix4<T> & M, T left, T right, T bottom, T top, T zNear, T zFar)
		{
			float sx = 2.0f / (right - left);
			float sy = 2.0f / (top - bottom);
			float sz = 2.0f / (zFar - zNear);

			float tx = -(right + left) / (right - left);
			float ty = -(top + bottom) / (top - bottom);
			float tz = -(zFar + zNear) / (zFar - zNear);

			//matrix is stored column major
			M._array[0] = sx, M._array[4] = 0.0f, M._array[8] = 0.0f, M._array[12] = tx;
			M._array[1] = 0.0f, M._array[5] = sy, M._array[9] = 0.0f, M._array[13] = ty;
			M._array[2] = 0.0f, M._array[6] = 0.0f, M._array[10] = sz, M._array[14] = tz;
			M._array[3] = 0.0f, M._array[7] = 0.0f, M._array[11] = 0.0f, M._array[15] = 1.0f;

			return M;
		}

		union {
			struct {
				T _11, _12, _13, _14;   // standard names for components
				T _21, _22, _23, _24;   // standard names for components
				T _31, _32, _33, _34;   // standard names for components
				T _41, _42, _43, _44;   // standard names for components
			};
			T _array[16];     // array access
		};

		static const Matrix4<T> ZERO;
		static const Matrix4<T> IDENTITY;
	};

	template<class T>const Matrix4<T> Matrix4<T>::ZERO(
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0);
	template<class T>const Matrix4<T> Matrix4<T>::IDENTITY(
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1);

	typedef Matrix4<float> Matrix4f; ///< float 4x4 matrices
}