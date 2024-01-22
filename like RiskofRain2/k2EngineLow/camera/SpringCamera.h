#pragma once

#include "CameraCollisionSolver.h"

namespace nsK2EngineLow{

	class SpringCamera : public Noncopyable
	{
	public:
		SpringCamera();
		~SpringCamera();

		//初期化
		void Init(
			Camera& camera,
			float maxMoveSpeed,
			bool isEnableCollisionSolver,
			float sphereCollisionRadius
		);

		//目標にする注視点を設定
		void SetTarget(const Vector3& target)
		{
			m_target = target;
		}

		//目標にする視点を設定
		void SetPosition(const Vector3& position)
		{
			m_position = position;
		}

		//遠平面を設定
		void SetFar(float _far)
		{
			if (m_camera == nullptr)
			{
				return;
			}

			m_camera->SetFar(_far);
		}

		//近平面を設定
		void SetNear(float _near)
		{
			if (m_camera == nullptr)
			{
				return;
			}

			m_camera->SetNear(_near);
		}

		//カメラの回転行列を取得
		const Matrix& GetCameraRotation() const
		{
			if (m_camera == nullptr)
			{
				return Matrix::Identity;
			}

			return m_camera->GetCameraRotation();
		}

		//目標の注視点を取得
		const Vector3& GetTarget() const
		{
			return m_target;
		}

		//目標の視点を取得
		const Vector3& GetPosition() const
		{
			return m_position;
		}

		//実際の注視点を取得
		const Vector3& GetRealTarget() const
		{
			if (m_camera == nullptr)
			{
				return Vector3::Zero;
			}

			return m_camera->GetTarget();
		}

		//実際の視点を取得
		const Vector3& GetRealPosition() const
		{
			if (m_camera == nullptr)
			{
				return Vector3::Zero;
			}

			return m_camera->GetPosition();
		}

		//更新
		void Update();

		//カメラを取得
		const Camera* GetCamera() const
		{
			return m_camera;
		}

		//ばねの減衰率を設定
		void SetDampingRate(float dampingRate)
		{
			m_targetDampingRate = dampingRate;
		}

		//カメラを取得
		Camera* GetCamera()
		{
			return m_camera;
		}

		//画角を設定
		void SetViewAngle(float angle)
		{
			if (m_camera == nullptr)
			{
				return;
			}

			m_camera->SetViewAngle(angle);
		}

		//画角を取得
		float GetViewAngle() const
		{
			if (m_camera == nullptr)
			{
				return 0.0f;
			}

			return m_camera->GetViewAngle();
		}

		//リフレッシュをする
		void Refresh()
		{
			m_targetMoveSpeed = Vector3::Zero;
			m_positionMoveSpeed = Vector3::Zero;
			m_isRefresh = true;
		}

		//ばねカメラの更新処理
		void UpdateSpringCamera();

		//カメラの更新
		void UpdateCamera()
		{
			if (m_camera)
			{
				m_camera->Update();
			}
		}

		private:
			//カメラ
			Camera* m_camera = nullptr;
			//目標となる注視点
			Vector3	m_target = Vector3::Zero;
			//目標となる視点
			Vector3	m_position = Vector3::Zero;
			//注視点の移動速度
			Vector3	m_targetMoveSpeed = Vector3::Zero;
			//視点の移動速度
			Vector3	m_positionMoveSpeed = Vector3::Zero;
			//最高移動速度
			float m_maxMoveSpeed = 0.0f;
			//減衰率
			float m_targetDampingRate = 1.0f;
			//減衰率
			float m_dampingRate = 1.0f;
			float m_dampingRateVel = 0.0f;
			//コリジョン処理が有効かどうか
			bool m_isEnableCollisionSolver = false;
			//リフレッシュが必要かどうか
			bool m_isRefresh = true;

			CameraCollisionSolver m_cameraCollisionSolver;
	};

}