#pragma once
#include "Number.h"
#include "Player_const.h"

class GameCamera;

class Player : public IGameObject
{
public:
	Player();
	~Player();
	void Update();
	//移動、ジャンプ
	void Move();
	//向きの回転
	void Turn();
	//レベルアップ
	void LevelUp();
	//ステータスの設定
	void StatusSetUp();
	//ダメージを受けた処理
	void Damaged();
	//死亡
	void Dead();
	//攻撃
	void Attack();
	//攻撃インターバルの計算
	void AttackInterval();
	//箱を開ける
	void Action();
	//アイテムを取る
	void ItemGet(int itemRarity, int itemNum);
	//持っているアイテムの恩恵
	void ItemPower();
	void Render(RenderContext& rc);

	//モデルレンダー
	ModelRender m_playerRender;


	//デバッグ:レンダー
	ModelRender m_testRen;
	FontRender m_fontRender;
	FontRender m_posfontRender;
	
	wchar_t m_posText[256];
	//プレイヤーの初期座標
	const Vector3 m_firstPosition = { 0.0f,100.0f,300.0f };
	//プレイヤーの座標
	Vector3 m_position = m_firstPosition;
	//キャラクターコントローラー
	CharacterController m_characterController;
	//移動速度
	Vector3 m_moveSpeed;
	//プレイヤーの角度
	Quaternion m_rotation;

	//受けたダメージ量
	float m_receiveDamage = m_firstReceiveDamage;

	//行動を起こしたか
	bool m_actionFlag = false;

	//基礎ダメージ
	float m_playerDamage = FirstPlayerDamage;

	//倒した敵の座標を設定する
	void SetKillEnemy(Vector3 pos, int enemyCount = 1)
	{
		m_killEnemyPos[enemyCount] = pos;
		m_killEnemyCount = enemyCount;
		m_killEnemyFlag = true;
	}

private:
	//参考はコマンドー
	//プレイヤーのレベル
	int m_playerLevel = 1;

	//所持経験値
	int m_playerEXP = 0;

	//必要経験値
	int m_needPlayerEXP = m_playerLevel * NeedPlayerEXPMultiplier;

	//所持金
	int m_money = 0;

	//最大体力
	float m_playerMaxHP = FirstPlayerMaxHP;

	//現在の体力
	float m_playerHP = m_playerMaxHP;

	//自然治癒力
	float m_autoHeal = FirstAutoHeal;

	//アーマー量
	int m_playerArmor = FirstPlayerArmor;

	//被ダメ倍率
	float m_playerTakenDamageMultiply = FirstPlayerTakenDamageMultiply;

	//クリティカル確率
	int m_criticalRate = FirstCriticalRate;

	//クリティカルダメージ
	const int m_criticalDamage = 2;

	//スティック入力に対する移動速度の倍率
	float m_playerMoveMultiplier = 200.0f;

	//無敵フラグ
	bool m_invincibleFlag = false;
	//無敵時間
	float m_invincible = 0.0f;

	//アイテムによる強化
	
	//氷の遺物の重複数
	int m_frostRelicRepetitive = 0;
	//氷の遺物の経過時間
	float m_frostRelicTime;


	//体力の増強
	int m_hpBoost = 0;

	//回復力の増強
	int m_healBoost = 0;

	//アーマーの増強
	int m_armorBoost = 0;

	//固定値の軽減(アーマープレート)
	int m_abatement = 0;

	//攻撃を遮断する確率(タファー)
	float m_blockProb;

	//追加ジャンプ回数
	int m_jumpCount;

	//クリティカル率の増強
	int m_criticalBoost = 0;

	//移動速度の増強
	float m_moveBoost = 1;

	//動いてない判定をする境界の値
	const float NoneMoveJudge = 0.001f;

	//被ダメ倍率の初期値
	const float FirstPlayerTakenDamageMultiply = 1;

	//クリティカル確率の初期値
	const int FirstCriticalRate = 1;

	//移動速度の初期化値
	const Vector3 FirstMoveSpeed = { 0.0f,0.0f,0.0f };

	//被ダメージの初期化値
	const float m_firstReceiveDamage = 0.0f;

	//通常攻撃間隔
	float m_normalShotInterval = 0.0f;

	//通常攻撃をできるフラグ
	bool m_normalShot = true;

	//前方向
	Vector3 m_forward = Vector3::AxisZ;

	//1秒を読む変数
	float m_oneSecond = 0;

	GameCamera* m_gameCamera;

	//ダッシュフラグ
	bool m_dashFlag = false;

	//死んでるフラグ
	bool m_deadFlag = false;

	//敵を倒したフラグ
	bool m_killEnemyFlag = false;
	//倒した敵数
	int m_killEnemyCount;
	//倒した敵の座標
	Vector3 m_killEnemyPos[20];

	//持っているアイテムと個数
	//コモン
	int m_playerItemList_common[CommonNum][ItemJudgeNum];
	//アンコモン
	int m_playerItemList_uncommon[UncommonNum][ItemJudgeNum];
	//レア
	int m_playerItemList_rare[RareNum][ItemJudgeNum];

	enum EnAnimationClips
	{
		ANIMATION_IDLE,
		ANIMATION_WALK,
		ANIMTION_JUMP,
		ANIMATION_NUM
	};
	AnimationClip m_playerAnimationClips[ANIMATION_NUM];

};

