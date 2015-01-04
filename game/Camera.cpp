#include "Camera.h"
#include "core/uutContext.h"
#include "video/uutVideo.h"

namespace uut
{
	Camera::Camera(Context* context)
		: Object(context)
		, VideoObject(_context->GetModule<Video>())
		, _position(Vector3::ZERO)
		, _rotation(Vector3::ZERO)
		, _update(true)
	{
	}

	void Camera::SetPosition(const Vector3& position)
	{
		_position = position;
		_update = true;
	}

	const Vector3& Camera::GetPosition() const
	{
		return _position;
	}

	void Camera::SetRotation(const Vector3& rotation)
	{
		_rotation = rotation;
		_update = true;
	}

	const Vector3& Camera::GetRotation() const
	{
		return _rotation;
	}

	void Camera::UpdatePosition()
	{
		if (!_update)
			return;

		_update = false;
// 		_matrix = Matrix4::BuildPerspective()
	}

}