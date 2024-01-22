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

	//���W��ݒ肷��
	void SetPosition(const Vector3& position)
	{
		m_position = position;
	}
	//��]��ݒ肷��
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
	//���W
	Vector3	m_position;
	//��]
	Quaternion m_rotation;
	//�傫��
	Vector3	m_scale = Vector3::One;
	//�ړ����x
	Vector3	m_moveSpeed;
	//�R���W�����I�u�W�F�N�g
	CollisionObject* m_collisionObject;
	//�^�C�}�[
	float m_timer = 0.0f;

	GameCamera* m_gameCamera;
};