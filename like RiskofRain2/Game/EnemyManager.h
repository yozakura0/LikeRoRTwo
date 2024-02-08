#pragma once

class E_Beetle;
class E_Golem;
class E_Drone;
class E_BlueWisp;
class Player;

class EnemyManager : public IGameObject
{
public:
	EnemyManager();
	~EnemyManager();
	//�G���o�������鏈��
	void SetEnemy();
	//���񂾓G��T������
	void DeadEnemySearch();
	void Update();

private:

	//�r�[�g���̏o����
	int m_beetleCount;
	//�S�[�����̏o����
	int m_golemCount;
	//�C���v�̏o����
	//int m_impCount;
	//�h���[���̏o����
	int m_droneCount;
	//�E�B�X�v�̏o����
	int m_blueWispCount;

	//�G�̑��o����
	int m_enemyCount;
	//�G�̌��E�o����
	const int MaxEnemyCount = 30;
	
	//�G�̏o�Ă�����W
	const Vector3 EnemyShowPosition[6]
		=
	{
		{ -300,210,-2735},
		{-4930,-70,-2435},
		{3453,-70,1354},
		{-4146,1695,4432},
		{4480,1695,3846},
		{-838,1695,3000}
	};

	//�G
	enum Enemy
	{
		Beetle,
		BlueWisp,
		Drone,
		Golem,
		EnemyNum
	};

	//�e�G�̏����
	enum EnemyLimit
	{
		BeetleMax = /*12*/1,
		BlueWispMax = /*12*/1,
		DroneMax = /*10*/1,
		GolemMax = /*6*/1
	};

	enum EnemyDefaultDropMoney
	{
		MonsterMoney = 5,
		EliteMonsterMoney = 9,
	};

	enum EnemyDropMoneyMultiply
	{
		MonsterMoneyMul = 2,
		EliteMonsterMoneyMul = 13,
	};

	//�o����G�̃��X�g
	//std::vector<int> m_showPossibleEnemyList[4];
	
	E_Beetle* m_beetle[BeetleMax];
	//E_Imp* m_imp;
	E_BlueWisp* m_blueWisp[BlueWispMax];
	E_Drone* m_drone[DroneMax];
	E_Golem* m_golem[GolemMax];
	Player* m_player;
};

