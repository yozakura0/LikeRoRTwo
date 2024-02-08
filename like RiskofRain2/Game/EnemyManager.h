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
	//敵を出現させる処理
	void SetEnemy();
	//死んだ敵を探す処理
	void DeadEnemySearch();
	void Update();

private:

	//ビートルの出現数
	int m_beetleCount;
	//ゴーレムの出現数
	int m_golemCount;
	//インプの出現数
	//int m_impCount;
	//ドローンの出現数
	int m_droneCount;
	//青ウィスプの出現数
	int m_blueWispCount;

	//敵の総出現数
	int m_enemyCount;
	//敵の限界出現数
	const int MaxEnemyCount = 30;
	
	//敵の出てくる座標
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

	//敵
	enum Enemy
	{
		Beetle,
		BlueWisp,
		Drone,
		Golem,
		EnemyNum
	};

	//各敵の上限数
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

	//出せる敵のリスト
	//std::vector<int> m_showPossibleEnemyList[4];
	
	E_Beetle* m_beetle[BeetleMax];
	//E_Imp* m_imp;
	E_BlueWisp* m_blueWisp[BlueWispMax];
	E_Drone* m_drone[DroneMax];
	E_Golem* m_golem[GolemMax];
	Player* m_player;
};

