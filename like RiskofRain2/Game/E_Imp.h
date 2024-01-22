#pragma once
#include "AI/PathFinding/NaviMesh.h"
#include "AI/PathFinding/Path.h"
#include "AI/PathFinding/PathFinding.h"

class Player;

class E_Imp : public IGameObject
{
public:
	E_Imp();
	void ShowImp();
	void Move();
	void Rotation();
	void Attack();
	void MakeAttackCollision();
	void ActionCoolCount();
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
	ModelRender m_impRender;

	//�L�����N�^�[�R���g���[���[
	CharacterController m_impController;

	//���񂾂�
	bool m_dead = false;

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
	const float CapsuleHeight = 60.0f;

	//�̗�
	int m_HP = 65;

	//��b�_���[�W��
	int m_damage;

	//�ߋ����U���t���O
	bool m_attackFlag;
	//���U���t���O
	bool m_notAttack = true;

	//�A�j���[�V�����̍U�����t���O
	bool m_attackForAnim;

	//�ߋ����U���̃N�[���^�C��
	float m_attackCool = 0.0f;
	const float m_attackCoolLimit = 1.0f;
	bool m_attackCoolFlag = false;

	//�u�����N�̃N�[���^�C��
	float m_brinkCool = 0.0f;
	const float m_brinkCoolLimit = 5.0f;
	int m_brinkCharge = BrinkChargeLimit;
	const int BrinkChargeLimit = 3;

	//�ߋ�������
	const float m_nearDistance = 200.0f;

	//�S�[�����̏��
	enum ImpState
	{
		CREATE,
		MOVE,
		ATTACK_CLOSE,
		BROKEN
	};
	//��Ԃ��Ǘ�����ϐ�
	int m_impStateNumber = 0;

	enum ImpAnimation
	{
		IMP_ENTRY,
		IMP_MOVE,
		IMP_ATTACK,
		IMP_BREAK,
		IMP_ANIMNUM
	};
	AnimationClip m_impAnimationClips[IMP_ANIMNUM];

	Player* m_player;
};

