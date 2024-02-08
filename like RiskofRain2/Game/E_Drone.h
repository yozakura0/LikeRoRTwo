#pragma once
#include "AI/PathFinding/NaviMesh.h"
#include "AI/PathFinding/Path.h"
#include "AI/PathFinding/PathFinding.h"

class Player;

class E_Drone : public IGameObject
{
public:
	E_Drone();
	~E_Drone();
	void ShowDrone();
	void SetStatus();
	void Move();
	void Rotation();
	void Attack();
	void RangedAttack();
	void AttackCoolCount();
	void Update();
	void StateManage();
	void AnimationState();
	void Damage();
	void Render(RenderContext& rc);

	void SetPosition(Vector3 pos)
	{
		m_pos = pos;
	}
	Vector3 GetPosition()
	{
		return m_pos;
	}

	//モデルレンダー
	ModelRender m_droneRender;

	//キャラクターコントローラー
	CharacterController m_droneController;

	void SetDropMoney(int money)
	{
		m_dropMoney = money;
	}

	//レベルを設定
	void SetLevel(int Lv)
	{
		m_Level = Lv;
	}

private:
	nsAI::NaviMesh m_nvmMesh;
	nsAI::Path m_path;
	nsAI::PathFinding m_pathFiding;

	//座標
	Vector3 m_pos;
	//移動速度
	Vector3 m_moveSpeed = Vector3::Zero;
	//前方向
	Vector3 m_forward = Vector3::AxisZ;
	//クォータニオン
	Quaternion m_rotation;

	//当たり判定の半径
	const float CapsuleRadius = 40.0f;

	//当たり判定の高さ
	const float CapsuleHeight = 20.0f;

	//レベル
	int m_Level = 0;

	//体力
	int m_HP = 35;
	//体力の増加量
	const int AddHPtoLv = 10;

	//基礎ダメージ量
	int m_damage = 4;
	//ダメージの増加量
	const double AddDamagetoLv = 0.6;

	//遠距離攻撃フラグ
	bool m_attackFlag;
	//未攻撃フラグ
	bool m_notAttack = true;

	//遠距離攻撃のクールタイム
	float m_attackCool = 0.0f;
	const float m_attackCoolLimit = 4.0f;
	bool m_attackCoolFlag = false;

	//距離判定
	const float m_nearDistance = 400.0f;

	//無敵フラグ
	bool m_invincibleFlag = false;
	//無敵時間
	float m_invincible = 0.0f;
	//キャラの無敵時間
	const float InvincibleTime = 0.1f;

	//倒されたときにドロップする金額
	int m_dropMoney;

	////ウィスプの状態
	//enum RedWispState
	//{
	//	CREATE,
	//	MOVE,
	//	ATTACK_RANGE,
	//	BROKEN
	//};
	////状態を管理する変数
	//int m_redWispStateNumber = 0;

	/*enum RedWispAnimation
	{
		REDWISP_ENTRY,
		REDWISP_MOVE,
		REDWISP_ATTACK,
		REDWISP_BREAK,
		REDWISP_ANIMNUM
	};
	AnimationClip m_redWispAnimationClips[REDWISP_ANIMNUM];*/

	EffectEmitter* m_startEmitter;

	Player* m_player;
};