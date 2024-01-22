#include "stdafx.h"
#include "Game.h"
#include "Number.h"

#include "Player.h"
#include "BackGround.h"
#include "GameCamera.h"
#include "ItemBoxManager.h"
#include "ItemManager.h"
#include "EnemyManager.h"
#include "UI.h"

Game::Game()
{
	m_player = NewGO<Player>(0, "player");
	m_backGround = NewGO<BackGround>(0, "backGround");
	m_gameCamera = NewGO<GameCamera>(0, "gameCamera");
	m_itemBoxManager = NewGO<ItemBoxManager>(0, "itemBoxManager");
	m_itemManager = NewGO<ItemManager>(0, "itemManager");
	m_enemyManager = NewGO<EnemyManager>(0, "enemyManager");
	m_ui= NewGO<UI>(0, "ui");


	/*g_sceneLight->SetDirPosition(Vector3(1.0f, -1.0f, -1.0f));
	g_sceneLight->SetDirColor(Vector3(0.5f, 0.5f, 0.5f));*/

	//pointNum = m_pointLight.Init();
	//m_pointLight.SetPosition(pointLPos, pointNum);
	//m_pointLight.SetColor(Vector3(10.0f, 10.0f, 10.0f), pointNum);
	////m_pointLight.SetAffectPowParam(0.7f);
	//m_pointLight.SetRange(100.0f, pointNum);

	//“–‚½‚è”»’è‚ð—LŒø‰»‚·‚éB
	PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();
}

Game::~Game()
{
	DeleteGO(m_player);
	DeleteGO(m_backGround);
	DeleteGO(m_gameCamera);
}

void Game::Update()
{
	if (flag)
	{
		flag = false;
		//m_itemBoxManager->SetBox();
	}

	Timer();

	/*if (g_pad[0]->IsPress(enButtonUp))
	{
		m_modelPos.z += 1.0f;
	}
	if (g_pad[0]->IsPress(enButtonDown))
	{
		m_modelPos.z -= 1.0f;
	}*/

	//g_sceneLight->SetPtPosition(pointLPos);
	//m_light.pointLights.SetPosition(pointLPos);
	//m_light.pointLights.Update();
	//m_pointLight.SetPosition(pointLPos, pointNum);
	//m_pointLight.Update();

}

void Game::Timer()
{
	m_frameCount++;

	if (m_frameCount >= 60)
	{
		m_frameCount = 0;
		m_secondCount++;
	}

	if (m_secondCount >= 60)
	{
		m_secondCount = 0;
		m_minuteCount++;
	}
}

void Game::Render(RenderContext& rc)
{

}