#include "stdafx.h"
#include "E_Imp.h"

#include "Player.h"

E_Imp::E_Imp()
{
	m_impAnimationClips[IMP_ENTRY].Load("Assets/animData/enemy/imp_entry.tka");
	m_impAnimationClips[IMP_ENTRY].SetLoopFlag(false);
	m_impAnimationClips[IMP_ATTACK].Load("Assets/animData/enemy/imp_attack.tka");
	m_impAnimationClips[IMP_ATTACK].SetLoopFlag(false);
	m_impAnimationClips[IMP_MOVE].Load("Assets/animData/enemy/imp_move.tka");
	m_impAnimationClips[IMP_MOVE].SetLoopFlag(true);
	m_impAnimationClips[IMP_BREAK].Load("Assets/animData/enemy/imp_break.tka");
	m_impAnimationClips[IMP_BREAK].SetLoopFlag(false);

	m_player = FindGO<Player>("player");

	m_impRender.AddAnimationEvent
	([&](const wchar_t* clipName, const wchar_t* eventName)
		{
			OnAnimationEvent(clipName, eventName);
		}
	);
}

void E_Imp::ShowImp()
{
	m_impController.Init(
		CapsuleRadius,
		CapsuleHeight,
		m_pos
	);

	m_impRender.Init("Assets/modelData/enemy/imp.tkm", m_impAnimationClips, IMP_ANIMNUM);
	m_impRender.SetPosition(m_pos);
}

void E_Imp::Move()
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

	m_impRender.SetPosition(m_pos);
	m_impRender.Update();
}

void E_Imp::Rotation()
{
	if (fabsf(m_moveSpeed.x) < 0.001f
		&& fabsf(m_moveSpeed.z) < 0.001f)
	{
		return;
	}

	float angle = atan2(-m_moveSpeed.x, m_moveSpeed.z);

	m_rotation.SetRotationY(-angle);

	m_impRender.SetRotation(m_rotation);

	m_forward = Vector3::AxisZ;
	m_rotation.Apply(m_forward);

}

void E_Imp::Attack()
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
		if (m_attackForAnim)
		{
			MakeAttackCollision();
		}
		if (m_impRender.PlayingAnimation() == false)
		{
			m_notAttack = true;
		}
	}
}

void E_Imp::MakeAttackCollision()
{
	if (m_attackForAnim)
	{
		auto collisionObject = NewGO<CollisionObject>(0);

		Vector3 collisionPosition = m_pos;
		collisionPosition.y += 50.0f;
		collisionPosition += m_forward * 60.0f;

		collisionObject->CreateSphere(collisionPosition, Quaternion::Identity, 45.0f);

		collisionObject->SetName("imp_attack");

		if (collisionObject->IsHit(m_player->m_characterController))
		{
			m_attackForAnim = false;
		}
	}
}

void E_Imp::ActionCoolCount()
{
	if (m_attackCoolFlag)
	{
		m_attackCool += g_gameTime->GetFrameDeltaTime();
		if (m_attackCool >= m_attackCoolLimit)
		{
			m_attackCool = 0;
			m_attackCoolFlag = false;
		}
	}
	if (m_brinkCharge < BrinkChargeLimit)
	{
		m_brinkCool += g_gameTime->GetFrameDeltaTime();
		if (m_brinkCool >= m_brinkCoolLimit)
		{
			m_brinkCool = 0;
			m_brinkCharge++;
		}
	}
}

void E_Imp::OnAnimationEvent(const wchar_t* clipName, const wchar_t* eventName)
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

void E_Imp::StateManage()
{
	if (m_HP <= 0)
	{
		m_impStateNumber = BROKEN;
	}
	else if (m_notAttack == false)
	{
		m_impStateNumber = ATTACK_CLOSE;
	}
	else
	{
		m_impStateNumber = MOVE;
	}
}

void E_Imp::AnimationState()
{
	switch (m_impStateNumber)
	{
	case CREATE:
		m_impRender.PlayAnimation(IMP_ENTRY, 0.2f);
		m_impRender.SetAnimationSpeed(1.0f);
		break;
	case MOVE:
		m_impRender.PlayAnimation(IMP_MOVE, 0.2f);
		m_impRender.SetAnimationSpeed(1.0f);
		break;
	case ATTACK_CLOSE:
		m_impRender.PlayAnimation(IMP_ATTACK, 0.2f);
		m_impRender.SetAnimationSpeed(1.0f);
		break;
	case BROKEN:
		m_impRender.PlayAnimation(IMP_BREAK, 0.2f);
		m_impRender.SetAnimationSpeed(1.0f);
		break;
	default:
		break;
	}
}

void E_Imp::Damage()
{
	{
		const auto& collisions = g_collisionObjectManager->FindCollisionObjects("player_bullet");

		for (auto collision : collisions)
		{
			if (collision->IsHit(m_impController))
			{
				//ダメージを取得
				int m_receiveDamage = m_player->m_playerDamage;

				//受けたダメージ分体力を減らす
				m_HP -= m_receiveDamage;
			}
		}
	}

	{
		const auto& collisions = g_collisionObjectManager->FindCollisionObjects("frostRelic_attack");

		for (auto collision : collisions)
		{
			if (collision->IsHit(m_impController))
			{
				//ダメージを取得
				int m_receiveDamage = m_player->m_playerDamage;

				//受けたダメージ分体力を減らす
				m_HP -= m_receiveDamage;
			}
		}
	}

	{
		const auto& collisions = g_collisionObjectManager->FindCollisionObjects("dynamite_attack");

		for (auto collision : collisions)
		{
			if (collision->IsHit(m_impController))
			{
				//ダメージを取得
				int m_receiveDamage = m_player->m_playerDamage;

				//受けたダメージ分体力を減らす
				m_HP -= m_receiveDamage;
			}
		}
	}

	{
		const auto& collisions = g_collisionObjectManager->FindCollisionObjects("gasoline_attack");

		for (auto collision : collisions)
		{
			if (collision->IsHit(m_impController))
			{
				//ダメージを取得
				int m_receiveDamage = m_player->m_playerDamage;

				//受けたダメージ分体力を減らす
				m_HP -= m_receiveDamage;
			}
		}
	}

	//HPが0以下なら死んでる
	if (m_HP <= 0)
	{
		m_dead = true;
		m_player->SetKillEnemy(m_pos);
	}
}

void E_Imp::Update()
{
	if (m_impStateNumber == BROKEN)
	{
		m_impRender.Update();
		
		if (m_impRender.PlayingAnimation() == false)
		{
			DeleteGO(this);
		}
		return;
	}

	/*Move();
	Rotation();*/

	Attack();
	ActionCoolCount();
	Damage();
	StateManage();
	AnimationState();
	m_impRender.Update();
}

void E_Imp::Render(RenderContext& rc)
{
	m_impRender.Draw(rc);
}