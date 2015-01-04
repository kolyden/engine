#include "Camera.h"
#include "core/uutContext.h"
#include "video/uutVideo.h"

namespace uut
{
	Camera::Camera(Context* context)
		: Object(context)
		, VideoObject(_context->GetModule<Video>())
		, _position(Vector3f::ZERO)
		, _rotation(Vector3f::ZERO)
		, _update(true)
	{
	}

	void Camera::SetPosition(const Vector3f& position)
	{
		_position = position;
		_update = true;
	}

	const Vector3f& Camera::GetPosition() const
	{
		return _position;
	}

	void Camera::SetRotation(const Vector3f& rotation)
	{
		_rotation = rotation;
		_update = true;
	}

	const Vector3f& Camera::GetRotation() const
	{
		return _rotation;
	}

	void Camera::UpdatePosition()
	{
		if (_update)
		{
			_update = false;
			_matrix.make_identity();
			Matrix4f::translation(_matrix, _position);
		}

		_video->SetTransform(TRANSFORM_VIEW, _matrix);
	}

}