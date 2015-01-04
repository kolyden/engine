#include "uutMatrix.h"

namespace uut
{
	Matrix4::Matrix4() {}

	Matrix4::Matrix4(const float* mat)
	{
		memcpy(m, mat, sizeof(float) * 16);
	}

	Matrix4 Matrix4::BuildOrtho(const Rect& rect, 
		float znear, float zfar)
	{
		Matrix4 ret;

        const float left = rect._pos._x;
        const float right = left + rect._size._x;

        const float top = rect._pos._y;
        const float bottom = top + rect._size._y;

        const float r_l = (right - left);
		const float t_b = (top - bottom);
		const float f_n = (zfar - znear);

		const float tx = -(right + left) / r_l;
		const float ty = -(top + bottom) / t_b;
		const float tz = -(zfar + znear) / f_n;

		ret.m[0][0] = 2.0f / r_l;
		ret.m[0][1] = 0.0f;
		ret.m[0][2] = 0.0f;
		ret.m[0][3] = 0.0f;

		ret.m[1][0] = 0.0f;
		ret.m[1][1] = 2.0f / t_b;
		ret.m[1][2] = 0.0f;
		ret.m[1][3] = 0.0f;

		ret.m[2][0] = 0.0f;
		ret.m[2][1] = 0.0f;
		ret.m[2][2] = -2.0f / f_n;
		ret.m[2][3] = 0.0f;

		ret.m[3][0] = tx;
		ret.m[3][1] = ty;
		ret.m[3][2] = tz;
		ret.m[3][3] = 1.0f;

		return ret;
	}

	Matrix4 Matrix4::BuildPerspective(float fov, float aspect, float znear, float zfar)
	{
		Matrix4 m;
		const float PI_OVER_360 = 0.0087266f;
		float xymax = znear * tan(fov * PI_OVER_360);
		float ymin = -xymax;
		float xmin = -xymax;

		float width = xymax - xmin;
		float height = xymax - ymin;

		float depth = zfar - znear;
		float q = -(zfar + znear) / depth;
		float qn = -2 * (zfar * znear) / depth;

		float w = 2 * znear / width;
		w = w / aspect;
		float h = 2 * znear / height;

		m.data[0] = w;
		m.data[1] = 0;
		m.data[2] = 0;
		m.data[3] = 0;

		m.data[4] = 0;
		m.data[5] = h;
		m.data[6] = 0;
		m.data[7] = 0;

		m.data[8] = 0;
		m.data[9] = 0;
		m.data[10] = q;
		m.data[11] = -1;

		m.data[12] = 0;
		m.data[13] = 0;
		m.data[14] = qn;
		m.data[15] = 0;

		return m;
	}

}
