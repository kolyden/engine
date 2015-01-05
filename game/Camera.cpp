#include "Camera.h"
#include "core/uutContext.h"
#include "video/uutVideo.h"
#include "math/uutQuaternion.h"

namespace uut
{
	const float Camera::DEFAULT_FOVX = 90.0f;
	const float Camera::DEFAULT_ZFAR = 1000.0f;
	const float Camera::DEFAULT_ZNEAR = 0.1f;
	const Vector3f Camera::WORLD_XAXIS(1.0f, 0.0f, 0.0f);
	const Vector3f Camera::WORLD_YAXIS(0.0f, 1.0f, 0.0f);
	const Vector3f Camera::WORLD_ZAXIS(0.0f, 0.0f, 1.0f);

	Camera::Camera(Context* context)
		: Object(context)
	{
		m_behavior = CAMERA_BEHAVIOR_FLIGHT;

		m_fovx = DEFAULT_FOVX;
		m_znear = DEFAULT_ZNEAR;
		m_zfar = DEFAULT_ZFAR;
		m_aspectRatio = 0.0f;

		m_accumPitchDegrees = 0.0f;

		m_eye = Vector3f(0.0f, 0.0f, 0.0f);
		m_xAxis = Vector3f(1.0f, 0.0f, 0.0f);
		m_yAxis = Vector3f(0.0f, 1.0f, 0.0f);
		m_zAxis = Vector3f(0.0f, 0.0f, 1.0f);
		m_viewDir = Vector3f(0.0f, 0.0f, -1.0f);

		m_acceleration = Vector3f(0.0f, 0.0f, 0.0f);
		m_currentVelocity = Vector3f(0.0f, 0.0f, 0.0f);
		m_velocity = Vector3f(0.0f, 0.0f, 0.0f);

		m_orientation = Quaternionf::IDENTITY;

		m_viewMatrix.make_identity();
		m_projMatrix.make_identity();
	}

	Camera::~Camera()
	{
	}

	void Camera::lookAt(const Vector3f &target)
	{
		lookAt(m_eye, target, m_yAxis);
	}

	void Camera::lookAt(const Vector3f &eye, const Vector3f &target, const Vector3f &up)
	{
		m_eye = eye;

		m_zAxis = eye - target;
		Vector3f::normalize(m_zAxis);

		m_viewDir = -m_zAxis;

		m_xAxis = Vector3f::cross(up, m_zAxis);
		Vector3f::normalize(m_xAxis);

		m_yAxis = Vector3f::cross(m_zAxis, m_xAxis);
		Vector3f::normalize(m_yAxis);
		Vector3f::normalize(m_xAxis);

		m_viewMatrix._11 = m_xAxis.x;
		m_viewMatrix._21 = m_xAxis.y;
		m_viewMatrix._31 = m_xAxis.z;
		m_viewMatrix._41 = -Vector3f::dot(m_xAxis, eye);

		m_viewMatrix._12 = m_yAxis.x;
		m_viewMatrix._22 = m_yAxis.y;
		m_viewMatrix._32 = m_yAxis.z;
		m_viewMatrix._42 = -Vector3f::dot(m_yAxis, eye);

		m_viewMatrix._13 = m_zAxis.x;
		m_viewMatrix._23 = m_zAxis.y;
		m_viewMatrix._33 = m_zAxis.z;
		m_viewMatrix._43 = -Vector3f::dot(m_zAxis, eye);

		// Extract the pitch angle from the view matrix.
		m_accumPitchDegrees = Math::ToDeg(asinf(m_viewMatrix._23));

		m_orientation.set_value(m_viewMatrix);
	}

	void Camera::move(float dx, float dy, float dz)
	{
		// Moves the camera by dx world units to the left or right; dy
		// world units upwards or downwards; and dz world units forwards
		// or backwards.

		Vector3f eye = m_eye;
		Vector3f forwards;

		if (m_behavior == CAMERA_BEHAVIOR_FIRST_PERSON)
		{
			// Calculate the forwards direction. Can't just use the camera's local
			// z axis as doing so will cause the camera to move more slowly as the
			// camera's view approaches 90 degrees straight up and down.

			forwards = Vector3f::cross(WORLD_YAXIS, m_xAxis);
			Vector3f::normalize(forwards);
		}
		else
		{
			forwards = m_viewDir;
		}

		eye += m_xAxis * dx;
		eye += WORLD_YAXIS * dy;
		eye += forwards * dz;

		setPosition(eye);
	}

	void Camera::move(const Vector3f &direction, const Vector3f &amount)
	{
		// Moves the camera by the specified amount of world units in the specified
		// direction in world space.

		m_eye.x += direction.x * amount.x;
		m_eye.y += direction.y * amount.y;
		m_eye.z += direction.z * amount.z;

		updateViewMatrix();
	}

	void Camera::perspective(float fovx, float aspect, float znear, float zfar)
	{
		// Construct a projection matrix based on the horizontal field of view
		// 'fovx' rather than the more traditional vertical field of view 'fovy'.

		float e = 1.0f / tanf(Math::ToRad(fovx) / 2.0f);
		float aspectInv = 1.0f / aspect;
		float fovy = 2.0f * atanf(aspectInv / e);
		float xScale = 1.0f / tanf(0.5f * fovy);
		float yScale = xScale / aspectInv;

		m_projMatrix._11 = xScale;
		m_projMatrix._12 = 0.0f;
		m_projMatrix._13 = 0.0f;
		m_projMatrix._14 = 0.0f;

		m_projMatrix._21 = 0.0f;
		m_projMatrix._22 = yScale;
		m_projMatrix._23 = 0.0f;
		m_projMatrix._24 = 0.0f;

		m_projMatrix._31 = 0.0f;
		m_projMatrix._32 = 0.0f;
		m_projMatrix._33 = (zfar + znear) / (znear - zfar);
		m_projMatrix._34 = -1.0f;

		m_projMatrix._41 = 0.0f;
		m_projMatrix._42 = 0.0f;
		m_projMatrix._43 = (2.0f * zfar * znear) / (znear - zfar);
		m_projMatrix._44 = 0.0f;

		m_fovx = fovx;
		m_aspectRatio = aspect;
		m_znear = znear;
		m_zfar = zfar;
	}

	void Camera::rotate(float headingDegrees, float pitchDegrees, float rollDegrees)
	{
		// Rotates the camera based on its current behavior.
		// Note that not all behaviors support rolling.

		pitchDegrees = -pitchDegrees;
		headingDegrees = -headingDegrees;
		rollDegrees = -rollDegrees;

		switch (m_behavior)
		{
		case CAMERA_BEHAVIOR_FIRST_PERSON:
			rotateFirstPerson(headingDegrees, pitchDegrees);
			break;

		case CAMERA_BEHAVIOR_FLIGHT:
			rotateFlight(headingDegrees, pitchDegrees, rollDegrees);
			break;
		}

		updateViewMatrix();
	}

	void Camera::rotateFlight(float headingDegrees, float pitchDegrees, float rollDegrees)
	{
		// Implements the rotation logic for the flight style camera behavior.

		Quaternionf rot;

// 		rot.fromHeadPitchRoll(headingDegrees, pitchDegrees, rollDegrees);
		Matrix4f mat;
		Matrix4f::rotationYawPitchRoll(mat, headingDegrees, pitchDegrees, rollDegrees);
		rot.set_value(mat);
		m_orientation *= rot;
	}

	void Camera::rotateFirstPerson(float headingDegrees, float pitchDegrees)
	{
		// Implements the rotation logic for the first person style and
		// spectator style camera behaviors. Roll is ignored.

		m_accumPitchDegrees += pitchDegrees;

		if (m_accumPitchDegrees > 90.0f)
		{
			pitchDegrees = 90.0f - (m_accumPitchDegrees - pitchDegrees);
			m_accumPitchDegrees = 90.0f;
		}

		if (m_accumPitchDegrees < -90.0f)
		{
			pitchDegrees = -90.0f - (m_accumPitchDegrees - pitchDegrees);
			m_accumPitchDegrees = -90.0f;
		}

		Quaternionf rot;

		// Rotate camera about the world y axis.
		// Note the order the quaternions are multiplied. That is important!
		if (headingDegrees != 0.0f)
		{
			rot.set_value(WORLD_YAXIS, headingDegrees);
			m_orientation = rot * m_orientation;
		}

		// Rotate camera about its local x axis.
		// Note the order the quaternions are multiplied. That is important!
		if (pitchDegrees != 0.0f)
		{
			rot.set_value(WORLD_XAXIS, pitchDegrees);
			m_orientation = m_orientation * rot;
		}
	}

	void Camera::setAcceleration(float x, float y, float z)
	{
		m_acceleration = Vector3f(x, y, z);
	}

	void Camera::setAcceleration(const Vector3f &acceleration)
	{
		m_acceleration = acceleration;
	}

	void Camera::setBehavior(CameraBehavior newBehavior)
	{
		if (m_behavior == CAMERA_BEHAVIOR_FLIGHT && newBehavior == CAMERA_BEHAVIOR_FIRST_PERSON)
		{
			// Moving from flight-simulator mode to first-person.
			// Need to ignore camera roll, but retain existing pitch and heading.

			lookAt(m_eye, m_eye - m_zAxis, WORLD_YAXIS);
		}

		m_behavior = newBehavior;
	}

	void Camera::setCurrentVelocity(float x, float y, float z)
	{
		m_currentVelocity = Vector3f(x, y, z);
	}

	void Camera::setCurrentVelocity(const Vector3f &currentVelocity)
	{
		m_currentVelocity = currentVelocity;
	}

	void Camera::setOrientation(const Quaternionf &orientation)
	{
		Matrix4f m;
		orientation.get_value(m);

		m_accumPitchDegrees = Math::ToDeg(asinf(m._23));
		m_orientation = orientation;

		if (m_behavior == CAMERA_BEHAVIOR_FIRST_PERSON)
			lookAt(m_eye, m_eye + m_viewDir, WORLD_YAXIS);

		updateViewMatrix();
	}

	void Camera::setPosition(float x, float y, float z)
	{
		m_eye = Vector3f(x, y, z);
		updateViewMatrix();
	}

	void Camera::setPosition(const Vector3f &position)
	{
		m_eye = position;
		updateViewMatrix();
	}

	void Camera::setVelocity(float x, float y, float z)
	{
		m_velocity = Vector3f(x, y, z);
	}

	void Camera::setVelocity(const Vector3f &velocity)
	{
		m_velocity = velocity;
	}

	void Camera::updatePosition(const Vector3f &direction, float elapsedTimeSec)
	{
		// Moves the camera using Newton's second law of motion. Unit mass is
		// assumed here to somewhat simplify the calculations. The direction vector
		// is in the range [-1,1].

		if (Vector3f::length(m_currentVelocity) != 0.0f)
		{
			// Only move the camera if the velocity vector is not of zero length.
			// Doing this guards against the camera slowly creeping around due to
			// floating point rounding errors.

			Vector3f displacement = (m_currentVelocity * elapsedTimeSec) +
				(0.5f * m_acceleration * elapsedTimeSec * elapsedTimeSec);

			// Floating point rounding errors will slowly accumulate and cause the
			// camera to move along each axis. To prevent any unintended movement
			// the displacement vector is clamped to zero for each direction that
			// the camera isn't moving in. Note that the updateVelocity() method
			// will slowly decelerate the camera's velocity back to a stationary
			// state when the camera is no longer moving along that direction. To
			// account for this the camera's current velocity is also checked.

			if (direction.x == 0.0f && Math::Equals(m_currentVelocity.x, 0.0f))
				displacement.x = 0.0f;

			if (direction.y == 0.0f && Math::Equals(m_currentVelocity.y, 0.0f))
				displacement.y = 0.0f;

			if (direction.z == 0.0f && Math::Equals(m_currentVelocity.z, 0.0f))
				displacement.z = 0.0f;

			move(displacement.x, displacement.y, displacement.z);
		}

		// Continuously update the camera's velocity vector even if the camera
		// hasn't moved during this call. When the camera is no longer being moved
		// the camera is decelerating back to its stationary state.

		updateVelocity(direction, elapsedTimeSec);
	}

	void Camera::updateVelocity(const Vector3f &direction, float elapsedTimeSec)
	{
		// Updates the camera's velocity based on the supplied movement direction
		// and the elapsed time (since this method was last called). The movement
		// direction is in the range [-1,1].

		if (direction.x != 0.0f)
		{
			// Camera is moving along the x axis.
			// Linearly accelerate up to the camera's max speed.

			m_currentVelocity.x += direction.x * m_acceleration.x * elapsedTimeSec;

			if (m_currentVelocity.x > m_velocity.x)
				m_currentVelocity.x = m_velocity.x;
			else if (m_currentVelocity.x < -m_velocity.x)
				m_currentVelocity.x = -m_velocity.x;
		}
		else
		{
			// Camera is no longer moving along the x axis.
			// Linearly decelerate back to stationary state.

			if (m_currentVelocity.x > 0.0f)
			{
				if ((m_currentVelocity.x -= m_acceleration.x * elapsedTimeSec) < 0.0f)
					m_currentVelocity.x = 0.0f;
			}
			else
			{
				if ((m_currentVelocity.x += m_acceleration.x * elapsedTimeSec) > 0.0f)
					m_currentVelocity.x = 0.0f;
			}
		}

		if (direction.y != 0.0f)
		{
			// Camera is moving along the y axis.
			// Linearly accelerate up to the camera's max speed.

			m_currentVelocity.y += direction.y * m_acceleration.y * elapsedTimeSec;

			if (m_currentVelocity.y > m_velocity.y)
				m_currentVelocity.y = m_velocity.y;
			else if (m_currentVelocity.y < -m_velocity.y)
				m_currentVelocity.y = -m_velocity.y;
		}
		else
		{
			// Camera is no longer moving along the y axis.
			// Linearly decelerate back to stationary state.

			if (m_currentVelocity.y > 0.0f)
			{
				if ((m_currentVelocity.y -= m_acceleration.y * elapsedTimeSec) < 0.0f)
					m_currentVelocity.y = 0.0f;
			}
			else
			{
				if ((m_currentVelocity.y += m_acceleration.y * elapsedTimeSec) > 0.0f)
					m_currentVelocity.y = 0.0f;
			}
		}

		if (direction.z != 0.0f)
		{
			// Camera is moving along the z axis.
			// Linearly accelerate up to the camera's max speed.

			m_currentVelocity.z += direction.z * m_acceleration.z * elapsedTimeSec;

			if (m_currentVelocity.z > m_velocity.z)
				m_currentVelocity.z = m_velocity.z;
			else if (m_currentVelocity.z < -m_velocity.z)
				m_currentVelocity.z = -m_velocity.z;
		}
		else
		{
			// Camera is no longer moving along the z axis.
			// Linearly decelerate back to stationary state.

			if (m_currentVelocity.z > 0.0f)
			{
				if ((m_currentVelocity.z -= m_acceleration.z * elapsedTimeSec) < 0.0f)
					m_currentVelocity.z = 0.0f;
			}
			else
			{
				if ((m_currentVelocity.z += m_acceleration.z * elapsedTimeSec) > 0.0f)
					m_currentVelocity.z = 0.0f;
			}
		}
	}

	void Camera::updateViewMatrix()
	{
		// Reconstruct the view matrix.

		m_orientation.get_value(m_viewMatrix);

		m_xAxis = Vector3f(m_viewMatrix._11, m_viewMatrix._21, m_viewMatrix._31);
		m_yAxis = Vector3f(m_viewMatrix._12, m_viewMatrix._22, m_viewMatrix._32);
		m_zAxis = Vector3f(m_viewMatrix._13, m_viewMatrix._23, m_viewMatrix._33);
		m_viewDir = -m_zAxis;

		m_viewMatrix._41 = -Vector3f::dot(m_xAxis, m_eye);
		m_viewMatrix._42 = -Vector3f::dot(m_yAxis, m_eye);
		m_viewMatrix._43 = -Vector3f::dot(m_zAxis, m_eye);
	}

}