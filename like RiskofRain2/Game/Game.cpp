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

#include "graphics/effect/EffectEmitter.h"

Game::Game()
{
	EffectEngine::GetInstance()->ResistEffect(0, u"Assets/effect/impact.efk");
	EffectEngine::GetInstance()->ResistEffect(1, u"Assets/effect/moneydrop.efk");
	EffectEngine::GetInstance()->ResistEffect(2, u"Assets/effect/dronesporn.efk");

	//m_skyCube = NewGO<SkyCube>(0, "skycube");

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


	//当たり判定を有効化する。
	//PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();
}

Game::~Game()
{
	DeleteGO(m_player);
	//DeleteGO(m_skyCube);
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
	//フレーム経過数を計測
	m_frameCount++;

	//秒数を進める
	if (m_frameCount >= 60)
	{
		m_frameCount = 0;
		m_secondCount++;
	}

	//分数を進める
	if (m_secondCount >= 60)
	{
		m_secondCount = 0;
		m_minuteCount++;
	}

	//敵のレベルアップ処理
	if (m_minuteCount)
	{

	}

	m_ui->SetTime(m_minuteCount, m_secondCount);
}

void Game::Render(RenderContext& rc)
{

}