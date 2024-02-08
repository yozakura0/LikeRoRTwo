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
	//�G�������o�Ă邩�v�Z
	float enemyRatio = m_enemyCount / MaxEnemyCount;
	
	//�w���֐�
	int exponentialResult = pow(0.5, enemyRatio) * 100;

	if (exponentialResult < 1)
	{
		exponentialResult = 0;
	}

	int randomNumber = rand() % 100 + 1;

	//�G���o�����m�����v�Z
	if (exponentialResult < randomNumber)
	{
		return;
	}

	int showPossibleEnemyCount = EnemyNum;
	int m_ShowPossibleEnemyList[4];

	//�e�G���ő吔�܂ŏo�����Ă��邩�m�F
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

	//�o����G�����Ȃ�
	if (showPossibleEnemyCount == 0)return;

	//�o���G��I��
	int showEnemyNum = rand() % showPossibleEnemyCount;

	/*for (int i = 0; i < m_showPossibleEnemyList->size(); i++)
	{
		if (i == showEnemyNum)
			m_showPossibleEnemyList->at(showEnemyNum);
		break;
	}*/

	//�I�΂ꂽ�G�������o���Ȃ�
	if (m_ShowPossibleEnemyList[showEnemyNum] == false)return;

	//���W����
	int showPos = rand() % 6;

	//�G���X�|�[��������
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
	//�e�G������ł��Ȃ������ׂ�
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