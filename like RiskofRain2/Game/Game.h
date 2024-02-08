#pragma once

class Player;
class BackGround;
class GameCamera;
class ItemBoxManager;
class ItemManager;
class EnemyManager;
class UI;

class Game : public IGameObject
{
public:
	Game();
	~Game();
	void Update();
	void Timer();
	void Render(RenderContext& rc);

	//経過フレーム数
	int m_frameCount = FirstFrameCount;
	//初期化値
	const int FirstFrameCount = 0;
	
	//秒数時計
	int m_secondCount = FirstSecondCount;
	const int FirstSecondCount = 0;

	//分数時計
	int m_minuteCount = FirstMinuteCount;
	//初期化値
	const int FirstMinuteCount = 0;

	//敵のレベルを取得する
	int GetEnemyLevel()
	{
		return m_enemyLevel;
	}

private:
	//敵のレベル
	int m_enemyLevel = 0;

	//モデルの座標
	Vector3 m_modelPos = { 0.0f,0.0f,0.0f };

	bool flag = true;

	//SceneLight m_sceneLight;
	//modelSLight m_light;
	int m_pointNum;

	//空
	SkyCube* m_skyCube = nullptr;
	//プレイヤー
	Player* m_player = nullptr;
	//背景
	BackGround* m_backGround = nullptr;
	//ゲームカメラ
	GameCamera* m_gameCamera = nullptr;
	//箱マネージャー
	ItemBoxManager* m_itemBoxManager = nullptr;
	//アイテムマネージャー
	ItemManager* m_itemManager = nullptr;
	//敵マネージャー
	EnemyManager* m_enemyManager = nullptr;
	//UI
	UI* m_ui = nullptr;
};

