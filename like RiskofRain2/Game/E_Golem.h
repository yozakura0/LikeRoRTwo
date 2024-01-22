#pragma once
#include "AI/PathFinding/NaviMesh.h"
#include "AI/PathFinding/Path.h"
#include "AI/PathFinding/PathFinding.h"

class Player;

class E_Golem : public IGameObject
{
public:
	E_Golem();
	void ShowGolem();
	void Move();
	void Rotation();
	void Attack();
	void AttackCoolCount();
	void RangedAttack();
	void CloseRangedAttack();
	void OnAnimationEvent(const wchar_t* clipName, const wchar_t* eventName);
	void MakeAttackCollision();
	void Damage();
	void StateManage();
	void AnimationState();
	void Update();
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
	ModelRender m_golemRender;

	//キャラクターコントローラー
	CharacterController m_golemController;

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
	int m_HP = 100;

	//基礎ダメージ量
	int m_damage;

	//近距離攻撃のクールタイム
	float m_closeRangedAttackCool = 0.0f;
	const float m_closeRangedAttackCoolLimit = 1.0f;
	bool m_closeRangedAttackCoolFlag = false;

	//遠距離攻撃のクールタイム
	float m_rangedAttackCool = 0.0f;
	const float m_rangedAttackCoolLimit = 5.0f;
	bool m_rangedAttackCoolFlag = false;

	//遠距離攻撃フラグ
	bool m_rangedAttackFlag;
	//近距離攻撃フラグ
	bool m_closeRangedAttackFlag;
	//未攻撃フラグ
	bool m_notAttack = true;

	//アニメーションの攻撃中フラグ
	bool m_attackForAnim;

	//当たり判定の半径
	const float CapsuleRadius = 45.0f;

	//当たり判定の高さ
	const float CapsuleHeight = 200.0f;

	//近距離判定
	const float m_nearDistance = 200.0f;
	//遠距離判定
	const float m_longDistance = 600.0f;

	//無敵フラグ
	bool m_invincibleFlag = false;
	//無敵時間
	float m_invincible = 0.0f;
	//キャラの無敵時間
	const float InvincibleTime = 0.1f;

	//ゴーレムの状態
	enum GolemState
	{
		CREATE,
		MOVE,
		ATTACK_CLOSE,
		ATTACK_RANGE,
		BROKEN
	};
	//状態を管理する変数
	int m_golemStateNumber = 0;

	enum GolemAnimation
	{
		GOLEM_MOVE,
		GOLEM_PUNCH,
		GOLEM_BREAK,
		GOLEM_ANIMNUM
	};
	AnimationClip m_golemAnimationClips[GOLEM_ANIMNUM];

	Bone* m_bone;
	Player* m_player;
};

