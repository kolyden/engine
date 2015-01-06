#pragma once
#include "core/uutObject.h"
#include "math/uutVector3.h"
#include "math/uutQuaternion.h"
#include "math/uutMatrix4.h"
#include "Camera.h"

namespace uut
{
	class Camera : public Object
	{
		OBJECT(Camera)
	public:
		enum CameraBehavior
		{
			CAMERA_BEHAVIOR_FIRST_PERSON,
			CAMERA_BEHAVIOR_FLIGHT
		};

		Camera(Context* context);
		~Camera();

		void lookAt(const Vector3f &target);
		void lookAt(const Vector3f &eye, const Vector3f &target, const Vector3f &up);
		void move(float dx, float dy, float dz);
		void move(const Vector3f &direction, const Vector3f &amount);
		void perspective(float fovx, float aspect, float znear, float zfar);
		void rotate(float headingDegrees, float pitchDegrees, float rollDegrees);
		void updatePosition(const Vector3f &direction, float elapsedTimeSec);

		// Getter methods.

		const Vector3f &getAcceleration() const;
		CameraBehavior getBehavior() const;
		const Vector3f &getCurrentVelocity() const;
		const Quaternionf &getOrientation() const;
		const Vector3f &getPosition() const;
		const Matrix4f &getProjectionMatrix() const;
		const Vector3f &getVelocity() const;
		const Vector3f &getViewDirection() const;
		const Matrix4f &getViewMatrix() const;
		const Vector3f &getXAxis() const;
		const Vector3f &getYAxis() const;
		const Vector3f &getZAxis() const;

		// Setter methods.

		void setAcceleration(float x, float y, float z);
		void setAcceleration(const Vector3f &acceleration);
		void setBehavior(CameraBehavior newBehavior);
		void setCurrentVelocity(float x, float y, float z);
		void setCurrentVelocity(const Vector3f &currentVelocity);
		void setOrientation(const Quaternionf &orientation);
		void setPosition(float x, float y, float z);
		void setPosition(const Vector3f &position);
		void setVelocity(float x, float y, float z);
		void setVelocity(const Vector3f &velocity);

	private:
		void rotateFlight(float headingDegrees, float pitchDegrees, float rollDegrees);
		void rotateFirstPerson(float headingDegrees, float pitchDegrees);
		void updateVelocity(const Vector3f &direction, float elapsedTimeSec);
		void updateViewMatrix();

		static const float DEFAULT_FOVX;
		static const float DEFAULT_ZFAR;
		static const float DEFAULT_ZNEAR;
		static const Vector3f WORLD_XAXIS;
		static const Vector3f WORLD_YAXIS;
		static const Vector3f WORLD_ZAXIS;

		CameraBehavior m_behavior;
		float m_fovx;
		float m_znear;
		float m_zfar;
		float m_aspectRatio;
		float m_accumPitchDegrees;
		Vector3f m_eye;
		Vector3f m_xAxis;
		Vector3f m_yAxis;
		Vector3f m_zAxis;
		Vector3f m_viewDir;
		Vector3f m_acceleration;
		Vector3f m_currentVelocity;
		Vector3f m_velocity;
		Quaternionf m_orientation;
		Matrix4f m_viewMatrix;
		Matrix4f m_projMatrix;
	};

	//-----------------------------------------------------------------------------

	inline const Vector3f &Camera::getAcceleration() const
	{
		return m_acceleration;
	}

	inline Camera::CameraBehavior Camera::getBehavior() const
	{
		return m_behavior;
	}

	inline const Vector3f &Camera::getCurrentVelocity() const
	{
		return m_currentVelocity;
	}

	inline const Quaternionf &Camera::getOrientation() const
	{
		return m_orientation;
	}

	inline const Vector3f &Camera::getPosition() const
	{
		return m_eye;
	}

	inline const Matrix4f &Camera::getProjectionMatrix() const
	{
		return m_projMatrix;
	}

	inline const Vector3f &Camera::getVelocity() const
	{
		return m_velocity;
	}

	inline const Vector3f &Camera::getViewDirection() const
	{
		return m_viewDir;
	}

	inline const Matrix4f &Camera::getViewMatrix() const
	{
		return m_viewMatrix;
	}

	inline const Vector3f &Camera::getXAxis() const
	{
		return m_xAxis;
	}

	inline const Vector3f &Camera::getYAxis() const
	{
		return m_yAxis;
	}

	inline const Vector3f &Camera::getZAxis() const
	{
		return m_zAxis;
	}
}