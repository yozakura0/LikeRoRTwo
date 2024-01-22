#include "stdafx.h"
#include "E_Wisp.h"

#include "Player.h"

#include "graphics/effect/EffectEmitter.h"

E_Wisp::E_Wisp()
{

	m_wispAnimationClips[WISP_ENTRY].Load("Assets/animData/enemy/wispA_entry.tka");
	m_wispAnimationClips[WISP_ENTRY].SetLoopFlag(false);
	m_wispAnimationClips[WISP_MOVE].Load("Assets/animData/enemy/wispA_move.tka");
	m_wispAnimationClips[WISP_MOVE].SetLoopFlag(true);
	m_wispAnimationClips[WISP_ATTACK].Load("Assets/animData/enemy/wispA_attack.tka");
	m_wispAnimationClips[WISP_ATTACK].SetLoopFlag(false);
	m_wispAnimationClips[WISP_BREAK].Load("Assets/animData/enemy/wispA_break.tka");
	m_wispAnimationClips[WISP_BREAK].SetLoopFlag(false);

	m_player = FindGO<Player>("player");

	//EffectEngine::GetInstance()->ResistEffect(0, u"Assets/effect/fire.efk");
	//EffectEngine::GetInstance()->ResistEffect(0, u"Assets/effect/fire_b.efk");
}

void E_Wisp::ShowWisp()
{
	m_wispController.Init(
		CapsuleRadius,
		CapsuleHeight,
		m_pos
	);

	m_wispRender.Init("Assets/modelData/enemy/wispA.tkm", m_wispAnimationClips, WISP_ANIMNUM);
	m_pos.y += 100.0f;
	m_wispRender.SetPosition(m_pos);
}

void E_Wisp::Move()
{
	bool isEnd;

	// パス検索
	m_pathFiding.Execute(
		m_path,							// 構築されたパスの格納先
		m_nvmMesh,						// ナビメッシュ
		m_pos,						// 開始座標
		m_player->m_position,			// 移動目標座標
		PhysicsWorld::GetInstance(),	// 物理エンジン	
		50.0f,							// AIエージェントの半径
		200.0f							// AIエージェントの高さ。
	);

	// パス上を移動する。
	m_pos = m_path.Move(
		m_pos,
		5.0f,
		isEnd
	);
	m_wispRender.SetPosition(m_pos);
	m_wispRender.Update();
}

void E_Wisp::Rotation()
{
	if (fabsf(m_moveSpeed.x) < 0.001f
		&& fabsf(m_moveSpeed.z) < 0.001f)
	{
		return;
	}

	float angle = atan2(-m_moveSpeed.x, m_moveSpeed.z);

	m_rotation.SetRotationY(-angle);

	m_wispRender.SetRotation(m_rotation);

	m_forward = Vector3::AxisZ;
	m_rotation.Apply(m_forward);

}

void E_Wisp::Attack()
{
	if (m_notAttack)
	{
		int x = pow(m_player->m_position.x - m_pos.x, 2.0f);
		int y = pow(m_player->m_position.y - m_pos.y, 2.0f);
		int z = pow(m_player->m_position.z - m_pos.z, 2.0f);
		float distance = sqrt(x + y + z);

		//プレイヤーとの距離が近い
		if (m_nearDistance > distance && m_attackCoolFlag == false)
		{
			//攻撃する
			m_notAttack = false;
		}
	}
	else
	{
		m_attackCoolFlag = true;
		m_notAttack = true;
	}
}

void E_Wisp::AttackCoolCount()
{
	if (m_attackCoolFlag)
	{
		m_attackCool += g_gameTime->GetFrameDeltaTime();

		if (m_attackCool >= m_attackCoolLimit)
		{
			m_attackCoolFlag = false;
		}
	}
}

void E_Wisp::StateManage()
{
	if (m_HP <= 0)
	{
		m_wispStateNumber = BROKEN;
	}
	else if (m_notAttack == false)
	{
		m_wispStateNumber = ATTACK_CLOSE;
	}
	else
	{
		m_wispStateNumber = MOVE;
	}
}

void E_Wisp::AnimationState()
{
	switch (m_wispStateNumber)
	{
	case CREATE:
		m_wispRender.PlayAnimation(WISP_ENTRY, 0.2f);
		m_wispRender.SetAnimationSpeed(1.0f);
		break;
	case MOVE:
		m_wispRender.PlayAnimation(WISP_MOVE, 0.2f);
		m_wispRender.SetAnimationSpeed(1.0f);
		break;
	case ATTACK_CLOSE:
		m_wispRender.PlayAnimation(WISP_ATTACK, 0.2f);
		m_wispRender.SetAnimationSpeed(1.0f);
		break;
	case BROKEN:
		m_wispRender.PlayAnimation(WISP_BREAK, 0.2f);
		m_wispRender.SetAnimationSpeed(1.0f);
		break;
	default:
		break;
	}
}

void E_Wisp::Damage()
{
	const auto& collisions = g_collisionObjectManager->FindCollisionObjects("player_bullet");

	for (auto collision : collisions)
	{
		if (collision->IsHit(m_wispController))
		{
			//ダメージ
			int m_receiveDamage = m_player->m_playerDamage;

			//受けたダメージ分体力を減らす
			m_HP -= m_receiveDamage;

		}
	}
}

void E_Wisp::Update()
{
	/*Move();
	Rotation();*/

	/*EffectEmitter* effectEmitter = NewGO<EffectEmitter>(0);
	effectEmitter->Init(0);
	effectEmitter->SetScale({ 5.0f,5.0f,5.0f });
	effectEmitter->Play();*/

	Attack();
	AttackCoolCount();
	Damage();
	StateManage();
	AnimationState();
	m_wispRender.Update();
}

void E_Wisp::Render(RenderContext& rc)
{
	m_wispRender.Draw(rc);
}