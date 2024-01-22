#pragma once
#include "AI/PathFinding/NaviMesh.h"
#include "AI/PathFinding/Path.h"
#include "AI/PathFinding/PathFinding.h"

class Player;

class E_Wisp : public IGameObject
{
public:
	E_Wisp();
	void ShowWisp();
	void Move();
	void Rotation();
	void Attack();
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
	ModelRender m_wispRender;

	//�L�����N�^�[�R���g���[���[
	CharacterController m_wispController;

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

	//�E�B�X�v�̏��
	enum WispState
	{
		CREATE,
		MOVE,
		ATTACK_CLOSE,
		BROKEN
	};
	//��Ԃ��Ǘ�����ϐ�
	int m_wispStateNumber = 0;

	enum WispAnimation
	{
		WISP_ENTRY,
		WISP_MOVE,
		WISP_ATTACK,
		WISP_BREAK,
		WISP_ANIMNUM
	};
	AnimationClip m_wispAnimationClips[WISP_ANIMNUM];

	Player* m_player;
};

