#pragma once
#include "AI/PathFinding/NaviMesh.h"
#include "AI/PathFinding/Path.h"
#include "AI/PathFinding/PathFinding.h"

class Player;

class E_Golem : public IGameObject
{
public:
	E_Golem();
	void ShowGolem();
	void Move();
	void Rotation();
	void Attack();
	void AttackCoolCount();
	void RangedAttack();
	void CloseRangedAttack();
	void OnAnimationEvent(const wchar_t* clipName, const wchar_t* eventName);
	void MakeAttackCollision();
	void Damage();
	void StateManage();
	void AnimationState();
	void Update();
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
	ModelRender m_golemRender;

	//�L�����N�^�[�R���g���[���[
	CharacterController m_golemController;

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
	int m_HP = 100;

	//��b�_���[�W��
	int m_damage;

	//�ߋ����U���̃N�[���^�C��
	float m_closeRangedAttackCool = 0.0f;
	const float m_closeRangedAttackCoolLimit = 1.0f;
	bool m_closeRangedAttackCoolFlag = false;

	//�������U���̃N�[���^�C��
	float m_rangedAttackCool = 0.0f;
	const float m_rangedAttackCoolLimit = 5.0f;
	bool m_rangedAttackCoolFlag = false;

	//�������U���t���O
	bool m_rangedAttackFlag;
	//�ߋ����U���t���O
	bool m_closeRangedAttackFlag;
	//���U���t���O
	bool m_notAttack = true;

	//�A�j���[�V�����̍U�����t���O
	bool m_attackForAnim;

	//�����蔻��̔��a
	const float CapsuleRadius = 45.0f;

	//�����蔻��̍���
	const float CapsuleHeight = 200.0f;

	//�ߋ�������
	const float m_nearDistance = 200.0f;
	//����������
	const float m_longDistance = 600.0f;

	//���G�t���O
	bool m_invincibleFlag = false;
	//���G����
	float m_invincible = 0.0f;
	//�L�����̖��G����
	const float InvincibleTime = 0.1f;

	//�S�[�����̏��
	enum GolemState
	{
		CREATE,
		MOVE,
		ATTACK_CLOSE,
		ATTACK_RANGE,
		BROKEN
	};
	//��Ԃ��Ǘ�����ϐ�
	int m_golemStateNumber = 0;

	enum GolemAnimation
	{
		GOLEM_MOVE,
		GOLEM_PUNCH,
		GOLEM_BREAK,
		GOLEM_ANIMNUM
	};
	AnimationClip m_golemAnimationClips[GOLEM_ANIMNUM];

	Bone* m_bone;
	Player* m_player;
};

