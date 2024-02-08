#pragma once
#include "AI/PathFinding/NaviMesh.h"
#include "AI/PathFinding/Path.h"
#include "AI/PathFinding/PathFinding.h"

class Player;

class E_Beetle : public IGameObject
{
public:
	E_Beetle();
	~E_Beetle();
	void ShowBeetle();
	void SetStatus();
	void Move();
	void Rotation();
	void MakeAttackCollision();
	void Attack();
	void Update();
	void OnAnimationEvent(const wchar_t* clipName, const wchar_t* eventName);
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
	ModelRender m_beetleRender;

	//�L�����N�^�[�R���g���[���[
	CharacterController m_beetleController;

	//���Ƃ����z
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
	nsAI::PathFinding m_pathFinding;
	bool m_isEnd;

	//���W
	Vector3 m_pos;
	//�ړ����x
	Vector3 m_moveSpeed = Vector3::Zero;
	//�O����
	Vector3 m_forward = Vector3::AxisZ;
	//�N�H�[�^�j�I��
	Quaternion m_rotation;

	//�����蔻��̔��a
	const float CapsuleRadius = 45.0f;
	//�����蔻��̍���
	const float CapsuleHeight = 20.0f;

	//���x��
	int m_Level = 0;

	//�̗�
	int m_HP = 80;
	//�̗͂̑�����
	const int AddHPtoLv = 24;

	//��b�_���[�W��
	int m_damage = 12;
	//�_���[�W�̑�����
	const double AddDamagetoLv = 2.4;

	//���U���t���O
	bool m_notAttack = true;

	//�A�j���[�V�����̍U�����t���O
	bool m_attackForAnim;

	//�ߋ�������
	const float m_nearDistance = 200.0f;

	//���G�t���O
	bool m_invincibleFlag = false;
	//���G����
	float m_invincible = 0.0f;
	//�L�����̖��G����
	const float InvincibleTime = 0.1f;

	//�|���ꂽ�Ƃ��Ƀh���b�v������z
	int m_dropMoney;

	//�r�[�g���̏��
	enum BeetleState
	{
		CREATE,
		MOVE,
		ATTACK_CLOSE,
		BROKEN
	};
	//��Ԃ��Ǘ�����ϐ�
	int m_beetleStateNumber = 0;

	enum BeetleAnimation
	{
		BEETLE_ENTRY,
		BEETLE_MOVE,
		BEETLE_ATTACK,
		BEETLE_BREAK,
		BEETLE_ANIMNUM
	};
	AnimationClip m_beetleAnimationClips[BEETLE_ANIMNUM];

	Player* m_player;
};

