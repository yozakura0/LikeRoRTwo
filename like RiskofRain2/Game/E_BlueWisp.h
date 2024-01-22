#pragma once
#include "AI/PathFinding/NaviMesh.h"
#include "AI/PathFinding/Path.h"
#include "AI/PathFinding/PathFinding.h"

class Player;

class E_BlueWisp : public IGameObject
{
public:
	E_BlueWisp();
	void ShowBlueWisp();
	void Move();
	void Rotation();
	void Attack();
	void CloseRangedAttack();
	void AttackCoolCount();
	void OnAnimationEvent(const wchar_t* clipName, const wchar_t* eventName);
	void MakeAttackCollision();
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
	ModelRender m_blueWispRender;

	//キャラクターコントローラー
	CharacterController m_blueWispController;

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
	//アニメーションの攻撃開始
	bool m_attackForAnim;

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
	enum BlueWispState
	{
		CREATE,
		MOVE,
		ATTACK_RANGE,
		BROKEN
	};
	//状態を管理する変数
	int m_blueWispStateNumber = 0;

	enum BlueWispAnimation
	{
		BLUEWISP_ENTRY,
		BLUEWISP_MOVE,
		BLUEWISP_ATTACK,
		BLUEWISP_BREAK,
		BLUEWISP_ANIMNUM
	};
	AnimationClip m_blueWispAnimationClips[BLUEWISP_ANIMNUM];

	Player* m_player;
};