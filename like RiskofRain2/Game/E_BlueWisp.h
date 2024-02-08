#pragma once
#include "AI/PathFinding/NaviMesh.h"
#include "AI/PathFinding/Path.h"
#include "AI/PathFinding/PathFinding.h"

class Player;

class E_BlueWisp : public IGameObject
{
public:
	E_BlueWisp();
	~E_BlueWisp();
	void ShowBlueWisp();
	void SetStatus();
	void Move();
	void Rotation();
	void Attack();
	void CloseRangedAttack();
	void AttackCoolCount();
	void OnAnimationEvent(const wchar_t* clipName, const wchar_t* eventName);
	void MakeAttackCollision();
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
	ModelRender m_blueWispRender;

	//�L�����N�^�[�R���g���[���[
	CharacterController m_blueWispController;

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
	int m_HP = 55;
	//�̗͂̑�����
	const int AddHPtoLv = 15;

	//��b�_���[�W��
	int m_damage = 5;
	//�_���[�W�̑�����
	const double AddDamagetoLv = 1.6;

	//�������U���t���O
	bool m_attackFlag;
	//���U���t���O
	bool m_notAttack = true;
	//�A�j���[�V�����̍U���J�n
	bool m_attackForAnim;

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

	//�E�B�X�v�̏��
	enum BlueWispState
	{
		CREATE,
		MOVE,
		ATTACK_RANGE,
		BROKEN
	};
	//��Ԃ��Ǘ�����ϐ�
	int m_blueWispStateNumber = 0;

	enum BlueWispAnimation
	{
		BLUEWISP_ENTRY,
		BLUEWISP_MOVE,
		BLUEWISP_ATTACK,
		BLUEWISP_BREAK,
		BLUEWISP_ANIMNUM
	};
	AnimationClip m_blueWispAnimationClips[BLUEWISP_ANIMNUM];

	Player* m_player;
	EffectEmitter* effectEmitter;
};