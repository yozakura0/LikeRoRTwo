#include "stdafx.h"
#include "EnemyManager.h"
#include "E_Beetle.h"
#include "E_Golem.h"
//#include "E_Imp.h"
//#include "E_Wisp.h"
#include "E_RedWisp.h"
#include "E_BlueWisp.h"
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
	//ìGÇ™âΩäÑèoÇƒÇÈÇ©åvéZ
	float enemyRatio = m_enemyCount / MaxEnemyCount;
	
	//éwêîä÷êî
	int exponentialResult = pow(0.5, enemyRatio) * 100;

	if (exponentialResult < 1)
	{
		exponentialResult = 0;
	}

	int randomNumber = rand() % 100 + 1;

	//ìGÇèoÇ∑Ç©ämó¶ÇåvéZ
	if (exponentialResult < randomNumber)
	{
		return;
	}

	int showPossibleEnemyCount = EnemyNum;
	int m_ShowPossibleEnemyList[4];

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

	if (m_redWispCount == RedWispMax) 
	{
		showPossibleEnemyCount--; 
		m_ShowPossibleEnemyList[RedWisp] = false;
	}
	else
	{
		//m_showPossibleEnemyList->push_back(RedWisp);
		m_ShowPossibleEnemyList[RedWisp] = true;
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

	//èoÇπÇÈìGÇ™Ç¢Ç»Ç¢
	if (showPossibleEnemyCount == 0)return;

	int showEnemyNum = rand() % showPossibleEnemyCount;

	/*for (int i = 0; i < m_showPossibleEnemyList->size(); i++)
	{
		if (i == showEnemyNum)
			m_showPossibleEnemyList->at(showEnemyNum);
		break;
	}*/

	if (m_ShowPossibleEnemyList[showEnemyNum] == false)return;

	int showPos = rand() % 6;

	switch (showEnemyNum)
	{
	case Beetle:
		for (int i = 0; i < BeetleMax; i++)
		{
			if (m_beetle[i] != nullptr) continue;

			m_beetle[i] = NewGO<E_Beetle>(0, "beetle");
			m_beetle[i]->SetPosition(EnemyShowPosition[showPos]);
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
			m_blueWisp[i]->ShowBlueWisp();
			m_blueWispCount++;
			break;
		}
	case RedWisp:
		for (int i = 0; i < RedWispMax; i++)
		{
			if (m_redWisp[i] != nullptr) continue;

			m_redWisp[i] = NewGO<E_RedWisp>(0, "redwisp");
			m_redWisp[i]->SetPosition(EnemyShowPosition[showPos]);
			m_redWisp[i]->ShowRedWisp();
			m_redWispCount++;
			break;
		}
	case Golem:
		for (int i = 0; i < GolemMax; i++)
		{
			if (m_golem[i] != nullptr) continue;

			m_golem[i] = NewGO<E_Golem>(0, "golem");
			m_golem[i]->SetPosition(EnemyShowPosition[showPos]);
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

	for (int i = 0; i < RedWispMax; i++)
	{
		if (m_redWisp[i] == nullptr)continue;
		if (m_redWisp[i]->IsDead())
		{
			m_redWisp[i] = nullptr;
			m_redWispCount--;
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