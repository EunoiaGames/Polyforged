#include "Transform.h"

namespace Eunoia { namespace Math {

	Transform::Transform(const Math::Vector3f & pos, const Math::Vector3f & scale, const Math::Quaternion & rot) :
		m_pos(pos),
		m_scale(scale),
		m_rot(rot)
	{}

	Matrix4f Transform::CreateWorldMatrix() const
	{
		return (Matrix4f().InitTranslation(m_pos) * (m_rot.CreateRotationMatrix() * Matrix4f().InitScale(m_scale)));
	}

	Transform & Transform::Translate(const Vector3f & translation)
	{
		m_pos += translation;
		return *this;
	}

	Transform & Transform::Scale(const Vector3f & scale)
	{
		m_scale *= scale;
		return *this;
	}

	Transform & Transform::Scale(float scale)
	{
		m_scale *= scale;
		return *this;
	}

	Transform & Transform::Rotate(const Quaternion & rot)
	{
		m_rot = (rot * m_rot).Normalized();
		return *this;
	}

	Transform & Transform::Rotate(const Vector3f & axis, float deg)
	{
		return Rotate(Quaternion(axis, deg));
	}

	Math::Vector3f & Transform::GetPos() { return m_pos; }
	Math::Vector3f & Transform::GetScale() { return m_scale; }
	Math::Quaternion & Transform::GetRot() { return m_rot; }

	const Math::Vector3f & Transform::GetPos() const { return m_pos; }
	const Math::Vector3f & Transform::GetScale() const { return m_scale; }
	const Math::Quaternion & Transform::GetRot() const { return m_rot; }

} }
