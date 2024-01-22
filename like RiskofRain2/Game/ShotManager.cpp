#include "stdafx.h"
#include "ShotManager.h"

#include "GameCamera.h"

ShotManager::ShotManager()
{
	m_gameCamera = FindGO<GameCamera>("gameCamera");
	m_shotRender.Init("Assets/modelData/player/shotN.tkm");
}

ShotManager::~ShotManager()
{
	DeleteGO(m_collisionObject);
}

void ShotManager::NormalShot()
{
	//�R���W�����I�u�W�F�N�g���쐬����B
	m_collisionObject = NewGO<CollisionObject>(0);
	//����̃R���W�������쐬����B
	m_collisionObject->CreateSphere(m_position, Quaternion::Identity, 5.0f * m_scale.z);

	//�ړ����x���v�Z
	//m_rotation.SetRotation(m_position, m_gameCamera->m_rayHitPos);
	//m_rotation.AddRotationDegX(360.0f);
	//m_rotation.Apply(m_moveSpeed);
	m_moveSpeed.Normalize();
	m_position += m_moveSpeed * 50.0f;
	m_moveSpeed *= 7000.0f;

	m_collisionObject->SetIsEnableAutoDelete(false);

	m_collisionObject->SetName("player_bullet");
}

void ShotManager::Update()
{
	//���W���ړ�������
	m_position += m_moveSpeed * g_gameTime->GetFrameDeltaTime();
	//�R���W�����I�u�W�F�N�g�ɍ��W��ݒ肷��
	m_collisionObject->SetPosition(m_position);

	//�^�C�}�[�����Z����
	m_timer += g_gameTime->GetFrameDeltaTime();

	if (m_timer >= 0.5f)
	{
		DeleteGO(this);
	}

	m_shotRender.SetPosition(m_position);
	m_shotRender.Update();
}

void ShotManager::Render(RenderContext& rc)
{
	m_shotRender.Draw(rc);
}