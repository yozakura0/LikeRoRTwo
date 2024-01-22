#pragma once
namespace nsK2EngineLow
{
	class CameraCollisionSolver : public Noncopyable
	{
	public:
		CameraCollisionSolver();
		~CameraCollisionSolver();

		//������
		void Init(float radius);

		//�R���W���������̎��s
		bool Execute(Vector3& result, const Vector3& position, const Vector3& target);

	private:
		//�R���C�_�[
		SphereCollider m_collider;

		//���a
		float m_radius = 0.0f;

		//�������ς̃t���O
		bool m_isInited = false;
	};

}