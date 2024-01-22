#pragma once
#include "AI/PathFinding/NaviMesh.h"
#include "AI/PathFinding/Path.h"
#include "AI/PathFinding/PathFinding.h"

class Player;

class E_Wisp : public IGameObject
{
public:
	E_Wisp();
	void ShowWisp();
	void Move();
	void Rotation();
	void Attack();
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
	ModelRender m_wispRender;

	//キャラクターコントローラー
	CharacterController m_wispController;

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

	//ウィスプの状態
	enum WispState
	{
		CREATE,
		MOVE,
		ATTACK_CLOSE,
		BROKEN
	};
	//状態を管理する変数
	int m_wispStateNumber = 0;

	enum WispAnimation
	{
		WISP_ENTRY,
		WISP_MOVE,
		WISP_ATTACK,
		WISP_BREAK,
		WISP_ANIMNUM
	};
	AnimationClip m_wispAnimationClips[WISP_ANIMNUM];

	Player* m_player;
};

