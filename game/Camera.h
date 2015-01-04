#pragma once
#include "core/uutObject.h"
#include "video/uutVideoObject.h"
#include "video/uutColor.h"
#include "math/uutVector3.h"
#include "math/uutMatrix.h"

namespace uut
{
	class Camera : public Object, public VideoObject
	{
		OBJECT(Camera)
	public:
		Camera(Context* context);

		void SetPosition(const Vector3& position);
		const Vector3& GetPosition() const;

		void SetRotation(const Vector3& rotation);
		const Vector3& GetRotation() const;

		void UpdatePosition();

	protected:
		Vector3 _position;
		Vector3 _rotation;
		Matrix4 _matrix;
		bool _update;
	};
}
