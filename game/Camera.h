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

		void SetPosition(const Vector3f& position);
		const Vector3f& GetPosition() const;

		void SetRotation(const Vector3f& rotation);
		const Vector3f& GetRotation() const;

		void UpdatePosition();

	protected:
		Vector3f _position;
		Vector3f _rotation;
		Matrix4f _matrix;
		bool _update;
	};
}
