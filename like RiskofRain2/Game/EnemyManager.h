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

	//ビートルの出現数
	int m_beetleCount;
	//ゴーレムの出現数
	int m_golemCount;
	//インプの出現数
	//int m_impCount;
	//赤ウィスプの出現数
	int m_redWispCount;
	//青ウィスプの出現数
	int m_blueWispCount;

	//敵の総出現数
	int m_enemyCount;
	//敵の限界出現数
	const int MaxEnemyCount = 40;
	
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
		RedWisp,
		Golem,
		EnemyNum
	};

	//各敵の上限数
	enum EnemyLimit
	{
		BeetleMax = 12,
		BlueWispMax = 12,
		RedWispMax = 10,
		GolemMax = 6
	};

	//出せる敵のリスト
	//std::vector<int> m_showPossibleEnemyList[4];
	
	E_Beetle* m_beetle[BeetleMax];
	//E_Imp* m_imp;
	E_BlueWisp* m_blueWisp[BlueWispMax];
	E_RedWisp* m_redWisp[RedWispMax];
	E_Golem* m_golem[GolemMax];
	Player* m_player;
};

