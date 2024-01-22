#pragma once
#include "AI/PathFinding/NaviMesh.h"
#include "AI/PathFinding/Path.h"
#include "AI/PathFinding/PathFinding.h"

class Player;

class E_RedWisp : public IGameObject
{
public:
	E_RedWisp();
	void ShowRedWisp();
	void Move();
	void Rotation();
	void Attack();
	void RangedAttack();
	void AttackCoolCount();
	void Update();
	void StateManage();
	void AnimationState();
	void Damage();
	void Render(RenderContext& rc);

	void SetPosition(Vector3 pos)
	{
		m_pos = pos;
	}
	Vector3 GetPosition()
	{
		return m_pos;
	}

	//���f�������_�[
	ModelRender m_redWispRender;

	//�L�����N�^�[�R���g���[���[
	CharacterController m_redWispController;

private:
	nsAI::NaviMesh m_nvmMesh;
	nsAI::Path m_path;
	nsAI::PathFinding m_pathFiding;

	//���W
	Vector3 m_pos;
	//�ړ����x
	Vector3 m_moveSpeed;
	//�O����
	Vector3 m_forward = Vector3::AxisZ;
	//�N�H�[�^�j�I��
	Quaternion m_rotation;

	//�����蔻��̔��a
	const float CapsuleRadius = 40.0f;

	//�����蔻��̍���
	const float CapsuleHeight = 20.0f;

	//�̗�
	int m_HP = 55;

	//��b�_���[�W��
	int m_damage;

	//�������U���t���O
	bool m_attackFlag;
	//���U���t���O
	bool m_notAttack = true;

	//�������U���̃N�[���^�C��
	float m_attackCool = 0.0f;
	const float m_attackCoolLimit = 4.0f;
	bool m_attackCoolFlag = false;

	//��������
	const float m_nearDistance = 400.0f;

	//���G�t���O
	bool m_invincibleFlag = false;
	//���G����
	float m_invincible = 0.0f;
	//�L�����̖��G����
	const float InvincibleTime = 0.1f;

	//�E�B�X�v�̏��
	enum RedWispState
	{
		CREATE,
		MOVE,
		ATTACK_RANGE,
		BROKEN
	};
	//��Ԃ��Ǘ�����ϐ�
	int m_redWispStateNumber = 0;

	enum RedWispAnimation
	{
		REDWISP_ENTRY,
		REDWISP_MOVE,
		REDWISP_ATTACK,
		REDWISP_BREAK,
		REDWISP_ANIMNUM
	};
	AnimationClip m_redWispAnimationClips[REDWISP_ANIMNUM];

	Player* m_player;
};