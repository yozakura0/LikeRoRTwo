#pragma once
#include "AI/PathFinding/NaviMesh.h"
#include "AI/PathFinding/Path.h"
#include "AI/PathFinding/PathFinding.h"

class Player;

class E_Imp : public IGameObject
{
public:
	E_Imp();
	void ShowImp();
	void Move();
	void Rotation();
	void Attack();
	void MakeAttackCollision();
	void ActionCoolCount();
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
	ModelRender m_impRender;

	//キャラクターコントローラー
	CharacterController m_impController;

	//死んだか
	bool m_dead = false;

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
	const float CapsuleHeight = 60.0f;

	//体力
	int m_HP = 65;

	//基礎ダメージ量
	int m_damage;

	//近距離攻撃フラグ
	bool m_attackFlag;
	//未攻撃フラグ
	bool m_notAttack = true;

	//アニメーションの攻撃中フラグ
	bool m_attackForAnim;

	//近距離攻撃のクールタイム
	float m_attackCool = 0.0f;
	const float m_attackCoolLimit = 1.0f;
	bool m_attackCoolFlag = false;

	//ブリンクのクールタイム
	float m_brinkCool = 0.0f;
	const float m_brinkCoolLimit = 5.0f;
	int m_brinkCharge = BrinkChargeLimit;
	const int BrinkChargeLimit = 3;

	//近距離判定
	const float m_nearDistance = 200.0f;

	//ゴーレムの状態
	enum ImpState
	{
		CREATE,
		MOVE,
		ATTACK_CLOSE,
		BROKEN
	};
	//状態を管理する変数
	int m_impStateNumber = 0;

	enum ImpAnimation
	{
		IMP_ENTRY,
		IMP_MOVE,
		IMP_ATTACK,
		IMP_BREAK,
		IMP_ANIMNUM
	};
	AnimationClip m_impAnimationClips[IMP_ANIMNUM];

	Player* m_player;
};

