#pragma once
#include "AI/PathFinding/NaviMesh.h"
#include "AI/PathFinding/Path.h"
#include "AI/PathFinding/PathFinding.h"

class Player;

class E_Beetle : public IGameObject
{
public:
	E_Beetle();
	void ShowBeetle();
	void Move();
	void Rotation();
	void MakeAttackCollision();
	void Attack();
	void Update();
	void OnAnimationEvent(const wchar_t* clipName, const wchar_t* eventName);
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
	ModelRender m_beetleRender;

	//キャラクターコントローラー
	CharacterController m_beetleController;

private:
	nsAI::NaviMesh m_nvmMesh;
	nsAI::Path m_path;
	nsAI::PathFinding m_pathFinding;
	bool m_isEnd;

	//座標
	Vector3 m_pos;
	//移動速度
	Vector3 m_moveSpeed;
	//前方向
	Vector3 m_forward = Vector3::AxisZ;
	//クォータニオン
	Quaternion m_rotation;

	//当たり判定の半径
	const float CapsuleRadius = 45.0f;
	//当たり判定の高さ
	const float CapsuleHeight = 20.0f;

	//体力
	int m_HP = 50;

	//基礎ダメージ量
	int m_damage;

	//未攻撃フラグ
	bool m_notAttack = true;

	//アニメーションの攻撃中フラグ
	bool m_attackForAnim;

	//近距離判定
	const float m_nearDistance = 200.0f;

	//無敵フラグ
	bool m_invincibleFlag = false;
	//無敵時間
	float m_invincible = 0.0f;
	//キャラの無敵時間
	const float InvincibleTime = 0.1f;

	//ビートルの状態
	enum BeetleState
	{
		CREATE,
		MOVE,
		ATTACK_CLOSE,
		BROKEN
	};
	//状態を管理する変数
	int m_beetleStateNumber = 0;

	enum BeetleAnimation
	{
		BEETLE_ENTRY,
		BEETLE_MOVE,
		BEETLE_ATTACK,
		BEETLE_BREAK,
		BEETLE_ANIMNUM
	};
	AnimationClip m_beetleAnimationClips[BEETLE_ANIMNUM];

	Player* m_player;
};

