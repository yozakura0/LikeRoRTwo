#include "stdafx.h"
#include "EnemyManager.h"
#include "E_Beetle.h"
#include "E_Golem.h"
#include "E_RedWisp.h"
#include "E_BlueWisp.h"
#include "E_Drone.h"
#include "Player.h"

EnemyManager::EnemyManager()
{
	SetEnemy();
}

EnemyManager::~EnemyManager()
{

}

void EnemyManager::SetEnemy()
{
	//敵が何割出てるか計算
	float enemyRatio = m_enemyCount / MaxEnemyCount;
	
	//指数関数
	int exponentialResult = pow(0.5, enemyRatio) * 100;

	if (exponentialResult < 1)
	{
		exponentialResult = 0;
	}

	int randomNumber = rand() % 100 + 1;

	//敵を出すか確率を計算
	if (exponentialResult < randomNumber)
	{
		return;
	}

	int showPossibleEnemyCount = EnemyNum;
	int m_ShowPossibleEnemyList[4];

	//各敵が最大数まで出現しているか確認
	if (m_beetleCount == BeetleMax)
	{
		showPossibleEnemyCount--;
		m_ShowPossibleEnemyList[Beetle] = false;
	}
	else 
	{
		//m_showPossibleEnemyList->push_back(Beetle);
		m_ShowPossibleEnemyList[Beetle] = true;
	}

	if (m_droneCount == DroneMax) 
	{
		showPossibleEnemyCount--; 
		m_ShowPossibleEnemyList[Drone] = false;
	}
	else
	{
		//m_showPossibleEnemyList->push_back(RedWisp);
		m_ShowPossibleEnemyList[Drone] = true;
	}

	if (m_blueWispCount == BlueWispMax)
	{
		showPossibleEnemyCount--;		
		m_ShowPossibleEnemyList[BlueWisp] = false;
	}
	else
	{
		//m_showPossibleEnemyList->push_back(BlueWisp);
		m_ShowPossibleEnemyList[BlueWisp] = true;
	}

	if (m_golemCount == GolemMax)
	{
		showPossibleEnemyCount--;
		m_ShowPossibleEnemyList[Golem] = false;
	}
	else
	{
		//m_showPossibleEnemyList->push_back(Golem);
		m_ShowPossibleEnemyList[Golem] = true;
	}

	//出せる敵がいない
	if (showPossibleEnemyCount == 0)return;

	//出す敵を選択
	int showEnemyNum = rand() % showPossibleEnemyCount;

	/*for (int i = 0; i < m_showPossibleEnemyList->size(); i++)
	{
		if (i == showEnemyNum)
			m_showPossibleEnemyList->at(showEnemyNum);
		break;
	}*/

	//選ばれた敵がもう出せない
	if (m_ShowPossibleEnemyList[showEnemyNum] == false)return;

	//座標決め
	int showPos = rand() % 6;

	//敵をスポーンさせる
	switch (showEnemyNum)
	{
	case Beetle:
		for (int i = 0; i < BeetleMax; i++)
		{
			if (m_beetle[i] != nullptr) continue;

			m_beetle[i] = NewGO<E_Beetle>(0, "beetle");
			m_beetle[i]->SetPosition(EnemyShowPosition[showPos]);
			m_beetle[i]->SetDropMoney(MonsterMoney);
			m_beetle[i]->ShowBeetle();
			m_beetleCount++;
			break;
		}

	case BlueWisp:
		for (int i = 0; i < BlueWispMax; i++)
		{
			if (m_blueWisp[i] != nullptr) continue;

			m_blueWisp[i] = NewGO<E_BlueWisp>(0, "bluewisp");
			m_blueWisp[i]->SetPosition(EnemyShowPosition[showPos]);
			m_blueWisp[i]->SetDropMoney(MonsterMoney);
			m_blueWisp[i]->ShowBlueWisp();
			m_blueWispCount++;
			break;
		}
	case Drone:
		for (int i = 0; i < DroneMax; i++)
		{
			if (m_drone[i] != nullptr) continue;

			m_drone[i] = NewGO<E_Drone>(0, "drone");
			m_drone[i]->SetPosition(EnemyShowPosition[showPos]);
			m_drone[i]->SetDropMoney(MonsterMoney);
			m_drone[i]->ShowDrone();
			m_droneCount++;
			break;
		}
	case Golem:
		for (int i = 0; i < GolemMax; i++)
		{
			if (m_golem[i] != nullptr) continue;

			m_golem[i] = NewGO<E_Golem>(0, "golem");
			m_golem[i]->SetPosition(EnemyShowPosition[showPos]);
			m_golem[i]->SetDropMoney(EliteMonsterMoney);
			m_golem[i]->ShowGolem();
			m_golemCount++;
			break;
		}
	default:
		break;
	}

	m_enemyCount++;
}

void EnemyManager::DeadEnemySearch()
{
	//各敵が死んでいないか調べる
	for (int i = 0; i < BeetleMax; i++)
	{
		if (m_beetle[i] == nullptr)continue;
		if (m_beetle[i]->IsDead())
		{
			m_beetle[i] = nullptr;
			m_beetleCount--;
			m_enemyCount--;
		}
	}

	for (int i = 0; i < BlueWispMax; i++)
	{
		if (m_blueWisp[i] == nullptr)continue;
		if (m_blueWisp[i]->IsDead())
		{
			m_blueWisp[i] = nullptr;
			m_blueWispCount--;
			m_enemyCount--;
		}
	}

	for (int i = 0; i < DroneMax; i++)
	{
		if (m_drone[i] == nullptr)continue;
		if (m_drone[i]->IsDead())
		{
			m_drone[i] = nullptr;
			m_droneCount--;
			m_enemyCount--;
		}
	}

	for (int i = 0; i < GolemMax; i++)
	{
		if (m_golem[i] == nullptr)continue;
		if (m_golem[i]->IsDead())
		{
			m_golem[i] = nullptr;
			m_golemCount--;
			m_enemyCount--;
		}
	}
}

void EnemyManager::Update()
{
	SetEnemy();
	DeadEnemySearch();

}