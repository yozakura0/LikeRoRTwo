#include "stdafx.h"
#include "GameCamera.h"

#include "player.h"

GameCamera::GameCamera()
{
	m_physicsWorld = PhysicsWorld::GetInstance();

	//�����_���王�_�܂ł̃x�N�g����ݒ�
	m_toCameraPos.Set(0.0f, 100.0f, 400.0f);

	//�v���C���[�̃C���X�^���X��T��
	m_player = FindGO<Player>("player");

	//�΂˃J�����̏�����
	m_springCamera.Init(
		*g_camera3D,
		1000.0f,
		true,
		5.0f
	);

	m_springCamera.SetFar(15000.0f);
}

GameCamera::~GameCamera()
{

}

void GameCamera::Update()
{
	//�����_���v�Z
	m_target = m_player->m_position;

	//������Ə������
	m_target.y += 200.0f;
	//m_target += g_camera3D->GetForward() * 1.0f;

	Vector3 toCameraPosOld = m_toCameraPos;

	//�p�b�h�̓��͂��g���ăJ��������
	float x = g_pad[0]->GetRStickXF();
	float y = g_pad[0]->GetRStickYF();

	//Y������̉�]
	Quaternion qRot;
	qRot.SetRotationDeg(Vector3::AxisY, 2.0f * x);
	qRot.Apply(m_toCameraPos);

	//X������̉�]
	Vector3 axisX;
	axisX.Cross(Vector3::AxisY, m_toCameraPos);
	axisX.Normalize();
	qRot.SetRotationDeg(axisX, 2.0f * y);
	qRot.Apply(m_toCameraPos);

	//�J�����̉�]�̏�����`�F�b�N
	Vector3 toPosDir = m_toCameraPos;
	toPosDir.Normalize();

	if (toPosDir.y < -0.9f)
	{
		//�J������������������Ă���
		m_toCameraPos = toCameraPosOld;
	}
	else if (toPosDir.y > 0.9f)
	{
		//�J�������������������Ă���
		m_toCameraPos = toCameraPosOld;
	}

	//���_���v�Z
	m_pos = m_target + m_toCameraPos;

	//�J�����ɒ����_�Ǝ��_��ݒ�
	m_springCamera.SetTarget(m_target);
	m_springCamera.SetPosition(m_pos);

	//�J�����̍X�V
	m_springCamera.Update();

	//���W�����ۂ̍��W�ɒu������
	m_pos = m_springCamera.GetRealPosition();

	SearchObstacle();
}

void GameCamera::SearchObstacle()
{
	Vector3 vectorTtoP = m_target - m_pos;
	vectorTtoP.Normalize();
	//���C�̏I�_�̍��W���v�Z
	Vector3 rayEndPos = { m_pos.x + vectorTtoP.x * 3000, m_pos.y + vectorTtoP.y * 3000, m_pos.z + vectorTtoP.z * 3000 };
	
	//���C�𔭎ˁA�Փˍ��W���L�^����
	bool rayHit = m_physicsWorld->RayTest(m_pos, rayEndPos, m_rayHitPos);
	
	//���C��������Ȃ��������A�Փˍ��W�����C�̏I�_�ɂ���
	if (rayHit == false)
	{
		m_rayHitPos = rayEndPos;
	}
}