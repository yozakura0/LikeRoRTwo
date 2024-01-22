#pragma once
#include "Number.h"
#include "Player_const.h"

class GameCamera;

class Player : public IGameObject
{
public:
	Player();
	~Player();
	void Update();
	//�ړ��A�W�����v
	void Move();
	//�����̉�]
	void Turn();
	//���x���A�b�v
	void LevelUp();
	//�X�e�[�^�X�̐ݒ�
	void StatusSetUp();
	//�_���[�W���󂯂�����
	void Damaged();
	//���S
	void Dead();
	//�U��
	void Attack();
	//�U���C���^�[�o���̌v�Z
	void AttackInterval();
	//�����J����
	void Action();
	//�A�C�e�������
	void ItemGet(int itemRarity, int itemNum);
	//�����Ă���A�C�e���̉��b
	void ItemPower();
	void Render(RenderContext& rc);

	//���f�������_�[
	ModelRender m_playerRender;


	//�f�o�b�O:�����_�[
	ModelRender m_testRen;
	FontRender m_fontRender;
	FontRender m_posfontRender;
	
	wchar_t m_posText[256];
	//�v���C���[�̏������W
	const Vector3 m_firstPosition = { 0.0f,100.0f,300.0f };
	//�v���C���[�̍��W
	Vector3 m_position = m_firstPosition;
	//�L�����N�^�[�R���g���[���[
	CharacterController m_characterController;
	//�ړ����x
	Vector3 m_moveSpeed;
	//�v���C���[�̊p�x
	Quaternion m_rotation;

	//�󂯂��_���[�W��
	float m_receiveDamage = m_firstReceiveDamage;

	//�s�����N��������
	bool m_actionFlag = false;

	//��b�_���[�W
	float m_playerDamage = FirstPlayerDamage;

	//�|�����G�̍��W��ݒ肷��
	void SetKillEnemy(Vector3 pos, int enemyCount = 1)
	{
		m_killEnemyPos[enemyCount] = pos;
		m_killEnemyCount = enemyCount;
		m_killEnemyFlag = true;
	}

private:
	//�Q�l�̓R�}���h�[
	//�v���C���[�̃��x��
	int m_playerLevel = 1;

	//�����o���l
	int m_playerEXP = 0;

	//�K�v�o���l
	int m_needPlayerEXP = m_playerLevel * NeedPlayerEXPMultiplier;

	//������
	int m_money = 0;

	//�ő�̗�
	float m_playerMaxHP = FirstPlayerMaxHP;

	//���݂̗̑�
	float m_playerHP = m_playerMaxHP;

	//���R������
	float m_autoHeal = FirstAutoHeal;

	//�A�[�}�[��
	int m_playerArmor = FirstPlayerArmor;

	//��_���{��
	float m_playerTakenDamageMultiply = FirstPlayerTakenDamageMultiply;

	//�N���e�B�J���m��
	int m_criticalRate = FirstCriticalRate;

	//�N���e�B�J���_���[�W
	const int m_criticalDamage = 2;

	//�X�e�B�b�N���͂ɑ΂���ړ����x�̔{��
	float m_playerMoveMultiplier = 200.0f;

	//���G�t���O
	bool m_invincibleFlag = false;
	//���G����
	float m_invincible = 0.0f;

	//�A�C�e���ɂ�鋭��
	
	//�X�̈╨�̏d����
	int m_frostRelicRepetitive = 0;
	//�X�̈╨�̌o�ߎ���
	float m_frostRelicTime;


	//�̗͂̑���
	int m_hpBoost = 0;

	//�񕜗͂̑���
	int m_healBoost = 0;

	//�A�[�}�[�̑���
	int m_armorBoost = 0;

	//�Œ�l�̌y��(�A�[�}�[�v���[�g)
	int m_abatement = 0;

	//�U�����Ւf����m��(�^�t�@�[)
	float m_blockProb;

	//�ǉ��W�����v��
	int m_jumpCount;

	//�N���e�B�J�����̑���
	int m_criticalBoost = 0;

	//�ړ����x�̑���
	float m_moveBoost = 1;

	//�����ĂȂ���������鋫�E�̒l
	const float NoneMoveJudge = 0.001f;

	//��_���{���̏����l
	const float FirstPlayerTakenDamageMultiply = 1;

	//�N���e�B�J���m���̏����l
	const int FirstCriticalRate = 1;

	//�ړ����x�̏������l
	const Vector3 FirstMoveSpeed = { 0.0f,0.0f,0.0f };

	//��_���[�W�̏������l
	const float m_firstReceiveDamage = 0.0f;

	//�ʏ�U���Ԋu
	float m_normalShotInterval = 0.0f;

	//�ʏ�U�����ł���t���O
	bool m_normalShot = true;

	//�O����
	Vector3 m_forward = Vector3::AxisZ;

	//1�b��ǂޕϐ�
	float m_oneSecond = 0;

	GameCamera* m_gameCamera;

	//�_�b�V���t���O
	bool m_dashFlag = false;

	//����ł�t���O
	bool m_deadFlag = false;

	//�G��|�����t���O
	bool m_killEnemyFlag = false;
	//�|�����G��
	int m_killEnemyCount;
	//�|�����G�̍��W
	Vector3 m_killEnemyPos[20];

	//�����Ă���A�C�e���ƌ�
	//�R����
	int m_playerItemList_common[CommonNum][ItemJudgeNum];
	//�A���R����
	int m_playerItemList_uncommon[UncommonNum][ItemJudgeNum];
	//���A
	int m_playerItemList_rare[RareNum][ItemJudgeNum];

	enum EnAnimationClips
	{
		ANIMATION_IDLE,
		ANIMATION_WALK,
		ANIMTION_JUMP,
		ANIMATION_NUM
	};
	AnimationClip m_playerAnimationClips[ANIMATION_NUM];

};

