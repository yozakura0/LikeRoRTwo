#pragma once

#include "CameraCollisionSolver.h"

namespace nsK2EngineLow{

	class SpringCamera : public Noncopyable
	{
	public:
		SpringCamera();
		~SpringCamera();

		//������
		void Init(
			Camera& camera,
			float maxMoveSpeed,
			bool isEnableCollisionSolver,
			float sphereCollisionRadius
		);

		//�ڕW�ɂ��钍���_��ݒ�
		void SetTarget(const Vector3& target)
		{
			m_target = target;
		}

		//�ڕW�ɂ��鎋�_��ݒ�
		void SetPosition(const Vector3& position)
		{
			m_position = position;
		}

		//�����ʂ�ݒ�
		void SetFar(float _far)
		{
			if (m_camera == nullptr)
			{
				return;
			}

			m_camera->SetFar(_far);
		}

		//�ߕ��ʂ�ݒ�
		void SetNear(float _near)
		{
			if (m_camera == nullptr)
			{
				return;
			}

			m_camera->SetNear(_near);
		}

		//�J�����̉�]�s����擾
		const Matrix& GetCameraRotation() const
		{
			if (m_camera == nullptr)
			{
				return Matrix::Identity;
			}

			return m_camera->GetCameraRotation();
		}

		//�ڕW�̒����_���擾
		const Vector3& GetTarget() const
		{
			return m_target;
		}

		//�ڕW�̎��_���擾
		const Vector3& GetPosition() const
		{
			return m_position;
		}

		//���ۂ̒����_���擾
		const Vector3& GetRealTarget() const
		{
			if (m_camera == nullptr)
			{
				return Vector3::Zero;
			}

			return m_camera->GetTarget();
		}

		//���ۂ̎��_���擾
		const Vector3& GetRealPosition() const
		{
			if (m_camera == nullptr)
			{
				return Vector3::Zero;
			}

			return m_camera->GetPosition();
		}

		//�X�V
		void Update();

		//�J�������擾
		const Camera* GetCamera() const
		{
			return m_camera;
		}

		//�΂˂̌�������ݒ�
		void SetDampingRate(float dampingRate)
		{
			m_targetDampingRate = dampingRate;
		}

		//�J�������擾
		Camera* GetCamera()
		{
			return m_camera;
		}

		//��p��ݒ�
		void SetViewAngle(float angle)
		{
			if (m_camera == nullptr)
			{
				return;
			}

			m_camera->SetViewAngle(angle);
		}

		//��p���擾
		float GetViewAngle() const
		{
			if (m_camera == nullptr)
			{
				return 0.0f;
			}

			return m_camera->GetViewAngle();
		}

		//���t���b�V��������
		void Refresh()
		{
			m_targetMoveSpeed = Vector3::Zero;
			m_positionMoveSpeed = Vector3::Zero;
			m_isRefresh = true;
		}

		//�΂˃J�����̍X�V����
		void UpdateSpringCamera();

		//�J�����̍X�V
		void UpdateCamera()
		{
			if (m_camera)
			{
				m_camera->Update();
			}
		}

		private:
			//�J����
			Camera* m_camera = nullptr;
			//�ڕW�ƂȂ钍���_
			Vector3	m_target = Vector3::Zero;
			//�ڕW�ƂȂ鎋�_
			Vector3	m_position = Vector3::Zero;
			//�����_�̈ړ����x
			Vector3	m_targetMoveSpeed = Vector3::Zero;
			//���_�̈ړ����x
			Vector3	m_positionMoveSpeed = Vector3::Zero;
			//�ō��ړ����x
			float m_maxMoveSpeed = 0.0f;
			//������
			float m_targetDampingRate = 1.0f;
			//������
			float m_dampingRate = 1.0f;
			float m_dampingRateVel = 0.0f;
			//�R���W�����������L�����ǂ���
			bool m_isEnableCollisionSolver = false;
			//���t���b�V�����K�v���ǂ���
			bool m_isRefresh = true;

			CameraCollisionSolver m_cameraCollisionSolver;
	};

}