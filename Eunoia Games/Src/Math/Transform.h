#pragma once

#include "Math.h"

namespace Eunoia { namespace Math {

	class Transform
	{
	public:
		Transform(const Math::Vector3f& pos = Math::Vector3f(0.0f, 0.0f, 0.0f),
			const Math::Vector3f& scale = Math::Vector3f(1.0f, 1.0f, 1.0f),
			const Math::Quaternion& rot = Math::Quaternion(0.0f, 0.0f, 0.0f, 1.0f));

		Matrix4f CreateWorldMatrix() const;

		Transform& Translate(const Vector3f& translation);
		Transform& Scale(const Vector3f& scale);
		Transform& Scale(float scale);
		Transform& Rotate(const Quaternion& rot);
		Transform& Rotate(const Vector3f& axis, float deg);

		Math::Vector3f& GetPos();
		Math::Vector3f& GetScale();
		Math::Quaternion& GetRot();

		const Math::Vector3f& GetPos() const;
		const Math::Vector3f& GetScale() const;
		const Math::Quaternion& GetRot() const;
	private:
		Math::Vector3f m_pos;
		Math::Vector3f m_scale;
		Math::Quaternion m_rot;
	};

} }
