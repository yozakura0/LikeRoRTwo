#pragma once

class E_Beetle;
class E_Golem;
//class E_Imp;
class E_RedWisp;
class E_BlueWisp;
class Player;

class EnemyManager : public IGameObject
{
public:
	EnemyManager();
	~EnemyManager();
	void SetEnemy();
	void DeadEnemySearch();
	void Update();

private:

	//�r�[�g���̏o����
	int m_beetleCount;
	//�S�[�����̏o����
	int m_golemCount;
	//�C���v�̏o����
	//int m_impCount;
	//�ԃE�B�X�v�̏o����
	int m_redWispCount;
	//�E�B�X�v�̏o����
	int m_blueWispCount;

	//�G�̑��o����
	int m_enemyCount;
	//�G�̌��E�o����
	const int MaxEnemyCount = 40;
	
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
		RedWisp,
		Golem,
		EnemyNum
	};

	//�e�G�̏����
	enum EnemyLimit
	{
		BeetleMax = 12,
		BlueWispMax = 12,
		RedWispMax = 10,
		GolemMax = 6
	};

	//�o����G�̃��X�g
	//std::vector<int> m_showPossibleEnemyList[4];
	
	E_Beetle* m_beetle[BeetleMax];
	//E_Imp* m_imp;
	E_BlueWisp* m_blueWisp[BlueWispMax];
	E_RedWisp* m_redWisp[RedWispMax];
	E_Golem* m_golem[GolemMax];
	Player* m_player;
};

