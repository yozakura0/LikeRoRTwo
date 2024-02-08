#pragma once
#include "AI/PathFinding/NaviMesh.h"
#include "AI/PathFinding/Path.h"
#include "AI/PathFinding/PathFinding.h"

class Player;

class E_Drone : public IGameObject
{
public:
	E_Drone();
	~E_Drone();
	void ShowDrone();
	void SetStatus();
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
	ModelRender m_droneRender;

	//�L�����N�^�[�R���g���[���[
	CharacterController m_droneController;

	void SetDropMoney(int money)
	{
		m_dropMoney = money;
	}

	//���x����ݒ�
	void SetLevel(int Lv)
	{
		m_Level = Lv;
	}

private:
	nsAI::NaviMesh m_nvmMesh;
	nsAI::Path m_path;
	nsAI::PathFinding m_pathFiding;

	//���W
	Vector3 m_pos;
	//�ړ����x
	Vector3 m_moveSpeed = Vector3::Zero;
	//�O����
	Vector3 m_forward = Vector3::AxisZ;
	//�N�H�[�^�j�I��
	Quaternion m_rotation;

	//�����蔻��̔��a
	const float CapsuleRadius = 40.0f;

	//�����蔻��̍���
	const float CapsuleHeight = 20.0f;

	//���x��
	int m_Level = 0;

	//�̗�
	int m_HP = 35;
	//�̗͂̑�����
	const int AddHPtoLv = 10;

	//��b�_���[�W��
	int m_damage = 4;
	//�_���[�W�̑�����
	const double AddDamagetoLv = 0.6;

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

	//�|���ꂽ�Ƃ��Ƀh���b�v������z
	int m_dropMoney;

	////�E�B�X�v�̏��
	//enum RedWispState
	//{
	//	CREATE,
	//	MOVE,
	//	ATTACK_RANGE,
	//	BROKEN
	//};
	////��Ԃ��Ǘ�����ϐ�
	//int m_redWispStateNumber = 0;

	/*enum RedWispAnimation
	{
		REDWISP_ENTRY,
		REDWISP_MOVE,
		REDWISP_ATTACK,
		REDWISP_BREAK,
		REDWISP_ANIMNUM
	};
	AnimationClip m_redWispAnimationClips[REDWISP_ANIMNUM];*/

	EffectEmitter* m_startEmitter;

	Player* m_player;
};