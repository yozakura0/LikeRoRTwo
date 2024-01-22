#include "stdafx.h"
#include "E_BlueWisp.h"
#include "Player.h"

#include "graphics/effect/EffectEmitter.h"

E_BlueWisp::E_BlueWisp()
{

	m_blueWispAnimationClips[BLUEWISP_ENTRY].Load("Assets/animData/enemy/wispA_entry.tka");
	m_blueWispAnimationClips[BLUEWISP_ENTRY].SetLoopFlag(false);
	m_blueWispAnimationClips[BLUEWISP_MOVE].Load("Assets/animData/enemy/wispA_move.tka");
	m_blueWispAnimationClips[BLUEWISP_MOVE].SetLoopFlag(true);
	m_blueWispAnimationClips[BLUEWISP_ATTACK].Load("Assets/animData/enemy/wispA_attack.tka");
	m_blueWispAnimationClips[BLUEWISP_ATTACK].SetLoopFlag(false);
	m_blueWispAnimationClips[BLUEWISP_BREAK].Load("Assets/animData/enemy/wispA_break.tka");
	m_blueWispAnimationClips[BLUEWISP_BREAK].SetLoopFlag(false);

	m_player = FindGO<Player>("player");

	m_blueWispRender.AddAnimationEvent
	([&](const wchar_t* clipName, const wchar_t* eventName)
		{
			OnAnimationEvent(clipName, eventName);
		}
	);

	//EffectEngine::GetInstance()->ResistEffect(0, u"Assets/effect/fire.efk");
	//EffectEngine::GetInstance()->ResistEffect(0, u"Assets/effect/fire_b.efk");
}

void E_BlueWisp::ShowBlueWisp()
{
	m_pos.y += 100.0f;

	m_blueWispController.Init(
		CapsuleRadius,
		CapsuleHeight,
		m_pos
	);

	m_blueWispRender.Init("Assets/modelData/enemy/wispA.tkm", m_blueWispAnimationClips, BLUEWISP_ANIMNUM);
	m_blueWispRender.SetPosition(m_pos);

	m_blueWispRender.PlayAnimation(BLUEWISP_ENTRY, 0.2f);
	m_blueWispRender.SetAnimationSpeed(1.0f);
}

void E_BlueWisp::Move()
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

	m_blueWispRender.SetPosition(m_pos);
	m_blueWispRender.Update();
}

void E_BlueWisp::Rotation()
{
	if (fabsf(m_moveSpeed.x) < 0.001f
		&& fabsf(m_moveSpeed.z) < 0.001f)
	{
		return;
	}

	float angle = atan2(-m_moveSpeed.x, m_moveSpeed.z);

	m_rotation.SetRotationY(-angle);

	m_blueWispRender.SetRotation(m_rotation);

	m_forward = Vector3::AxisZ;
	m_rotation.Apply(m_forward);

}

void E_BlueWisp::Attack()
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
		CloseRangedAttack();
	}
}

void E_BlueWisp::CloseRangedAttack()
{
	if (m_attackForAnim)
	{
		MakeAttackCollision();
	}
	if (m_blueWispRender.PlayingAnimation() == false)
	{
		m_notAttack = true;
		m_attackCoolFlag = true;
	}
}

void E_BlueWisp::AttackCoolCount()
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

void E_BlueWisp::OnAnimationEvent(const wchar_t* clipName, const wchar_t* eventName)
{
	//アニメーションのキーでフラグを変更
	if (wcscmp(eventName, L"attack_start") == 0)
	{
		m_attackForAnim = true;
	}
	else if (wcscmp(eventName, L"attack_end") == 0)
	{
		m_attackForAnim = false;
	}
}

void E_BlueWisp::MakeAttackCollision()
{
	if (m_attackForAnim)
	{
		auto collisionObject = NewGO<CollisionObject>(0);

		Vector3 collisionPosition = m_pos;
		collisionPosition.y += 50.0f;

		collisionObject->CreateSphere(collisionPosition, Quaternion::Identity, 75.0f);

		collisionObject->SetName("bluewisp_attack");

		/*if (collisionObject->IsHit(m_player->m_characterController))
		{
			m_attackForAnim = false;
		}*/
	}
}

void E_BlueWisp::StateManage()
{
	if (m_HP <= 0)
	{
		m_blueWispStateNumber = BROKEN;
	}
	else if (m_notAttack == false)
	{
		m_blueWispStateNumber = ATTACK_RANGE;
	}
	else
	{
		m_blueWispStateNumber = MOVE;
	}
}

void E_BlueWisp::AnimationState()
{
	switch (m_blueWispStateNumber)
	{
	case CREATE:
		m_blueWispRender.PlayAnimation(BLUEWISP_ENTRY, 0.2f);
		m_blueWispRender.SetAnimationSpeed(1.0f);
		break;
	case MOVE:
		m_blueWispRender.PlayAnimation(BLUEWISP_MOVE, 0.2f);
		m_blueWispRender.SetAnimationSpeed(1.0f);
		break;
	case ATTACK_RANGE:
		m_blueWispRender.PlayAnimation(BLUEWISP_ATTACK, 0.2f);
		m_blueWispRender.SetAnimationSpeed(1.0f);
		break;
	case BROKEN:
		m_blueWispRender.PlayAnimation(BLUEWISP_BREAK, 0.2f);
		m_blueWispRender.SetAnimationSpeed(1.0f);
		break;
	default:
		break;
	}
}

void E_BlueWisp::Damage()
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
		if (collision->IsHit(m_blueWispController))
		{
			//ダメージ
			int m_receiveDamage = m_player->m_playerDamage;

			//受けたダメージ分体力を減らす
			m_HP -= m_receiveDamage;

			m_invincibleFlag = true;
		}
	}
}

void E_BlueWisp::Update()
{
	if (m_blueWispStateNumber == BROKEN)
	{
		m_blueWispRender.Update();

		if (m_blueWispRender.PlayingAnimation() == false)
		{
			DeleteGO(this);
		}
		return;
	}

	Damage();

	if (m_blueWispStateNumber == CREATE && m_blueWispRender.PlayingAnimation())
	{
		m_blueWispRender.Update();

		return;
	}

	/*Move();
	Rotation();*/

	/*EffectEmitter* effectEmitter = NewGO<EffectEmitter>(0);
	effectEmitter->Init(0);
	effectEmitter->SetScale({ 5.0f,5.0f,5.0f });
	effectEmitter->Play();*/

	Attack();
	AttackCoolCount();
	StateManage();
	AnimationState();
	m_blueWispRender.Update();
}

void E_BlueWisp::Render(RenderContext& rc)
{
	m_blueWispRender.Draw(rc);
}