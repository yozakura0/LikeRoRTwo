#pragma once

class GameCamera;

class ShotManager : public IGameObject
{
public:
	ShotManager();
	~ShotManager();
	void NormalShot();
	void Update();
	void Render(RenderContext& rc);

	//座標を設定する
	void SetPosition(const Vector3& position)
	{
		m_position = position;
	}
	//回転を設定する
	void SetRotation(const Quaternion& rotation)
	{
		m_rotation = rotation;
	}
	void SetMoveSpeed(const Vector3& vector)
	{
		m_moveSpeed = vector;
	}

	ModelRender m_shotRender;

private:
	//座標
	Vector3	m_position;
	//回転
	Quaternion m_rotation;
	//大きさ
	Vector3	m_scale = Vector3::One;
	//移動速度
	Vector3	m_moveSpeed;
	//コリジョンオブジェクト
	CollisionObject* m_collisionObject;
	//タイマー
	float m_timer = 0.0f;

	GameCamera* m_gameCamera;
};