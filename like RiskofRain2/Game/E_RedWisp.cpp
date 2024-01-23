#include "stdafx.h"
#include "E_RedWisp.h"

#include "Player.h"

#include "graphics/effect/EffectEmitter.h"

E_RedWisp::E_RedWisp()
{
	m_redWispAnimationClips[REDWISP_ENTRY].Load("Assets/animData/enemy/wispB_entry.tka");
	m_redWispAnimationClips[REDWISP_ENTRY].SetLoopFlag(false);
	m_redWispAnimationClips[REDWISP_MOVE].Load("Assets/animData/enemy/wispB_move.tka");
	m_redWispAnimationClips[REDWISP_MOVE].SetLoopFlag(true);
	m_redWispAnimationClips[REDWISP_ATTACK].Load("Assets/animData/enemy/wispB_attack.tka");
	m_redWispAnimationClips[REDWISP_ATTACK].SetLoopFlag(false);
	m_redWispAnimationClips[REDWISP_BREAK].Load("Assets/animData/enemy/wispB_break.tka");
	m_redWispAnimationClips[REDWISP_BREAK].SetLoopFlag(false);

	m_player = FindGO<Player>("player");

	//EffectEngine::GetInstance()->ResistEffect(0, u"Assets/effect/fire.efk");
	//EffectEngine::GetInstance()->ResistEffect(0, u"Assets/effect/fire_b.efk");
}

void E_RedWisp::ShowRedWisp()
{
	m_pos.y += 100.0f;

	m_redWispController.Init(
		CapsuleRadius,
		CapsuleHeight,
		m_pos
	);

	m_redWispRender.Init("Assets/modelData/enemy/wispB.tkm", m_redWispAnimationClips, REDWISP_ANIMNUM);
	m_redWispRender.SetPosition(m_pos);


	m_redWispRender.PlayAnimation(REDWISP_ENTRY, 0.2f);
	m_redWispRender.SetAnimationSpeed(1.0f);
}

void E_RedWisp::Move()
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
	m_pos.y += 100.0f;

	m_redWispRender.SetPosition(m_pos);
	m_redWispRender.Update();
}

void E_RedWisp::Rotation()
{
	if (fabsf(m_moveSpeed.x) < 0.001f
		&& fabsf(m_moveSpeed.z) < 0.001f)
	{
		return;
	}

	float angle = atan2(-m_moveSpeed.x, m_moveSpeed.z);

	m_rotation.SetRotationY(-angle);

	m_redWispRender.SetRotation(m_rotation);

	m_forward = Vector3::AxisZ;
	m_rotation.Apply(m_forward);

}

void E_RedWisp::Attack()
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
		RangedAttack();
	}
}

void E_RedWisp::RangedAttack()
{
	m_attackCoolFlag = true;
	m_notAttack = true;
}

void E_RedWisp::AttackCoolCount()
{
	if (m_attackCoolFlag)
	{
		m_attackCool += g_gameTime->GetFrameDeltaTime();

		if (m_attackCool >= m_attackCoolLimit)
		{
			m_attackCool = 0.0f;
			m_attackCoolFlag = false;
		}
	}
}

void E_RedWisp::StateManage()
{
	if (m_HP <= 0)
	{
		m_redWispStateNumber = BROKEN;
	}
	else if (m_notAttack == false)
	{
		m_redWispStateNumber = ATTACK_RANGE;
	}
	else
	{
		m_redWispStateNumber = MOVE;
	}
}

void E_RedWisp::AnimationState()
{
	switch (m_redWispStateNumber)
	{
	case CREATE:
		m_redWispRender.PlayAnimation(REDWISP_ENTRY, 0.2f);
		m_redWispRender.SetAnimationSpeed(1.0f);
		break;
	case MOVE:
		m_redWispRender.PlayAnimation(REDWISP_MOVE, 0.2f);
		m_redWispRender.SetAnimationSpeed(1.0f);
		break;
	case ATTACK_RANGE:
		m_redWispRender.PlayAnimation(REDWISP_ATTACK, 0.2f);
		m_redWispRender.SetAnimationSpeed(1.0f);
		break;
	case BROKEN:
		m_redWispRender.PlayAnimation(REDWISP_BREAK, 0.2f);
		m_redWispRender.SetAnimationSpeed(1.0f);
		break;
	default:
		break;
	}
}

void E_RedWisp::Damage()
{
	//無敵時間のカウント
	if (m_invincibleFlag)
	{
		m_invincible += g_gameTime->GetFrameDeltaTime();

		if (m_invincible < InvincibleTime)
		{
			return;
		}
	}
	m_invincibleFlag = false;
	m_invincible = 0.0f;

	const auto& collisions = g_collisionObjectManager->FindCollisionObjects("player_bullet");

	for (auto collision : collisions)
	{
		if (collision->IsHit(m_redWispController))
		{
			//ダメージ
			int m_receiveDamage = m_player->m_playerDamage;

			//受けたダメージ分体力を減らす
			m_HP -= m_receiveDamage;

			m_invincibleFlag = true;
		}
	}
}

void E_RedWisp::Update()
{
	if (m_redWispStateNumber == BROKEN)
	{
		m_redWispRender.Update();

		if (m_redWispRender.PlayingAnimation() == false)
		{
			DeleteGO(this);
		}
		return;
	}

	Damage();

	/*EffectEmitter* effectEmitter = NewGO<EffectEmitter>(0);
	effectEmitter->Init(0);
	effectEmitter->SetScale({ 5.0f,5.0f,5.0f });
	effectEmitter->Play();*/

	if (m_redWispStateNumber == CREATE && m_redWispRender.PlayingAnimation())
	{
		m_redWispRender.Update();

		return;
	}

	/*Move();
	Rotation();*/
	Attack();
	AttackCoolCount();
	StateManage();
	AnimationState();
	m_redWispRender.Update();
}

void E_RedWisp::Render(RenderContext& rc)
{
	m_redWispRender.Draw(rc);
}