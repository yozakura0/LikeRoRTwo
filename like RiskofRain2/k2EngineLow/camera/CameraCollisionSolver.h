#pragma once
namespace nsK2EngineLow
{
	class CameraCollisionSolver : public Noncopyable
	{
	public:
		CameraCollisionSolver();
		~CameraCollisionSolver();

		//初期化
		void Init(float radius);

		//コリジョン解決の実行
		bool Execute(Vector3& result, const Vector3& position, const Vector3& target);

	private:
		//コライダー
		SphereCollider m_collider;

		//半径
		float m_radius = 0.0f;

		//初期化済のフラグ
		bool m_isInited = false;
	};

}