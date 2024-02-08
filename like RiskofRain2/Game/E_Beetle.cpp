#include "stdafx.h"
#include "E_Beetle.h"
#include "Player.h"

E_Beetle::E_Beetle()
{
	m_beetleAnimationClips[BEETLE_ENTRY].Load("Assets/animData/enemy/beetle_entry.tka");
	m_beetleAnimationClips[BEETLE_ENTRY].SetLoopFlag(false);
	m_beetleAnimationClips[BEETLE_ATTACK].Load("Assets/animData/enemy/beetle_attack.tka");
	m_beetleAnimationClips[BEETLE_ATTACK].SetLoopFlag(false);
	m_beetleAnimationClips[BEETLE_MOVE].Load("Assets/animData/enemy/beetle_move.tka");
	m_beetleAnimationClips[BEETLE_MOVE].SetLoopFlag(true);
	m_beetleAnimationClips[BEETLE_BREAK].Load("Assets/animData/enemy/beetle_break.tka");
	m_beetleAnimationClips[BEETLE_BREAK].SetLoopFlag(false);
	
	m_player = FindGO<Player>("player");

	// ナビメッシュを構築。
	m_nvmMesh.Init("Assets/nvm/a.tkn");

	m_beetleRender.AddAnimationEvent
	([&](const wchar_t* clipName, const wchar_t* eventName)
		{
			OnAnimationEvent(clipName, eventName);
		}
	);
}

E_Beetle::~E_Beetle()
{
	if (m_beetleStateNumber == BROKEN)
	{
		m_player->AddMoney(m_dropMoney);
	}
}

void E_Beetle::ShowBeetle()
{
	m_beetleController.Init(
		CapsuleRadius,
		CapsuleHeight,
		m_pos
	);

	m_beetleRender.Init("Assets/modelData/enemy/beetle.tkm", m_beetleAnimationClips, BEETLE_ANIMNUM);
	m_beetleRender.SetPosition(m_pos);
	m_beetleRender.SetScale(Vector3(2.0f, 2.0f, 2.0f));

	SetStatus();
}

void E_Beetle::SetStatus()
{
	m_HP += AddHPtoLv * m_Level;
	m_damage += AddDamagetoLv * m_Level;
}

void E_Beetle::Move()
{
	m_pathFinding.Execute(
		m_path,
		m_nvmMesh,
		m_pos,
		m_player->m_position,
		PhysicsWorld::GetInstance(),
		50.0f,
		200.0f
	);

	m_pos = m_path.Move(
		m_pos,
		5.0f,
		m_isEnd
	);

	m_beetleController.SetPosition(m_pos);
	m_beetleController.Execute(m_moveSpeed, g_gameTime->GetFrameDeltaTime());
	m_beetleRender.SetPosition(m_pos);
	m_beetleRender.Update();
}

void E_Beetle::Rotation()
{
	if (fabsf(m_moveSpeed.x) < 0.001f
		&& fabsf(m_moveSpeed.z) < 0.001f)
	{
		return;
	}

	float angle = atan2(-m_moveSpeed.x, m_moveSpeed.z);

	m_rotation.SetRotationY(-angle);

	m_beetleRender.SetRotation(m_rotation);

	m_forward = Vector3::AxisZ;
	m_rotation.Apply(m_forward);

}

void E_Beetle::Attack()
{
	if (m_notAttack)
	{
		int x = pow(m_player->m_position.x - m_pos.x, 2.0f);
		int y = pow(m_player->m_position.y - m_pos.y, 2.0f);
		int z = pow(m_player->m_position.z - m_pos.z, 2.0f);
		float distance = sqrt(x + y + z);

		//プレイヤーとの距離が近い
		if (m_nearDistance > distance)
		{
			//近距離攻撃
			m_notAttack = false;
		}
	}
	else
	{
		if (m_attackForAnim)
		{
			MakeAttackCollision();
		}
		if (m_beetleRender.PlayingAnimation() == false)
		{
			m_notAttack = true;
		}
	}
}

void E_Beetle::MakeAttackCollision()
{
	if (m_attackForAnim)
	{
		auto collisionObject = NewGO<CollisionObject>(0);

		Vector3 collisionPosition = m_pos;
		collisionPosition.y += 50.0f;
		collisionPosition += m_forward * 50.0f;

		collisionObject->CreateSphere(collisionPosition, Quaternion::Identity, 40.0f);

		collisionObject->SetName("beetle_attack");

		if (collisionObject->IsHit(m_player->m_characterController))
		{
			m_attackForAnim = false;
		}
	}
}

void E_Beetle::StateManage()
{
	if (m_HP <= 0)
	{
		m_beetleStateNumber = BROKEN;
	}
	else if (m_notAttack == false)
	{
		m_beetleStateNumber = ATTACK_CLOSE;
	}
	else
	{
		m_beetleStateNumber = MOVE;
	}
}

void E_Beetle::AnimationState()
{
	switch (m_beetleStateNumber)
	{
	case CREATE:
		m_beetleRender.PlayAnimation(BEETLE_ENTRY, 0.2f);
		m_beetleRender.SetAnimationSpeed(1.0f);
		break;
	case MOVE:
		m_beetleRender.PlayAnimation(BEETLE_MOVE, 0.2f);
		m_beetleRender.SetAnimationSpeed(0.5f);
		break;
	case ATTACK_CLOSE:
		m_beetleRender.PlayAnimation(BEETLE_ATTACK, 0.2f);
		m_beetleRender.SetAnimationSpeed(0.5f);
		break;
	case BROKEN:
		m_beetleRender.PlayAnimation(BEETLE_BREAK, 0.2f);
		m_beetleRender.SetAnimationSpeed(1.0f);
		break;
	default:
		break;
	}
}

void E_Beetle::OnAnimationEvent(const wchar_t* clipName, const wchar_t* eventName)
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

void E_Beetle::Damage()
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

	{
		const auto& collisions = g_collisionObjectManager->FindCollisionObjects("player_bullet");

		for (auto collision : collisions)
		{
			if (collision->IsHit(m_beetleController))
			{
				//ダメージ取得
				int m_receiveDamage = m_player->m_playerDamage;

				//受けたダメージ分体力を減らす
				m_HP -= m_receiveDamage;

				m_invincibleFlag = true;
			}
		}
	}

	{
		const auto& collisions = g_collisionObjectManager->FindCollisionObjects("frostRelic_attack");

		for (auto collision : collisions)
		{
			if (collision->IsHit(m_beetleController))
			{
				//ダメージを取得
				int m_receiveDamage = m_player->m_playerDamage;

				//受けたダメージ分体力を減らす
				m_HP -= m_receiveDamage;

				m_invincibleFlag = true;
			}
		}
	}

	{
		const auto& collisions = g_collisionObjectManager->FindCollisionObjects("dynamite_attack");

		for (auto collision : collisions)
		{
			if (collision->IsHit(m_beetleController))
			{
				//ダメージを取得
				int m_receiveDamage = m_player->m_playerDamage;

				//受けたダメージ分体力を減らす
				m_HP -= m_receiveDamage;

				m_invincibleFlag = true;
			}
		}
	}

	{
		const auto& collisions = g_collisionObjectManager->FindCollisionObjects("gasoline_attack");

		for (auto collision : collisions)
		{
			if (collision->IsHit(m_beetleController))
			{
				//ダメージを取得
				int m_receiveDamage = m_player->m_playerDamage;

				//受けたダメージ分体力を減らす
				m_HP -= m_receiveDamage;

				m_invincibleFlag = true;
			}
		}
	}

	if (m_invincibleFlag)
	{
		EffectEmitter* effectEmitter = NewGO<EffectEmitter>(0);

		effectEmitter->Init(0);
		effectEmitter->SetScale({ 10.0f,10.0f,10.0f });
		effectEmitter->SetPosition({ m_pos.x,m_pos.y + 40.0f,m_pos.z });
		effectEmitter->Play();
	}
}

void E_Beetle::Update()
{
	if (m_beetleStateNumber == BROKEN)
	{
		m_beetleRender.Update();

		if (m_beetleRender.PlayingAnimation() == false)
		{
			EffectEmitter* effectEmitter = NewGO<EffectEmitter>(0);

			effectEmitter->Init(1);
			effectEmitter->SetScale({ 10.0f,10.0f,10.0f });
			effectEmitter->SetPosition({ m_pos.x,m_pos.y + 40.0f,m_pos.z });
			effectEmitter->Play();

			DeleteGO(this);
		}
		return;
	}
	
	Damage();

	if (m_beetleStateNumber == CREATE && m_beetleRender.PlayingAnimation())
	{
		m_beetleRender.Update();

		return;
	}

	Move();
	Rotation();

	Attack();
	StateManage();
	AnimationState();
	m_beetleRender.Update();
}

void E_Beetle::Render(RenderContext& rc)
{
	m_beetleRender.Draw(rc);
}