#pragma once
#include "AI/PathFinding/NaviMesh.h"
#include "AI/PathFinding/Path.h"
#include "AI/PathFinding/PathFinding.h"

class Player;

class E_RedWisp : public IGameObject
{
public:
	E_RedWisp();
	void ShowRedWisp();
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
	ModelRender m_redWispRender;

	//キャラクターコントローラー
	CharacterController m_redWispController;

private:
	nsAI::NaviMesh m_nvmMesh;
	nsAI::Path m_path;
	nsAI::PathFinding m_pathFiding;

	//座標
	Vector3 m_pos;
	//移動速度
	Vector3 m_moveSpeed;
	//前方向
	Vector3 m_forward = Vector3::AxisZ;
	//クォータニオン
	Quaternion m_rotation;

	//当たり判定の半径
	const float CapsuleRadius = 40.0f;

	//当たり判定の高さ
	const float CapsuleHeight = 20.0f;

	//体力
	int m_HP = 55;

	//基礎ダメージ量
	int m_damage;

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

	//ウィスプの状態
	enum RedWispState
	{
		CREATE,
		MOVE,
		ATTACK_RANGE,
		BROKEN
	};
	//状態を管理する変数
	int m_redWispStateNumber = 0;

	enum RedWispAnimation
	{
		REDWISP_ENTRY,
		REDWISP_MOVE,
		REDWISP_ATTACK,
		REDWISP_BREAK,
		REDWISP_ANIMNUM
	};
	AnimationClip m_redWispAnimationClips[REDWISP_ANIMNUM];

	Player* m_player;
};