#pragma once
#include "uutRect.h"

namespace uut
{
	class Matrix4
	{
	public:
		union
		{
			float m[4][4];
			float data[16];
		};

		Matrix4();
		Matrix4(const float* mat);

		static Matrix4 BuildOrtho(const Rect& rect,
			float znear, float zfar);
		static Matrix4 BuildPerspective(float fov, float aspect,
			float znear, float zfar);
	};
}
